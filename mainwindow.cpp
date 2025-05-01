// mainwindow.cpp
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "login.h"
#include "dashboard.h"
#include "adminpage.h"
#include "patientrecords.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_isAdmin(false)
{
    ui->setupUi(this);

    stackedWidget = new QStackedWidget(this);
    setCentralWidget(stackedWidget);

    loginPage = new Login();
    dashboardPage = new Dashboard("", false);
    adminPage = new AdminPage();
    patientRecordsPage = new PatientRecords();

    stackedWidget->addWidget(loginPage);
    stackedWidget->addWidget(dashboardPage);
    stackedWidget->addWidget(adminPage);
    stackedWidget->addWidget(patientRecordsPage);

    connect(loginPage, &Login::loginSuccess, this, &MainWindow::showUserInterface);
    connect(dashboardPage, &Dashboard::logoutRequested, this, &MainWindow::showLogin);
    connect(dashboardPage, &Dashboard::showPatientRecords, this, &MainWindow::showPatientRecords);
    connect(adminPage, &AdminPage::logoutRequested, this, &MainWindow::showLogin);
    connect(patientRecordsPage, &PatientRecords::backToDashboard, this, &MainWindow::backToDashboard);

    showLogin();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showLogin()
{
    stackedWidget->setCurrentWidget(loginPage);
    m_currentUsername.clear();
    m_isAdmin = false;
}

void MainWindow::showUserInterface(const QString &username, bool isAdmin)
{
    m_currentUsername = username;
    m_isAdmin = isAdmin;

    if (isAdmin) {
        stackedWidget->setCurrentWidget(adminPage);
    } else {
        dashboardPage->setUserInfo(username, isAdmin);
        stackedWidget->setCurrentWidget(dashboardPage);
    }
}

void MainWindow::showPatientRecords()
{
    stackedWidget->setCurrentWidget(patientRecordsPage);
}

void MainWindow::backToDashboard()
{
    showUserInterface(m_currentUsername, m_isAdmin);
}
