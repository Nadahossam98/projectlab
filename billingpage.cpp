#include "billingpage.h"
#include "ui_billingpage.h"
#include <QDoubleValidator>
#include <QDate>
#include <QTableWidgetItem>

BillingPage::BillingPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BillingPage)
{
    ui->setupUi(this);

    // Setup validators
    ui->treatmentCostInput->setValidator(new QDoubleValidator(0, 999999, 2, this));
    ui->insuranceCoverageInput->setValidator(new QDoubleValidator(0, 100, 2, this));
    connect(ui->backButton, &QPushButton::clicked,
            this, &BillingPage::backToDashboard);
    setupTable();
    setupConnections();

    // Set current date
    ui->dateInput->setDate(QDate::currentDate());
}

BillingPage::~BillingPage()
{
    delete ui;
}

void BillingPage::setupTable()
{
    QStringList headers = {"Date", "Patient ID", "Description",
                           "Treatment Cost", "Insurance %",
                           "Amount Due", "Status"};
    ui->billsTable->setColumnCount(headers.size());
    ui->billsTable->setHorizontalHeaderLabels(headers);
    ui->billsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->billsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->billsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void BillingPage::setupConnections()
{
    connect(ui->addBillButton, &QPushButton::clicked,
            this, &BillingPage::onAddBillClicked);
    connect(ui->markPaidButton, &QPushButton::clicked,
            this, &BillingPage::onMarkAsPaidClicked);
    connect(ui->calculateButton, &QPushButton::clicked,
            this, &BillingPage::onCalculateTotalClicked);
    connect(ui->backButton, &QPushButton::clicked,
            this, &BillingPage::backToDashboard);

    // Real-time validation
    connect(ui->patientIdInput, &QLineEdit::textChanged,
            this, &BillingPage::validateInputs);
    connect(ui->treatmentCostInput, &QLineEdit::textChanged,
            this, &BillingPage::validateInputs);
}

void BillingPage::onAddBillClicked()
{
    if (!validatePaymentDetails()) return;

    double cost = ui->treatmentCostInput->text().toDouble();
    double insurance = ui->insuranceCoverageInput->text().toDouble();
    double amountDue = cost * (1 - insurance/100);

    int row = ui->billsTable->rowCount();
    ui->billsTable->insertRow(row);

    ui->billsTable->setItem(row, 0, new QTableWidgetItem(ui->dateInput->date().toString("dd/MM/yyyy")));
    ui->billsTable->setItem(row, 1, new QTableWidgetItem(ui->patientIdInput->text()));
    ui->billsTable->setItem(row, 2, new QTableWidgetItem(ui->descriptionInput->toPlainText()));
    ui->billsTable->setItem(row, 3, new QTableWidgetItem(QString::number(cost, 'f', 2)));
    ui->billsTable->setItem(row, 4, new QTableWidgetItem(QString::number(insurance, 'f', 2) + "%"));
    ui->billsTable->setItem(row, 5, new QTableWidgetItem(QString::number(amountDue, 'f', 2)));
    updateBillStatus(row, "Pending");

    clearForm();
}

void BillingPage::onMarkAsPaidClicked()
{
    int currentRow = ui->billsTable->currentRow();
    if (currentRow >= 0) {
        updateBillStatus(currentRow, "Paid");
    } else {
        QMessageBox::warning(this, "Warning", "Please select a bill to mark as paid");
    }
}

void BillingPage::onCalculateTotalClicked()
{
    double totalPending = 0;
    double totalPaid = 0;

    for (int i = 0; i < ui->billsTable->rowCount(); ++i) {
        QTableWidgetItem *amountItem = ui->billsTable->item(i, 5);
        QTableWidgetItem *statusItem = ui->billsTable->item(i, 6);

        if (amountItem && statusItem) {
            double amount = amountItem->text().toDouble();
            if (statusItem->text() == "Pending") {
                totalPending += amount;
            } else {
                totalPaid += amount;
            }
        }
    }

    ui->totalPendingLabel->setText(QString("$%1").arg(totalPending, 0, 'f', 2));
    ui->totalPaidLabel->setText(QString("$%1").arg(totalPaid, 0, 'f', 2));
}

bool BillingPage::validatePaymentDetails()
{
    if (ui->patientIdInput->text().isEmpty()) {
        QMessageBox::warning(this, "Error", "Patient ID is required");
        return false;
    }

    if (ui->treatmentCostInput->text().toDouble() <= 0) {
        QMessageBox::warning(this, "Error", "Treatment cost must be positive");
        return false;
    }

    double insurance = ui->insuranceCoverageInput->text().toDouble();
    if (insurance < 0 || insurance > 100) {
        QMessageBox::warning(this, "Error", "Insurance coverage must be between 0-100%");
        return false;
    }

    return true;
}

void BillingPage::validateInputs()
{
    bool valid = !ui->patientIdInput->text().isEmpty() &&
                 !ui->treatmentCostInput->text().isEmpty() &&
                 ui->treatmentCostInput->text().toDouble() > 0;

    ui->addBillButton->setEnabled(valid);
}

void BillingPage::updateBillStatus(int row, const QString &status)
{
    QTableWidgetItem *statusItem = new QTableWidgetItem(status);
    ui->billsTable->setItem(row, 6, statusItem);

    if (status == "Paid") {
        statusItem->setForeground(Qt::darkGreen);
    } else {
        statusItem->setForeground(Qt::black);
    }
}

void BillingPage::clearForm()
{
    ui->patientIdInput->clear();
    ui->treatmentCostInput->clear();
    ui->insuranceCoverageInput->clear();
    ui->descriptionInput->clear();
    ui->dateInput->setDate(QDate::currentDate());
}
