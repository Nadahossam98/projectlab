#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QString>

namespace Ui { class Login; }

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

signals:
    void loginSuccess(const QString &username, const QString &role);

private slots:
    void attemptLogin();

private:
    Ui::Login *ui;
};

#endif // LOGIN_H
