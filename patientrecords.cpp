#include "patientrecords.h"
#include "ui_patientrecords.h"
#include <QMessageBox>
#include <QStandardItem>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QPushButton>

PatientRecords::PatientRecords(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PatientRecords),
    model(new QStandardItemModel(this))
{
    ui->setupUi(this);

    setupTableView();
    setupConnections();
    loadSampleData();
}

PatientRecords::~PatientRecords()
{
    delete ui;
}

void PatientRecords::setupTableView()
{
    model->setHorizontalHeaderLabels({"ID", "Name", "Age", "Medical History", "Doctor Assigned"});
    ui->patientsTableView->setModel(model);
    ui->patientsTableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->patientsTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->patientsTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->patientsTableView->horizontalHeader()->setStretchLastSection(true);
}

void PatientRecords::setupConnections()
{
    ui->filterComboBox->addItems({"Name", "Doctor", "Medical History"});

    connect(ui->searchButton, &QPushButton::clicked, this, &PatientRecords::onSearchClicked);
    connect(ui->addButton, &QPushButton::clicked, this, &PatientRecords::onAddClicked);
    connect(ui->editButton, &QPushButton::clicked, this, &PatientRecords::onEditClicked);
    connect(ui->deleteButton, &QPushButton::clicked, this, &PatientRecords::onDeleteClicked);
    connect(ui->backToDashboard, &QPushButton::clicked, this, &PatientRecords::onBackToDashboardClicked);

    // Only connect save/load buttons if they exist in the UI
    if (ui->saveButton) {
        connect(ui->saveButton, &QPushButton::clicked, this, &PatientRecords::saveToFile);
    }
    if (ui->loadButton) {
        connect(ui->loadButton, &QPushButton::clicked, this, &PatientRecords::loadFromFile);
    }
}

void PatientRecords::loadSampleData()
{
    model->clear();
    setupTableView();

    addPatient("1", "John Doe", "35", "Hypertension", "Dr. Smith");
    addPatient("2", "Jane Smith", "28", "Diabetes", "Dr. Johnson");
    addPatient("3", "Robert Brown", "45", "Asthma", "Dr. Williams");
}

void PatientRecords::addPatient(const QString &id, const QString &name,
                                const QString &age, const QString &medicalHistory,
                                const QString &doctor)
{
    QList<QStandardItem*> row;
    row << new QStandardItem(id);
    row << new QStandardItem(name);
    row << new QStandardItem(age);
    row << new QStandardItem(medicalHistory);
    row << new QStandardItem(doctor);
    model->appendRow(row);
}

void PatientRecords::onSearchClicked()
{
    QString searchText = ui->searchLineEdit->text().trimmed().toLower();
    QString filter = ui->filterComboBox->currentText();

    for (int row = 0; row < model->rowCount(); ++row) {
        bool match = false;
        int column = -1;

        if (filter == "Name") column = 1;
        else if (filter == "Doctor") column = 4;
        else if (filter == "Medical History") column = 3;

        if (column >= 0) {
            QString cellText = model->item(row, column)->text().toLower();
            match = cellText.contains(searchText);
        }

        ui->patientsTableView->setRowHidden(row, !match);
    }
}

void PatientRecords::onAddClicked()
{
    QString newId = QString::number(model->rowCount() + 1);
    addPatient(newId, "New Patient", "0", "", "");

    QModelIndex index = model->index(model->rowCount() - 1, 1);
    ui->patientsTableView->edit(index);
}

void PatientRecords::onEditClicked()
{
    QModelIndexList selected = ui->patientsTableView->selectionModel()->selectedRows();
    if (!selected.isEmpty()) {
        ui->patientsTableView->edit(selected.first());
    } else {
        QMessageBox::warning(this, "No Selection", "Please select a patient to edit.");
    }
}

void PatientRecords::onDeleteClicked()
{
    QModelIndexList selected = ui->patientsTableView->selectionModel()->selectedRows();
    if (!selected.isEmpty()) {
        int row = selected.first().row();
        QString patientName = model->item(row, 1)->text();

        if (QMessageBox::question(this, "Confirm Delete",
                                  QString("Delete patient %1?").arg(patientName),
                                  QMessageBox::Yes|QMessageBox::No) == QMessageBox::Yes) {
            model->removeRow(row);

            // Re-number remaining patients
            for (int i = 0; i < model->rowCount(); ++i) {
                model->item(i, 0)->setText(QString::number(i + 1));
            }
        }
    } else {
        QMessageBox::warning(this, "No Selection", "Please select a patient to delete.");
    }
}

void PatientRecords::onBackToDashboardClicked()
{
    emit backToDashboard();
}

void PatientRecords::saveToFile()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save Patient Records", "", "CSV Files (*.csv)");
    if (fileName.isEmpty()) return;

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "Could not save file");
        return;
    }

    QTextStream out(&file);

    // Write headers
    for (int col = 0; col < model->columnCount(); ++col) {
        out << model->headerData(col, Qt::Horizontal).toString();
        if (col < model->columnCount() - 1) out << ",";
    }
    out << "\n";

    // Write data
    for (int row = 0; row < model->rowCount(); ++row) {
        for (int col = 0; col < model->columnCount(); ++col) {
            out << model->item(row, col)->text();
            if (col < model->columnCount() - 1) out << ",";
        }
        out << "\n";
    }

    file.close();
    currentFilePath = fileName;
}

void PatientRecords::loadFromFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Load Patient Records", "", "CSV Files (*.csv)");
    if (fileName.isEmpty()) return;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "Could not open file");
        return;
    }

    model->clear();
    setupTableView();

    QTextStream in(&file);

    // Skip header line
    in.readLine();

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(",");

        if (fields.size() >= 5) {
            addPatient(fields[0], fields[1], fields[2], fields[3], fields[4]);
        }
    }

    file.close();
    currentFilePath = fileName;
}
