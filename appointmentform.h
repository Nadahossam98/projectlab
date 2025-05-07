#ifndef APPOINTMENTFORM_H
#define APPOINTMENTFORM_H

#include <QWidget>
#include <QList>
#include <QDateTime>

namespace Ui {
class appointmentform;
}

class appointmentform : public QWidget
{
    Q_OBJECT

public:
    explicit appointmentform(QWidget *parent = nullptr);
    ~appointmentform();

public slots:
    void resetForm();

signals:
    void appointmentScheduled();
    void cancelled();

private slots:
    void on_saveButton_clicked();
    void on_cancelButton_clicked();
    void on_doctorComboBox_currentIndexChanged(int index);
    void updateTimeSlots();
    void validateForm();

private:
    Ui::appointmentform *ui;

    struct Patient {
        int id;
        QString firstName;
        QString lastName;
        QString fullName() const { return firstName + " " + lastName; }
    };

    struct Doctor {
        int id;
        QString firstName;
        QString lastName;
        QString specialty;
        QString fullName() const { return firstName + " " + lastName + " (" + specialty + ")"; }
    };

    struct Appointment {
        int patientId;
        int doctorId;
        QDateTime dateTime;
        QString reason;
        QString status = "Scheduled";
    };

    QList<Patient> patients;
    QList<Doctor> doctors;
    QList<Appointment> appointments;
    int nextPatientId = 1;
    int nextDoctorId = 1;
    int nextAppointmentId = 1;

    void initializeSampleData();
    void loadPatients();
    void loadDoctors();
    void saveAppointment(const Appointment& appointment);
    bool isTimeSlotAvailable(int doctorId, const QDateTime& dateTime) const;
    QList<QDateTime> getAvailableTimeSlots(int doctorId, const QDate& date) const;
    void updateUiAfterSave();
};

#endif // APPOINTMENTFORM_H
