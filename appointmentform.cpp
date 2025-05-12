#include "AppointmentForm.h"
#include "ui_appointmentform.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QComboBox>
#include <QDateEdit>
#include <QMessageBox>
#include <QTextEdit>
#include <QPushButton>
#include <QDateTime>
#include <QTime>

// --- AppointmentForm Implementation ---

AppointmentForm::AppointmentForm(QWidget *parent)
    : QWidget(parent),
    ui(new Ui::AppointmentForm),
    nextPatientId(1),
    nextDoctorId(1),
    nextAppointmentId(1)
{
    ui->setupUi(this);
    this->setFixedSize(800, 600);
    ui->dateEdit->setMinimumDate(QDate::currentDate());
    ui->timeSlotComboBox->setEnabled(false);

    // Load from file (or initialize sample data if file missing)
    loadFromFile();
    if (patients.isEmpty() || doctors.isEmpty()) {
        initializeSampleData();
        saveToFile();
    }

    loadPatients();
    loadDoctors();

    connect(ui->doctorComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &AppointmentForm::on_doctorComboBox_currentIndexChanged);
    connect(ui->dateEdit, &QDateEdit::dateChanged,
            this, &AppointmentForm::updateTimeSlots);
    connect(ui->saveButton, &QPushButton::clicked,
            this, &AppointmentForm::on_saveButton_clicked);
    connect(ui->cancelButton, &QPushButton::clicked,
            this, &AppointmentForm::on_cancelButton_clicked);

    connect(ui->patientComboBox, &QComboBox::currentTextChanged,
            this, &AppointmentForm::validateForm);
    connect(ui->doctorComboBox, &QComboBox::currentTextChanged,
            this, &AppointmentForm::validateForm);
    connect(ui->timeSlotComboBox, &QComboBox::currentTextChanged,
            this, &AppointmentForm::validateForm);
    connect(ui->reasonTextEdit, &QTextEdit::textChanged,
            this, &AppointmentForm::validateForm);

    validateForm();
}

AppointmentForm::~AppointmentForm() {
    saveToFile();
    delete ui;
}

void AppointmentForm::resetForm() {
    if (!ui) return;
    ui->patientComboBox->setCurrentIndex(0);
    ui->doctorComboBox->setCurrentIndex(0);
    ui->dateEdit->setDate(QDate::currentDate());
    ui->timeSlotComboBox->clear();
    ui->reasonTextEdit->clear();
    validateForm();
}

void AppointmentForm::initializeSampleData() {
    patients.clear();
    doctors.clear();
    appointments.clear();
    nextPatientId = 1;
    nextDoctorId = 1;
    nextAppointmentId = 1;

    patients.append({nextPatientId++, "John", "Doe"});
    patients.append({nextPatientId++, "Jane", "Smith"});
    patients.append({nextPatientId++, "Robert", "Johnson"});
    patients.append({nextPatientId++, "Emily", "Williams"});

    doctors.append({nextDoctorId++, "Sarah", "Wilson", "Cardiology"});
    doctors.append({nextDoctorId++, "Michael", "Brown", "Pediatrics"});
    doctors.append({nextDoctorId++, "David", "Miller", "Neurology"});
    doctors.append({nextDoctorId++, "Lisa", "Davis", "Dermatology"});

    QDateTime now = QDateTime::currentDateTime();
    appointments.append({nextAppointmentId++, 1, 1, now.addDays(1).addSecs(9*3600), "Heart checkup"});
    appointments.append({nextAppointmentId++, 2, 2, now.addDays(2).addSecs(10*3600 + 30*60), "Child vaccination"});
    appointments.append({nextAppointmentId++, 3, 3, now.addDays(3).addSecs(14*3600), "Neurological consultation"});
}

void AppointmentForm::loadPatients() {
    if (!ui || !ui->patientComboBox) return;
    ui->patientComboBox->clear();
    ui->patientComboBox->addItem("Select Patient", -1);
    for (const Patient& patient : patients)
        ui->patientComboBox->addItem(patient.fullName(), patient.id);
}

void AppointmentForm::loadDoctors() {
    if (!ui || !ui->doctorComboBox) return;
    ui->doctorComboBox->clear();
    ui->doctorComboBox->addItem("Select Doctor", -1);
    for (const Doctor& doctor : doctors)
        ui->doctorComboBox->addItem(doctor.fullName(), doctor.id);
}

void AppointmentForm::updateTimeSlots() {
    if (!ui || !ui->timeSlotComboBox || !ui->doctorComboBox || !ui->dateEdit) return;
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
    for (const QDateTime& slot : availableSlots)
        ui->timeSlotComboBox->addItem(slot.time().toString("hh:mm AP"), slot);
}

QList<QDateTime> AppointmentForm::getAvailableTimeSlots(int doctorId, const QDate& date) const {
    QList<QDateTime> availableSlots;
    for (int hour = 9; hour <= 16; hour++) {
        availableSlots << QDateTime(date, QTime(hour, 0));
        availableSlots << QDateTime(date, QTime(hour, 30));
    }
    for (const Appointment& appt : appointments) {
        if (appt.doctorId == doctorId && appt.dateTime.date() == date)
            availableSlots.removeAll(appt.dateTime);
    }
    return availableSlots;
}

bool AppointmentForm::isTimeSlotAvailable(int doctorId, const QDateTime& dateTime) const {
    for (const Appointment& appt : appointments)
        if (appt.doctorId == doctorId && appt.dateTime == dateTime)
            return false;
    return true;
}

void AppointmentForm::on_doctorComboBox_currentIndexChanged(int) {
    updateTimeSlots();
}

void AppointmentForm::on_saveButton_clicked() {
    if (!ui) return;
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

    appointments.append({nextAppointmentId++, patientId, doctorId, dateTime, reason});
    saveToFile();
    QMessageBox::information(this, "Success", "Appointment scheduled successfully!");
    emit appointmentScheduled();
    emit finished();
}

void AppointmentForm::on_cancelButton_clicked() {
    emit finished();
}

void AppointmentForm::validateForm() {
    if (!ui) return;
    bool isValid = ui->patientComboBox->currentData().toInt() != -1 &&
                   ui->doctorComboBox->currentData().toInt() != -1 &&
                   ui->timeSlotComboBox->currentData().isValid() &&
                   !ui->reasonTextEdit->toPlainText().isEmpty();
    if (ui->saveButton)
        ui->saveButton->setEnabled(isValid);
}

// --- File Persistence ---

void AppointmentForm::saveToFile() {
    QFile file("appointments.json");
    if (!file.open(QIODevice::WriteOnly)) return;

    QJsonObject root;
    QJsonArray patientsArray, doctorsArray, appointmentsArray;

    for (const Patient &p : patients) patientsArray.append(p.toJson());
    for (const Doctor &d : doctors) doctorsArray.append(d.toJson());
    for (const Appointment &a : appointments) appointmentsArray.append(a.toJson());

    root["patients"] = patientsArray;
    root["doctors"] = doctorsArray;
    root["appointments"] = appointmentsArray;
    root["nextPatientId"] = nextPatientId;
    root["nextDoctorId"] = nextDoctorId;
    root["nextAppointmentId"] = nextAppointmentId;

    QJsonDocument doc(root);
    file.write(doc.toJson());
    file.close();
}

void AppointmentForm::loadFromFile() {
    QFile file("appointments.json");
    if (!file.open(QIODevice::ReadOnly)) return;

    QByteArray data = file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject root = doc.object();

    patients.clear();
    for (const QJsonValue &v : root["patients"].toArray())
        patients.append(Patient::fromJson(v.toObject()));

    doctors.clear();
    for (const QJsonValue &v : root["doctors"].toArray())
        doctors.append(Doctor::fromJson(v.toObject()));

    appointments.clear();
    for (const QJsonValue &v : root["appointments"].toArray())
        appointments.append(Appointment::fromJson(v.toObject()));

    nextPatientId = root.value("nextPatientId").toInt(1);
    nextDoctorId = root.value("nextDoctorId").toInt(1);
    nextAppointmentId = root.value("nextAppointmentId").toInt(1);

    file.close();
}
