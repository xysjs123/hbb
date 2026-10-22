#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;
    QString expression_;       // 计算器内部表达式，只使用 ASCII 运算符。
    QString completedExpression_;
    bool showingError_ = false;
    bool justCalculated_ = false;

    void updateDisplay();
    void showError(const QString &message);
    void appendDigit(const QString &digit);
    void appendDot();
    void appendOperator(QChar op);
    void appendParenthesis(QChar parenthesis);
    void deleteLast();
    void clearEntry();
    void toggleSign();
    void percent();
    void squareRoot();
    void calculate();
    void prepareForNewExpression();
    QString displayExpression(const QString &expression) const;

    bool evaluate(const QString &text, double *result, QString *error) const;
    int currentNumberStart() const;
    bool endsWithValue() const;
};

#endif // WIDGET_H
