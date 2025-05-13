#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H


#include "datastructures.h"
#include <QObject>
#include <QJsonObject>

class DatabaseManager : public QObject {
    Q_OBJECT

public:
    explicit DatabaseManager(QObject *parent = nullptr);
    ~DatabaseManager();

    // Initialization
    bool initializeDatabase();

    // User management
    bool addUser(const User &user);
    User getUser(const QString &username) const;
    QList<User> getAllUsers() const;
    bool authenticateUser(const QString &username, const QString &password) const;
    bool updateUser(const User &user);
    bool deleteUser(const QString &username);

    // Patient management
    bool addPatient(const Patient &patient);
    Patient getPatient(const QString &id) const;
    QList<Patient> getAllPatients() const;
    bool updatePatient(const Patient &patient);
    bool deletePatient(const QString &id);

    // Doctor management
    bool addDoctor(const Doctor &doctor);
    Doctor getDoctor(const QString &id) const;
    QList<Doctor> getAllDoctors() const;

    // ... Similar methods for appointments, treatments, bills ...

    // File operations
    bool saveAllData();
    bool loadAllData();

private:
    QList<User> m_users;
    QHash<QString, Patient> m_patients;
    QList<Doctor> m_doctors;
    QHash<QString, Appointment> m_appointments;
    QList<Treatment> m_treatments;
    QHash<QString, Bill> m_bills;

    // Helper methods
    QString generateId(const QString &prefix) const;
    QJsonObject userToJson(const User &user) const;
    User jsonToUser(const QJsonObject &json) const;
    // ... similar conversion methods for other types ...

    // File paths
    const QString USERS_FILE = "users.json";
    const QString PATIENTS_FILE = "patients.json";
    const QString DOCTORS_FILE = "doctors.json";
    const QString APPOINTMENTS_FILE = "appointments.json";
    const QString TREATMENTS_FILE = "treatments.json";
    const QString BILLS_FILE = "bills.json";
};

#endif // DATABASEMANAGER_H
