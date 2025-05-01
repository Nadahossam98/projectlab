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

    connect(ui->patientsButton, &QPushButton::clicked,
            this, &Dashboard::onPatientRecordsClicked);
    connect(ui->appointmentsButton, &QPushButton::clicked,
            this, &Dashboard::onAppointmentsButtonClicked);
    connect(ui->reportsButton, &QPushButton::clicked,
            this, &Dashboard::onReportsButtonClicked);
}

void Dashboard::setupUI()
{
    ui->welcomeLabel->setText(tr("Welcome, %1!").arg(currentUsername));

    ui->reportsButton->setVisible(isAdmin);
}

void Dashboard::loadStatistics()
{
    ui->patientsCountLabel->setText("142");
    ui->appointmentsCountLabel->setText("15");
    ui->billsCountLabel->setText("7");
}

void Dashboard::onPatientRecordsClicked()
{
    emit showPatientRecords();
    this->hide();
}

void Dashboard::onAppointmentsButtonClicked()
{
    QMessageBox::information(this, tr("Appointments"),
                             tr("Appointment scheduling module would open here"));
}

void Dashboard::onReportsButtonClicked()
{
    QMessageBox::information(this, tr("Reports"),
                             tr("Report generation module would open here"));
}


void Dashboard::setUserInfo(const QString &username, bool isAdmin)
{
    currentUsername = username;
    this->isAdmin = isAdmin;
    ui->welcomeLabel->setText(tr("Welcome, %1!").arg(currentUsername));
    ui->reportsButton->setVisible(isAdmin);
}
Dashboard::~Dashboard()
{
    delete ui;
}
