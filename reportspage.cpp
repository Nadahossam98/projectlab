#include "reportsPage.h"
#include "ui_reportsPage.h"

#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

/*
 * ReportsPage provides a summary and export functionality for hospital reports.
 * It displays total patients, total revenue, and a list of doctor appointment counts.
 * Users can generate the report, and export it to CSV or TXT format.
 */

ReportsPage::ReportsPage(QWidget *parent)
    : QWidget(parent),
    ui(new Ui::ReportsPage)
{
    ui->setupUi(this);
    this->setFixedSize(800, 600);

    // Initialize report data with zero/default values
    totalPatients = 0;
    totalRevenue = 0.0;
    doctorAppointments.clear();
}

/*
 * Destructor: cleans up the UI.
 */
ReportsPage::~ReportsPage()
{
    delete ui;
}

/*
 * Generates the reports data.
 * In a real application, replace the hardcoded values with actual data retrieval logic.
 * Updates the UI with new values.
 */
void ReportsPage::generateReports()
{
    // Get patient count from PatientRecords
    QFile patientFile(QDir::homePath() + "/patient_records.csv");
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

    // Get revenue data from billing (assuming billing records exist)
    QFile billingFile("data/billing_records.csv");
    totalRevenue = 0.0;
    if (billingFile.exists() && billingFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&billingFile);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList fields = line.split(",");
            if (fields.size() >= 2) {  // Assuming amount is in second column
                bool ok;
                double amount = fields[1].toDouble(&ok);
                if (ok) totalRevenue += amount;
            }
        }
        billingFile.close();
    } else {
        qWarning() << "Could not open billing records file";
    }

    // Get doctor appointment counts (assuming appointments file exists)
    QFile appointmentsFile("data/appointments.csv");
    doctorAppointments.clear();
    QMap<QString, int> doctorCounts;

    if (appointmentsFile.exists() && appointmentsFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&appointmentsFile);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList fields = line.split(",");
            if (fields.size() >= 2) {  // Assuming doctor name is in second column
                QString doctor = fields[1].trimmed();
                doctorCounts[doctor]++;
            }
        }
        appointmentsFile.close();

        // Convert QMap to QList<QPair>
        QMapIterator<QString, int> i(doctorCounts);
        while (i.hasNext()) {
            i.next();
            doctorAppointments.append(qMakePair(i.key(), i.value()));
        }

        // Sort doctors by appointment count (descending)
        std::sort(doctorAppointments.begin(), doctorAppointments.end(),
                  [](const QPair<QString, int> &a, const QPair<QString, int> &b) {
                      return a.second > b.second;
                  });
    } else {
        qWarning() << "Could not open appointments file";
        // Fallback to default values if file doesn't exist
        doctorAppointments = {
            {"Dr. Smith", 0},
            {"Dr. Johnson", 0},
            {"Dr. Williams", 0}
        };
    }

    // Update UI labels with the actual data
    ui->totalPatientsLabel->setText(QString::number(totalPatients));
    ui->totalRevenueLabel->setText(QString("$%1").arg(totalRevenue, 0, 'f', 2));

    // Clear and repopulate the doctor list widget
    ui->doctorListWidget->clear();
    for (const auto& doctor : doctorAppointments) {
        ui->doctorListWidget->addItem(
            QString("%1: %2 appointments").arg(doctor.first).arg(doctor.second)
            );
    }

    QMessageBox::information(this, "Success", "Reports generated successfully!");
}

/*
 * Exports the report data to a CSV file.
 * Prompts the user for a file location and writes the summary and doctor data.
 */
void ReportsPage::exportToCSV()
{
    QString fileName = QFileDialog::getSaveFileName(
        this, "Export to CSV", "", "CSV Files (*.csv)"
        );
    if (fileName.isEmpty()) return; // User cancelled

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", "Could not create file!");
        return;
    }

    QTextStream out(&file);
    // Write summary data
    out << "Report Type,Value\n";
    out << "Total Patients," << totalPatients << "\n";
    out << "Total Revenue," << QString::number(totalRevenue, 'f', 2) << "\n";
    out << "\nDoctor,Appointments\n";
    // Write doctor appointment data
    for (const auto& doctor : doctorAppointments) {
        out << doctor.first << "," << doctor.second << "\n";
    }

    file.close();
    QMessageBox::information(this, "Success", "Data exported to CSV successfully!");
}

/*
 * Exports the report data to a plain text (TXT) file.
 * Prompts the user for a file location and writes a formatted textual report.
 */
void ReportsPage::exportToTXT()
{
    QString fileName = QFileDialog::getSaveFileName(
        this, "Export to TXT", "", "Text Files (*.txt)"
        );
    if (fileName.isEmpty()) return; // User cancelled

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", "Could not create file!");
        return;
    }

    QTextStream out(&file);
    // Write formatted report
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

/*
 * Slot: Handles the Generate button click.
 * Calls the generateReports() function to update the report data and UI.
 */
void ReportsPage::on_generateButton_clicked()
{
    generateReports();
}

/*
 * Slot: Handles the Export CSV button click.
 * Calls the exportToCSV() function to export the report data.
 */
void ReportsPage::on_exportCSVButton_clicked()
{
    exportToCSV();
}

/*
 * Slot: Handles the Export TXT button click.
 * Calls the exportToTXT() function to export the report data.
 */
void ReportsPage::on_exportTXTButton_clicked()
{
    exportToTXT();
}

/*
 * Slot: Handles the Back button click.
 * Emits the backToDashboard() signal to return to the dashboard.
 */
void ReportsPage::on_backButton_clicked()
{
    emit backToDashboard();
}
