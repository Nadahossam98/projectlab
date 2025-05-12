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

    void setAccessLevel(const QString &role);
    int getPatientCount() const;


signals:
    void backToDashboard();
    void patientCountChanged(int newCount);


public slots:
    void refreshData();

private slots:
    void onSearchClicked();
    void onAddClicked();
    void onEditClicked();
    void onDeleteClicked();
    void onBackClicked();

private:
    Ui::PatientRecords *ui;
    QStandardItemModel *model;
    QSortFilterProxyModel *proxyModel;
    QString currentUserRole;

    void setupTableView();
    void loadDataFromFile();
    void saveDataToFile();
    bool validatePatientData(int row);
    void showErrorMessage(const QString &message);
    QString getDataFilePath() const;
};

#endif // PATIENTRECORDS_H
