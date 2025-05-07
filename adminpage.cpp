#include "adminpage.h"
#include "ui_adminpage.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QRegularExpression>
#include <QListWidgetItem>
#include <QCloseEvent>

AdminPage::AdminPage(QWidget *parent) :
    QMainWindow(parent),  // Changed back to QMainWindow
    ui(new Ui::AdminPage),
    dataModified(false)
{
    ui->setupUi(this);

    // Setup role options - only Admin can create other Admins
    ui->roleComboBox->addItems({"Doctor", "Receptionist"});

    // Connect buttons
    connect(ui->addUserButton, &QPushButton::clicked, this, &AdminPage::on_addUserButton_clicked);
    connect(ui->listUsersButton, &QPushButton::clicked, this, &AdminPage::on_listUsersButton_clicked);
    connect(ui->deleteUserButton, &QPushButton::clicked, this, &AdminPage::on_deleteUserButton_clicked);
    connect(ui->logoutButton, &QPushButton::clicked, this, &AdminPage::on_logoutButton_clicked);

    loadUsers();
}

AdminPage::~AdminPage()
{
    if (dataModified) {
        saveUsersToFile();
    }
    delete ui;
}

bool AdminPage::isCurrentUserAdmin() const
{
    // In a real application, you would check the currently logged in user's role
    // For this example, we'll assume this page is only accessible by admins
    return true;
}

bool AdminPage::saveUsersToFile()
{
    QFile file("users.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", "Failed to save user data!");
        return false;
    }

    QTextStream out(&file);
    for (const QStringList &user : usersList) {
        if (user.size() >= 3) {
            out << user[0] << ":" << user[1] << ":" << user[2] << "\n";
        }
    }

    file.close();
    dataModified = false;
    return true;
}

void AdminPage::loadUsers()
{
    usersList.clear();
    ui->userListWidget->clear();

    QFile file("users.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (!line.isEmpty()) {
            QStringList userData = line.split(":");
            if (userData.size() >= 3) {
                usersList.append(userData);
                ui->userListWidget->addItem(userData[0] + " (" + userData[2] + ")");
            }
        }
    }
    file.close();
}

bool AdminPage::validatePassword(const QString &password)
{
    if (password.length() < 8) {
        return false;
    }

    QRegularExpression letterRegex("[a-zA-Z]");
    QRegularExpression digitRegex("\\d");

    return password.contains(letterRegex) && password.contains(digitRegex);
}

bool AdminPage::userExists(const QString &username)
{
    for (const QStringList &user : usersList) {
        if (user[0] == username) {
            return true;
        }
    }
    return false;
}

void AdminPage::on_addUserButton_clicked()
{
    if (!isCurrentUserAdmin()) {
        QMessageBox::warning(this, "Access Denied", "Only administrators can create new accounts");
        return;
    }

    QString username = ui->usernameInput->text().trimmed();
    QString password = ui->passwordInput->text();
    QString role = ui->roleComboBox->currentText();

    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Error", "Both fields are required");
        return;
    }

    if (!validatePassword(password)) {
        QMessageBox::warning(this, "Error", "Password must be at least 8 characters and contain both letters and numbers");
        return;
    }

    if (userExists(username)) {
        QMessageBox::warning(this, "Error", "Username already exists");
        return;
    }

    usersList.append({username, password, role});
    dataModified = true;

    if (saveUsersToFile()) {
        QMessageBox::information(this, "Success", QString("%1 account created successfully").arg(role));
        ui->usernameInput->clear();
        ui->passwordInput->clear();
        loadUsers();
    }
}

void AdminPage::on_listUsersButton_clicked()
{
    loadUsers();
}

void AdminPage::on_deleteUserButton_clicked()
{
    if (!isCurrentUserAdmin()) {
        QMessageBox::warning(this, "Access Denied", "Only administrators can delete accounts");
        return;
    }

    QListWidgetItem *item = ui->userListWidget->currentItem();
    if (!item) {
        QMessageBox::warning(this, "Error", "Please select a user to delete");
        return;
    }

    QString username = item->text().split(" ").first();
    QString role = item->text().split("(").last().remove(")").trimmed();

    if (role == "Admin") {
        QMessageBox::warning(this, "Error", "Cannot delete administrator accounts");
        return;
    }

    QMessageBox::StandardButton reply = QMessageBox::question(
        this, "Confirm Delete",
        QString("Are you sure you want to delete %1's account?").arg(username),
        QMessageBox::Yes|QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        for (int i = 0; i < usersList.size(); ++i) {
            if (usersList[i][0] == username) {
                usersList.removeAt(i);
                dataModified = true;

                if (saveUsersToFile()) {
                    QMessageBox::information(this, "Success", "User deleted");
                    loadUsers();
                }
                return;
            }
        }
    }
}

void AdminPage::on_logoutButton_clicked()
{
    if (dataModified && !saveUsersToFile()) {
        QMessageBox::warning(this, "Warning", "Failed to save changes!");
    }
    emit logoutRequested();
}

void AdminPage::closeEvent(QCloseEvent *event)
{
    if (dataModified) {
        QMessageBox::StandardButton reply = QMessageBox::question(
            this, "Unsaved Changes", "Save changes before closing?",
            QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel);

        if (reply == QMessageBox::Cancel) {
            event->ignore();
            return;
        }
        else if (reply == QMessageBox::Yes && !saveUsersToFile()) {
            event->ignore();
            return;
        }
    }
    event->accept();
}
