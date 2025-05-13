#ifndef PATIENTRECORDS_H
#define PATIENTRECORDS_H

#include <QWidget>
#include <QStandardItemModel>
#include <QSortFilterProxyModel>

namespace Ui {
class PatientRecords;
}

class PatientRecords : public QWidget
{
    Q_OBJECT

public:
    explicit PatientRecords(QWidget *parent = nullptr);
    ~PatientRecords();

    void setAccessLevel(const QString &role); // Set access based on role (Admin/Doctor)
    int getPatientCount() const;  // Get the number of patients (rows in model)

signals:
    void backToDashboard();  // Signal for back button
    void patientCountChanged(int newCount);  // Signal when patient count changes

public slots:
    void refreshData();  // Refresh the patient data

private slots:
    void onSearchClicked();  // Slot to handle search button
    void onAddClicked();     // Slot to handle add button
    void onEditClicked();    // Slot to handle edit button
    void onDeleteClicked();  // Slot to handle delete button
    void onBackClicked();    // Slot for back button action
    void on_pushButton_clicked(); // Another action button slot

private:
    Ui::PatientRecords *ui;  // UI pointer
    QStandardItemModel *model;  // Model for patient data
    QSortFilterProxyModel *proxyModel;  // Proxy model for filtering
    QString currentUserRole;  // Current user's role (e.g., Admin, Doctor)

    void setupTableView();  // Method to setup table view layout
    void loadDataFromFile();  // Load patient data from file (CSV)
    void saveDataToFile();  // Save patient data back to file (CSV)
    bool validatePatientData(int row);  // Validate patient data before saving
    void showErrorMessage(const QString &message);  // Show error message box
    QString getDataFilePath() const;  // Get path for the patient records CSV file
};

#endif // PATIENTRECORDS_H
