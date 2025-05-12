#ifndef ADMINPAGE_H
#define ADMINPAGE_H

#include <QWidget>  // Use this instead of QMainWindow

namespace Ui {
class AdminPage;
}

class AdminPage : public QWidget {
    Q_OBJECT
public:
    enum UserRole {
        Admin,
        Doctor,
        Receptionist
    };
    Q_ENUM(UserRole)
     explicit AdminPage(QWidget *parent = nullptr);
    ~AdminPage();

signals:
    void logoutRequested();

public slots:
    void on_addUserButton_clicked();
    void on_deleteUserButton_clicked();
    void on_logoutButton_clicked();


private:
    Ui::AdminPage *ui;
    QList<QStringList> usersList;
    void initializeUserData();
    bool validatePassword(const QString &password);
    bool userExists(const QString &username);
    bool saveUsersToFile();
    void loadUsers();
    void refreshUserList();
    void closeEvent(QCloseEvent *event) override;
};

#endif // ADMINPAGE_H
