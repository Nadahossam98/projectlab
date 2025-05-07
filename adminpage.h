#ifndef ADMINPAGE_H
#define ADMINPAGE_H

#include <QMainWindow>  // Changed back to QMainWindow
#include <QStringList>

namespace Ui {
class AdminPage;
}

class AdminPage : public QMainWindow  // Changed back to QMainWindow
{
    Q_OBJECT

public:
    explicit AdminPage(QWidget *parent = nullptr);
    ~AdminPage();

signals:
    void logoutRequested();
private slots:
    void on_addUserButton_clicked();
    void on_listUsersButton_clicked();
    void on_deleteUserButton_clicked();
    void on_logoutButton_clicked();

private:
    Ui::AdminPage *ui;
    QList<QStringList> usersList;
    bool dataModified;
    void closeEvent(QCloseEvent *event) override;  // Added override
    bool saveUsersToFile();
    void loadUsers();
    bool validatePassword(const QString &password);
    bool userExists(const QString &username);
    bool isCurrentUserAdmin() const;
};

#endif // ADMINPAGE_H
