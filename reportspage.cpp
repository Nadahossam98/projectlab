#include "reportsPage.h"
#include "ui_reportsPage.h"

#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QMap>
#include <QMapIterator>
#include <QPair>
#include <QDebug>

ReportsPage::ReportsPage(QWidget *parent)
    : QWidget(parent),
    ui(new Ui::ReportsPage)
{
    ui->setupUi(this);
    this->setFixedSize(800, 600);

    totalPatients = 0;
    totalRevenue = 0.0;
    doctorAppointments.clear();
}

ReportsPage::~ReportsPage()
{
    delete ui;
}

void ReportsPage::generateReports()
{
    QFile patientFile("C:/Users/osama/Downloads/projectlab/projectlab/patient_records.csv");
    if (patientFile.exists() && patientFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        totalPatients = 0;
        QTextStream in(&patientFile);
        while (!in.atEnd()) {
            in.readLine();
            totalPatients++;
        }
        patientFile.close();
    } else {
        totalPatients = 0;
        qWarning() << "Could not open patient records file";
    }

    QFile billingFile("C:/Users/osama/Downloads/projectlab/projectlab/billing_records.csv");
    totalRevenue = 0.0;
    if (billingFile.exists() && billingFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&billingFile);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList fields = line.split(",");
            if (fields.size() >= 6) {
                bool ok;
                double amount = fields[5].toDouble(&ok);
                if (ok) totalRevenue += amount;
            }
        }
        billingFile.close();
    } else {
        qWarning() << "Could not open billing records file";
    }

    QMap<QString, QString> doctorIdToName;
    QFile userFile("C:/Users/osama/Downloads/projectlab/projectlab/build/Desktop_Qt_6_8_0_MinGW_64_bit-Debug/users.txt");
    if (userFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&userFile);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList parts = line.split(":");
            if (parts.size() == 3 && parts[2].trimmed().compare("Doctor", Qt::CaseInsensitive) == 0) {
                doctorIdToName[QString::number(doctorIdToName.size() + 1)] = parts[0];
            }
        }
        userFile.close();
    }

    QFile appointmentsFile("appointments.csv");
    doctorAppointments.clear();
    QMap<QString, int> doctorCounts;

    if (appointmentsFile.exists() && appointmentsFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&appointmentsFile);
        QString headerLine = in.readLine();
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList fields = line.split(",");
            if (fields.size() >= 3) {
                QString doctorId = fields[2].trimmed();
                doctorCounts[doctorId]++;
            }
        }
        appointmentsFile.close();

        QMapIterator<QString, int> i(doctorCounts);
        while (i.hasNext()) {
            i.next();
            QString docName = doctorIdToName.contains(i.key()) ? doctorIdToName[i.key()] : ("Doctor ID " + i.key());
            doctorAppointments.append(qMakePair(docName + " (ID: " + i.key() + ")", i.value()));
        }

        std::sort(doctorAppointments.begin(), doctorAppointments.end(),
                  [](const QPair<QString, int> &a, const QPair<QString, int> &b) {
                      return a.second > b.second;
                  });
    } else {
        qWarning() << "Could not open appointments file";
    }

    ui->totalPatientsLabel->setText(QString::number(totalPatients));
    ui->totalRevenueLabel->setText(QString("$%1").arg(totalRevenue, 0, 'f', 2));

    ui->doctorListWidget->clear();
    for (const auto& doctor : doctorAppointments) {
        ui->doctorListWidget->addItem(QString("%1: %2 appointments").arg(doctor.first).arg(doctor.second));
    }

    QMessageBox::information(this, "Success", "Reports generated successfully!");
}

void ReportsPage::exportToCSV()
{
    QString fileName = QFileDialog::getSaveFileName(
        this, "Export to CSV", "", "CSV Files (*.csv)");
    if (fileName.isEmpty()) return;

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", "Could not create file!");
        return;
    }

    QTextStream out(&file);
    out << "Report Type,Value\n";
    out << "Total Patients," << totalPatients << "\n";
    out << "Total Revenue," << QString::number(totalRevenue, 'f', 2) << "\n";
    out << "\nDoctor,Appointments\n";
    for (const auto& doctor : doctorAppointments) {
        out << doctor.first << "," << doctor.second << "\n";
    }

    file.close();
    QMessageBox::information(this, "Success", "Data exported to CSV successfully!");
}

void ReportsPage::exportToTXT()
{
    QString fileName = QFileDialog::getSaveFileName(
        this, "Export to TXT", "", "Text Files (*.txt)");
    if (fileName.isEmpty()) return;

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", "Could not create file!");
        return;
    }

    QTextStream out(&file);
    out << "Hospital Management System Report\n";
    out << "================================\n\n";
    out << "Total Patients: " << totalPatients << "\n";
    out << "Total Revenue: $" << QString::number(totalRevenue, 'f', 2) << "\n\n";
    out << "Most Booked Doctors:\n";
    out << "-------------------\n";
    for (const auto& doctor : doctorAppointments) {
        out << doctor.first << ": " << doctor.second << " appointments\n";
    }

    file.close();
    QMessageBox::information(this, "Success", "Data exported to TXT successfully!");
}

void ReportsPage::on_generateButton_clicked()
{
    generateReports();
}

void ReportsPage::on_exportCSVButton_clicked()
{
    exportToCSV();
}

void ReportsPage::on_exportTXTButton_clicked()
{
    exportToTXT();
}

void ReportsPage::on_backButton_clicked()
{
    emit backToDashboard();
}
