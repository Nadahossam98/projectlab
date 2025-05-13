#ifndef APPOINTMENTFORM_H
#define APPOINTMENTFORM_H

#include <QWidget>
#include <QList>
#include <QDateTime>
#include <QJsonObject>
#include <QJsonArray>

namespace Ui {
class AppointmentForm;
}

class AppointmentForm : public QWidget
{
    Q_OBJECT

public:
    explicit AppointmentForm(QWidget *parent = nullptr);
    ~AppointmentForm();

    void resetForm();

signals:
    void appointmentScheduled();
    void finished();

private slots:
    void on_saveButton_clicked();
    void on_cancelButton_clicked();
    void on_doctorComboBox_currentIndexChanged(int index);
    void updateTimeSlots();
    void validateForm();

private:
    Ui::AppointmentForm *ui;

    struct Patient {
        int id;
        QString firstName;
        QString lastName;

        QString fullName() const { return firstName + " " + lastName; }

        QJsonObject toJson() const {
            QJsonObject obj;
            obj["id"] = id;
            obj["firstName"] = firstName;
            obj["lastName"] = lastName;
            return obj;
        }
        static Patient fromJson(const QJsonObject &obj) {
            Patient p;
            p.id = obj["id"].toInt();
            p.firstName = obj["firstName"].toString();
            p.lastName = obj["lastName"].toString();
            return p;
        }
    };

    struct Doctor {
        int id;
        QString firstName;
        QString lastName;
        QString specialty;

        QString fullName() const {
            if (lastName.isEmpty() && specialty.isEmpty())
                return firstName;  // Username only
            return firstName + " " + lastName + " (" + specialty + ")";
        }

        QJsonObject toJson() const {
            QJsonObject obj;
            obj["id"] = id;
            obj["firstName"] = firstName;
            obj["lastName"] = lastName;
            obj["specialty"] = specialty;
            return obj;
        }
        static Doctor fromJson(const QJsonObject &obj) {
            Doctor d;
            d.id = obj["id"].toInt();
            d.firstName = obj["firstName"].toString();
            d.lastName = obj["lastName"].toString();
            d.specialty = obj["specialty"].toString();
            return d;
        }
    };

    struct Appointment {
        int id;
        int patientId;
        int doctorId;
        QDateTime dateTime;
        QString reason;

        QJsonObject toJson() const {
            QJsonObject obj;
            obj["id"] = id;
            obj["patientId"] = patientId;
            obj["doctorId"] = doctorId;
            obj["dateTime"] = dateTime.toString(Qt::ISODate);
            obj["reason"] = reason;
            return obj;
        }
        static Appointment fromJson(const QJsonObject &obj) {
            Appointment a;
            a.id = obj["id"].toInt();
            a.patientId = obj["patientId"].toInt();
            a.doctorId = obj["doctorId"].toInt();
            a.dateTime = QDateTime::fromString(obj["dateTime"].toString(), Qt::ISODate);
            a.reason = obj["reason"].toString();
            return a;
        }
    };

    QList<Patient> patients;
    QList<Doctor> doctors;
    QList<Appointment> appointments;

    int nextPatientId = 1;
    int nextDoctorId = 1;
    int nextAppointmentId = 1;

    void initializeSampleData();
    void loadPatients();
    bool isTimeSlotAvailable(int doctorId, const QDateTime& dateTime) const;
    QList<QDateTime> getAvailableTimeSlots(int doctorId, const QDate& date) const;

    void saveToFile();
    void loadFromFile();
};

#endif // APPOINTMENTFORM_H

