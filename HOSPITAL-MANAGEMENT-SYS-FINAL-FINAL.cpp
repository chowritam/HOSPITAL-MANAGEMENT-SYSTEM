#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

struct Patient 
{
    int id;
    string name, contact, history;

    void input() 
    {
        cout << "ID: "; cin >> id; cin.ignore();
        cout << "Name: "; getline(cin, name);
        cout << "Contact: "; getline(cin, contact);
        cout << "History: "; getline(cin, history);
    }

    void display()
     const {
        cout << "\nID: " << id
             << "\nName: " << name
             << "\nContact: " << contact
             << "\nHistory: " << history
             << "\n-------------------\n";
    }
};

struct Appointment 
{
    int pid;
    string date, doctor;

    void input() 
    {
        cout << "Patient ID: "; cin >> pid; cin.ignore();
        cout << "Date: "; getline(cin, date);
        cout << "Doctor: "; getline(cin, doctor);
    }

    void display() const 
    {
        cout << "\nPatient ID: " << pid
             << "\nDate: " << date
             << "\nDoctor: " << doctor
             << "\n-------------------\n";
    }
};

struct Bill 
{
    int pid;
    double amount;

    void input() 
    {
        cout << "Patient ID: "; cin >> pid;
        cout << "Amount: Rs."; cin >> amount;
    }

    void display() const 
    {
        cout << "\nPatient ID: " << pid
             << "\nBill Amount: Rs." << amount
             << "\n-------------------\n";
    }
};



template <typename T>
void saveToFile(const vector<T>& data, const string& filename) 
{
    ofstream f(filename);
    for (const auto& item : data) 
    {
        if constexpr (is_same_v<T, Patient>)
            f << item.id << "," << item.name << "," << item.contact << "," << item.history << "\n";
        else if constexpr (is_same_v<T, Appointment>)
            f << item.pid << "," << item.date << "," << item.doctor << "\n";
        else if constexpr (is_same_v<T, Bill>)
            f << item.pid << "," << item.amount << "\n";
    }
}

vector<Patient> loadPatients() 
{
    vector<Patient> pts; ifstream f("patients.txt"); string line;
    while (getline(f, line)) 
    {
        stringstream ss(line); Patient p; string id;
        getline(ss, id, ',');
        getline(ss, p.name, ',');
        getline(ss, p.contact, ',');
        getline(ss, p.history);
        if (!id.empty()) { p.id = stoi(id); pts.push_back(p); }
    }
    return pts;
}

vector<Appointment> loadAppointments() 
{
    vector<Appointment> apps; ifstream f("appointments.txt"); string line;
    while (getline(f, line)) 
    {
        stringstream ss(line); Appointment a; string id;
        getline(ss, id, ',');
        getline(ss, a.date, ',');
        getline(ss, a.doctor);
        if (!id.empty()) { a.pid = stoi(id); apps.push_back(a); }
    }
    return apps;
}

vector<Bill> loadBills() 
{
    vector<Bill> bills; ifstream f("bills.txt"); string line;
    while (getline(f, line)) 
    {
        stringstream ss(line); Bill b; string id, amt;
        getline(ss, id, ',');
        getline(ss, amt);
        if (!id.empty()) { b.pid = stoi(id); b.amount = stod(amt); bills.push_back(b); }
    }
    return bills;
}


int main() 
{
    vector<Patient> patients = loadPatients();
    vector<Appointment> appointments = loadAppointments();
    vector<Bill> bills = loadBills();

    while (true) 
    {
        cout << "\n==== HOSPITAL MANAGEMENT ====\n";
        cout << "1. Add Patient\n2. View Patients\n";
        cout << "3. Add Appointment\n4. View Appointments\n";
        cout << "5. Add Bill\n6. View Bills\n";
        cout << "7. Exit\nChoice: ";

        int ch; cin >> ch; cin.ignore();

        if (ch == 1) 
        {
            Patient p; p.input();
            patients.push_back(p);
            saveToFile(patients, "patients.txt");
        }
        else if (ch == 2) 
        {
            if (patients.empty()) cout << "No patients found.\n";
            else for (auto &p : patients) p.display();
        }
        else if (ch == 3) 
        {
            Appointment a; a.input();
            appointments.push_back(a);
            saveToFile(appointments, "appointments.txt");
        }
        else if (ch == 4) 
        {
            if (appointments.empty()) cout << "No appointments found.\n";
            else for (auto &a : appointments) a.display();
        }
        else if (ch == 5) 
        {
            Bill b; b.input();
            bills.push_back(b);
            saveToFile(bills, "bills.txt");
        }
        else if (ch == 6) 
        {
            if (bills.empty()) cout << "No bills found.\n";
            else for (auto &b : bills) b.display();
        }
        else if (ch == 7) 
        {
            cout << "Exiting...\n";
            break;
        }
        else cout << "Invalid choice.\n";
    }
    return 0;
}
