/********************************************************************************
** Form generated from reading UI file 'billingpage.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BILLINGPAGE_H
#define UI_BILLINGPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BillingPage
{
public:
    QVBoxLayout *verticalLayout;
    QPushButton *backButton;
    QGroupBox *groupBox;
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *patientIdInput;
    QLabel *label_2;
    QDateEdit *dateInput;
    QLabel *label_3;
    QLineEdit *treatmentCostInput;
    QLabel *label_4;
    QLineEdit *insuranceCoverageInput;
    QLabel *label_5;
    QTextEdit *descriptionInput;
    QPushButton *addBillButton;
    QTableWidget *billsTable;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label_6;
    QLabel *totalPendingLabel;
    QSpacerItem *horizontalSpacer;
    QLabel *label_7;
    QLabel *totalPaidLabel;
    QHBoxLayout *buttonLayout;
    QPushButton *calculateButton;
    QPushButton *markPaidButton;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *BillingPage)
    {
        if (BillingPage->objectName().isEmpty())
            BillingPage->setObjectName("BillingPage");
        BillingPage->resize(800, 600);
        verticalLayout = new QVBoxLayout(BillingPage);
        verticalLayout->setObjectName("verticalLayout");
        backButton = new QPushButton(BillingPage);
        backButton->setObjectName("backButton");
        backButton->setStyleSheet(QString::fromUtf8("\n"
"          QPushButton {\n"
"            background-color: #f8f9fa;\n"
"            border: 1px solid #dadce0;\n"
"            color: #3c4043;\n"
"            padding: 8px 16px;\n"
"            border-radius: 4px;\n"
"          }\n"
"          QPushButton:hover {\n"
"            background-color: #e8eaed;\n"
"            border: 1px solid #d2e3fc;\n"
"          }\n"
"          QPushButton:pressed {\n"
"            background-color: #d2e3fc;\n"
"          }\n"
"        "));

        verticalLayout->addWidget(backButton, 0, Qt::AlignmentFlag::AlignLeft);

        groupBox = new QGroupBox(BillingPage);
        groupBox->setObjectName("groupBox");
        formLayout = new QFormLayout(groupBox);
        formLayout->setObjectName("formLayout");
        label = new QLabel(groupBox);
        label->setObjectName("label");

        formLayout->setWidget(0, QFormLayout::ItemRole::LabelRole, label);

        patientIdInput = new QLineEdit(groupBox);
        patientIdInput->setObjectName("patientIdInput");

        formLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, patientIdInput);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName("label_2");

        formLayout->setWidget(1, QFormLayout::ItemRole::LabelRole, label_2);

        dateInput = new QDateEdit(groupBox);
        dateInput->setObjectName("dateInput");
        dateInput->setCalendarPopup(true);

        formLayout->setWidget(1, QFormLayout::ItemRole::FieldRole, dateInput);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName("label_3");

        formLayout->setWidget(2, QFormLayout::ItemRole::LabelRole, label_3);

        treatmentCostInput = new QLineEdit(groupBox);
        treatmentCostInput->setObjectName("treatmentCostInput");

        formLayout->setWidget(2, QFormLayout::ItemRole::FieldRole, treatmentCostInput);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName("label_4");

        formLayout->setWidget(3, QFormLayout::ItemRole::LabelRole, label_4);

        insuranceCoverageInput = new QLineEdit(groupBox);
        insuranceCoverageInput->setObjectName("insuranceCoverageInput");

        formLayout->setWidget(3, QFormLayout::ItemRole::FieldRole, insuranceCoverageInput);

        label_5 = new QLabel(groupBox);
        label_5->setObjectName("label_5");

        formLayout->setWidget(4, QFormLayout::ItemRole::LabelRole, label_5);

        descriptionInput = new QTextEdit(groupBox);
        descriptionInput->setObjectName("descriptionInput");

        formLayout->setWidget(4, QFormLayout::ItemRole::FieldRole, descriptionInput);

        addBillButton = new QPushButton(groupBox);
        addBillButton->setObjectName("addBillButton");
        addBillButton->setEnabled(false);

        formLayout->setWidget(5, QFormLayout::ItemRole::FieldRole, addBillButton);


        verticalLayout->addWidget(groupBox);

        billsTable = new QTableWidget(BillingPage);
        billsTable->setObjectName("billsTable");

        verticalLayout->addWidget(billsTable);

        groupBox_2 = new QGroupBox(BillingPage);
        groupBox_2->setObjectName("groupBox_2");
        horizontalLayout = new QHBoxLayout(groupBox_2);
        horizontalLayout->setObjectName("horizontalLayout");
        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName("label_6");

        horizontalLayout->addWidget(label_6);

        totalPendingLabel = new QLabel(groupBox_2);
        totalPendingLabel->setObjectName("totalPendingLabel");

        horizontalLayout->addWidget(totalPendingLabel);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label_7 = new QLabel(groupBox_2);
        label_7->setObjectName("label_7");

        horizontalLayout->addWidget(label_7);

        totalPaidLabel = new QLabel(groupBox_2);
        totalPaidLabel->setObjectName("totalPaidLabel");

        horizontalLayout->addWidget(totalPaidLabel);


        verticalLayout->addWidget(groupBox_2);

        buttonLayout = new QHBoxLayout();
        buttonLayout->setObjectName("buttonLayout");
        calculateButton = new QPushButton(BillingPage);
        calculateButton->setObjectName("calculateButton");

        buttonLayout->addWidget(calculateButton);

        markPaidButton = new QPushButton(BillingPage);
        markPaidButton->setObjectName("markPaidButton");

        buttonLayout->addWidget(markPaidButton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        buttonLayout->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(buttonLayout);


        retranslateUi(BillingPage);

        QMetaObject::connectSlotsByName(BillingPage);
    } // setupUi

    void retranslateUi(QWidget *BillingPage)
    {
        BillingPage->setWindowTitle(QCoreApplication::translate("BillingPage", "Billing Management", nullptr));
        backButton->setText(QCoreApplication::translate("BillingPage", "Back to Dashboard", nullptr));
        groupBox->setTitle(QCoreApplication::translate("BillingPage", "Add New Bill", nullptr));
        label->setText(QCoreApplication::translate("BillingPage", "Patient ID:", nullptr));
        label_2->setText(QCoreApplication::translate("BillingPage", "Date:", nullptr));
        label_3->setText(QCoreApplication::translate("BillingPage", "Treatment Cost ($):", nullptr));
        label_4->setText(QCoreApplication::translate("BillingPage", "Insurance Coverage (%):", nullptr));
        insuranceCoverageInput->setText(QCoreApplication::translate("BillingPage", "0", nullptr));
        label_5->setText(QCoreApplication::translate("BillingPage", "Description:", nullptr));
        addBillButton->setText(QCoreApplication::translate("BillingPage", "Add Bill", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("BillingPage", "Payment Summary", nullptr));
        label_6->setText(QCoreApplication::translate("BillingPage", "Total Pending:", nullptr));
        totalPendingLabel->setText(QCoreApplication::translate("BillingPage", "$0.00", nullptr));
        label_7->setText(QCoreApplication::translate("BillingPage", "Total Paid:", nullptr));
        totalPaidLabel->setText(QCoreApplication::translate("BillingPage", "$0.00", nullptr));
        calculateButton->setText(QCoreApplication::translate("BillingPage", "Calculate Totals", nullptr));
        markPaidButton->setText(QCoreApplication::translate("BillingPage", "Mark as Paid", nullptr));
    } // retranslateUi

};

namespace Ui {
    class BillingPage: public Ui_BillingPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BILLINGPAGE_H
