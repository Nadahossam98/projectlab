/********************************************************************************
** Form generated from reading UI file 'patientrecords.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PATIENTRECORDS_H
#define UI_PATIENTRECORDS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PatientRecords
{
public:
    QTableView *patientsTableView;
    QLabel *label;
    QPushButton *backToDashboard;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *addButton;
    QPushButton *deleteButton;
    QPushButton *editButton;
    QWidget *widget1;
    QGridLayout *gridLayout;
    QComboBox *filterComboBox;
    QLineEdit *searchLineEdit;
    QPushButton *searchButton;
    QPushButton *saveButton;
    QPushButton *loadButton;

    void setupUi(QWidget *PatientRecords)
    {
        if (PatientRecords->objectName().isEmpty())
            PatientRecords->setObjectName("PatientRecords");
        PatientRecords->resize(800, 600);
        patientsTableView = new QTableView(PatientRecords);
        patientsTableView->setObjectName("patientsTableView");
        patientsTableView->setGeometry(QRect(10, 240, 781, 251));
        label = new QLabel(PatientRecords);
        label->setObjectName("label");
        label->setGeometry(QRect(230, 50, 391, 51));
        QFont font;
        font.setPointSize(28);
        font.setBold(true);
        label->setFont(font);
        backToDashboard = new QPushButton(PatientRecords);
        backToDashboard->setObjectName("backToDashboard");
        backToDashboard->setGeometry(QRect(10, 30, 171, 51));
        widget = new QWidget(PatientRecords);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(400, 500, 381, 31));
        horizontalLayout_2 = new QHBoxLayout(widget);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        addButton = new QPushButton(widget);
        addButton->setObjectName("addButton");
        QPalette palette;
        QBrush brush(QColor(27, 170, 1, 255));
        brush.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Button, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Button, brush);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Button, brush);
        addButton->setPalette(palette);

        horizontalLayout_2->addWidget(addButton);

        deleteButton = new QPushButton(widget);
        deleteButton->setObjectName("deleteButton");
        QPalette palette1;
        QBrush brush1(QColor(255, 0, 0, 255));
        brush1.setStyle(Qt::BrushStyle::SolidPattern);
        palette1.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Button, brush1);
        palette1.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Button, brush1);
        palette1.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Button, brush1);
        deleteButton->setPalette(palette1);

        horizontalLayout_2->addWidget(deleteButton);

        editButton = new QPushButton(widget);
        editButton->setObjectName("editButton");
        QPalette palette2;
        QBrush brush2(QColor(0, 0, 255, 255));
        brush2.setStyle(Qt::BrushStyle::SolidPattern);
        palette2.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Button, brush2);
        palette2.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Button, brush2);
        palette2.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Button, brush2);
        editButton->setPalette(palette2);

        horizontalLayout_2->addWidget(editButton);

        widget1 = new QWidget(PatientRecords);
        widget1->setObjectName("widget1");
        widget1->setGeometry(QRect(20, 150, 751, 77));
        gridLayout = new QGridLayout(widget1);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        filterComboBox = new QComboBox(widget1);
        filterComboBox->setObjectName("filterComboBox");

        gridLayout->addWidget(filterComboBox, 0, 2, 1, 1);

        searchLineEdit = new QLineEdit(widget1);
        searchLineEdit->setObjectName("searchLineEdit");
        QFont font1;
        font1.setPointSize(14);
        searchLineEdit->setFont(font1);

        gridLayout->addWidget(searchLineEdit, 0, 0, 1, 1);

        searchButton = new QPushButton(widget1);
        searchButton->setObjectName("searchButton");

        gridLayout->addWidget(searchButton, 0, 3, 1, 1);

        saveButton = new QPushButton(widget1);
        saveButton->setObjectName("saveButton");
        QPalette palette3;
        palette3.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Button, brush);
        palette3.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Button, brush);
        palette3.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Button, brush);
        saveButton->setPalette(palette3);

        gridLayout->addWidget(saveButton, 1, 2, 1, 1);

        loadButton = new QPushButton(widget1);
        loadButton->setObjectName("loadButton");
        QPalette palette4;
        palette4.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Button, brush2);
        palette4.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Button, brush2);
        palette4.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Button, brush2);
        loadButton->setPalette(palette4);

        gridLayout->addWidget(loadButton, 1, 3, 1, 1);


        retranslateUi(PatientRecords);

        QMetaObject::connectSlotsByName(PatientRecords);
    } // setupUi

    void retranslateUi(QWidget *PatientRecords)
    {
        PatientRecords->setWindowTitle(QCoreApplication::translate("PatientRecords", "Form", nullptr));
        label->setText(QCoreApplication::translate("PatientRecords", "Patient Records", nullptr));
        backToDashboard->setText(QCoreApplication::translate("PatientRecords", "Back To Dashboard", nullptr));
        addButton->setText(QCoreApplication::translate("PatientRecords", "Add", nullptr));
        deleteButton->setText(QCoreApplication::translate("PatientRecords", "Delete", nullptr));
        editButton->setText(QCoreApplication::translate("PatientRecords", "edit", nullptr));
        searchButton->setText(QCoreApplication::translate("PatientRecords", "search", nullptr));
        saveButton->setText(QCoreApplication::translate("PatientRecords", "save ", nullptr));
        loadButton->setText(QCoreApplication::translate("PatientRecords", "Load", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PatientRecords: public Ui_PatientRecords {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PATIENTRECORDS_H
