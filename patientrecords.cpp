#include "patientrecords.h"
#include "ui_patientrecords.h"
#include <QMessageBox>
#include <QStandardItem>

PatientRecords::PatientRecords(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PatientRecords),
    model(new QStandardItemModel(this))
{
    ui->setupUi(this);

    setupTableView();
    loadSampleData();

    ui->filterComboBox->addItems({"Name", "Doctor", "Medical Condition"});

    connect(ui->searchButton, &QPushButton::clicked, this, &PatientRecords::onSearchClicked);
    connect(ui->addButton, &QPushButton::clicked, this, &PatientRecords::onAddClicked);
    connect(ui->editButton, &QPushButton::clicked, this, &PatientRecords::onEditClicked);
    connect(ui->deleteButton, &QPushButton::clicked, this, &PatientRecords::onDeleteClicked);
}

void PatientRecords::setupTableView()
{
    model->setHorizontalHeaderLabels({"ID", "Name", "Age", "Medical History", "Doctor"});
    ui->patientsTableView->setModel(model);
    ui->patientsTableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->patientsTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
}

void PatientRecords::loadSampleData()
{
    QList<QStandardItem*> row1;
    row1 << new QStandardItem("1");
    row1 << new QStandardItem("John Doe");
    row1 << new QStandardItem("35");
    row1 << new QStandardItem("Hypertension");
    row1 << new QStandardItem("Dr. Smith");
    model->appendRow(row1);

    QList<QStandardItem*> row2;
    row2 << new QStandardItem("2");
    row2 << new QStandardItem("Jane Smith");
    row2 << new QStandardItem("28");
    row2 << new QStandardItem("Diabetes");
    row2 << new QStandardItem("Dr. Johnson");
    model->appendRow(row2);
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
        else if (filter == "Medical Condition") column = 3;

        if (column >= 0) {
            QString cellText = model->item(row, column)->text().toLower();
            match = cellText.contains(searchText);
        }

        ui->patientsTableView->setRowHidden(row, !match);
    }
}

void PatientRecords::onAddClicked()
{
    QList<QStandardItem*> newRow;
    newRow << new QStandardItem(QString::number(model->rowCount() + 1));
    newRow << new QStandardItem("New Patient");
    newRow << new QStandardItem("0");
    newRow << new QStandardItem("");
    newRow << new QStandardItem("");
    model->appendRow(newRow);

    QModelIndex index = model->index(model->rowCount() - 1, 1);
    ui->patientsTableView->edit(index);
}

void PatientRecords::onEditClicked()
{
    QModelIndex index = ui->patientsTableView->currentIndex();
    if (index.isValid()) {
        ui->patientsTableView->edit(index);
    }
}

void PatientRecords::onDeleteClicked()
{
    QModelIndex index = ui->patientsTableView->currentIndex();
    if (index.isValid()) {
        QString patientName = model->item(index.row(), 1)->text();

        if (QMessageBox::question(this, "Confirm Delete",
                                  QString("Delete patient %1?").arg(patientName)) == QMessageBox::Yes) {
            model->removeRow(index.row());
        }
    }
}

PatientRecords::~PatientRecords()
{
    delete ui;
}
