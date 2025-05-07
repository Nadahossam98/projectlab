#include "appointmentform.h"
#include "ui_appointmentform.h"

#include <QMessageBox>
#include <QTime>
#include <QDebug>

appointmentform::appointmentform(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::appointmentform)
{
    ui->setupUi(this);

    // Initialize UI elements
    ui->dateEdit->setMinimumDate(QDate::currentDate());
    ui->timeSlotComboBox->setEnabled(false);

    // Initialize sample data
    initializeSampleData();

    // Load data into UI
    loadPatients();
    loadDoctors();

    // Connect signals and slots
    connect(ui->doctorComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &appointmentform::on_doctorComboBox_currentIndexChanged);
    connect(ui->dateEdit, &QDateEdit::dateChanged, this, &appointmentform::updateTimeSlots);
    connect(ui->saveButton, &QPushButton::clicked, this, &appointmentform::on_saveButton_clicked);
    connect(ui->cancelButton, &QPushButton::clicked, this, &appointmentform::on_cancelButton_clicked);

    // Form validation connections
    connect(ui->patientComboBox, &QComboBox::currentTextChanged, this, &appointmentform::validateForm);
    connect(ui->doctorComboBox, &QComboBox::currentTextChanged, this, &appointmentform::validateForm);
    connect(ui->timeSlotComboBox, &QComboBox::currentTextChanged, this, &appointmentform::validateForm);

    validateForm(); // Initial validation
}

appointmentform::~appointmentform()
{
    delete ui;
}
void appointmentform::resetForm()
{
    // Clear all form fields
    ui->patientComboBox->setCurrentIndex(0);
    ui->doctorComboBox->setCurrentIndex(0);
    ui->dateEdit->setDate(QDate::currentDate());
    ui->timeSlotComboBox->clear();
    ui->reasonTextEdit->clear();
}


void appointmentform::initializeSampleData()
{
    // Sample patients
    patients.append({nextPatientId++, "John", "Doe"});
    patients.append({nextPatientId++, "Jane", "Smith"});
    patients.append({nextPatientId++, "Robert", "Johnson"});
    patients.append({nextPatientId++, "Emily", "Williams"});

    // Sample doctors
    doctors.append({nextDoctorId++, "Sarah", "Wilson", "Cardiology"});
    doctors.append({nextDoctorId++, "Michael", "Brown", "Pediatrics"});
    doctors.append({nextDoctorId++, "David", "Miller", "Neurology"});
    doctors.append({nextDoctorId++, "Lisa", "Davis", "Dermatology"});

    // Sample appointments
    QDateTime now = QDateTime::currentDateTime();
    appointments.append({1, 1, now.addDays(1).addSecs(9*3600), "Heart checkup"});
    appointments.append({2, 2, now.addDays(2).addSecs(10*3600 + 30*60), "Child vaccination"});
    appointments.append({3, 3, now.addDays(3).addSecs(14*3600), "Neurological consultation"});
}

void appointmentform::loadPatients()
{
    ui->patientComboBox->clear();
    ui->patientComboBox->addItem("Select Patient", -1);

    for (const Patient& patient : patients) {
        ui->patientComboBox->addItem(patient.fullName(), patient.id);
    }
}

void appointmentform::loadDoctors()
{
    ui->doctorComboBox->clear();
    ui->doctorComboBox->addItem("Select Doctor", -1);

    for (const Doctor& doctor : doctors) {
        ui->doctorComboBox->addItem(doctor.fullName(), doctor.id);
    }
}

void appointmentform::updateTimeSlots()
{
    ui->timeSlotComboBox->clear();
    ui->timeSlotComboBox->setEnabled(true);

    int doctorId = ui->doctorComboBox->currentData().toInt();
    if (doctorId == -1) {
        ui->timeSlotComboBox->setEnabled(false);
        ui->timeSlotComboBox->addItem("Select doctor first");
        return;
    }

    QDate date = ui->dateEdit->date();
    QList<QDateTime> availableSlots = getAvailableTimeSlots(doctorId, date);

    if (availableSlots.isEmpty()) {
        ui->timeSlotComboBox->addItem("No available slots");
        return;
    }

    ui->timeSlotComboBox->addItem("Select Time Slot");
    for (const QDateTime& slot : availableSlots) {
        ui->timeSlotComboBox->addItem(slot.time().toString("hh:mm AP"), slot);
    }
}

QList<QDateTime> appointmentform::getAvailableTimeSlots(int doctorId, const QDate& date) const
{
    QList<QDateTime> availableSlots;

    // Generate time slots from 9AM to 4PM, every 30 minutes
    for (int hour = 9; hour <= 16; hour++) {
        availableSlots << QDateTime(date, QTime(hour, 0));
        availableSlots << QDateTime(date, QTime(hour, 30));
    }

    // Remove booked slots
    for (const Appointment& appt : appointments) {
        if (appt.doctorId == doctorId && appt.dateTime.date() == date) {
            availableSlots.removeAll(appt.dateTime);
        }
    }

    return availableSlots;
}

bool appointmentform::isTimeSlotAvailable(int doctorId, const QDateTime& dateTime) const
{
    for (const Appointment& appt : appointments) {
        if (appt.doctorId == doctorId && appt.dateTime == dateTime) {
            return false;
        }
    }
    return true;
}

void appointmentform::on_doctorComboBox_currentIndexChanged(int index)
{
    Q_UNUSED(index);
    updateTimeSlots();
}

void appointmentform::on_saveButton_clicked()
{
    int patientId = ui->patientComboBox->currentData().toInt();
    int doctorId = ui->doctorComboBox->currentData().toInt();
    QDateTime dateTime = ui->timeSlotComboBox->currentData().toDateTime();
    QString reason = ui->reasonTextEdit->toPlainText().trimmed();

    if (patientId == -1 || doctorId == -1 || !dateTime.isValid()) {
        QMessageBox::warning(this, "Validation Error", "Please fill all required fields.");
        return;
    }

    if (!isTimeSlotAvailable(doctorId, dateTime)) {
        QMessageBox::warning(this, "Time Slot Unavailable",
                             "The selected time slot is no longer available. Please choose another time.");
        updateTimeSlots();
        return;
    }

    // Create new appointment
    appointments.append({patientId, doctorId, dateTime, reason});

    QMessageBox::information(this, "Success", "Appointment scheduled successfully!");
    emit appointmentScheduled();
    close();
}

void appointmentform::on_cancelButton_clicked()
{
    emit cancelled();
    close();
}

void appointmentform::validateForm()
{
    bool isValid = ui->patientComboBox->currentData().toInt() != -1 &&
                   ui->doctorComboBox->currentData().toInt() != -1 &&
                   ui->timeSlotComboBox->currentData().isValid();

    ui->saveButton->setEnabled(isValid);
}
