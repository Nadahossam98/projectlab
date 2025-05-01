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
    void setUserInfo(const QString &username, bool isAdmin);

    ~Dashboard();

signals:
    void logoutRequested();
    void showPatientRecords();

private slots:
    void onPatientRecordsClicked();
    void onAppointmentsButtonClicked();
    void onReportsButtonClicked();

private:
    Ui::Dashboard *ui;
    bool isAdmin;
    QString currentUsername;
    void setupUI();
    void loadStatistics();
};

#endif
