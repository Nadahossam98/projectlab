/********************************************************************************
** Form generated from reading UI file 'dashboard.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DASHBOARD_H
#define UI_DASHBOARD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Dashboard
{
public:
    QLabel *welcomeLabel;
    QGroupBox *groupBox;
    QLabel *appointmentsCountLabel;
    QLabel *patientsCountLabel;
    QLabel *billsCountLabel;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QPushButton *patientsButton;
    QPushButton *appointmentsButton;
    QPushButton *billingButton;
    QPushButton *logoutButton;

    void setupUi(QWidget *Dashboard)
    {
        if (Dashboard->objectName().isEmpty())
            Dashboard->setObjectName("Dashboard");
        Dashboard->resize(800, 600);
        welcomeLabel = new QLabel(Dashboard);
        welcomeLabel->setObjectName("welcomeLabel");
        welcomeLabel->setGeometry(QRect(220, 50, 541, 91));
        QFont font;
        font.setPointSize(26);
        welcomeLabel->setFont(font);
        groupBox = new QGroupBox(Dashboard);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(87, 154, 611, 219));
        appointmentsCountLabel = new QLabel(groupBox);
        appointmentsCountLabel->setObjectName("appointmentsCountLabel");
        appointmentsCountLabel->setGeometry(QRect(20, 60, 201, 31));
        patientsCountLabel = new QLabel(groupBox);
        patientsCountLabel->setObjectName("patientsCountLabel");
        patientsCountLabel->setGeometry(QRect(20, 160, 331, 41));
        billsCountLabel = new QLabel(groupBox);
        billsCountLabel->setObjectName("billsCountLabel");
        billsCountLabel->setGeometry(QRect(320, 60, 221, 41));
        label = new QLabel(groupBox);
        label->setObjectName("label");
        label->setGeometry(QRect(20, 20, 291, 41));
        QFont font1;
        font1.setPointSize(18);
        label->setFont(font1);
        label_2 = new QLabel(groupBox);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(320, 20, 241, 41));
        label_2->setFont(font1);
        label_3 = new QLabel(groupBox);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(20, 110, 231, 31));
        label_3->setFont(font1);
        patientsButton = new QPushButton(Dashboard);
        patientsButton->setObjectName("patientsButton");
        patientsButton->setGeometry(QRect(158, 420, 91, 51));
        QPalette palette;
        QBrush brush(QColor(49, 32, 240, 255));
        brush.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Button, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Button, brush);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Button, brush);
        patientsButton->setPalette(palette);
        appointmentsButton = new QPushButton(Dashboard);
        appointmentsButton->setObjectName("appointmentsButton");
        appointmentsButton->setGeometry(QRect(336, 420, 111, 51));
        QPalette palette1;
        palette1.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Button, brush);
        palette1.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Button, brush);
        palette1.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Button, brush);
        appointmentsButton->setPalette(palette1);
        billingButton = new QPushButton(Dashboard);
        billingButton->setObjectName("billingButton");
        billingButton->setGeometry(QRect(540, 420, 101, 51));
        QPalette palette2;
        palette2.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Button, brush);
        palette2.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Button, brush);
        palette2.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Button, brush);
        billingButton->setPalette(palette2);
        logoutButton = new QPushButton(Dashboard);
        logoutButton->setObjectName("logoutButton");
        logoutButton->setGeometry(QRect(20, 30, 91, 61));
        QPalette palette3;
        QBrush brush1(QColor(255, 0, 0, 255));
        brush1.setStyle(Qt::BrushStyle::SolidPattern);
        palette3.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Button, brush1);
        palette3.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Button, brush1);
        palette3.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Button, brush1);
        logoutButton->setPalette(palette3);

        retranslateUi(Dashboard);

        QMetaObject::connectSlotsByName(Dashboard);
    } // setupUi

    void retranslateUi(QWidget *Dashboard)
    {
        Dashboard->setWindowTitle(QCoreApplication::translate("Dashboard", "Form", nullptr));
        welcomeLabel->setText(QString());
        groupBox->setTitle(QString());
        appointmentsCountLabel->setText(QString());
        patientsCountLabel->setText(QString());
        billsCountLabel->setText(QString());
        label->setText(QCoreApplication::translate("Dashboard", "Appointments Count ", nullptr));
        label_2->setText(QCoreApplication::translate("Dashboard", "Bills Count", nullptr));
        label_3->setText(QCoreApplication::translate("Dashboard", "Patients Count", nullptr));
        patientsButton->setText(QCoreApplication::translate("Dashboard", "Patient ", nullptr));
        appointmentsButton->setText(QCoreApplication::translate("Dashboard", "Appointments ", nullptr));
        billingButton->setText(QCoreApplication::translate("Dashboard", "reports", nullptr));
        logoutButton->setText(QCoreApplication::translate("Dashboard", "Log out", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dashboard: public Ui_Dashboard {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DASHBOARD_H
