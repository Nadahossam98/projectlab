#ifndef BILLINGPAGE_H
#define BILLINGPAGE_H

#include <QWidget>
#include <QMessageBox>

namespace Ui {
class BillingPage;
}

class BillingPage : public QWidget
{
    Q_OBJECT

public:
    explicit BillingPage(QWidget *parent = nullptr);
    ~BillingPage();

signals:
    void backToDashboard();

private slots:
    void onAddBillClicked();
    void onMarkAsPaidClicked();
    void onCalculateTotalClicked();
    void validateInputs();

private:
    Ui::BillingPage *ui;
    void setupConnections();
    void setupTable();
    void clearForm();
    bool validatePaymentDetails();
    void updateBillStatus(int row, const QString &status);
};

#endif // BILLINGPAGE_H
