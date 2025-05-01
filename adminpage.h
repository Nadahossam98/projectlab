#ifndef ADMINPAGE_H
#define ADMINPAGE_H

#include <QMainWindow>
#include <QList>
#include <QStringList>
#include <QCloseEvent>

namespace Ui {
class AdminPage;
}

class AdminPage : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdminPage(QMainWindow *parent = nullptr);
    ~AdminPage();

    bool validatePassword(const QString &password);
    bool userExists(const QString &username);

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
    void loadUsers();

    bool saveUsersToFile();

protected:
    void closeEvent(QCloseEvent *event) override;
};

#endif
