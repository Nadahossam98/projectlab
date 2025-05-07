#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QWidget>

namespace Ui {
class Dashboard;
}

class Dashboard : public QWidget
{
    Q_OBJECT

public:
    explicit Dashboard(const QString &username, bool isAdmin, QWidget *parent = nullptr);
    ~Dashboard();

    void setUserInfo(const QString &username, bool isAdmin);

signals:
    void showPatientRecords();
    void showAppointments();  // Add this signal
     void showBillingPage();
    void logoutRequested();

private slots:
    void onPatientRecordsClicked();
    void onAppointmentsButtonClicked();
    void onReportsButtonClicked();
    void onLogoutClicked();

private:
    Ui::Dashboard *ui;
    bool isAdmin;
    QString currentUsername;

    void setupUI();
    void loadStatistics();
};

#endif // DASHBOARD_H
