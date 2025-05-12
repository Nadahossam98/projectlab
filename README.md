Hospital Patient Management System
Overview
The Hospital Patient Management System is a cross-platform desktop application (built with Qt/C++) that allows hospital staff to efficiently manage patient records, appointments, billing, and reporting. It supports multiple user roles (Admin, Doctor, Receptionist), each with appropriate access levels. The system is designed for clarity, reliability, and ease of use, with persistent data storage and export capabilities.

Features
User Authentication:
Secure login with role-based access (Admin, Doctor, Receptionist).
Passwords are stored securely (hashed).

Dashboard:
Overview of key statistics: patient count, appointments, bills, and reports.
Quick navigation to all modules.

Patient Records:
Add, edit, delete, and search patient records.
Each record includes ID, name, age, medical history, doctor, and last visit date.
Data is stored in a CSV file for persistence.

Appointment Scheduling:
Book appointments between patients and doctors.
Prevents double-booking and allows time slot selection.
Validates input and manages appointment data in memory.

Billing:
Add, view, and mark bills as paid.
Calculates total pending and paid amounts.
Validates all billing inputs.

Reports:
Generate summary reports (total patients, revenue, doctor appointments).
Export reports as CSV or TXT files.

Profile Management:
Each user can upload and change their profile picture.

Navigation:
All modules have a "Back" button to return to the dashboard.
