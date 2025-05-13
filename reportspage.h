#ifndef REPORTSPAGE_H
#define REPORTSPAGE_H


#include <QWidget>
#include <QVector>
#include <QStringList>

namespace Ui {
class ReportsPage;
}

class ReportsPage : public QWidget
{
    Q_OBJECT

public:
    explicit ReportsPage(QWidget *parent = nullptr);
    ~ReportsPage();

    void generateReports();
    void exportToCSV();
    void exportToTXT();

private slots:
    void on_generateButton_clicked();
    void on_exportCSVButton_clicked();
    void on_exportTXTButton_clicked();
    void on_backButton_clicked();

signals:
    void patientCountChanged(int newCount);
    void backToDashboard();

private:
    Ui::ReportsPage *ui;

    // Sample data structures - replace with your actual data
    int totalPatients;
    double totalRevenue;
    QVector<QPair<QString, int>> doctorAppointments; // doctor name, appointment count
};

#endif // REPORTSPAGE_H
