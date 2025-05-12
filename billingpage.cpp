#include "billingpage.h"
#include "ui_billingpage.h"

#include <QMessageBox>
#include <QDate>
#include <QHeaderView>
#include <QDoubleValidator>

/*
 * BillingPage implements a billing management interface for healthcare billing.
 * It allows adding new bills, marking bills as paid, calculating totals, and validates all inputs.
 */

BillingPage::BillingPage(QWidget *parent)
    : QWidget(parent),
    ui(new Ui::BillingPage)
{
    ui->setupUi(this);
    this->setFixedSize(800, 600); // Set a fixed window size for consistent layout

    // Set input validators for numeric fields
    ui->treatmentCostInput->setValidator(new QDoubleValidator(0, 999999, 2, this));
    ui->insuranceCoverageInput->setValidator(new QDoubleValidator(0, 100, 2, this));

    // Set the date input to the current date by default
    ui->dateInput->setDate(QDate::currentDate());

    // Initialize the bills table and connect UI signals to slots
    setupTable();
    setupConnections();

    // Set initial state of the form
    validateInputs();
}

BillingPage::~BillingPage()
{
    delete ui;
}

// Set up the bills table with headers and behavior
void BillingPage::setupTable()
{
    // Define table headers
    QStringList headers = {
        "Date", "Patient ID", "Description",
        "Treatment Cost", "Insurance %",
        "Amount Due", "Status"
    };
    ui->billsTable->setColumnCount(headers.size());
    ui->billsTable->setHorizontalHeaderLabels(headers);

    // Stretch columns to fill the table width
    ui->billsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // Configure selection and editing behavior
    ui->billsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->billsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->billsTable->setSelectionMode(QAbstractItemView::SingleSelection);
}

// Connect UI elements to their respective slots
void BillingPage::setupConnections()
{
    // Button actions
    connect(ui->addBillButton, &QPushButton::clicked, this, &BillingPage::onAddBillClicked);
    connect(ui->markPaidButton, &QPushButton::clicked, this, &BillingPage::onMarkAsPaidClicked);
    connect(ui->calculateButton, &QPushButton::clicked, this, &BillingPage::onCalculateTotalClicked);
    connect(ui->backButton, &QPushButton::clicked, this, &BillingPage::backToDashboard);

    // Input validation triggers
    connect(ui->patientIdInput, &QLineEdit::textChanged, this, &BillingPage::validateInputs);
    connect(ui->treatmentCostInput, &QLineEdit::textChanged, this, &BillingPage::validateInputs);
    connect(ui->insuranceCoverageInput, &QLineEdit::textChanged, this, &BillingPage::validateInputs);
}

// Slot: Add a new bill to the table after validating inputs
void BillingPage::onAddBillClicked()
{
    if (!validatePaymentDetails()) {
        return;
    }

    // Gather input values
    QDate date = ui->dateInput->date();
    QString patientId = ui->patientIdInput->text();
    QString description = ui->descriptionInput->toPlainText();
    double cost = ui->treatmentCostInput->text().toDouble();
    double insurance = ui->insuranceCoverageInput->text().toDouble();
    double amountDue = cost * (1 - insurance / 100.0);

    // Insert new row at the end
    int row = ui->billsTable->rowCount();
    ui->billsTable->insertRow(row);

    // Populate the row with bill details
    ui->billsTable->setItem(row, 0, new QTableWidgetItem(date.toString("dd/MM/yyyy")));
    ui->billsTable->setItem(row, 1, new QTableWidgetItem(patientId));
    ui->billsTable->setItem(row, 2, new QTableWidgetItem(description));
    ui->billsTable->setItem(row, 3, new QTableWidgetItem(QString::number(cost, 'f', 2)));
    ui->billsTable->setItem(row, 4, new QTableWidgetItem(QString::number(insurance, 'f', 2) + "%"));
    ui->billsTable->setItem(row, 5, new QTableWidgetItem(QString::number(amountDue, 'f', 2)));

    // Set status to "Pending"
    updateBillStatus(row, "Pending");

    // Clear form for the next entry
    clearForm();
}

// Slot: Mark the selected bill as paid
void BillingPage::onMarkAsPaidClicked()
{
    int currentRow = ui->billsTable->currentRow();
    if (currentRow >= 0) {
        updateBillStatus(currentRow, "Paid");
    } else {
        QMessageBox::warning(this, "Warning", "Please select a bill to mark as paid");
    }
}

// Slot: Calculate and display the total amounts for pending and paid bills
void BillingPage::onCalculateTotalClicked()
{
    double totalPending = 0;
    double totalPaid = 0;

    for (int i = 0; i < ui->billsTable->rowCount(); ++i) {
        QTableWidgetItem *amountItem = ui->billsTable->item(i, 5); // Amount Due
        QTableWidgetItem *statusItem = ui->billsTable->item(i, 6); // Status

        if (amountItem && statusItem) {
            double amount = amountItem->text().toDouble();
            if (statusItem->text() == "Pending") {
                totalPending += amount;
            } else if (statusItem->text() == "Paid") {
                totalPaid += amount;
            }
        }
    }

    // Update UI with calculated totals
    ui->totalPendingLabel->setText(QString("$%1").arg(totalPending, 0, 'f', 2));
    ui->totalPaidLabel->setText(QString("$%1").arg(totalPaid, 0, 'f', 2));
}

// Validates payment details before adding a bill
bool BillingPage::validatePaymentDetails()
{
    // Patient ID must not be empty
    if (ui->patientIdInput->text().isEmpty()) {
        QMessageBox::warning(this, "Error", "Patient ID is required");
        return false;
    }

    // Treatment cost must be positive
    if (ui->treatmentCostInput->text().isEmpty() ||
        ui->treatmentCostInput->text().toDouble() <= 0) {
        QMessageBox::warning(this, "Error", "Treatment cost must be positive");
        return false;
    }

    // Insurance coverage must be between 0 and 100
    double insurance = ui->insuranceCoverageInput->text().toDouble();
    if (insurance < 0 || insurance > 100) {
        QMessageBox::warning(this, "Error", "Insurance coverage must be between 0-100%");
        return false;
    }

    return true;
}

// Enables/disables the Add Bill button based on form validity
void BillingPage::validateInputs()
{
    bool valid = !ui->patientIdInput->text().isEmpty() &&
                 !ui->treatmentCostInput->text().isEmpty() &&
                 ui->treatmentCostInput->text().toDouble() > 0;
    ui->addBillButton->setEnabled(valid);
}

// Updates the status of a bill and sets the color accordingly
void BillingPage::updateBillStatus(int row, const QString &status)
{
    QTableWidgetItem *statusItem = new QTableWidgetItem(status);
    ui->billsTable->setItem(row, 6, statusItem);

    // Set color and font based on status
    if (status == "Paid") {
        statusItem->setForeground(Qt::darkGreen);
        statusItem->setFont(QFont("Segoe UI", 9, QFont::Bold));
    } else {
        statusItem->setForeground(Qt::darkRed);
        statusItem->setFont(QFont("Segoe UI", 9));
    }
}

// Clears all input fields and resets the form
void BillingPage::clearForm()
{
    ui->patientIdInput->clear();
    ui->treatmentCostInput->clear();
    ui->insuranceCoverageInput->clear();
    ui->descriptionInput->clear();
    ui->dateInput->setDate(QDate::currentDate());
    ui->addBillButton->setEnabled(false);
}
