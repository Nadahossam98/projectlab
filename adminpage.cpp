#include "adminpage.h"
#include "ui_adminpage.h"

#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QDir>
#include <QFileDialog>
#include <QRegularExpression>
#include <QDebug>
#include <algorithm>
#include <qevent.h>

// Constructor: Initializes the AdminPage UI and sets up connections
AdminPage::AdminPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminPage)
{
    ui->setupUi(this);
    setWindowTitle("Admin Dashboard");
    setFixedSize(800, 600);

    // Connect button signals to their respective slots
    connect(ui->addUserButton, &QPushButton::clicked, this, &AdminPage::on_addUserButton_clicked);
    connect(ui->deleteUserButton, &QPushButton::clicked, this, &AdminPage::on_deleteUserButton_clicked);
    connect(ui->logoutButton, &QPushButton::clicked, this, &AdminPage::on_logoutButton_clicked);

    // Initialize user data and populate the user list
    initializeUserData();
    refreshUserList();
}

// Destructor: Saves users to file and cleans up UI
AdminPage::~AdminPage()
{
    saveUsersToFile();
    delete ui;
}



// Initializes user data, creates users.txt and default admin if not present
void AdminPage::initializeUserData()
{
    QFile file("users.txt");
    if (!file.exists()) {
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            // Create default admin account
            QTextStream out(&file);
            out << "admin:admin123:Admin\n";
            file.close();
        } else {
            qDebug() << "Could not create users file";
        }
    }
    loadUsers();
}

// Validates password: must be at least 8 characters, contain letters and numbers
bool AdminPage::validatePassword(const QString &password)
{
    QRegularExpression regex("^(?=.*[a-zA-Z])(?=.*\\d).{8,}$");
    return regex.match(password).hasMatch();
}

// Checks if a username already exists in the user list
bool AdminPage::userExists(const QString &username)
{
    return std::any_of(usersList.begin(), usersList.end(),
                       [&username](const QStringList &user) {
                           return !user.isEmpty() && user[0] == username;
                       });
}

// Saves the current usersList to users.txt
bool AdminPage::saveUsersToFile()
{
    QFile file("users.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Could not save user data!";
        return false;
    }
    QTextStream out(&file);
    for (const QStringList &user : usersList) {
        if (user.size() >= 3) {
            out << user[0] << ":" << user[1] << ":" << user[2];
            if (user.size() > 3) out << ":" << user[3]; // Save profile pic path if exists
            out << "\n";
        }
    }
    file.close();
    return true;
}

// Loads users from users.txt into usersList
void AdminPage::loadUsers()
{
    usersList.clear();
    QFile file("users.txt");
    if (!file.exists()) return;
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine().trimmed();
            if (!line.isEmpty()) {
                usersList.append(line.split(":"));
            }
        }
        file.close();
    }
}

// Refreshes the user list widget to display current users
void AdminPage::refreshUserList()
{
    ui->userListWidget->clear();
    for (const QStringList &user : usersList) {
        if (user.size() >= 3) {
            QString displayText = user[0] + " (" + user[2] + ")";
            if (user.size() > 3 && !user[3].isEmpty()) {
                displayText += " [Has Photo]";
            }
            ui->userListWidget->addItem(displayText);
        }
    }
}

// Slot: Handles adding a new user
void AdminPage::on_addUserButton_clicked()
{
    QString username = ui->usernameInput->text().trimmed();
    QString password = ui->passwordInput->text();
    QString role = ui->roleComboBox->currentText();

    // Validation: Empty fields
    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Error", "Username and password cannot be empty.");
        return;
    }

    // Validation: Password strength
    if (!validatePassword(password)) {
        QMessageBox::warning(this, "Error",
                             "Password must be:\n- At least 8 characters\n- Contain both letters and numbers");
        return;
    }

    // Validation: Username uniqueness
    if (userExists(username)) {
        QMessageBox::warning(this, "Error", "Username already exists.");
        return;
    }

    // Handle profile picture selection
    QString profilePicPath;
    if (ui->profilePicCheckBox->isChecked()) {
        QString fileName = QFileDialog::getOpenFileName(this,
                                                        tr("Select Profile Picture"), "",
                                                        tr("Images (*.png *.jpg *.jpeg)"));
        if (!fileName.isEmpty()) {
            QDir dir("profile_pics");
            if (!dir.exists() && !dir.mkpath(".")) {
                QMessageBox::warning(this, "Error", "Failed to create profile pictures directory.");
                return;
            }
            QString newFileName = "profile_pics/" + username + ".png";
            if (QFile::exists(newFileName) && !QFile::remove(newFileName)) {
                QMessageBox::warning(this, "Error", "Failed to replace existing profile picture.");
                return;
            }
            if (!QFile::copy(fileName, newFileName)) {
                QMessageBox::warning(this, "Error", "Failed to save profile picture.");
                return;
            }
            profilePicPath = newFileName;
        }
    }

    // Add new user to the list
    QStringList newUser = {username, password, role};
    if (!profilePicPath.isEmpty()) newUser.append(profilePicPath);
    usersList.append(newUser);

    // Save to file, rollback on failure
    if (!saveUsersToFile()) {
        QMessageBox::critical(this, "Error", "Failed to save user data!");
        usersList.removeLast();
        return;
    }

    // Update UI and clear input fields
    refreshUserList();
    ui->usernameInput->clear();
    ui->passwordInput->clear();
    ui->profilePicCheckBox->setChecked(false);

    QMessageBox::information(this, "Success", "User added successfully.");
}


// Slot: Handles deleting the selected user
void AdminPage::on_deleteUserButton_clicked()
{
    QListWidgetItem *currentItem = ui->userListWidget->currentItem();
    if (!currentItem) {
        QMessageBox::warning(this, "Error", "Please select a user to delete.");
        return;
    }

    QString username = currentItem->text().split(" ").first();
    if (username == "admin") {
        QMessageBox::warning(this, "Error", "Cannot delete admin account.");
        return;
    }

    int reply = QMessageBox::question(this, "Confirm",
                                      QString("Are you sure you want to delete user '%1'?").arg(username),
                                      QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        auto it = std::find_if(usersList.begin(), usersList.end(),
                               [&username](const QStringList &user) { return user[0] == username; });
        if (it != usersList.end()) {
            // Remove profile picture if exists
            if (it->size() > 3 && !it->at(3).isEmpty()) {
                QFile::remove(it->at(3));
            }
            usersList.erase(it);
            if (!saveUsersToFile()) {
                QMessageBox::critical(this, "Error", "Failed to save changes!");
                loadUsers(); // Revert changes
            }
            refreshUserList();
            QMessageBox::information(this, "Success", "User deleted successfully.");
        }
    }
}

// Slot: Handles logout button click
void AdminPage::on_logoutButton_clicked()
{
    if (saveUsersToFile()) {
        emit logoutRequested();
    } else {
        QMessageBox::critical(this, "Error", "Failed to save user data on logout!");
    }
}

// Handles window close event: saves user data before closing
void AdminPage::closeEvent(QCloseEvent *event)
{
    if (saveUsersToFile()) {
        event->accept();
    } else {
        QMessageBox::critical(this, "Error", "Failed to save user data!");
        event->ignore();
    }
}
