
#include "login.h"
#include "ui_login.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QIcon>

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login),
    passwordVisible(false)
{
    ui->setupUi(this);

    // Password field setup
    ui->passwordInput->setEchoMode(QLineEdit::Password);
    ui->passwordInput->setClearButtonEnabled(true);

    // Toggle action
    QAction *toggleAction = ui->passwordInput->addAction(
        QIcon::fromTheme("view-hidden"),
        QLineEdit::TrailingPosition
        );

    // Connections
    connect(ui->loginButton, &QPushButton::clicked,
            this, &Login::onLoginButtonClicked);
    connect(toggleAction, &QAction::triggered,
            this, &Login::togglePasswordVisibility);
}

Login::~Login()
{
    delete ui;
}

void Login::togglePasswordVisibility()
{
    passwordVisible = !passwordVisible;
    ui->passwordInput->setEchoMode(passwordVisible ? QLineEdit::Normal : QLineEdit::Password);

    // Change icon based on visibility
QIcon icon(passwordVisible ? QIcon::fromTheme("view-visible") : QIcon::fromTheme("view-hidden"));
    qobject_cast<QAction*>(sender())->setIcon(icon);
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
        ui->passwordInput->clear();
    }
}
