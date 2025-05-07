#ifndef PATIENTRECORDS_H
#define PATIENTRECORDS_H

#include <QWidget>
#include <QStandardItemModel>

QT_BEGIN_NAMESPACE
namespace Ui { class PatientRecords; }
QT_END_NAMESPACE

class PatientRecords : public QWidget
{
    Q_OBJECT

public:
    explicit PatientRecords(QWidget *parent = nullptr);
    ~PatientRecords();

signals:
    void backToDashboard();

public slots:
    void onBackToDashboardClicked();

private slots:
    void onSearchClicked();
    void onAddClicked();
    void onEditClicked();
    void onDeleteClicked();
    void saveToFile();
    void loadFromFile();

private:
    Ui::PatientRecords *ui;
    QStandardItemModel *model;
    QString currentFilePath;

    void setupTableView();
    void setupConnections();
    void loadSampleData();
    void addPatient(const QString &id,
                    const QString &name,
                    const QString &age,
                    const QString &medicalHistory,
                    const QString &doctor);
};

#endif // PATIENTRECORDS_H
