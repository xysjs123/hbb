#include "widget.h"
#include "ui_widget.h"       // 由 widget.ui 自动生成；不要手动创建此文件。

#include <QLabel>
#include <QPushButton>

#include <cmath>

namespace {

// 递归下降解析器：expression -> term -> unary -> primary。
// 这样天然满足 *、/ 高于 +、-，且括号可递归嵌套。
class ExpressionParser
{
public:
    explicit ExpressionParser(const QString &input) : input_(input) {}

    bool parse(double *result)
    {
        skipSpaces();
        if (atEnd())
            return fail(QStringLiteral("请输入表达式"));

        double value = 0.0;
        if (!parseExpression(&value))
            return false;
        skipSpaces();
        if (!atEnd())
            return fail(QStringLiteral("第 %1 个字符附近有错误").arg(pos_ + 1));
        if (!std::isfinite(value))
            return fail(QStringLiteral("计算结果超出范围"));

        *result = value;
        return true;
    }

    QString error() const { return error_; }

private:
    const QString &input_;
    int pos_ = 0;
    QString error_;

    bool atEnd() const { return pos_ >= input_.size(); }
    QChar peek() const { return atEnd() ? QChar() : input_.at(pos_); }
    void skipSpaces() { while (!atEnd() && peek().isSpace()) ++pos_; }
    bool fail(const QString &message) { error_ = message; return false; }

    bool parseExpression(double *value)
    {
        if (!parseTerm(value)) return false;
        while (true) {
            skipSpaces();
            const QChar op = peek();
            if (op != '+' && op != '-') break;
            ++pos_;
            double right = 0.0;
            if (!parseTerm(&right)) return fail(QStringLiteral("运算符后缺少数字或括号"));
            *value = op == '+' ? *value + right : *value - right;
            if (!std::isfinite(*value)) return fail(QStringLiteral("计算结果超出范围"));
        }
        return true;
    }

    bool parseTerm(double *value)
    {
        if (!parseUnary(value)) return false;
        while (true) {
            skipSpaces();
            const QChar op = peek();
            if (op != '*' && op != '/') break;
            ++pos_;
            double right = 0.0;
            if (!parseUnary(&right)) return fail(QStringLiteral("运算符后缺少数字或括号"));
            if (op == '/') {
                if (std::abs(right) < 1e-15) return fail(QStringLiteral("除数不能为零"));
                *value /= right;
            } else {
                *value *= right;
            }
            if (!std::isfinite(*value)) return fail(QStringLiteral("计算结果超出范围"));
        }
        return true;
    }

    bool parseUnary(double *value)
    {
        skipSpaces();
        if (peek() == '+') { ++pos_; return parseUnary(value); }
        if (peek() == '-') { ++pos_; if (!parseUnary(value)) return false; *value = -*value; return true; }
        return parsePrimary(value);
    }

    bool parsePrimary(double *value)
    {
        skipSpaces();
        if (peek() == '(') {
            ++pos_;
            if (!parseExpression(value)) return false;
            skipSpaces();
            if (peek() != ')') return fail(QStringLiteral("缺少右括号 )"));
            ++pos_;
            return true;
        }

        // sqrt(x) 仅由“√x”按钮生成，但解析器也会校验其语法。
        if (input_.mid(pos_, 4) == QStringLiteral("sqrt")) {
            pos_ += 4;
            skipSpaces();
            if (peek() != '(') return fail(QStringLiteral("sqrt 后缺少左括号"));
            ++pos_;
            if (!parseExpression(value)) return false;
            skipSpaces();
            if (peek() != ')') return fail(QStringLiteral("sqrt 缺少右括号 )"));
            ++pos_;
            if (*value < 0.0) return fail(QStringLiteral("负数不能开平方"));
            *value = std::sqrt(*value);
            return true;
        }

        const int start = pos_;
        bool hasDigit = false;
        while (!atEnd() && peek().isDigit()) { hasDigit = true; ++pos_; }
        if (!atEnd() && peek() == '.') {
            ++pos_;
            while (!atEnd() && peek().isDigit()) { hasDigit = true; ++pos_; }
        }
        if (!hasDigit) return fail(QStringLiteral("需要数字或左括号"));

        bool ok = false;
        *value = input_.mid(start, pos_ - start).toDouble(&ok);
        return ok ? true : fail(QStringLiteral("数字格式错误"));
    }
};

bool isBinaryOperator(QChar ch)
{
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
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
    ExpressionParser parser(text);
    if (parser.parse(result)) return true;
    *error = parser.error();
    return false;
}
