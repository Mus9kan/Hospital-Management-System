#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

struct Doctor {
    int id;
    string name;
    string specialization;
    string availableTime;
};

struct Patient {
    int id;
    string name;
    string disease;
    int doctorId;
};

struct Appointment {
    int patientId;
    int doctorId;
    string date;
};

struct Bill {
    int patientId;
    float consultationFee;
    float testCharges;
    float medicineCharges;

    float total() const {
        return consultationFee + testCharges + medicineCharges;
    }
};

vector<Doctor> doctors;
vector<Patient> patients;
vector<Appointment> appointments;
vector<Bill> bills;

bool login() {
    string username, password;
    cout << "---- Admin Login ----\n";
    cout << "Username: "; cin >> username;
    cout << "Password: "; cin >> password;
    return (username == "admin" && password == "admin123");
}

void saveDoctorsToFile() {
    ofstream out("doctors.txt");
    for (auto& d : doctors)
        out << d.id << "," << d.name << "," << d.specialization << "," << d.availableTime << "\n";
}

void savePatientsToFile() {
    ofstream out("patients.txt");
    for (auto& p : patients)
        out << p.id << "," << p.name << "," << p.disease << "," << p.doctorId << "\n";
}

void loadDoctorsFromFile() {
    doctors.clear();
    ifstream in("doctors.txt");
    string line;
    while (getline(in, line)) {
        Doctor d;
        size_t pos;
        pos = line.find(","); d.id = stoi(line.substr(0, pos)); line.erase(0, pos + 1);
        pos = line.find(","); d.name = line.substr(0, pos); line.erase(0, pos + 1);
        pos = line.find(","); d.specialization = line.substr(0, pos); line.erase(0, pos + 1);
        d.availableTime = line;
        doctors.push_back(d);
    }
}

void loadPatientsFromFile() {
    patients.clear();
    ifstream in("patients.txt");
    string line;
    while (getline(in, line)) {
        Patient p;
        size_t pos;
        pos = line.find(","); p.id = stoi(line.substr(0, pos)); line.erase(0, pos + 1);
        pos = line.find(","); p.name = line.substr(0, pos); line.erase(0, pos + 1);
        pos = line.find(","); p.disease = line.substr(0, pos); line.erase(0, pos + 1);
        p.doctorId = stoi(line);
        patients.push_back(p);
    }
}

void loadSampleData() {
    doctors = {
        {101, "Dr. Raj Mehta", "Cardiology", "9 AM - 12 PM"},
        {102, "Dr. Anjali Sharma", "Neurology", "10 AM - 1 PM"},
        {103, "Dr. Ravi Verma", "Orthopedics", "2 PM - 5 PM"},
        {104, "Dr. Sneha Kapoor", "Pediatrics", "11 AM - 2 PM"},
        {105, "Dr. Arjun Desai", "ENT", "3 PM - 6 PM"},
        {106, "Dr. Priya Nair", "Dermatology", "1 PM - 4 PM"},
        {107, "Dr. Manish Rao", "Oncology", "9 AM - 11 AM"},
        {108, "Dr. Komal Jain", "Gynecology", "10 AM - 12 PM"},
        {109, "Dr. Vikas Saxena", "Urology", "12 PM - 3 PM"},
        {110, "Dr. Alka Bansal", "Psychiatry", "2 PM - 5 PM"}
    };

    patients = {
        {201, "Aryan Singh", "Heart Disease", 101},
        {202, "Meera Das", "Migraine", 102},
        {203, "Rohan Malhotra", "Fracture", 103},
        {204, "Ishita Dey", "Flu", 104},
        {205, "Kunal Tiwari", "Hearing Loss", 105},
        {206, "Pooja Roy", "Skin Rash", 106},
        {207, "Aman Yadav", "Cancer", 107},
        {208, "Neha Sinha", "Pregnancy", 108},
        {209, "Rahul Bhatt", "Kidney Stone", 109},
        {210, "Tanvi Joshi", "Anxiety", 110}
    };

    saveDoctorsToFile();
    savePatientsToFile();
    cout << "[Sample Data Loaded]\n";
}

void addDoctor() {
    Doctor d;
    cout << "Enter Doctor ID: "; cin >> d.id;
    cout << "Enter Name: "; cin.ignore(); getline(cin, d.name);
    cout << "Enter Specialization: "; getline(cin, d.specialization);
    cout << "Enter Available Time: "; getline(cin, d.availableTime);
    doctors.push_back(d);
    saveDoctorsToFile();
    cout << "Doctor added successfully.\n";
}

void addPatient() {
    Patient p;
    cout << "Enter Patient ID: "; cin >> p.id;
    cout << "Enter Name: "; cin.ignore(); getline(cin, p.name);
    cout << "Enter Disease: "; getline(cin, p.disease);
    cout << "Enter Doctor ID: "; cin >> p.doctorId;
    patients.push_back(p);
    savePatientsToFile();
    cout << "Patient added successfully.\n";
}

void scheduleAppointment() {
    Appointment a;
    cout << "Enter Patient ID: "; cin >> a.patientId;
    cout << "Enter Doctor ID: "; cin >> a.doctorId;
    cout << "Enter Date (DD/MM/YYYY): "; cin >> a.date;
    appointments.push_back(a);
    cout << "Appointment scheduled successfully.\n";

    // Show appointment report
    Patient patient;
    Doctor doctor;
    bool foundP = false, foundD = false;

    for (auto& p : patients)
        if (p.id == a.patientId) { patient = p; foundP = true; break; }

    for (auto& d : doctors)
        if (d.id == a.doctorId) { doctor = d; foundD = true; break; }

    if (foundP && foundD) {
        cout << "--- Appointment Report ---\n";
        cout << "Patient: " << patient.name << " | Disease: " << patient.disease << "\n";
        cout << "Doctor: " << doctor.name << " | Specialization: " << doctor.specialization << " | Time: " << doctor.availableTime << "\n";
        cout << "Date: " << a.date << "\n";
    } else {
        cout << "Warning: Doctor or Patient record not found.\n";
    }
}

void generateBill() {
    Bill b;
    cout << "Enter Patient ID: "; cin >> b.patientId;
    cout << "Consultation Fee: "; cin >> b.consultationFee;
    cout << "Test Charges: "; cin >> b.testCharges;
    cout << "Medicine Charges: "; cin >> b.medicineCharges;
    bills.push_back(b);
    float total = b.total();

    string filename = "Bill_" + to_string(b.patientId) + ".txt";
    ofstream out(filename);
    out << "--- Patient Bill ---\n";
    out << "Patient ID: " << b.patientId << "\n";
    out << "Consultation Fee: Rs. " << b.consultationFee << "\n";
    out << "Test Charges: Rs. " << b.testCharges << "\n";
    out << "Medicine Charges: Rs. " << b.medicineCharges << "\n";
    out << "Total: Rs. " << total << "\n";
    out.close();

    cout << "Bill saved to: " << filename << "\n";
    cout << "--- Bill Report ---\n";
    cout << "Patient ID: " << b.patientId << "\n";
    cout << "Consultation: Rs. " << b.consultationFee << "\n";
    cout << "Tests: Rs. " << b.testCharges << "\n";
    cout << "Medicine: Rs. " << b.medicineCharges << "\n";
    cout << "Total: Rs. " << total << "\n";
}

void searchPatientByName() {
    string name;
    cout << "Enter Name to Search: ";
    cin.ignore(); getline(cin, name);
    for (auto& p : patients) {
        if (p.name.find(name) != string::npos) {
            cout << "ID: " << p.id << ", Name: " << p.name << ", Disease: " << p.disease << ", Doctor ID: " << p.doctorId << "\n";
        }
    }
}

void searchPatientByDisease() {
    string disease;
    cout << "Enter Disease to Search: ";
    cin.ignore(); getline(cin, disease);
    for (auto& p : patients) {
        if (p.disease.find(disease) != string::npos) {
            cout << "ID: " << p.id << ", Name: " << p.name << ", Disease: " << p.disease << ", Doctor ID: " << p.doctorId << "\n";
        }
    }
}

void displayDoctors() {
    for (auto& d : doctors) {
        cout << "ID: " << d.id << ", Name: " << d.name << ", Specialization: " << d.specialization << ", Time: " << d.availableTime << "\n";
    }
}

void displayPatients() {
    for (auto& p : patients) {
        cout << "ID: " << p.id << ", Name: " << p.name << ", Disease: " << p.disease << ", Doctor ID: " << p.doctorId << "\n";
    }
}

void mainMenu() {
    int choice;

    loadDoctorsFromFile();
    loadPatientsFromFile();

    if (doctors.empty() || patients.empty()) {
        loadSampleData();
    }

    do {
        cout << "\n--- Hospital Management System ---\n";
        cout << "1. Add Doctor\n2. Add Patient\n3. View Doctors\n4. View Patients\n";
        cout << "5. Schedule Appointment\n6. Generate Bill\n7. Search by Name\n8. Search by Disease\n0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1: addDoctor(); break;
            case 2: addPatient(); break;
            case 3: displayDoctors(); break;
            case 4: displayPatients(); break;
            case 5: scheduleAppointment(); break;
            case 6: generateBill(); break;
            case 7: searchPatientByName(); break;
            case 8: searchPatientByDisease(); break;
            case 0: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice. Try again.\n"; break;
        }
    } while (choice != 0);
}

int main() {
    if (login()) {
        mainMenu();
    } else {
        cout << "Login failed.\n";
    }
    return 0;
}
