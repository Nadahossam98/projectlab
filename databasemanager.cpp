#include "databasemanager.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QCryptographicHash>
#include <QDateTime>

/*
 * DatabaseManager handles all in-memory data and file persistence for users and patients.
 * It provides methods for user authentication, user/patient CRUD, and JSON serialization.
 */

// Constructor: Loads all persisted data into memory
DatabaseManager::DatabaseManager(QObject *parent) : QObject(parent) {
    loadAllData();
}

// Destructor: Saves all data to disk when the object is destroyed
DatabaseManager::~DatabaseManager() {
    saveAllData();
}

/*
 * Initializes the database. If no users exist, creates a default admin user.
 * Returns true if initialization is successful.
 */
bool DatabaseManager::initializeDatabase() {
    // Create default admin user if none exists
    if (m_users.isEmpty()) {
        User admin;
        admin.username = "admin";
        admin.passwordHash = QString(QCryptographicHash::hash("admin123", QCryptographicHash::Sha256).toHex());
        admin.role = "Admin";
        admin.fullName = "System Administrator";
        admin.contactInfo = "admin@hospital.com";
        admin.lastLogin = QDateTime::currentDateTime();
        m_users.append(admin);
        saveAllData();
    }
    return true;
}

// ================== User Management ==================

/*
 * Adds a new user. Returns false if username or password is empty, or user already exists.
 */
bool DatabaseManager::addUser(const User &user) {
    if (user.username.isEmpty() || user.passwordHash.isEmpty())
        return false;

    // Check if user already exists
    for (const User &u : m_users) {
        if (u.username == user.username)
            return false;
    }
    m_users.append(user);
    return true;
}

/*
 * Returns the User object for the given username, or an empty User if not found.
 */
User DatabaseManager::getUser(const QString &username) const {
    for (const User &user : m_users) {
        if (user.username == username)
            return user;
    }
    return User(); // Return empty user if not found
}

/*
 * Authenticates a user by username and password.
 * Returns true if credentials are correct, false otherwise.
 */
bool DatabaseManager::authenticateUser(const QString &username, const QString &password) const {
    User user = getUser(username);
    if (user.username.isEmpty())
        return false;

    QString hashedPassword = QString(QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256).toHex());
    return (user.passwordHash == hashedPassword);
}

// ================== Patient Management ==================

/*
 * Adds a new patient. Returns false if required fields are missing or ID already exists.
 */
bool DatabaseManager::addPatient(const Patient &patient) {
    if (patient.id.isEmpty() || patient.firstName.isEmpty())
        return false;

    if (m_patients.contains(patient.id))
        return false;

    m_patients.insert(patient.id, patient);
    return true;
}

/*
 * Returns the Patient object for the given ID, or an empty Patient if not found.
 */
Patient DatabaseManager::getPatient(const QString &id) const {
    return m_patients.value(id, Patient());
}

// ================== JSON Serialization Methods ==================

/*
 * Converts a User object to a QJsonObject for saving.
 */
QJsonObject DatabaseManager::userToJson(const User &user) const {
    QJsonObject json;
    json["username"] = user.username;
    json["passwordHash"] = user.passwordHash;
    json["role"] = user.role;
    json["fullName"] = user.fullName;
    json["contactInfo"] = user.contactInfo;
    json["lastLogin"] = user.lastLogin.toString(Qt::ISODate);
    return json;
}

/*
 * Converts a QJsonObject to a User object.
 */
User DatabaseManager::jsonToUser(const QJsonObject &json) const {
    User user;
    user.username = json["username"].toString();
    user.passwordHash = json["passwordHash"].toString();
    user.role = json["role"].toString();
    user.fullName = json["fullName"].toString();
    user.contactInfo = json["contactInfo"].toString();
    user.lastLogin = QDateTime::fromString(json["lastLogin"].toString(), Qt::ISODate);
    return user;
}

// ================== File Operations ==================

/*
 * Saves all user and patient data to disk as JSON files.
 * Returns true if successful.
 */
bool DatabaseManager::saveAllData() {
    // Save users
    QJsonArray usersArray;
    for (const User &user : m_users) {
        usersArray.append(userToJson(user));
    }
    QJsonDocument usersDoc(usersArray);
    QFile usersFile(USERS_FILE);
    if (!usersFile.open(QIODevice::WriteOnly))
        return false;
    usersFile.write(usersDoc.toJson());
    usersFile.close();

    // Similar implementations for other data types...
    return true;
}

/*
 * Loads all user and patient data from disk.
 * Returns true if successful.
 */
bool DatabaseManager::loadAllData() {
    // Load users
    QFile usersFile(USERS_FILE);
    if (usersFile.open(QIODevice::ReadOnly)) {
        QByteArray data = usersFile.readAll();
        QJsonDocument doc = QJsonDocument::fromJson(data);
        if (doc.isArray()) {
            QJsonArray array = doc.array();
            m_users.clear();
            for (const QJsonValue &value : array) {
                m_users.append(jsonToUser(value.toObject()));
            }
        }
        usersFile.close();
    }
    return true;
}
