// mainwindow.h
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class Login;
class Dashboard;
class AdminPage;
class PatientRecords;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void showLogin();
    void showUserInterface(const QString &username, bool isAdmin);
    void showPatientRecords();
    void backToDashboard();

private:
    Ui::MainWindow *ui;
    QStackedWidget *stackedWidget;
    Login *loginPage;
    Dashboard *dashboardPage;
    AdminPage *adminPage;
    PatientRecords *patientRecordsPage;
    QString m_currentUsername;
    bool m_isAdmin;
};

#endif
