#ifndef APPOINTMENTSCHEDULER_H
#define APPOINTMENTSCHEDULER_H

#include <QWidget>

namespace Ui {
class AppointmentScheduler;
}

class AppointmentScheduler : public QWidget
{
    Q_OBJECT

public:
    explicit AppointmentScheduler(QWidget *parent = nullptr);
    ~AppointmentScheduler();

private:
    Ui::AppointmentScheduler *ui;
};

#endif
