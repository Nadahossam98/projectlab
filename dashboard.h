#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QGroupBox>

class PatientRecords; // Forward declaration

namespace Ui {
class Dashboard;
}

class Dashboard : public QWidget
{
    Q_OBJECT

public:
    explicit Dashboard(QWidget *parent = nullptr);
    ~Dashboard();

    void setUserInfo(const QString &username, const QString &role);
    void connectPatientRecords(PatientRecords* patientRecords);

public slots:
    void updateAppointmentCount();
    void updatePatientCount(int count);

signals:
    void logoutRequested();
    void showPatientRecords();
    void showAppointmentForm();
    void showBillingPage();
    void showReportsPage();

private slots:
    void onChangeProfilePicture();

private:
    Ui::Dashboard *ui;

    QLabel *m_profilePicLabel;
    QLabel *m_welcomeLabel;

    QGroupBox *m_patientsCard;
    QGroupBox *m_appointmentsCard;
    QGroupBox *m_billsCard;
    QGroupBox *m_reportsCard;
    int m_patientsCount = 0;
    int m_appointmentsCount = 0;
    int m_billsCount = 0;
    int m_reportsCount = 0;

    // Navigation Buttons
    QPushButton *m_patientsButton;
    QPushButton *m_appointmentsButton;
    QPushButton *m_billingButton;
    QPushButton *m_reportsButton;
    QPushButton *m_logoutButton;
    QPushButton *m_changeProfileButton;
    void on_dashboardButton_clicked() ;
    void setupConnections();
    void loadProfilePicture(const QString &username);
};

#endif // DASHBOARD_H
