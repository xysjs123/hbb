#include "widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Widget calculator;
    calculator.show();
    return app.exec();
}
