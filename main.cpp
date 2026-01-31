#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <memory>
#include <ctime>

using namespace std;

class User;
class Admin;
class Doctor;
class Patient;
class Receptionist;
class Appointment;
class MedicalRecord;
class Billing;
class Room;
class HospitalManager;

class User {
protected:
    string userId;
    string name;
    string password;
    string role;

public:
    User(const string& id, const string& username, const string& pwd, const string& userRole)
        : userId(id), name(username), password(pwd), role(userRole) {}

    virtual ~User() = default;

    bool login(const string& id, const string& pwd) const {
        return (userId == id && password == pwd);
    }

    string getUserId() const { return userId; }
    string getName() const { return name; }
    string getRole() const { return role; }

    virtual void displayMenu() const = 0;
    virtual void saveToFile() const = 0;
};

class MedicalRecord {
private:
    string recordId;
    string patientId;
    string doctorId;
    string date;
    string diagnosis;
    string treatment;

public:
    MedicalRecord(const string& recId, const string& patId, const string& docId,
                  const string& dt, const string& diag, const string& treat)
        : recordId(recId), patientId(patId), doctorId(docId), date(dt), diagnosis(diag), treatment(treat) {}

    string getRecordId() const { return recordId; }
    string getPatientId() const { return patientId; }
    string getDoctorId() const { return doctorId; }
    string getDate() const { return date; }
    string getDiagnosis() const { return diagnosis; }
    string getTreatment() const { return treatment; }

    void saveToFile() const {
        ofstream file("medical_records.txt", ios::app);
        if (file.is_open()) {
            file << recordId << "," << patientId << "," << doctorId << ","
                 << date << "," << diagnosis << "," << treatment << "\n";
            file.close();
        }
    }

    void display() const {
        cout << "Record ID: " << recordId << "\n";
        cout << "Date: " << date << "\n";
        cout << "Diagnosis: " << diagnosis << "\n";
        cout << "Treatment: " << treatment << "\n";
    }
};

class Billing {
private:
    string billId;
    string patientId;
    double amount;
    bool isPaid;
    string date;
    string description;

public:
    Billing(const string& bId, const string& patId, double amt, bool paid,
            const string& dt, const string& desc)
        : billId(bId), patientId(patId), amount(amt), isPaid(paid), date(dt), description(desc) {}

    string getBillId() const { return billId; }
    string getPatientId() const { return patientId; }
    double getAmount() const { return amount; }
    bool getIsPaid() const { return isPaid; }

    void setIsPaid(bool paid) { isPaid = paid; }

    void saveToFile() const {
        ofstream file("billing.txt", ios::app);
        if (file.is_open()) {
            file << billId << "," << patientId << "," << amount << ","
                 << (isPaid ? "1" : "0") << "," << date << "," << description << "\n";
            file.close();
        }
    }

    void display() const {
        cout << "Bill ID: " << billId << "\n";
        cout << "Date: " << date << "\n";
        cout << "Amount: $" << amount << "\n";
        cout << "Status: " << (isPaid ? "Paid" : "Unpaid") << "\n";
        cout << "Description: " << description << "\n";
    }
};

class Appointment {
private:
    string appointmentId;
    string patientId;
    string doctorId;
    string date;
    string time;
    string status;

public:
    Appointment(const string& appId, const string& patId, const string& docId,
                const string& dt, const string& tm, const string& stat)
        : appointmentId(appId), patientId(patId), doctorId(docId), date(dt), time(tm), status(stat) {}

    string getAppointmentId() const { return appointmentId; }
    string getPatientId() const { return patientId; }
    string getDoctorId() const { return doctorId; }
    string getDate() const { return date; }
    string getTime() const { return time; }
    string getStatus() const { return status; }

    void setStatus(const string& stat) { status = stat; }

    void saveToFile() const {
        ofstream file("appointments.txt", ios::app);
        if (file.is_open()) {
            file << appointmentId << "," << patientId << "," << doctorId << ","
                 << date << "," << time << "," << status << "\n";
            file.close();
        }
    }

    void display() const {
        cout << "Appointment ID: " << appointmentId << "\n";
        cout << "Date: " << date << " Time: " << time << "\n";
        cout << "Status: " << status << "\n";
    }
};

class Room {
private:
    string roomId;
    bool isOccupied;
    string patientId;
    string roomType;

public:
    Room(const string& rId, bool occupied, const string& patId, const string& type)
        : roomId(rId), isOccupied(occupied), patientId(patId), roomType(type) {}

    string getRoomId() const { return roomId; }
    bool getIsOccupied() const { return isOccupied; }
    string getPatientId() const { return patientId; }
    string getRoomType() const { return roomType; }

    void setIsOccupied(bool occupied) { isOccupied = occupied; }
    void setPatientId(const string& patId) { patientId = patId; }

    void saveToFile() const {
        ofstream file("rooms.txt", ios::app);
        if (file.is_open()) {
            file << roomId << "," << (isOccupied ? "1" : "0") << "," << patientId << "," << roomType << "\n";
            file.close();
        }
    }
};

class Admin : public User {
public:
    Admin(const string& id, const string& username, const string& pwd)
        : User(id, username, pwd, "Admin") {}

    void displayMenu() const override {
        cout << "\n--- Admin Menu ---\n";
        cout << "1. Add Doctor\n";
        cout << "2. Add Receptionist\n";
        cout << "3. View All Appointments\n";
        cout << "4. View Billing Summary\n";
        cout << "5. Logout\n";
    }

    void saveToFile() const override {
        ofstream file("users.txt", ios::app);
        if (file.is_open()) {
            file << userId << "," << name << "," << password << "," << role << "\n";
            file.close();
        }
    }
};

class Doctor : public User {
private:
    string specialization;

public:
    Doctor(const string& id, const string& username, const string& pwd, const string& spec)
        : User(id, username, pwd, "Doctor"), specialization(spec) {}

    string getSpecialization() const { return specialization; }

    void displayMenu() const override {
        cout << "\n--- Doctor Menu ---\n";
        cout << "1. View Appointments\n";
        cout << "2. Add Medical Record\n";
        cout << "3. View Patient Records\n";
        cout << "4. Logout\n";
    }

    void saveToFile() const override {
        ofstream file("users.txt", ios::app);
        if (file.is_open()) {
            file << userId << "," << name << "," << password << "," << role << "," << specialization << "\n";
            file.close();
        }
    }
};

class Patient : public User {
private:
    string contactNumber;
    string address;
    string gender;
    int age;

public:
    Patient(const string& id, const string& username, const string& pwd,
            const string& contact, const string& addr, const string& gen, int a)
        : User(id, username, pwd, "Patient"), contactNumber(contact), address(addr), gender(gen), age(a) {}

    void displayMenu() const override {
        cout << "\n--- Patient Menu ---\n";
        cout << "1. Book Appointment\n";
        cout << "2. View Appointments\n";
        cout << "3. Cancel Appointment\n";
        cout << "4. View Medical Records\n";
        cout << "5. View Bills\n";
        cout << "6. Update Profile\n";
        cout << "7. Logout\n";
    }

    void saveToFile() const override {
        ofstream file("users.txt", ios::app);
        if (file.is_open()) {
            file << userId << "," << name << "," << password << "," << role << ","
                 << contactNumber << "," << address << "," << gender << "," << age << "\n";
            file.close();
        }
    }
};

class Receptionist : public User {
public:
    Receptionist(const string& id, const string& username, const string& pwd)
        : User(id, username, pwd, "Receptionist") {}

    void displayMenu() const override {
        cout << "\n--- Receptionist Menu ---\n";
        cout << "1. Register New Patient\n";
        cout << "2. Schedule Appointment\n";
        cout << "3. Assign Room\n";
        cout << "4. Handle Billing\n";
        cout << "5. Logout\n";
    }

    void saveToFile() const override {
        ofstream file("users.txt", ios::app);
        if (file.is_open()) {
            file << userId << "," << name << "," << password << "," << role << "\n";
            file.close();
        }
    }
};

class UserFactory {
public:
    static unique_ptr<User> createUser(const string& role, const vector<string>& data) {
        if (role == "Admin") {
            return make_unique<Admin>(data[0], data[1], data[2]);
        }
        else if (role == "Doctor") {
            return make_unique<Doctor>(data[0], data[1], data[2], data[4]);
        }
        else if (role == "Patient") {
            return make_unique<Patient>(data[0], data[1], data[2], data[4], data[5], data[6], stoi(data[7]));
        }
        else if (role == "Receptionist") {
            return make_unique<Receptionist>(data[0], data[1], data[2]);
        }
        return nullptr;
    }
};

class HospitalManager {
private:
    static HospitalManager* instance;
    vector<unique_ptr<User>> users;
    vector<Appointment> appointments;
    vector<MedicalRecord> medicalRecords;
    vector<Billing> billings;
    vector<Room> rooms;

    HospitalManager() {
        loadUsers();
        loadAppointments();
        loadMedicalRecords();
        loadBillings();
        loadRooms();
    }

    void loadUsers() {
        ifstream file("users.txt");
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                vector<string> data;
                size_t pos = 0;
                string token;
                while ((pos = line.find(",")) != string::npos) {
                    token = line.substr(0, pos);
                    data.push_back(token);
                    line.erase(0, pos + 1);
                }
                data.push_back(line);

                if (data.size() >= 4) {
                    unique_ptr<User> user = UserFactory::createUser(data[3], data);
                    if (user) {
                        users.push_back(move(user));
                    }
                }
            }
            file.close();
        }
    }

    void loadAppointments() {
        ifstream file("appointments.txt");
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                vector<string> data;
                size_t pos = 0;
                string token;
                while ((pos = line.find(",")) != string::npos) {
                    token = line.substr(0, pos);
                    data.push_back(token);
                    line.erase(0, pos + 1);
                }
                data.push_back(line);

                if (data.size() >= 6) {
                    appointments.emplace_back(data[0], data[1], data[2], data[3], data[4], data[5]);
                }
            }
            file.close();
        }
    }

    void loadMedicalRecords() {
        ifstream file("medical_records.txt");
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                vector<string> data;
                size_t pos = 0;
                string token;
                while ((pos = line.find(",")) != string::npos) {
                    token = line.substr(0, pos);
                    data.push_back(token);
                    line.erase(0, pos + 1);
                }
                data.push_back(line);

                if (data.size() >= 6) {
                    medicalRecords.emplace_back(data[0], data[1], data[2], data[3], data[4], data[5]);
                }
            }
            file.close();
        }
    }

    void loadBillings() {
        ifstream file("billing.txt");
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                vector<string> data;
                size_t pos = 0;
                string token;
                while ((pos = line.find(",")) != string::npos) {
                    token = line.substr(0, pos);
                    data.push_back(token);
                    line.erase(0, pos + 1);
                }
                data.push_back(line);

                if (data.size() >= 6) {
                    billings.emplace_back(data[0], data[1], stod(data[2]), data[3] == "1", data[4], data[5]);
                }
            }
            file.close();
        }
    }

    void loadRooms() {
        ifstream file("rooms.txt");
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                vector<string> data;
                size_t pos = 0;
                string token;
                while ((pos = line.find(",")) != string::npos) {
                    token = line.substr(0, pos);
                    data.push_back(token);
                    line.erase(0, pos + 1);
                }
                data.push_back(line);

                if (data.size() >= 4) {
                    rooms.emplace_back(data[0], data[1] == "1", data[2], data[3]);
                }
            }
            file.close();
        }
    }

public:
    HospitalManager(const HospitalManager&) = delete;
    HospitalManager& operator=(const HospitalManager&) = delete;

    static HospitalManager* getInstance() {
        if (!instance) {
            instance = new HospitalManager();
        }
        return instance;
    }

    User* login(const string& id, const string& password) {
        for (const auto& user : users) {
            if (user->login(id, password)) {
                return user.get();
            }
        }
        return nullptr;
    }

    void addUser(unique_ptr<User> user) {
        user->saveToFile();
        users.push_back(move(user));
    }

    void addAppointment(const Appointment& appointment) {
        appointment.saveToFile();
        appointments.push_back(appointment);
    }

    void addMedicalRecord(const MedicalRecord& record) {
        record.saveToFile();
        medicalRecords.push_back(record);
    }

    void addBilling(const Billing& bill) {
        bill.saveToFile();
        billings.push_back(bill);
    }

    void updateRoom(const Room& room) {
        for (auto& r : rooms) {
            if (r.getRoomId() == room.getRoomId()) {
                r = room;
                break;
            }
        }
        ofstream file("rooms.txt");
        if (file.is_open()) {
            for (const auto& r : rooms) {
                file << r.getRoomId() << "," << (r.getIsOccupied() ? "1" : "0") << ","
                     << r.getPatientId() << "," << r.getRoomType() << "\n";
            }
            file.close();
        }
    }

    vector<Appointment> getPatientAppointments(const string& patientId) {
        vector<Appointment> result;
        for (const auto& appointment : appointments) {
            if (appointment.getPatientId() == patientId) {
                result.push_back(appointment);
            }
        }
        return result;
    }

    vector<Appointment> getDoctorAppointments(const string& doctorId) {
        vector<Appointment> result;
        for (const auto& appointment : appointments) {
            if (appointment.getDoctorId() == doctorId) {
                result.push_back(appointment);
            }
        }
        return result;
    }

    vector<MedicalRecord> getPatientRecords(const string& patientId) {
        vector<MedicalRecord> result;
        for (const auto& record : medicalRecords) {
            if (record.getPatientId() == patientId) {
                result.push_back(record);
            }
        }
        return result;
    }

    vector<Billing> getPatientBills(const string& patientId) {
        vector<Billing> result;
        for (const auto& bill : billings) {
            if (bill.getPatientId() == patientId) {
                result.push_back(bill);
            }
        }
        return result;
    }

    vector<Room> getAvailableRooms() {
        vector<Room> result;
        for (const auto& room : rooms) {
            if (!room.getIsOccupied()) {
                result.push_back(room);
            }
        }
        return result;
    }

    vector<Doctor> getDoctors() {
        vector<Doctor> result;
        for (const auto& user : users) {
            if (user->getRole() == "Doctor") {
                auto doctor = dynamic_cast<Doctor*>(user.get());
                if (doctor) {
                    result.push_back(*doctor);
                }
            }
        }
        return result;
    }
};

HospitalManager* HospitalManager::instance = nullptr;

int main() {
    HospitalManager* manager = HospitalManager::getInstance();

    string userId, password;
    bool running = true;

    while (running) {
        cout << "\n===== Hospital Management System =====\n";
        cout << "1. Login\n";
        cout << "2. Exit\n";
        cout << "Choice: ";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1: {
                cout << "Enter User ID: ";
                cin >> userId;
                cout << "Enter Password: ";
                cin >> password;

                User* currentUser = manager->login(userId, password);
                if (currentUser) {
                    cout << "\nWelcome, " << currentUser->getName() << "!\n";
                    bool loggedIn = true;

                    while (loggedIn) {
                        currentUser->displayMenu();
                        cout << "Enter choice: ";
                        int userChoice;
                        cin >> userChoice;

                        if (currentUser->getRole() == "Admin") {
                            Admin* admin = dynamic_cast<Admin*>(currentUser);
                            if (userChoice == 5) {
                                loggedIn = false;
                            }
                        }
                        else if (currentUser->getRole() == "Doctor") {
                            Doctor* doctor = dynamic_cast<Doctor*>(currentUser);
                            if (userChoice == 4) {
                                loggedIn = false;
                            }
                        }
                        else if (currentUser->getRole() == "Patient") {
                            Patient* patient = dynamic_cast<Patient*>(currentUser);
                            if (userChoice == 7) {
                                loggedIn = false;
                            }
                        }
                        else if (currentUser->getRole() == "Receptionist") {
                            Receptionist* receptionist = dynamic_cast<Receptionist*>(currentUser);
                            if (userChoice == 5) {
                                loggedIn = false;
                            }
                        }
                    }
                } else {
                    cout << "Invalid User ID or Password!\n";
                }
                break;
            }
            case 2:
                running = false;
                cout << "Thank you for using Hospital Management System!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
