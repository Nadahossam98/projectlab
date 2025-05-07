#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>

// Forward declarations
namespace Ui {
class MainWindow;
}
class Login;
class Dashboard;
class AdminPage;
class PatientRecords;
class appointmentform;
class BillingPage;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void showLogin();
    void showUserInterface(const QString &username, bool isAdmin);
    void showPatientRecords();
    void showAppointmentForm();
    void showBillingPage();
    void backToDashboard();

private:
    Ui::MainWindow *ui;
    QStackedWidget *stackedWidget;

    // Page widgets
    Login *loginPage;
    Dashboard *dashboardPage;
    AdminPage *adminPage;
    PatientRecords *patientRecordsPage;
    appointmentform *appointmentForm;
    BillingPage *billingPage;

    // User state
    QString m_currentUsername;
    bool m_isAdmin;

    void initializePages();
    void setupConnections();
};

#endif // MAINWINDOW_H
