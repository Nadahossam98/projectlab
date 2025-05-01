#include "appointmentscheduler.h"
#include "ui_appointmentscheduler.h"

AppointmentScheduler::AppointmentScheduler(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AppointmentScheduler)
{
    ui->setupUi(this);
}

AppointmentScheduler::~AppointmentScheduler()
{
    delete ui;
}
