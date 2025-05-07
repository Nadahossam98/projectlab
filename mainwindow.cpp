#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "login.h"
#include "dashboard.h"
#include "adminpage.h"
#include "patientrecords.h"
#include "appointmentform.h"
#include "billingpage.h"
#include <QStackedWidget>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_isAdmin(false),
    m_currentUsername("")
{
    ui->setupUi(this);

    // Create stacked widget for page management
    stackedWidget = new QStackedWidget(this);
    setCentralWidget(stackedWidget);

    // Initialize all application pages
    initializePages();

    // Set up all signal-slot connections
    setupConnections();

    // Start with login page
    showLogin();
}

void MainWindow::initializePages()
{
    loginPage = new Login(stackedWidget);
    dashboardPage = new Dashboard("", false, stackedWidget);
    adminPage = new AdminPage(stackedWidget);
    patientRecordsPage = new PatientRecords(stackedWidget);
    appointmentForm = new appointmentform(stackedWidget);
    billingPage = new BillingPage(stackedWidget);

    // Add pages to stacked widget in logical order
    stackedWidget->addWidget(loginPage);
    stackedWidget->addWidget(dashboardPage);
    stackedWidget->addWidget(adminPage);
    stackedWidget->addWidget(patientRecordsPage);
    stackedWidget->addWidget(appointmentForm);
    stackedWidget->addWidget(billingPage);
}

void MainWindow::setupConnections()
{
    // Login connections
    connect(loginPage, &Login::loginSuccess,
            this, &MainWindow::showUserInterface);

    // Dashboard connections
    connect(dashboardPage, &Dashboard::logoutRequested,
            this, &MainWindow::showLogin);
    connect(dashboardPage, &Dashboard::showPatientRecords,
            this, &MainWindow::showPatientRecords);
    connect(dashboardPage, &Dashboard::showAppointments,
            this, &MainWindow::showAppointmentForm);
    connect(dashboardPage, &Dashboard::showBillingPage,
            this, &MainWindow::showBillingPage);

    // Admin page connection
    connect(adminPage, &AdminPage::logoutRequested,
            this, &MainWindow::showLogin);

    // Patient records connection
    connect(patientRecordsPage, &PatientRecords::backToDashboard,
            this, &MainWindow::backToDashboard);

    // Appointment form connections
    connect(appointmentForm, &appointmentform::appointmentScheduled,
            this, &MainWindow::backToDashboard);
    connect(appointmentForm, &appointmentform::cancelled,
            this, &MainWindow::backToDashboard);

    // Billing page connection
    connect(billingPage, &BillingPage::backToDashboard,
            this, &MainWindow::backToDashboard);
}

void MainWindow::showBillingPage()
{
    stackedWidget->setCurrentWidget(billingPage);
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

void MainWindow::showAppointmentForm()
{
    stackedWidget->setCurrentWidget(appointmentForm);
    appointmentForm->resetForm();
}

void MainWindow::backToDashboard()
{
    showUserInterface(m_currentUsername, m_isAdmin);
}

MainWindow::~MainWindow()
{
    delete ui;
}
