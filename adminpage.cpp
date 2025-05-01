#include "adminpage.h"
#include "ui_adminpage.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QRegularExpression>

AdminPage::AdminPage(QMainWindow *parent) :
    QMainWindow(parent),
    ui(new Ui::AdminPage)
{
    ui->setupUi(this);
    ui->roleComboBox->addItems({"Admin", "User"});
    loadUsers();
}

AdminPage::~AdminPage()
{
    delete ui;
}

bool AdminPage::saveUsersToFile()
{
    QFile file("users.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Error opening file:" << file.errorString();
        return false;
    }

    QTextStream out(&file);
    for (const QStringList &user : usersList) {
        if (user.size() >= 3) {
            out << user[0] << ":" << user[1] << ":" << user[2] << "\n";
        }
    }

    if (out.status() != QTextStream::Ok) {
        qDebug() << "Error writing to file";
        file.close();
        return false;
    }

    file.close();
    return true;
}

void AdminPage::loadUsers()
{
    usersList.clear();
    ui->userListWidget->clear();

    QFile file("users.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open users.txt for reading";
        QMessageBox::critical(this, "Error", "Could not load user data!");
        return;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (!line.isEmpty()) {
            QStringList userData = line.split(":");
            if (userData.size() >= 3) {
                usersList.append(userData);
                ui->userListWidget->addItem(line);
            }
        }
    }
    file.close();

    qDebug() << "Loaded users:" << usersList;
}
bool AdminPage::validatePassword(const QString &password)
{
    return password.length() >= 8 && password.contains(QRegularExpression("\\d"));
}

void AdminPage::on_addUserButton_clicked()
{
    QString username = ui->usernameInput->text().trimmed();
    QString password = ui->passwordInput->text();
    QString role = ui->roleComboBox->currentText();

    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please enter username and password.");
        return;
    }

    if (!validatePassword(password)) {
        QMessageBox::warning(this, "Password Error", "Password must be at least 8 characters and include a number.");
        return;
    }

    for (const QStringList &user : usersList) {
        if (user[0] == username) {
            QMessageBox::warning(this, "Duplicate", "Username already exists.");
            return;
        }
    }

    usersList.append({username, password, role});

    saveUsersToFile();

    QMessageBox::information(this, "Success", "User added.");
    ui->usernameInput->clear();
    ui->passwordInput->clear();
}


void AdminPage::on_listUsersButton_clicked()
{
    QString currentSelection;
    QListWidgetItem *currentItem = ui->userListWidget->currentItem();
    if (currentItem) {
        currentSelection = currentItem->text();
    }

    ui->userListWidget->clear();
    for (const QStringList &user : usersList) {
        ui->userListWidget->addItem(user.join(":"));
    }

    // Restore selection if it still exists
    if (!currentSelection.isEmpty()) {
        QList<QListWidgetItem*> items = ui->userListWidget->findItems(currentSelection, Qt::MatchExactly);
        if (!items.isEmpty()) {
            ui->userListWidget->setCurrentItem(items.first());
        }
    }
}

void AdminPage::on_deleteUserButton_clicked()
{
    QString usernameToDelete = ui->usernameInput->text().trimmed();

    if (usernameToDelete.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please enter a username to delete.");
        return;
    }



    bool userDeleted = false;
    for (int i = 0; i < usersList.size(); ++i) {
        if (!usersList[i].isEmpty() && usersList[i][0] == usernameToDelete) {
            usersList.removeAt(i);
            userDeleted = true;

            if (!saveUsersToFile()) {
                QMessageBox::critical(this, "Error", "Failed to save changes to file!");
                loadUsers();
                return;
            }

            loadUsers();
            ui->usernameInput->clear();

            QMessageBox::information(this, "Success",
                                     QString("User '%1' deleted successfully.").arg(usernameToDelete));
            return;
        }
    }

    QMessageBox::warning(this, "Not Found",
                         QString("User '%1' not found in the system.").arg(usernameToDelete));
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
void AdminPage::on_logoutButton_clicked()
{
    emit logoutRequested();
}
void AdminPage::closeEvent(QCloseEvent *event)
{
    if (!saveUsersToFile()) {
        QMessageBox::critical(this, "Error", "Failed to save user data!");
        event->ignore();
    } else {
        event->accept();
    }
}
