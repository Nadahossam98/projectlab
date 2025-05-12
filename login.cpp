#include "login.h"
#include "ui_login.h"

#include <QMessageBox>
#include <QFile>
#include <QTextStream>

/*
 * Login class implements the login window for the Hospital Management System.
 * It handles user input, validates credentials, and emits a signal on successful login.
 */
Login::Login(QWidget *parent)
    : QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    setWindowTitle("Hospital Management System - Login");

    // Hide password input for security
    ui->passwordInput->setEchoMode(QLineEdit::Password);

    // Connect login button and Enter key in password field to the attemptLogin slot
    connect(ui->loginButton, &QPushButton::clicked,
            this, &Login::attemptLogin);
    connect(ui->passwordInput, &QLineEdit::returnPressed,
            this, &Login::attemptLogin);
}

// Destructor: cleans up the UI
Login::~Login()
{
    delete ui;
}

/*
 * Attempts to log in with the entered username and password.
 * Checks for empty fields, reads the users.txt file, and validates credentials.
 * Emits loginSuccess(username, role) if successful, otherwise shows an error.
 */
void Login::attemptLogin()
{
    // Get input values and trim whitespace
    const QString username = ui->usernameInput->text().trimmed();
    const QString password = ui->passwordInput->text().trimmed();

    // Check for empty fields
    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Error", "Both fields are required");
        return;
    }

    // Open the users.txt file for reading
    QFile file("users.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", "Cannot access user database");
        return;
    }

    QTextStream in(&file);
    bool found = false;
    QString role = "User";

    // Read each line of the file and check for matching credentials
    while (!in.atEnd()) {
        const QString line = in.readLine().trimmed();
        if (line.isEmpty()) continue;

        // Each line format: username:password:role
        const QStringList parts = line.split(":");
        if (parts.size() >= 2 && parts[0] == username && parts[1] == password) {
            found = true;
            if (parts.size() >= 3) role = parts[2].trimmed();
            break;
        }
    }
    file.close();

    // If found, emit success signal; otherwise, show error
    if (found) {
        emit loginSuccess(username, role);
    } else {
        QMessageBox::warning(this, "Error", "Invalid username or password");
    }
}
