#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <qstackedwidget.h>


class Login;
class Dashboard;
class AdminPage;
class PatientRecords;
class AppointmentForm;
class BillingPage;
class ReportsPage;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



private slots:
    void showLogin();
    void showUserInterface(const QString &username, const QString &role);
    void showPatientRecords();
    void showAppointmentForm();
    void showBillingPage();
    void showReportsPage();
    void backToDashboard();

private:
    void initializePages();
    void setupConnections();

    Ui::MainWindow *ui;

    QStackedWidget *stackedWidget;

    // Pages
    Login *loginPage;
    Dashboard *dashboardPage;
    AdminPage *adminPage;
    PatientRecords *patientRecordsPage;
    AppointmentForm *appointmentForm;
    BillingPage *billingPage;
    ReportsPage *reportsPage;

    QString m_currentUsername;
    QString m_currentUserRole;
};

#endif // MAINWINDOW_H
