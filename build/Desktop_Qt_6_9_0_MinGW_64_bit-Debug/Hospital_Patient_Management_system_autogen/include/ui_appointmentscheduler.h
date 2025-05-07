/********************************************************************************
** Form generated from reading UI file 'appointmentscheduler.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_APPOINTMENTSCHEDULER_H
#define UI_APPOINTMENTSCHEDULER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AppointmentScheduler
{
public:

    void setupUi(QWidget *AppointmentScheduler)
    {
        if (AppointmentScheduler->objectName().isEmpty())
            AppointmentScheduler->setObjectName("AppointmentScheduler");
        AppointmentScheduler->resize(800, 600);

        retranslateUi(AppointmentScheduler);

        QMetaObject::connectSlotsByName(AppointmentScheduler);
    } // setupUi

    void retranslateUi(QWidget *AppointmentScheduler)
    {
        AppointmentScheduler->setWindowTitle(QCoreApplication::translate("AppointmentScheduler", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AppointmentScheduler: public Ui_AppointmentScheduler {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_APPOINTMENTSCHEDULER_H
