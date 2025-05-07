/********************************************************************************
** Form generated from reading UI file 'appointmentform.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_APPOINTMENTFORM_H
#define UI_APPOINTMENTFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_appointmentform
{
public:
    QLabel *label;
    QTextEdit *reasonTextEdit;
    QPushButton *saveButton;
    QPushButton *cancelButton;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QComboBox *doctorComboBox;
    QComboBox *patientComboBox;
    QDateEdit *dateEdit;
    QComboBox *timeSlotComboBox;

    void setupUi(QWidget *appointmentform)
    {
        if (appointmentform->objectName().isEmpty())
            appointmentform->setObjectName("appointmentform");
        appointmentform->resize(800, 600);
        label = new QLabel(appointmentform);
        label->setObjectName("label");
        label->setGeometry(QRect(250, 10, 331, 81));
        QFont font;
        font.setPointSize(18);
        font.setBold(true);
        label->setFont(font);
        reasonTextEdit = new QTextEdit(appointmentform);
        reasonTextEdit->setObjectName("reasonTextEdit");
        reasonTextEdit->setGeometry(QRect(20, 170, 751, 351));
        saveButton = new QPushButton(appointmentform);
        saveButton->setObjectName("saveButton");
        saveButton->setGeometry(QRect(460, 530, 161, 51));
        QPalette palette;
        QBrush brush(QColor(27, 170, 1, 255));
        brush.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Button, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Button, brush);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Button, brush);
        saveButton->setPalette(palette);
        QFont font1;
        font1.setBold(true);
        saveButton->setFont(font1);
        cancelButton = new QPushButton(appointmentform);
        cancelButton->setObjectName("cancelButton");
        cancelButton->setGeometry(QRect(640, 530, 131, 51));
        QPalette palette1;
        QBrush brush1(QColor(255, 0, 0, 255));
        brush1.setStyle(Qt::BrushStyle::SolidPattern);
        palette1.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Button, brush1);
        palette1.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Button, brush1);
        palette1.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Button, brush1);
        cancelButton->setPalette(palette1);
        layoutWidget = new QWidget(appointmentform);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(20, 90, 751, 67));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        doctorComboBox = new QComboBox(layoutWidget);
        doctorComboBox->setObjectName("doctorComboBox");

        gridLayout->addWidget(doctorComboBox, 0, 1, 1, 1);

        patientComboBox = new QComboBox(layoutWidget);
        patientComboBox->setObjectName("patientComboBox");

        gridLayout->addWidget(patientComboBox, 0, 0, 1, 1);

        dateEdit = new QDateEdit(layoutWidget);
        dateEdit->setObjectName("dateEdit");
        dateEdit->setWrapping(false);

        gridLayout->addWidget(dateEdit, 0, 2, 1, 1);

        timeSlotComboBox = new QComboBox(layoutWidget);
        timeSlotComboBox->setObjectName("timeSlotComboBox");

        gridLayout->addWidget(timeSlotComboBox, 1, 0, 1, 1);


        retranslateUi(appointmentform);

        QMetaObject::connectSlotsByName(appointmentform);
    } // setupUi

    void retranslateUi(QWidget *appointmentform)
    {
        appointmentform->setWindowTitle(QCoreApplication::translate("appointmentform", "Form", nullptr));
        label->setText(QCoreApplication::translate("appointmentform", "Schedule Appointment", nullptr));
        reasonTextEdit->setPlaceholderText(QCoreApplication::translate("appointmentform", "Enter reason for visit", nullptr));
        saveButton->setText(QCoreApplication::translate("appointmentform", "Save Appointment", nullptr));
        cancelButton->setText(QCoreApplication::translate("appointmentform", "Cancel", nullptr));
        doctorComboBox->setPlaceholderText(QCoreApplication::translate("appointmentform", "Select Doctor", nullptr));
        patientComboBox->setPlaceholderText(QCoreApplication::translate("appointmentform", "Select Patient", nullptr));
        timeSlotComboBox->setPlaceholderText(QCoreApplication::translate("appointmentform", "Select Time", nullptr));
    } // retranslateUi

};

namespace Ui {
    class appointmentform: public Ui_appointmentform {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_APPOINTMENTFORM_H
