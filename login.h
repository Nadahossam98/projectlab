// login.h
#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>

namespace Ui {
class Login;
}

class Login : public QMainWindow
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

signals:
    void loginSuccess(const QString &username, bool isAdmin);

private slots:
    void onLoginButtonClicked();
    void onSignUpButtonClicked();

private:
    Ui::Login *ui;
    bool validatePassword(const QString &password);
};

#endif
