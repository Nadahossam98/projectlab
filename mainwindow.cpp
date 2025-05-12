#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "login.h"
#include "dashboard.h"
#include "adminpage.h"
#include "patientrecords.h"
#include "AppointmentForm.h"
#include "billingpage.h"
#include "reportspage.h"

#include <QStackedWidget>
#include <QDir>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),

    loginPage(nullptr),
    dashboardPage(nullptr),
    adminPage(nullptr),
    patientRecordsPage(nullptr),
    appointmentForm(nullptr),
    billingPage(nullptr),
    reportsPage(nullptr)
{
    // Create necessary directories
    QDir().mkdir("profile_pics");
    QDir().mkdir("data");

    ui->setupUi(this);
    setWindowTitle("Hospital Management System");
    setMinimumSize(800, 610);
    setMaximumSize(800, 610);

    // Initialize stacked widget
    stackedWidget = new QStackedWidget(this);
    setCentralWidget(stackedWidget);

    // Create all pages
    initializePages();
    setupConnections();

    // Start with login page
    showLogin();

    qDebug() << "MainWindow initialized successfully";
}

MainWindow::~MainWindow()
{
    qDebug() << "MainWindow destructor";
    // Let Qt handle deletion of child widgets through parent-child hierarchy
    delete ui;
}

void MainWindow::initializePages()
{
    qDebug() << "Initializing pages...";
    // Create pages with proper parent hierarchy
    loginPage = new Login(stackedWidget);
    dashboardPage = new Dashboard(stackedWidget);
    adminPage = new AdminPage(stackedWidget);
    patientRecordsPage = new PatientRecords(stackedWidget);
    reportsPage = new ReportsPage(stackedWidget);

    // Add pages to stacked widget
    stackedWidget->addWidget(loginPage);
    stackedWidget->addWidget(dashboardPage);
    stackedWidget->addWidget(adminPage);
    stackedWidget->addWidget(patientRecordsPage);
    stackedWidget->addWidget(reportsPage);

    qDebug() << "All pages initialized";
}

void MainWindow::setupConnections()
{
    qDebug() << "Setting up connections...";

    // Login connections
    if (!connect(loginPage, &Login::loginSuccess,
                 this, &MainWindow::showUserInterface)) {
        qWarning() << "Failed to connect loginSuccess signal";
    }

    // Dashboard connections
    if (!connect(dashboardPage, &Dashboard::logoutRequested,
                 this, &MainWindow::showLogin)) {
        qWarning() << "Failed to connect logoutRequested signal";
    }

    if (!connect(dashboardPage, &Dashboard::showPatientRecords,
                 this, &MainWindow::showPatientRecords)) {
        qWarning() << "Failed to connect showPatientRecords signal";
    }

    if (!connect(dashboardPage, &Dashboard::showAppointmentForm,
                 this, &MainWindow::showAppointmentForm)) {
        qWarning() << "Failed to connect showAppointmentForm signal";
    }

    if (!connect(dashboardPage, &Dashboard::showBillingPage,
                 this, &MainWindow::showBillingPage)) {
        qWarning() << "Failed to connect showBillingPage signal";
    }

    if (!connect(dashboardPage, &Dashboard::showReportsPage,
                 this, &MainWindow::showReportsPage)) {
        qWarning() << "Failed to connect showReportsPage signal";
    }

    // Admin page connections
    if (!connect(adminPage, &AdminPage::logoutRequested,
                 this, &MainWindow::showLogin)) {
        qWarning() << "Failed to connect admin logoutRequested signal";
    }

    qDebug() << "All connections established";
}

void MainWindow::showLogin()
{
    qDebug() << "Showing login page";
    if (stackedWidget && loginPage) {
        stackedWidget->setCurrentWidget(loginPage);
        m_currentUsername.clear();
        m_currentUserRole.clear();
    } else {
        qCritical() << "Stacked widget or login page not initialized";
    }
}


void MainWindow::showUserInterface(const QString &username, const QString &role)
{
    qDebug() << "Showing user interface for:" << username << "role:" << role;
    m_currentUsername = username;
    m_currentUserRole = role;

    if (role == "Admin") {
        if (adminPage) {
            stackedWidget->setCurrentWidget(adminPage);
        } else {
            qCritical() << "Admin page not initialized";
        }
    } else {
        if (dashboardPage) {
            dashboardPage->setUserInfo(username, role);
            stackedWidget->setCurrentWidget(dashboardPage);
        } else {
            qCritical() << "Dashboard page not initialized";
        }
    }
}

void MainWindow::showPatientRecords()
{
    qDebug() << "Showing patient records";
    if (!patientRecordsPage) {
        patientRecordsPage = new PatientRecords(stackedWidget);
        stackedWidget->addWidget(patientRecordsPage);
    }

    // Always set up these connections and access level
    if (!connect(patientRecordsPage, &PatientRecords::backToDashboard,
                 this, &MainWindow::backToDashboard, Qt::UniqueConnection)) {
        qWarning() << "Failed to connect backToDashboard signal";
    }

    patientRecordsPage->setAccessLevel(m_currentUserRole);
    stackedWidget->setCurrentWidget(patientRecordsPage);
}
void MainWindow::showAppointmentForm()
{
    qDebug() << "Showing appointment form";
    if (!appointmentForm) {
        qDebug() << "Creating new AppointmentForm instance";
        appointmentForm = new AppointmentForm(stackedWidget);
        stackedWidget->addWidget(appointmentForm);

        if (!connect(appointmentForm, &AppointmentForm::appointmentScheduled,
                     dashboardPage, &Dashboard::updateAppointmentCount)) {
            qWarning() << "Failed to connect appointmentScheduled signal";
        }

        if (!connect(appointmentForm, &AppointmentForm::finished,
                     this, &MainWindow::backToDashboard)) {
            qWarning() << "Failed to connect finished signal";
        }
    }
    if (appointmentForm) {
        appointmentForm->resetForm();
        stackedWidget->setCurrentWidget(appointmentForm);
    } else {
        qCritical() << "Appointment form creation failed";
    }
}

void MainWindow::showBillingPage()
{
    qDebug() << "Showing billing page";
    if (!billingPage) {
        billingPage = new BillingPage(stackedWidget);
        stackedWidget->addWidget(billingPage);

        if (!connect(billingPage, &BillingPage::backToDashboard,
                     this, &MainWindow::backToDashboard)) {
            qWarning() << "Failed to connect backToDashboard signal";
        }
    }
    stackedWidget->setCurrentWidget(billingPage);
}

void MainWindow::showReportsPage()
{
    qDebug() << "Showing reports page";
    if (!reportsPage) {
        reportsPage = new ReportsPage(stackedWidget);
        stackedWidget->addWidget(reportsPage);
    }

    // Always set up this connection
    if (!connect(reportsPage, &ReportsPage::backToDashboard,
                 this, &MainWindow::backToDashboard, Qt::UniqueConnection)) {
        qWarning() << "Failed to connect backToDashboard signal";
    }

    reportsPage->generateReports();
    stackedWidget->setCurrentWidget(reportsPage);
}

void MainWindow::backToDashboard()
{
    qDebug() << "Returning to dashboard";
    showUserInterface(m_currentUsername, m_currentUserRole);
}
