#include "patientrecords.h"
#include "ui_patientrecords.h"

#include <QStandardItemModel>
#include <QSortFilterProxyModel>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QDate>
#include <QMessageBox>
#include <QHeaderView>
#include <QRegularExpression>

// --- PatientRecords Implementation ---

PatientRecords::PatientRecords(QWidget *parent)
    : QWidget(parent),
    ui(new Ui::PatientRecords),
    model(new QStandardItemModel(this)),
    proxyModel(new QSortFilterProxyModel(this)),
    currentUserRole("")
{
    ui->setupUi(this);
    this->setFixedSize(800, 600);

    // Set up models and table view
    proxyModel->setSourceModel(model);
    ui->patientsTableView->setModel(proxyModel);
    setupTableView();
    loadDataFromFile();

    // Set up filter options for searching
    ui->filterComboBox->addItems({"Name", "Doctor", "Medical Condition"});

    // Connect buttons to their respective slots
    connect(ui->searchButton, &QPushButton::clicked, this, &PatientRecords::onSearchClicked);
    connect(ui->addButton, &QPushButton::clicked, this, &PatientRecords::onAddClicked);
    connect(ui->editButton, &QPushButton::clicked, this, &PatientRecords::onEditClicked);
    connect(ui->deleteButton, &QPushButton::clicked, this, &PatientRecords::onDeleteClicked);
    connect(ui->backButton, &QPushButton::clicked, this, &PatientRecords::onBackClicked);
}

PatientRecords::~PatientRecords()
{
    delete ui;
}

void PatientRecords::setAccessLevel(const QString &role)
{
    currentUserRole = role;
    bool canEdit = (role == "Admin" || role == "Doctor");
    bool canDelete = (role == "Admin" || role == "Doctor");

    ui->addButton->setEnabled(canEdit);
    ui->editButton->setEnabled(canEdit);
    ui->deleteButton->setEnabled(canDelete);
}

int PatientRecords::getPatientCount() const
{
    return model->rowCount();
}

void PatientRecords::setupTableView()
{
    model->setHorizontalHeaderLabels({"ID", "Name", "Age", "Medical History", "Doctor", "Last Visit"});

    ui->patientsTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    ui->patientsTableView->horizontalHeader()->setStretchLastSection(true);

    ui->patientsTableView->setColumnWidth(0, 60);  // ID
    ui->patientsTableView->setColumnWidth(1, 150); // Name
    ui->patientsTableView->setColumnWidth(2, 60);  // Age
    ui->patientsTableView->setColumnWidth(3, 200); // Medical History
    ui->patientsTableView->setColumnWidth(4, 150); // Doctor
}

QString PatientRecords::getDataFilePath() const
{
    return "C:/Users/osama/Downloads/projectlab/projectlab/patient_records.csv";
}

void PatientRecords::loadDataFromFile()
{
    model->clear();
    setupTableView();

    QFile file(getDataFilePath());
    if (!file.exists()) {
        // Create default file with two sample patients
        QList<QStandardItem*> row1;
        row1 << new QStandardItem("1001")
             << new QStandardItem("John Doe")
             << new QStandardItem("35")
             << new QStandardItem("Hypertension, Allergies: Penicillin")
             << new QStandardItem("Dr. Smith")
             << new QStandardItem(QDate::currentDate().toString("yyyy-MM-dd"));
        model->appendRow(row1);

        QList<QStandardItem*> row2;
        row2 << new QStandardItem("1002")
             << new QStandardItem("Jane Smith")
             << new QStandardItem("28")
             << new QStandardItem("Type 2 Diabetes")
             << new QStandardItem("Dr. Johnson")
             << new QStandardItem(QDate::currentDate().toString("yyyy-MM-dd"));
        model->appendRow(row2);

        saveDataToFile();
        emit patientCountChanged(model->rowCount());
        return;
    }

    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList fields = line.split(",");
            if (fields.size() >= 6) {
                QList<QStandardItem*> row;
                for (int i = 0; i < 6; i++)
                    row << new QStandardItem(fields[i].trimmed());
                model->appendRow(row);
            }
        }
        file.close();
        emit patientCountChanged(model->rowCount());
    } else {
        showErrorMessage("Could not open patient records file for reading");
    }
}

void PatientRecords::saveDataToFile()
{
    QFile file(getDataFilePath());
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        for (int row = 0; row < model->rowCount(); ++row) {
            QStringList rowData;
            for (int col = 0; col < model->columnCount(); ++col)
                rowData << model->item(row, col)->text();
            out << rowData.join(",") << "\n";
        }
        file.close();
    } else {
        showErrorMessage("Could not save patient records to file");
    }
}

bool PatientRecords::validatePatientData(int row)
{
    if (row < 0 || row >= model->rowCount()) return false;

    QString name = model->item(row, 1)->text().trimmed();
    if (name.isEmpty()) {
        showErrorMessage("Patient name cannot be empty");
        return false;
    }

    bool ok;
    int age = model->item(row, 2)->text().toInt(&ok);
    if (!ok || age < 0 || age > 120) {
        showErrorMessage("Please enter a valid age (0-120)");
        return false;
    }

    return true;
}

void PatientRecords::showErrorMessage(const QString &message)
{
    QMessageBox::critical(this, "Input Error", message);
}

void PatientRecords::refreshData()
{
    loadDataFromFile();
}

void PatientRecords::onSearchClicked()
{
    QString searchText = ui->searchLineEdit->text().trimmed();
    if (searchText.isEmpty()) {
        proxyModel->setFilterRegularExpression(QRegularExpression());
        return;
    }

    QString filter = ui->filterComboBox->currentText();
    int column = -1;
    if (filter == "Name") column = 1;
    else if (filter == "Doctor") column = 4;
    else if (filter == "Medical Condition") column = 3;

    if (column >= 0) {
        proxyModel->setFilterKeyColumn(column);
        proxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
        proxyModel->setFilterRegularExpression(QRegularExpression(searchText, QRegularExpression::CaseInsensitiveOption));
    }
}

void PatientRecords::onAddClicked()
{
    int maxId = 1000;
    for (int row = 0; row < model->rowCount(); ++row) {
        int currentId = model->item(row, 0)->text().toInt();
        if (currentId > maxId)
            maxId = currentId;
    }

    QList<QStandardItem*> newRow;
    newRow << new QStandardItem(QString::number(maxId + 1))
           << new QStandardItem("New Patient")
           << new QStandardItem("0")
           << new QStandardItem("")
           << new QStandardItem("")
           << new QStandardItem(QDate::currentDate().toString("yyyy-MM-dd"));
    model->appendRow(newRow);
    saveDataToFile();
    emit patientCountChanged(model->rowCount());

    QModelIndex index = model->index(model->rowCount() - 1, 1);
    ui->patientsTableView->setCurrentIndex(proxyModel->mapFromSource(index));
    ui->patientsTableView->edit(proxyModel->mapFromSource(index));
}

void PatientRecords::onEditClicked()
{
    QModelIndex proxyIndex = ui->patientsTableView->currentIndex();
    if (!proxyIndex.isValid()) {
        showErrorMessage("Please select a patient to edit");
        return;
    }

    QModelIndex index = proxyModel->mapToSource(proxyIndex);
    if (validatePatientData(index.row())) {
        ui->patientsTableView->edit(proxyIndex);
        saveDataToFile();
    }
}

void PatientRecords::onDeleteClicked()
{
    QModelIndex proxyIndex = ui->patientsTableView->currentIndex();
    if (!proxyIndex.isValid()) {
        showErrorMessage("Please select a patient to delete");
        return;
    }

    QModelIndex index = proxyModel->mapToSource(proxyIndex);
    QString patientName = model->item(index.row(), 1)->text();
    QString patientId = model->item(index.row(), 0)->text();

    if (QMessageBox::question(this, "Confirm Delete",
                              QString("Are you sure you want to delete patient:\n\n%1 (ID: %2)?").arg(patientName).arg(patientId),
                              QMessageBox::Yes|QMessageBox::No) == QMessageBox::Yes) {
        model->removeRow(index.row());
        saveDataToFile();
        emit patientCountChanged(model->rowCount());
    }
}

void PatientRecords::onBackClicked()
{
    emit backToDashboard();
}

void PatientRecords::on_pushButton_clicked()
{
    if (model->rowCount() == 0) {
        showErrorMessage("No patients to save");
        return;
    }

    // Get the last row in the model
    int lastRow = model->rowCount() - 1;
    QStringList rowData;
    for (int col = 0; col < model->columnCount(); ++col) {
        QStandardItem* item = model->item(lastRow, col);
        rowData << (item ? item->text() : "");
    }

    QFile file(getDataFilePath());
    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        out << rowData.join(",") << "\n";
        file.close();
    } else {
        showErrorMessage("Could not append new patient to the file");
    }
}
