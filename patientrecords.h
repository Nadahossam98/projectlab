#ifndef PATIENTRECORDS_H
#define PATIENTRECORDS_H

#include <QWidget>
#include <qstandarditemmodel.h>

namespace Ui {
class PatientRecords;
}

class PatientRecords : public QWidget
{
    Q_OBJECT

public:
    explicit PatientRecords(QWidget *parent = nullptr);
    ~PatientRecords();

signals:
    void patientUpdated();
    void windowClosed();

signals:
    void backToDashboard();

private slots:
    void onSearchClicked();
    void onAddClicked();
    void onEditClicked();
    void onDeleteClicked();

private:
    Ui::PatientRecords *ui;
    QStandardItemModel *model;
    void loadSampleData();
    void setupTableView();
};

#endif
