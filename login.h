#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

    // Add this if missing
    bool passwordVisible = false;

signals:
    void loginSuccess(const QString &username, bool isAdmin);

private slots:
    void onLoginButtonClicked();
    void togglePasswordVisibility();

private:
    Ui::Login *ui;
};

#endif // LOGIN_H
