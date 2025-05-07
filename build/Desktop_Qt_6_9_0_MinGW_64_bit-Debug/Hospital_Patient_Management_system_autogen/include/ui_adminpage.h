/********************************************************************************
** Form generated from reading UI file 'adminpage.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADMINPAGE_H
#define UI_ADMINPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AdminPage
{
public:
    QWidget *centralwidget;
    QListWidget *userListWidget;
    QPushButton *logoutButton;
    QLabel *label_3;
    QWidget *widget;
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *usernameInput;
    QLabel *label_2;
    QLineEdit *passwordInput;
    QWidget *widget1;
    QGridLayout *gridLayout_2;
    QComboBox *roleComboBox;
    QPushButton *listUsersButton;
    QPushButton *addUserButton;
    QPushButton *deleteUserButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *AdminPage)
    {
        if (AdminPage->objectName().isEmpty())
            AdminPage->setObjectName("AdminPage");
        AdminPage->resize(800, 600);
        centralwidget = new QWidget(AdminPage);
        centralwidget->setObjectName("centralwidget");
        userListWidget = new QListWidget(centralwidget);
        userListWidget->setObjectName("userListWidget");
        userListWidget->setGeometry(QRect(340, 110, 421, 401));
        logoutButton = new QPushButton(centralwidget);
        logoutButton->setObjectName("logoutButton");
        logoutButton->setGeometry(QRect(30, 10, 81, 61));
        QPalette palette;
        QBrush brush(QColor(255, 0, 0, 255));
        brush.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Button, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Button, brush);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Button, brush);
        logoutButton->setPalette(palette);
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(300, 20, 181, 61));
        QFont font;
        font.setPointSize(28);
        font.setBold(true);
        font.setItalic(false);
        label_3->setFont(font);
        widget = new QWidget(centralwidget);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(41, 112, 291, 251));
        gridLayout = new QGridLayout(widget);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(widget);
        label->setObjectName("label");
        QFont font1;
        font1.setPointSize(16);
        label->setFont(font1);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        usernameInput = new QLineEdit(widget);
        usernameInput->setObjectName("usernameInput");
        usernameInput->setFont(font1);

        gridLayout->addWidget(usernameInput, 1, 0, 1, 1);

        label_2 = new QLabel(widget);
        label_2->setObjectName("label_2");
        label_2->setFont(font1);

        gridLayout->addWidget(label_2, 2, 0, 1, 1);

        passwordInput = new QLineEdit(widget);
        passwordInput->setObjectName("passwordInput");
        passwordInput->setFont(font1);

        gridLayout->addWidget(passwordInput, 3, 0, 1, 1);

        widget1 = new QWidget(widget);
        widget1->setObjectName("widget1");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(100);
        sizePolicy.setHeightForWidth(widget1->sizePolicy().hasHeightForWidth());
        widget1->setSizePolicy(sizePolicy);
        gridLayout_2 = new QGridLayout(widget1);
        gridLayout_2->setObjectName("gridLayout_2");
        roleComboBox = new QComboBox(widget1);
        roleComboBox->setObjectName("roleComboBox");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(1);
        sizePolicy1.setHeightForWidth(roleComboBox->sizePolicy().hasHeightForWidth());
        roleComboBox->setSizePolicy(sizePolicy1);

        gridLayout_2->addWidget(roleComboBox, 0, 0, 1, 1);

        listUsersButton = new QPushButton(widget1);
        listUsersButton->setObjectName("listUsersButton");
        listUsersButton->setMaximumSize(QSize(16777215, 16777215));
        QPalette palette1;
        QBrush brush1(QColor(0, 85, 255, 255));
        brush1.setStyle(Qt::BrushStyle::SolidPattern);
        palette1.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Button, brush1);
        palette1.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Button, brush1);
        palette1.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Button, brush1);
        listUsersButton->setPalette(palette1);

        gridLayout_2->addWidget(listUsersButton, 1, 0, 1, 1);

        addUserButton = new QPushButton(widget1);
        addUserButton->setObjectName("addUserButton");
        QPalette palette2;
        QBrush brush2(QColor(27, 170, 1, 255));
        brush2.setStyle(Qt::BrushStyle::SolidPattern);
        palette2.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Button, brush2);
        palette2.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Button, brush2);
        palette2.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Button, brush2);
        addUserButton->setPalette(palette2);

        gridLayout_2->addWidget(addUserButton, 0, 1, 1, 1);

        deleteUserButton = new QPushButton(widget1);
        deleteUserButton->setObjectName("deleteUserButton");
        QPalette palette3;
        palette3.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Button, brush);
        palette3.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Button, brush);
        palette3.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Button, brush);
        deleteUserButton->setPalette(palette3);

        gridLayout_2->addWidget(deleteUserButton, 1, 1, 1, 1);


        gridLayout->addWidget(widget1, 4, 0, 1, 1);

        AdminPage->setCentralWidget(centralwidget);
        menubar = new QMenuBar(AdminPage);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 25));
        AdminPage->setMenuBar(menubar);
        statusbar = new QStatusBar(AdminPage);
        statusbar->setObjectName("statusbar");
        AdminPage->setStatusBar(statusbar);

        retranslateUi(AdminPage);

        QMetaObject::connectSlotsByName(AdminPage);
    } // setupUi

    void retranslateUi(QMainWindow *AdminPage)
    {
        AdminPage->setWindowTitle(QCoreApplication::translate("AdminPage", "MainWindow", nullptr));
        logoutButton->setText(QCoreApplication::translate("AdminPage", "Logout", nullptr));
        label_3->setText(QCoreApplication::translate("AdminPage", "Admin", nullptr));
        label->setText(QCoreApplication::translate("AdminPage", "Username", nullptr));
        label_2->setText(QCoreApplication::translate("AdminPage", "Password", nullptr));
        listUsersButton->setText(QCoreApplication::translate("AdminPage", "List Users", nullptr));
        addUserButton->setText(QCoreApplication::translate("AdminPage", "Add User", nullptr));
        deleteUserButton->setText(QCoreApplication::translate("AdminPage", "Delete User", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AdminPage: public Ui_AdminPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADMINPAGE_H
