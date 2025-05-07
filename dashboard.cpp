#include "dashboard.h"
#include "ui_dashboard.h"
#include <QMessageBox>

Dashboard::Dashboard(const QString &username, bool isAdmin, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Dashboard),
    isAdmin(isAdmin),
    currentUsername(username)
{
    ui->setupUi(this);

    setupUI();
    loadStatistics();

    // Connect buttons to their slots
    connect(ui->patientsButton, &QPushButton::clicked,
            this, &Dashboard::onPatientRecordsClicked);
    connect(ui->appointmentsButton, &QPushButton::clicked,
            this, &Dashboard::onAppointmentsButtonClicked);
    connect(ui->billingButton, &QPushButton::clicked,
            this, &::Dashboard::onReportsButtonClicked);
    connect(ui->logoutButton, &QPushButton::clicked,
            this, &Dashboard::onLogoutClicked);
}

void Dashboard::setupUI()
{
    ui->welcomeLabel->setText(tr("Welcome, %1!").arg(currentUsername));

    // Set logout button text and style
    ui->logoutButton->setText(tr("Logout"));
    ui->logoutButton->setStyleSheet(
        "QPushButton {"
        "   background-color: #e74c3c;"
        "   color: white;"
        "   border: none;"
        "   padding: 8px;"
        "   border-radius: 4px;"
        "}"
        "QPushButton:hover {"
        "   background-color: #c0392b;"
        "}");
}

void Dashboard::loadStatistics()
{
    // Example data - replace with actual statistics
    ui->patientsCountLabel->setText("142");
    ui->appointmentsCountLabel->setText("15");
    ui->billsCountLabel->setText("7");
}

void Dashboard::onPatientRecordsClicked()
{
    emit showPatientRecords();
}

void Dashboard::onAppointmentsButtonClicked()
{
    emit showAppointments();
}

void Dashboard::onReportsButtonClicked()
{
    emit showBillingPage();
}

void Dashboard::onLogoutClicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, tr("Logout"),
                                  tr("Are you sure you want to logout?"),
                                  QMessageBox::Yes|QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        emit logoutRequested();
    }
}

void Dashboard::setUserInfo(const QString &username, bool isAdmin)
{
    currentUsername = username;
    this->isAdmin = isAdmin;
    ui->welcomeLabel->setText(tr("Welcome, %1!").arg(currentUsername));
}

Dashboard::~Dashboard()
{
    delete ui;
}
