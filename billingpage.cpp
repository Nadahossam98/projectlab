#include "billingpage.h"
#include "ui_billingpage.h"

#include <QMessageBox>
#include <QDate>
#include <QHeaderView>
#include <QDoubleValidator>
#include <QFile>
#include <QTextStream>
#include <QDir>

BillingPage::BillingPage(QWidget *parent)
    : QWidget(parent),
    ui(new Ui::BillingPage)
{
    ui->setupUi(this);
    this->setFixedSize(800, 600);

    ui->treatmentCostInput->setValidator(new QDoubleValidator(0, 999999, 2, this));
    ui->insuranceCoverageInput->setValidator(new QDoubleValidator(0, 100, 2, this));
    ui->dateInput->setDate(QDate::currentDate());

    setupTable();
    setupConnections();
    validateInputs();
}

BillingPage::~BillingPage()
{
    delete ui;
}

void BillingPage::setupTable()
{
    QStringList headers = {
        "Date", "Patient ID", "Description",
        "Treatment Cost", "Insurance %",
        "Amount Due", "Status"
    };
    ui->billsTable->setColumnCount(headers.size());
    ui->billsTable->setHorizontalHeaderLabels(headers);
    ui->billsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->billsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->billsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->billsTable->setSelectionMode(QAbstractItemView::SingleSelection);
}

void BillingPage::setupConnections()
{
    connect(ui->addBillButton, &QPushButton::clicked, this, &BillingPage::onAddBillClicked);
    connect(ui->markPaidButton, &QPushButton::clicked, this, &BillingPage::onMarkAsPaidClicked);
    connect(ui->calculateButton, &QPushButton::clicked, this, &BillingPage::onCalculateTotalClicked);
    connect(ui->backButton, &QPushButton::clicked, this, &BillingPage::backToDashboard);

    connect(ui->patientIdInput, &QLineEdit::textChanged, this, &BillingPage::validateInputs);
    connect(ui->treatmentCostInput, &QLineEdit::textChanged, this, &BillingPage::validateInputs);
    connect(ui->insuranceCoverageInput, &QLineEdit::textChanged, this, &BillingPage::validateInputs);
}

void BillingPage::onAddBillClicked()
{
    if (!validatePaymentDetails()) {
        return;
    }

    QDate date = ui->dateInput->date();
    QString patientId = ui->patientIdInput->text();
    QString description = ui->descriptionInput->toPlainText();
    double cost = ui->treatmentCostInput->text().toDouble();
    double insurance = ui->insuranceCoverageInput->text().toDouble();
    double amountDue = cost * (1 - insurance / 100.0);

    int row = ui->billsTable->rowCount();
    ui->billsTable->insertRow(row);
    ui->billsTable->setItem(row, 0, new QTableWidgetItem(date.toString("dd/MM/yyyy")));
    ui->billsTable->setItem(row, 1, new QTableWidgetItem(patientId));
    ui->billsTable->setItem(row, 2, new QTableWidgetItem(description));
    ui->billsTable->setItem(row, 3, new QTableWidgetItem(QString::number(cost, 'f', 2)));
    ui->billsTable->setItem(row, 4, new QTableWidgetItem(QString::number(insurance, 'f', 2) + "%"));
    ui->billsTable->setItem(row, 5, new QTableWidgetItem(QString::number(amountDue, 'f', 2)));

    updateBillStatus(row, "Pending");
    clearForm();
}

void BillingPage::onMarkAsPaidClicked()
{
    int currentRow = ui->billsTable->currentRow();
    if (currentRow < 0) {
        QMessageBox::warning(this, "Warning", "Please select a bill to mark as paid");
        return;
    }

    updateBillStatus(currentRow, "Paid");

    QDir dir("data");
    if (!dir.exists()) {
        dir.mkpath(".");
    }

    QString filePath = "C:/Users/osama/Downloads/projectlab/projectlab/billing_records.csv";
    QFile billingFile(filePath);
    bool fileExists = QFile::exists(filePath);

    if (!fileExists) {
        if (billingFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&billingFile);
            out << "Date,Patient ID,Description,Treatment Cost,Insurance %,Amount Due,Status\n";
            writeBillToStream(out, currentRow);
            billingFile.close();
        } else {
            QMessageBox::warning(this, "File Error", "Unable to create billing records file.");
        }
    } else {
        if (billingFile.open(QIODevice::Append | QIODevice::Text)) {
            QTextStream out(&billingFile);
            writeBillToStream(out, currentRow);
            billingFile.close();
        } else {
            QMessageBox::warning(this, "File Error", "Unable to write to billing records file.");
        }
    }
}

void BillingPage::writeBillToStream(QTextStream &out, int row)
{
    QStringList fields;
    for (int col = 0; col < ui->billsTable->columnCount(); ++col) {
        QTableWidgetItem *item = ui->billsTable->item(row, col);
        fields << (item ? item->text().replace(",", " ") : "");
    }
    out << fields.join(",") << "\n";
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
            } else if (statusItem->text() == "Paid") {
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

    if (ui->treatmentCostInput->text().isEmpty() ||
        ui->treatmentCostInput->text().toDouble() <= 0) {
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
        statusItem->setFont(QFont("Segoe UI", 9, QFont::Bold));
    } else {
        statusItem->setForeground(Qt::darkRed);
        statusItem->setFont(QFont("Segoe UI", 9));
    }
}

void BillingPage::clearForm()
{
    ui->patientIdInput->clear();
    ui->treatmentCostInput->clear();
    ui->insuranceCoverageInput->clear();
    ui->descriptionInput->clear();
    ui->dateInput->setDate(QDate::currentDate());
    ui->addBillButton->setEnabled(false);
}

