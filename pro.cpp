#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <limits>
using namespace std;

// Structs for Donor and Receiver
struct Donor {
    string name, bloodGroup, contact;
};

struct Receiver {
    string name, bloodGroup, contact;
};

// Utility to trim whitespace
string trim(const string& s) {
    size_t start = s.find_first_not_of(" \t\r\n");
    size_t end = s.find_last_not_of(" \t\r\n");
    return (start == string::npos) ? "" : s.substr(start, end - start + 1);
}

// Utility to convert string to uppercase
string toUpper(const string& s) {
    string res = s;
    transform(res.begin(), res.end(), res.begin(), ::toupper);
    return res;
}

// Valid blood groups
vector<string> validBloodGroups = {
    "O-", "O+", "A-", "A+", "B-", "B+", "AB-", "AB+"
};

// Display valid blood groups
void displayBloodGroups() {
    cout << "Valid blood groups: ";
    for (size_t i = 0; i < validBloodGroups.size(); ++i) {
        cout << validBloodGroups[i];
        if (i < validBloodGroups.size() - 1) cout << ", ";
    }
    cout << endl;
}

// Normalize blood group input
string normalizeBloodGroup(const string& bg) {
    string input = toUpper(trim(bg));
    if (input == "O NEGATIVE") return "O-";
    if (input == "O POSITIVE") return "O+";
    if (input == "A NEGATIVE") return "A-";
    if (input == "A POSITIVE") return "A+";
    if (input == "B NEGATIVE") return "B-";
    if (input == "B POSITIVE") return "B+";
    if (input == "AB NEGATIVE") return "AB-";
    if (input == "AB POSITIVE") return "AB+";
    return input;
}

// Validate blood group
bool isValidBloodGroup(const string& bg) {
    string normalized = normalizeBloodGroup(bg);
    for (const auto& v : validBloodGroups) {
        if (normalized == v) return true;
    }
    return false;
}

// Check blood group compatibility
bool isCompatible(const string& donor, const string& recipient) {
    string d = normalizeBloodGroup(donor);
    string r = normalizeBloodGroup(recipient);
    if (d == "O-") return true;
    if (d == "O+") return r == "O+" || r == "A+" || r == "B+" || r == "AB+";
    if (d == "A-") return r == "A-" || r == "A+" || r == "AB-" || r == "AB+";
    if (d == "A+") return r == "A+" || r == "AB+";
    if (d == "B-") return r == "B-" || r == "B+" || r == "AB-" || r == "AB+";
    if (d == "B+") return r == "B+" || r == "AB+";
    if (d == "AB-") return r == "AB-" || r == "AB+";
    if (d == "AB+") return r == "AB+";
    return false;
}

// Load donors from file
vector<Donor> loadDonors() {
    vector<Donor> donors;
    ifstream fin("donors.txt");
    if (!fin.is_open()) {
        cout << "Unable to open donors.txt. Starting with empty donor list.\n";
        return donors;
    }
    string line;
    while (getline(fin, line)) {
        stringstream ss(line);
        Donor d;
        getline(ss, d.name, ',');
        getline(ss, d.bloodGroup, ',');
        getline(ss, d.contact);
        d.name = trim(d.name);
        d.bloodGroup = normalizeBloodGroup(d.bloodGroup);
        d.contact = trim(d.contact);
        if (!d.name.empty() && isValidBloodGroup(d.bloodGroup) && !d.contact.empty()) {
            donors.push_back(d);
        }
    }
    fin.close();
    return donors;
}

// Load receivers from file
vector<Receiver> loadReceivers() {
    vector<Receiver> receivers;
    ifstream fin("receivers.txt");
    if (!fin.is_open()) {
        cout << "⚠️ Unable to open receivers.txt. Starting with empty receiver list.\n";
        return receivers;
    }
    string line;
    while (getline(fin, line)) {
        stringstream ss(line);
        Receiver r;
        getline(ss, r.name, ',');
        getline(ss, r.bloodGroup, ',');
        getline(ss, r.contact);
        r.name = trim(r.name);
        r.bloodGroup = normalizeBloodGroup(r.bloodGroup);
        r.contact = trim(r.contact);
        if (!r.name.empty() && isValidBloodGroup(r.bloodGroup) && !r.contact.empty()) {
            receivers.push_back(r);
        }
    }
    fin.close();
    return receivers;
}

// Save donor to file
void saveDonor(const Donor& d) {
    ofstream fout("donors.txt", ios::app);
    if (!fout.is_open()) {
        cout << " Error: Unable to save donor to file.\n";
        return;
    }
    fout << trim(d.name) << "," << normalizeBloodGroup(d.bloodGroup) << "," << trim(d.contact) << "\n";
    fout.close();
}

// Save receiver to file
void saveReceiver(const Receiver& r) {
    ofstream fout("receivers.txt", ios::app);
    if (!fout.is_open()) {
        cout << " Error: Unable to save receiver to file.\n";
        return;
    }
    fout << trim(r.name) << "," << normalizeBloodGroup(r.bloodGroup) << "," << trim(r.contact) << "\n";
    fout.close();
}

// Check for duplicate donor
bool isDuplicateDonor(const Donor& d, const vector<Donor>& donors) {
    for (const auto& donor : donors) {
        if (toUpper(trim(donor.name)) == toUpper(trim(d.name)) &&
            trim(donor.contact) == trim(d.contact)) {
            return true;
        }
    }
    return false;
}

// Register a new donor
void registerDonor() {
    Donor d;
    cout << "\nEnter your name: ";
    getline(cin, d.name);
    d.name = trim(d.name);
    if (d.name.empty()) {
        cout << " Error: Name cannot be empty.\n";
        return;
    }

    cout << "\n";
    displayBloodGroups();
    do {
        cout << "Enter blood group: ";
        getline(cin, d.bloodGroup);
        d.bloodGroup = normalizeBloodGroup(d.bloodGroup);
        if (!isValidBloodGroup(d.bloodGroup)) {
            cout << " Invalid blood group! Please choose from the list above.\n";
        }
    } while (!isValidBloodGroup(d.bloodGroup));

    cout << "Enter contact info (e.g., phone or email): ";
    getline(cin, d.contact);
    d.contact = trim(d.contact);
    if (d.contact.empty()) {
        cout << " Error: Contact cannot be empty.\n";
        return;
    }

    vector<Donor> donors = loadDonors();
    if (isDuplicateDonor(d, donors)) {
        cout << "\n Donor already registered!\n";
        return;
    }

    saveDonor(d);
    cout << "\n Donor registered successfully!\n";
}

// Request blood and auto-match donors
void requestBlood() {
    Receiver r;
    cout << "\nEnter your name: ";
    getline(cin, r.name);
    r.name = trim(r.name);
    if (r.name.empty()) {
        cout << " Error: Name cannot be empty.\n";
        return;
    }

    cout << "\n";
    displayBloodGroups();
    do {
        cout << "Enter required blood group: ";
        getline(cin, r.bloodGroup);
        r.bloodGroup = normalizeBloodGroup(r.bloodGroup);
        if (!isValidBloodGroup(r.bloodGroup)) {
            cout << " Invalid blood group! Please choose from the list above.\n";
        }
    } while (!isValidBloodGroup(r.bloodGroup));

    cout << "Enter your contact info (e.g., phone or email): ";
    getline(cin, r.contact);
    r.contact = trim(r.contact);
    if (r.contact.empty()) {
        cout << " Error: Contact cannot be empty.\n";
        return;
    }

    saveReceiver(r);

    vector<Donor> donors = loadDonors();
    vector<Donor> matched;

    // Find compatible donors if there exist any
    for (const auto& d : donors) {
        if (isCompatible(d.bloodGroup, r.bloodGroup)) {
            matched.push_back(d);
        }
    }

    cout << "\n Searching for compatible donors...\n";
    if (matched.empty()) {
        cout << "\n No compatible donors found at the moment.\n";
        cout << " Your request has been recorded. We'll notify you when a match is found.\n";
    } else {
        cout << "\n Yes, donor(s) exist! Here are the details:\n";
        cout << "---------------------------------------------\n";
        for (size_t i = 0; i < matched.size(); ++i) {
            cout << i + 1 << ". " << matched[i].name
                 << " [" << matched[i].bloodGroup << "], Contact: " << matched[i].contact << endl;
        }
        cout << "---------------------------------------------\n";

        int choice;
        cout << "\nEnter the number of the donor to contact (0 to skip): ";
        while (!(cin >> choice) || choice < 0 || choice > (int)matched.size()) {
            cout << " Invalid choice! Enter a number between 0 and " << matched.size() << ": ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore();

        if (choice >= 1) {
            const auto& selected = matched[choice - 1];
            cout << "\n Contact this donor ASAP: " << selected.name
                 << " [" << selected.bloodGroup << "], " << selected.contact << "\n";
        } else {
            cout << "\n⏭ No donor selected. Your request has been recorded.\n";
        }
    }
}

// View all donors
void viewDonors() {
    vector<Donor> donors = loadDonors();
    if (donors.empty()) {
        cout << "\nNo donors registered.\n";
        return;
    }
    cout << "\n Registered Donors:\n";
    cout << "---------------------------------------------\n";
    for (size_t i = 0; i < donors.size(); ++i) {
        const auto& d = donors[i];
        cout << (i + 1) << ". " << d.name << " (" << d.bloodGroup << "), Contact: " << d.contact << endl;
    }
    cout << "---------------------------------------------\n";
}

// Display menu
void showMenu() {
    cout << "\n========== 💉 BloRidge: Blood Donation System ==========\n";
    cout << "1. Register as Donor\n";
    cout << "2. Request Blood\n";
    cout << "3. View Donors\n";
    cout << "4. Exit\n";
    cout << "=======================================================\n";
    cout << "Enter choice: ";
}

// Main function
int main() {
    int choice;
    do {
        showMenu();
        while (!(cin >> choice) || choice < 1 || choice > 4) {
            cout << " Invalid choice! Enter a number between 1 and 4: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore();
        switch (choice) {
            case 1: registerDonor(); break;
            case 2: requestBlood(); break;
            case 3: viewDonors(); break;
            case 4: cout << "\n Thank you for using BloRidge. Stay safe!\n"; break;
        }
    } while (choice != 4);
    return 0;
}
