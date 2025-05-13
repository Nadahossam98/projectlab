#ifndef BILLINGPAGE_H
#define BILLINGPAGE_H

#include <QWidget>
#include <QTableWidgetItem>
#include <QTextStream>  // Needed for QTextStream used in writeBillToStream

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

    void setupTable();
    void setupConnections();
    bool validatePaymentDetails();
    void updateBillStatus(int row, const QString &status);
    void clearForm();
    void writeBillToStream(QTextStream &out, int row); // <- Add this line
};

#endif // BILLINGPAGE_H
