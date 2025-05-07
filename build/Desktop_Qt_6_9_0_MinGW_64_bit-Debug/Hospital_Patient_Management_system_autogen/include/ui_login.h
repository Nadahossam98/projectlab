/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Login
{
public:
    QLabel *label_3;
    QPushButton *loginButton;
    QWidget *widget;
    QGridLayout *gridLayout;
    QLineEdit *passwordInput;
    QLineEdit *usernameInput;
    QLabel *label;
    QLabel *label_2;

    void setupUi(QWidget *Login)
    {
        if (Login->objectName().isEmpty())
            Login->setObjectName("Login");
        Login->resize(800, 600);
        label_3 = new QLabel(Login);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(50, 60, 711, 53));
        QFont font;
        font.setPointSize(24);
        font.setBold(true);
        label_3->setFont(font);
        label_3->setAlignment(Qt::AlignmentFlag::AlignCenter);
        loginButton = new QPushButton(Login);
        loginButton->setObjectName("loginButton");
        loginButton->setGeometry(QRect(590, 480, 161, 81));
        loginButton->setMinimumSize(QSize(0, 50));
        loginButton->setStyleSheet(QString::fromUtf8("background-color: blue; color: white;"));
        widget = new QWidget(Login);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(150, 170, 521, 261));
        gridLayout = new QGridLayout(widget);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        passwordInput = new QLineEdit(widget);
        passwordInput->setObjectName("passwordInput");
        passwordInput->setMinimumSize(QSize(0, 40));
        passwordInput->setEchoMode(QLineEdit::EchoMode::Password);

        gridLayout->addWidget(passwordInput, 3, 0, 1, 1);

        usernameInput = new QLineEdit(widget);
        usernameInput->setObjectName("usernameInput");
        usernameInput->setMinimumSize(QSize(0, 40));

        gridLayout->addWidget(usernameInput, 1, 0, 1, 1);

        label = new QLabel(widget);
        label->setObjectName("label");
        QFont font1;
        font1.setPointSize(18);
        label->setFont(font1);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        label_2 = new QLabel(widget);
        label_2->setObjectName("label_2");
        label_2->setFont(font1);

        gridLayout->addWidget(label_2, 2, 0, 1, 1);


        retranslateUi(Login);

        QMetaObject::connectSlotsByName(Login);
    } // setupUi

    void retranslateUi(QWidget *Login)
    {
        Login->setWindowTitle(QCoreApplication::translate("Login", "Login", nullptr));
        label_3->setText(QCoreApplication::translate("Login", "Hospital Patient Management system", nullptr));
        loginButton->setText(QCoreApplication::translate("Login", "Sign in", nullptr));
        label->setText(QCoreApplication::translate("Login", "Username", nullptr));
        label_2->setText(QCoreApplication::translate("Login", "Password", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Login: public Ui_Login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
