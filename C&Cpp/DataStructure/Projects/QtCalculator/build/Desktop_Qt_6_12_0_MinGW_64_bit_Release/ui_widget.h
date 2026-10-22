/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *displayPanel;
    QVBoxLayout *displayLayout;
    QLabel *label_expression;
    QLabel *label_display;
    QGridLayout *gridLayout;
    QPushButton *btnPercent;
    QPushButton *btnCE;
    QPushButton *btnC;
    QPushButton *btnBack;
    QPushButton *btnLParen;
    QPushButton *btnRParen;
    QPushButton *btnSqrt;
    QPushButton *btnDiv;
    QPushButton *btn7;
    QPushButton *btn8;
    QPushButton *btn9;
    QPushButton *btnMul;
    QPushButton *btn4;
    QPushButton *btn5;
    QPushButton *btn6;
    QPushButton *btnSub;
    QPushButton *btn1;
    QPushButton *btn2;
    QPushButton *btn3;
    QPushButton *btnAdd;
    QPushButton *btnNeg;
    QPushButton *btn0;
    QPushButton *btnDot;
    QPushButton *btnEqual;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName("Widget");
        Widget->resize(460, 620);
        Widget->setStyleSheet(QString::fromUtf8("QWidget { background-color: #f6f7fb; }\n"
"QWidget#displayPanel { background: white; border: 1px solid #c9ced8; border-radius: 8px; }\n"
"QLabel#label_expression { color: #7a808a; padding: 0px 12px; }\n"
"QLabel#label_display { color: #101114; padding: 0px 12px 12px 12px; }\n"
"QPushButton { background: white; color: #202124; border: 1px solid #d7dbe3; border-radius: 7px; font-size: 18px; min-height: 44px; }\n"
"QPushButton:hover { background: #eef4ff; }\n"
"QPushButton:pressed { background: #dce9ff; }\n"
"QPushButton#btnEqual { background: #3478f6; color: white; border: none; }\n"
"QPushButton#btnEqual:hover { background: #2168e9; }\n"
"QPushButton#btnAdd, QPushButton#btnSub, QPushButton#btnMul, QPushButton#btnDiv { color: #1769d1; font-weight: bold; }\n"
""));
        verticalLayout = new QVBoxLayout(Widget);
        verticalLayout->setSpacing(10);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(16, 16, 16, 16);
        displayPanel = new QWidget(Widget);
        displayPanel->setObjectName("displayPanel");
        displayPanel->setMinimumSize(QSize(0, 130));
        displayLayout = new QVBoxLayout(displayPanel);
        displayLayout->setObjectName("displayLayout");
        displayLayout->setContentsMargins(8, 8, 8, 8);
        label_expression = new QLabel(displayPanel);
        label_expression->setObjectName("label_expression");
        label_expression->setMinimumSize(QSize(0, 26));
        QFont font;
        font.setFamilies({QString::fromUtf8("Microsoft YaHei UI")});
        font.setPointSize(12);
        label_expression->setFont(font);
        label_expression->setAlignment(Qt::AlignRight|Qt::AlignVCenter);

        displayLayout->addWidget(label_expression);

        label_display = new QLabel(displayPanel);
        label_display->setObjectName("label_display");
        label_display->setMinimumSize(QSize(0, 68));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Microsoft YaHei UI")});
        font1.setPointSize(26);
        font1.setBold(true);
        label_display->setFont(font1);
        label_display->setAlignment(Qt::AlignRight|Qt::AlignVCenter);

        displayLayout->addWidget(label_display);


        verticalLayout->addWidget(displayPanel);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        gridLayout->setHorizontalSpacing(8);
        gridLayout->setVerticalSpacing(8);
        btnPercent = new QPushButton(Widget);
        btnPercent->setObjectName("btnPercent");

        gridLayout->addWidget(btnPercent, 0, 0, 1, 1);

        btnCE = new QPushButton(Widget);
        btnCE->setObjectName("btnCE");

        gridLayout->addWidget(btnCE, 0, 1, 1, 1);

        btnC = new QPushButton(Widget);
        btnC->setObjectName("btnC");

        gridLayout->addWidget(btnC, 0, 2, 1, 1);

        btnBack = new QPushButton(Widget);
        btnBack->setObjectName("btnBack");

        gridLayout->addWidget(btnBack, 0, 3, 1, 1);

        btnLParen = new QPushButton(Widget);
        btnLParen->setObjectName("btnLParen");

        gridLayout->addWidget(btnLParen, 1, 0, 1, 1);

        btnRParen = new QPushButton(Widget);
        btnRParen->setObjectName("btnRParen");

        gridLayout->addWidget(btnRParen, 1, 1, 1, 1);

        btnSqrt = new QPushButton(Widget);
        btnSqrt->setObjectName("btnSqrt");

        gridLayout->addWidget(btnSqrt, 1, 2, 1, 1);

        btnDiv = new QPushButton(Widget);
        btnDiv->setObjectName("btnDiv");

        gridLayout->addWidget(btnDiv, 1, 3, 1, 1);

        btn7 = new QPushButton(Widget);
        btn7->setObjectName("btn7");

        gridLayout->addWidget(btn7, 2, 0, 1, 1);

        btn8 = new QPushButton(Widget);
        btn8->setObjectName("btn8");

        gridLayout->addWidget(btn8, 2, 1, 1, 1);

        btn9 = new QPushButton(Widget);
        btn9->setObjectName("btn9");

        gridLayout->addWidget(btn9, 2, 2, 1, 1);

        btnMul = new QPushButton(Widget);
        btnMul->setObjectName("btnMul");

        gridLayout->addWidget(btnMul, 2, 3, 1, 1);

        btn4 = new QPushButton(Widget);
        btn4->setObjectName("btn4");

        gridLayout->addWidget(btn4, 3, 0, 1, 1);

        btn5 = new QPushButton(Widget);
        btn5->setObjectName("btn5");

        gridLayout->addWidget(btn5, 3, 1, 1, 1);

        btn6 = new QPushButton(Widget);
        btn6->setObjectName("btn6");

        gridLayout->addWidget(btn6, 3, 2, 1, 1);

        btnSub = new QPushButton(Widget);
        btnSub->setObjectName("btnSub");

        gridLayout->addWidget(btnSub, 3, 3, 1, 1);

        btn1 = new QPushButton(Widget);
        btn1->setObjectName("btn1");

        gridLayout->addWidget(btn1, 4, 0, 1, 1);

        btn2 = new QPushButton(Widget);
        btn2->setObjectName("btn2");

        gridLayout->addWidget(btn2, 4, 1, 1, 1);

        btn3 = new QPushButton(Widget);
        btn3->setObjectName("btn3");

        gridLayout->addWidget(btn3, 4, 2, 1, 1);

        btnAdd = new QPushButton(Widget);
        btnAdd->setObjectName("btnAdd");

        gridLayout->addWidget(btnAdd, 4, 3, 1, 1);

        btnNeg = new QPushButton(Widget);
        btnNeg->setObjectName("btnNeg");

        gridLayout->addWidget(btnNeg, 5, 0, 1, 1);

        btn0 = new QPushButton(Widget);
        btn0->setObjectName("btn0");

        gridLayout->addWidget(btn0, 5, 1, 1, 1);

        btnDot = new QPushButton(Widget);
        btnDot->setObjectName("btnDot");

        gridLayout->addWidget(btnDot, 5, 2, 1, 1);

        btnEqual = new QPushButton(Widget);
        btnEqual->setObjectName("btnEqual");

        gridLayout->addWidget(btnEqual, 5, 3, 1, 1);


        verticalLayout->addLayout(gridLayout);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Calculator", nullptr));
        label_expression->setText(QString());
        label_display->setText(QCoreApplication::translate("Widget", "0", nullptr));
        btnPercent->setText(QCoreApplication::translate("Widget", "%", nullptr));
        btnCE->setText(QCoreApplication::translate("Widget", "CE", nullptr));
        btnC->setText(QCoreApplication::translate("Widget", "C", nullptr));
        btnBack->setText(QCoreApplication::translate("Widget", "\342\214\253", nullptr));
        btnLParen->setText(QCoreApplication::translate("Widget", "(", nullptr));
        btnRParen->setText(QCoreApplication::translate("Widget", ")", nullptr));
        btnSqrt->setText(QCoreApplication::translate("Widget", "\342\210\232x", nullptr));
        btnDiv->setText(QCoreApplication::translate("Widget", "\303\267", nullptr));
        btn7->setText(QCoreApplication::translate("Widget", "7", nullptr));
        btn8->setText(QCoreApplication::translate("Widget", "8", nullptr));
        btn9->setText(QCoreApplication::translate("Widget", "9", nullptr));
        btnMul->setText(QCoreApplication::translate("Widget", "\303\227", nullptr));
        btn4->setText(QCoreApplication::translate("Widget", "4", nullptr));
        btn5->setText(QCoreApplication::translate("Widget", "5", nullptr));
        btn6->setText(QCoreApplication::translate("Widget", "6", nullptr));
        btnSub->setText(QCoreApplication::translate("Widget", "\342\210\222", nullptr));
        btn1->setText(QCoreApplication::translate("Widget", "1", nullptr));
        btn2->setText(QCoreApplication::translate("Widget", "2", nullptr));
        btn3->setText(QCoreApplication::translate("Widget", "3", nullptr));
        btnAdd->setText(QCoreApplication::translate("Widget", "+", nullptr));
        btnNeg->setText(QCoreApplication::translate("Widget", "+/-", nullptr));
        btn0->setText(QCoreApplication::translate("Widget", "0", nullptr));
        btnDot->setText(QCoreApplication::translate("Widget", ".", nullptr));
        btnEqual->setText(QCoreApplication::translate("Widget", "=", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
