#include "dashboard.h"
#include "ui_dashboard.h"
#include "patientrecords.h"

#include <QFile>
#include <QDir>
#include <QPixmap>
#include <QFileDialog>
#include <QMessageBox>
#include <QString>
#include <QDebug>

Dashboard::Dashboard(QWidget *parent)
    : QWidget(parent),
    ui(new Ui::Dashboard),
    m_patientsCount(0),
    m_appointmentsCount(0),
    m_billsCount(0),
    m_reportsCount(0)
{
    ui->setupUi(this);
    setWindowTitle("Dashboard");

    // Connect member pointers to UI elements
    m_profilePicLabel = ui->profilePicLabel;
    m_welcomeLabel = ui->welcomeLabel;
    m_patientsCard = ui->patientsCard;
    m_appointmentsCard = ui->appointmentsCard;
    m_billsCard = ui->billsCard;
    m_reportsCard = ui->reportsCard;
    m_patientsButton = ui->patientsButton;
    m_appointmentsButton = ui->appointmentsButton;
    m_billingButton = ui->billingButton;
    m_reportsButton = ui->reportsButton;
    m_logoutButton = ui->logoutButton;
    m_changeProfileButton = ui->changeProfileButton;

    // Initialize UI with default values
    ui->patientsValueLabel->setText(QString::number(m_patientsCount));
    ui->appointmentsValueLabel->setText(QString::number(m_appointmentsCount));
    ui->billsValueLabel->setText(QString::number(m_billsCount));
    ui->reportsValueLabel->setText(QString::number(m_reportsCount));

    setupConnections();
}

Dashboard::~Dashboard()
{
    delete ui;
}

void Dashboard::setUserInfo(const QString &username, const QString &role)
{
    m_welcomeLabel->setText(QString("Welcome, %1 (%2)").arg(username, role));
    loadProfilePicture(username);
}

void Dashboard::connectPatientRecords(PatientRecords* patientRecords)
{
    if (!patientRecords) return;

    connect(patientRecords, &PatientRecords::patientCountChanged,
            this, &Dashboard::updatePatientCount);

    // Initialize with current count
    updatePatientCount(patientRecords->getPatientCount());
}

void Dashboard::updateAppointmentCount()
{
    m_appointmentsCount++;
    ui->appointmentsValueLabel->setText(QString::number(m_appointmentsCount));
}

void Dashboard::updatePatientCount(int count)
{
    m_patientsCount = count;
    ui->patientsValueLabel->setText(QString::number(count));
}

void Dashboard::setupConnections()
{
    connect(m_patientsButton, &QPushButton::clicked, this, &Dashboard::showPatientRecords);
    connect(m_appointmentsButton, &QPushButton::clicked, this, &Dashboard::showAppointmentForm);
    connect(m_billingButton, &QPushButton::clicked, this, &Dashboard::showBillingPage);
    connect(m_reportsButton, &QPushButton::clicked, this, &Dashboard::showReportsPage);
    connect(m_logoutButton, &QPushButton::clicked, this, &Dashboard::logoutRequested);
    connect(m_changeProfileButton, &QPushButton::clicked, this, &Dashboard::onChangeProfilePicture);
}

void Dashboard::loadProfilePicture(const QString &username)
{
    QString picPath = QString("profile_pics/%1.png").arg(username);
    QPixmap pixmap;

    if (QFile::exists(picPath)) {
        pixmap.load(picPath);
    } else {
        pixmap.load(":/images/default_profile.png");
    }

    if (pixmap.isNull()) {
        pixmap = QPixmap(100, 100);
        pixmap.fill(Qt::lightGray);
    }

    m_profilePicLabel->setPixmap(
        pixmap.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation)
    );
}

void Dashboard::onChangeProfilePicture()
{
    QString fileName = QFileDialog::getOpenFileName(
        this,
        tr("Select Profile Picture"),
        "",
        tr("Images (*.png *.jpg *.jpeg *.bmp)")
    );
    if (fileName.isEmpty()) return;

    QDir dir("profile_pics");
    if (!dir.exists() && !dir.mkpath(".")) {
        QMessageBox::warning(this, "Error", "Could not create profile pictures directory");
        return;
    }

    QString username = m_welcomeLabel->text().split(',').first().split(' ').last();
    QString newFileName = QString("profile_pics/%1.png").arg(username);

    if (QFile::exists(newFileName)) {
        if (!QFile::remove(newFileName)) {
            QMessageBox::warning(this, "Error", "Could not replace existing profile picture");
            return;
        }
    }

    if (QFile::copy(fileName, newFileName)) {
        loadProfilePicture(username);
        QMessageBox::information(this, "Success", "Profile picture updated successfully");
    } else {
        QMessageBox::warning(this, "Error", "Failed to save profile picture");
    }
}
