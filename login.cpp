// login.cpp
#include "login.h"
#include "ui_login.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QRegularExpression>

Login::Login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    connect(ui->loginButton, &QPushButton::clicked, this, &Login::onLoginButtonClicked);
    connect(ui->signUpButton, &QPushButton::clicked, this, &Login::onSignUpButtonClicked);
}

Login::~Login()
{
    delete ui;
}

void Login::onLoginButtonClicked()
{
    QString username = ui->usernameInput->text().trimmed();
    QString password = ui->passwordInput->text().trimmed();

    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Error", "Both fields are required");
        return;
    }

    QFile file("users.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", "Cannot access user database");
        return;
    }

    QTextStream in(&file);
    bool found = false;
    bool isAdmin = false;

    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty()) continue;

        QStringList parts = line.split(":");
        if (parts.size() >= 2 && parts[0] == username && parts[1] == password) {
            found = true;
            if (parts.size() >= 3 && parts[2].trimmed() == "Admin") {
                isAdmin = true;
            }
            break;
        }
    }
    file.close();

    if (found) {
        emit loginSuccess(username, isAdmin);
        this->close();
    } else {
        QMessageBox::warning(this, "Login Failed", "Invalid credentials");
    }
}

void Login::onSignUpButtonClicked()
{
    QString username = ui->usernameInput->text().trimmed();
    QString password = ui->passwordInput->text().trimmed();

    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Error", "Both fields are required");
        return;
    }

    if (!validatePassword(password)) {
        QMessageBox::warning(this, "Weak Password", "Password must be 8+ chars with a number");
        return;
    }

    QFile file("users.txt");
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", "Cannot access user database");
        return;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty()) continue;

        QStringList parts = line.split(":");
        if (parts.size() >= 1 && parts[0] == username) {
            QMessageBox::warning(this, "Exists", "Username already taken");
            file.close();
            return;
        }
    }

    QTextStream out(&file);
    out << username << ":" << password << ":User\n";
    file.close();

    QMessageBox::information(this, "Success", "Account created. Please login.");
}

bool Login::validatePassword(const QString &password)
{
    return password.length() >= 8 && password.contains(QRegularExpression("\\d"));
}
