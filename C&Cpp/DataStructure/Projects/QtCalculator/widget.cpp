#include "widget.h"
#include "ui_widget.h"       // 由 widget.ui 自动生成；不要手动创建此文件。

#include <QLabel>
#include <QPushButton>
#include <QStack>
#include <QVector>

#include <cmath>

namespace {

enum class TokenType { Number, Operator, Function, LeftParenthesis, RightParenthesis };

struct Token
{
    TokenType type;
    double number = 0.0;
    QChar symbol;
};

bool isBinaryOperator(QChar ch)
{
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

// 采用调度场（Shunting-yard）算法：把中缀表达式转为逆波兰式（RPN）。
// 一元负号用内部符号 '~' 表示，避免与二元减号混淆。
int precedence(QChar op)
{
    if (op == '~') return 3;
    if (op == '*' || op == '/') return 2;
    return 1;
}

bool isRightAssociative(QChar op)
{
    return op == '~';
}

bool toReversePolishNotation(const QString &input, QVector<Token> *output, QString *error)
{
    QStack<Token> operators;
    bool expectsValue = true;

    for (int pos = 0; pos < input.size();) {
        if (input.at(pos).isSpace()) { ++pos; continue; }

        if (input.mid(pos, 4) == QStringLiteral("sqrt")) {
            if (!expectsValue) { *error = QStringLiteral("第 %1 个字符附近缺少运算符").arg(pos + 1); return false; }
            int next = pos + 4;
            while (next < input.size() && input.at(next).isSpace()) ++next;
            if (next >= input.size() || input.at(next) != '(') { *error = QStringLiteral("sqrt 后缺少左括号"); return false; }
            operators.push({TokenType::Function, 0.0, QChar()});
            pos += 4;
            continue;
        }

        const QChar ch = input.at(pos);
        if (ch.isDigit() || ch == '.') {
            if (!expectsValue) { *error = QStringLiteral("第 %1 个字符附近缺少运算符").arg(pos + 1); return false; }
            const int start = pos;
            bool hasDigit = false;
            while (pos < input.size() && input.at(pos).isDigit()) { hasDigit = true; ++pos; }
            if (pos < input.size() && input.at(pos) == '.') {
                ++pos;
                while (pos < input.size() && input.at(pos).isDigit()) { hasDigit = true; ++pos; }
            }
            if (!hasDigit) { *error = QStringLiteral("数字格式错误"); return false; }
            bool ok = false;
            const double number = input.mid(start, pos - start).toDouble(&ok);
            if (!ok || !std::isfinite(number)) { *error = QStringLiteral("数字格式错误"); return false; }
            output->append({TokenType::Number, number, QChar()});
            expectsValue = false;
            continue;
        }

        if (ch == '(') {
            if (!expectsValue) { *error = QStringLiteral("第 %1 个字符附近缺少运算符").arg(pos + 1); return false; }
            operators.push({TokenType::LeftParenthesis, 0.0, ch});
            ++pos;
            continue;
        }

        if (ch == ')') {
            if (expectsValue) { *error = QStringLiteral("右括号前缺少数字或表达式"); return false; }
            while (!operators.isEmpty() && operators.top().type != TokenType::LeftParenthesis)
                output->append(operators.pop());
            if (operators.isEmpty()) { *error = QStringLiteral("缺少左括号 ("); return false; }
            operators.pop();
            if (!operators.isEmpty() && operators.top().type == TokenType::Function)
                output->append(operators.pop());
            ++pos;
            expectsValue = false;
            continue;
        }

        if (isBinaryOperator(ch)) {
            QChar op = ch;
            if (expectsValue) {
                if (ch == '+') { ++pos; continue; }
                if (ch == '-') op = '~';
                else { *error = QStringLiteral("运算符后缺少数字或括号"); return false; }
            }
            while (!operators.isEmpty() && operators.top().type == TokenType::Operator) {
                const QChar top = operators.top().symbol;
                if (precedence(top) > precedence(op)
                    || (precedence(top) == precedence(op) && !isRightAssociative(op)))
                    output->append(operators.pop());
                else
                    break;
            }
            operators.push({TokenType::Operator, 0.0, op});
            ++pos;
            expectsValue = true;
            continue;
        }

        *error = QStringLiteral("第 %1 个字符附近有错误").arg(pos + 1);
        return false;
    }

    if (expectsValue) { *error = QStringLiteral("运算符后缺少数字或括号"); return false; }
    while (!operators.isEmpty()) {
        const Token token = operators.pop();
        if (token.type == TokenType::LeftParenthesis) { *error = QStringLiteral("缺少右括号 )"); return false; }
        if (token.type == TokenType::Function) { *error = QStringLiteral("sqrt 后缺少左括号"); return false; }
        output->append(token);
    }
    return true;
}

bool evaluateReversePolishNotation(const QVector<Token> &tokens, double *result, QString *error)
{
    QStack<double> values;
    for (const Token &token : tokens) {
        if (token.type == TokenType::Number) {
            values.push(token.number);
        } else if (token.type == TokenType::Function) {
            if (values.isEmpty()) { *error = QStringLiteral("sqrt 缺少参数"); return false; }
            const double value = values.pop();
            if (value < 0.0) { *error = QStringLiteral("负数不能开平方"); return false; }
            values.push(std::sqrt(value));
        } else if (token.type == TokenType::Operator) {
            if (token.symbol == '~') {
                if (values.isEmpty()) { *error = QStringLiteral("负号后缺少数字或括号"); return false; }
                values.push(-values.pop());
                continue;
            }
            if (values.size() < 2) { *error = QStringLiteral("运算符后缺少数字或括号"); return false; }
            const double right = values.pop();
            const double left = values.pop();
            double value = 0.0;
            if (token.symbol == '+') value = left + right;
            else if (token.symbol == '-') value = left - right;
            else if (token.symbol == '*') value = left * right;
            else {
                if (std::abs(right) < 1e-15) { *error = QStringLiteral("除数不能为零"); return false; }
                value = left / right;
            }
            if (!std::isfinite(value)) { *error = QStringLiteral("计算结果超出范围"); return false; }
            values.push(value);
        }
    }
    if (values.size() != 1) { *error = QStringLiteral("表达式格式错误"); return false; }
    *result = values.pop();
    return true;
}

} // namespace

Widget::Widget(QWidget *parent)
    : QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->label_display->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    ui->label_expression->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    updateDisplay();

    const auto digit = [this](const QString &value) { appendDigit(value); };
    connect(ui->btn0, &QPushButton::clicked, this, [=] { digit("0"); });
    connect(ui->btn1, &QPushButton::clicked, this, [=] { digit("1"); });
    connect(ui->btn2, &QPushButton::clicked, this, [=] { digit("2"); });
    connect(ui->btn3, &QPushButton::clicked, this, [=] { digit("3"); });
    connect(ui->btn4, &QPushButton::clicked, this, [=] { digit("4"); });
    connect(ui->btn5, &QPushButton::clicked, this, [=] { digit("5"); });
    connect(ui->btn6, &QPushButton::clicked, this, [=] { digit("6"); });
    connect(ui->btn7, &QPushButton::clicked, this, [=] { digit("7"); });
    connect(ui->btn8, &QPushButton::clicked, this, [=] { digit("8"); });
    connect(ui->btn9, &QPushButton::clicked, this, [=] { digit("9"); });

    connect(ui->btnDot,     &QPushButton::clicked, this, [this] { appendDot(); });
    connect(ui->btnAdd,     &QPushButton::clicked, this, [this] { appendOperator('+'); });
    connect(ui->btnSub,     &QPushButton::clicked, this, [this] { appendOperator('-'); });
    connect(ui->btnMul,     &QPushButton::clicked, this, [this] { appendOperator('*'); });
    connect(ui->btnDiv,     &QPushButton::clicked, this, [this] { appendOperator('/'); });
    // 截图中此对象曾被 Designer 自动命名为 btnLParen_2；优先采用实验
    // 要求的 btnLParen，同时兼容尚未重命名的界面，避免因成员名不同而无法编译。
    QPushButton *lParenButton = findChild<QPushButton *>(QStringLiteral("btnLParen"));
    if (!lParenButton)
        lParenButton = findChild<QPushButton *>(QStringLiteral("btnLParen_2"));
    if (lParenButton)
        connect(lParenButton, &QPushButton::clicked, this, [this] { appendParenthesis('('); });
    connect(ui->btnRParen,  &QPushButton::clicked, this, [this] { appendParenthesis(')'); });
    connect(ui->btnEqual,   &QPushButton::clicked, this, [this] { calculate(); });
    connect(ui->btnC,       &QPushButton::clicked, this, [this] {
        expression_.clear(); completedExpression_.clear(); showingError_ = false; justCalculated_ = false; updateDisplay();
    });
    connect(ui->btnCE,      &QPushButton::clicked, this, [this] { clearEntry(); });
    connect(ui->btnBack,    &QPushButton::clicked, this, [this] { deleteLast(); });
    connect(ui->btnNeg,     &QPushButton::clicked, this, [this] { toggleSign(); });
    connect(ui->btnPercent, &QPushButton::clicked, this, [this] { percent(); });
    connect(ui->btnSqrt,    &QPushButton::clicked, this, [this] { squareRoot(); });
}

Widget::~Widget() { delete ui; }

void Widget::updateDisplay()
{
    if (showingError_)
        return;

    if (justCalculated_) {
        ui->label_expression->setText(displayExpression(completedExpression_) + QStringLiteral(" ="));
        ui->label_display->setText(displayExpression(expression_));
    } else {
        // 输入阶段只显示一个大号黑色数值/算式；按 = 后才拆成公式与答案两行。
        ui->label_expression->clear();
        ui->label_display->setText(expression_.isEmpty()
                                      ? QStringLiteral("0")
                                      : displayExpression(expression_));
    }
}

void Widget::showError(const QString &message)
{
    ui->label_expression->setText(displayExpression(expression_));
    ui->label_display->setText(QStringLiteral("错误：") + message);
    showingError_ = true;
}

QString Widget::displayExpression(const QString &expression) const
{
    QString shown = expression;
    shown.replace(QStringLiteral("sqrt"), QStringLiteral("√"));
    shown.replace('*', QChar(0x00d7));
    shown.replace('/', QChar(0x00f7));
    return shown;
}

void Widget::prepareForNewExpression()
{
    if (showingError_ || justCalculated_) {
        expression_.clear();
        completedExpression_.clear();
        showingError_ = false;
        justCalculated_ = false;
    }
}

bool Widget::endsWithValue() const
{
    return !expression_.isEmpty() && (expression_.back().isDigit() || expression_.back() == ')');
}

int Widget::currentNumberStart() const
{
    int i = expression_.size();
    while (i > 0 && (expression_.at(i - 1).isDigit() || expression_.at(i - 1) == '.')) --i;
    return i;
}

void Widget::appendDigit(const QString &digit)
{
    prepareForNewExpression();
    if (endsWithValue() && expression_.back() == ')') expression_ += '*';
    expression_ += digit;
    updateDisplay();
}

void Widget::appendDot()
{
    prepareForNewExpression();
    if (endsWithValue() && expression_.back() == ')') expression_ += "*0.";
    else {
        const int start = currentNumberStart();
        if (expression_.mid(start).contains('.')) return;
        if (start == expression_.size()) expression_ += '0';
        expression_ += '.';
    }
    updateDisplay();
}

void Widget::appendOperator(QChar op)
{
    if (showingError_ || expression_.isEmpty()) return;
    if (justCalculated_) { justCalculated_ = false; completedExpression_.clear(); }
    if (isBinaryOperator(expression_.back())) expression_.back() = op; // 避免 ++、+- 等连续运算符。
    else if (expression_.back() == '(') return;
    else expression_ += op;
    updateDisplay();
}

void Widget::appendParenthesis(QChar parenthesis)
{
    if (parenthesis == '(')
        prepareForNewExpression();
    else if (showingError_ || justCalculated_)
        return;
    if (parenthesis == '(') {
        if (endsWithValue()) expression_ += '*';
        expression_ += '(';
    } else {
        int balance = 0;
        for (const QChar ch : expression_) { if (ch == '(') ++balance; else if (ch == ')') --balance; }
        if (balance > 0 && endsWithValue()) expression_ += ')';
        else return;
    }
    updateDisplay();
}

void Widget::deleteLast()
{
    if (showingError_) { expression_.clear(); showingError_ = false; }
    else {
        if (justCalculated_) { justCalculated_ = false; completedExpression_.clear(); }
        if (!expression_.isEmpty()) expression_.chop(1);
    }
    updateDisplay();
}

void Widget::clearEntry()
{
    if (showingError_ || justCalculated_) {
        expression_.clear(); completedExpression_.clear(); showingError_ = false; justCalculated_ = false; updateDisplay(); return;
    }
    const int start = currentNumberStart();
    if (start < expression_.size()) expression_.remove(start, expression_.size() - start);
    updateDisplay();
}

void Widget::toggleSign()
{
    if (showingError_) return;
    if (justCalculated_) { justCalculated_ = false; completedExpression_.clear(); }
    const int start = currentNumberStart();
    if (start == expression_.size()) return; // 尚未输入当前数字
    const bool canBeUnary = start == 0 || expression_.at(start - 1) == '(' || isBinaryOperator(expression_.at(start - 1));
    const bool previousMinusIsUnary = start > 0 && expression_.at(start - 1) == '-'
            && (start - 1 == 0 || expression_.at(start - 2) == '('
                || isBinaryOperator(expression_.at(start - 2)));
    if (canBeUnary && previousMinusIsUnary) expression_.remove(start - 1, 1);
    else expression_.insert(start, '-');
    updateDisplay();
}

void Widget::percent()
{
    if (showingError_) return;
    if (justCalculated_) { justCalculated_ = false; completedExpression_.clear(); }
    const int start = currentNumberStart();
    if (start == expression_.size()) return;
    bool ok = false;
    const double number = expression_.mid(start).toDouble(&ok);
    if (!ok) { showError(QStringLiteral("百分号前需要数字")); return; }
    expression_.replace(start, expression_.size() - start, QString::number(number / 100.0, 'g', 15));
    updateDisplay();
}

void Widget::squareRoot()
{
    if (showingError_) return;
    if (justCalculated_) { justCalculated_ = false; completedExpression_.clear(); }
    const int start = currentNumberStart();
    if (start == expression_.size()) { showError(QStringLiteral("请先输入要开方的数字")); return; }
    expression_.insert(start, QStringLiteral("sqrt("));
    expression_ += ')';
    updateDisplay();
}

void Widget::calculate()
{
    if (showingError_ || expression_.isEmpty()) return;
    if (justCalculated_) return;

    const QString sourceExpression = expression_;
    double result = 0.0;
    QString error;
    if (!evaluate(expression_, &result, &error)) { showError(error); return; }
    expression_ = QString::number(result, 'g', 15);
    completedExpression_ = sourceExpression;
    showingError_ = false;
    justCalculated_ = true;
    updateDisplay();
}

bool Widget::evaluate(const QString &text, double *result, QString *error) const
{
    QVector<Token> reversePolishNotation;
    if (!toReversePolishNotation(text, &reversePolishNotation, error))
        return false;
    return evaluateReversePolishNotation(reversePolishNotation, result, error);
}
