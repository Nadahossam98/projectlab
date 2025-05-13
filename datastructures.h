#ifndef DATASTRUCTURES_H
#define DATASTRUCTURES_H

#include <QString>
#include <QList>
#include <QHash>
#include <QDate>
#include <QDateTime>
#include <QStringList>

struct User {
    QString username;
    QString passwordHash;
    QString role;
    QString profilePicturePath;
    QString fullName;
    QString contactInfo;
    QDateTime lastLogin;

    bool operator==(const User& other) const {
        return username == other.username;
    }
};

struct Patient {
    QString id;
    QString firstName;
    QString lastName;
    int age;
    QString gender;
    QString address;
    QString phoneNumber;
    QString email;
    QString bloodType;
    QStringList allergies;
    QStringList medications;
    QString primaryCarePhysician;
    QHash<QString, QString> medicalHistory; // date -> description

    QString fullName() const { return firstName + " " + lastName; }
};

struct Doctor {
    QString id;
    QString firstName;
    QString lastName;
    QString specialization;
    QStringList qualifications;
    QString contactNumber;

    QString fullName() const { return "Dr. " + firstName + " " + lastName; }
};

struct Appointment {
    QString appointmentId;
    QString patientId;
    QString doctorId;
    QDateTime dateTime;
    QString purpose;
    QString status; // "Scheduled", "Completed", "Cancelled", "No-show"
    QString notes;
    double duration; // in hours
};

struct Treatment {
    QString treatmentId;
    QString name;
    QString description;
    double baseCost;
    QString category; // "Consultation", "Procedure", "Test", "Medication"
};

struct Bill {
    QString billId;
    QString patientId;
    QDate issueDate;
    QDate dueDate;
    QList<QPair<QString, int>> treatments; // treatment ID and quantity
    double insuranceCoverage; // percentage
    QString paymentStatus; // "Pending", "Partial", "Paid", "Overdue"
    QList<QPair<QDate, double>> payments; // date and amount

    double calculateTotal() const;
};

#endif // DATASTRUCTURES_H
