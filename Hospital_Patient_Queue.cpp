#include <iostream>
#include <queue>
#include <string>
#include <iomanip>

using namespace std;

// Patient structure
struct Patient {
    string name;
    int severity; // Higher value indicates higher severity

    // Constructor
    Patient(string n, int s) : name(n), severity(s) {}
};

// Comparison operator for priority queue
struct CompareSeverity {
    bool operator()(const Patient& p1, const Patient& p2) {
        return p1.severity < p2.severity; // Higher severity has higher priority
    }
};

class HospitalQueue {
private:
    priority_queue<Patient, vector<Patient>, CompareSeverity> criticalQueue; // Priority queue for critical patients
    queue<Patient> regularQueue; // Normal queue for regular patients
    int waitTime; // Estimated wait time in minutes

public:
    HospitalQueue() : waitTime(0) {}

    void addCriticalPatient(const string& name, int severity) {
        criticalQueue.push(Patient(name, severity));
        cout << "Added critical patient: " << name << " with severity " << severity << endl;
    }

    void addRegularPatient(const string& name) {
        regularQueue.push(Patient(name, 1)); // Regular patients have a default severity of 1
        cout << "Added regular patient: " << name << endl;
    }

    void processNextPatient() {
        if (!criticalQueue.empty()) {
            Patient p = criticalQueue.top();
            criticalQueue.pop();
            cout << "Processing critical patient: " << p.name << " with severity " << p.severity << endl;
            waitTime += 5; // Assume critical patients take 5 minutes
        } else if (!regularQueue.empty()) {
            Patient p = regularQueue.front();
            regularQueue.pop();
            cout << "Processing regular patient: " << p.name << endl;
            waitTime += 10; // Assume regular patients take 10 minutes
        } else {
            cout << "No patients to process." << endl;
        }
    }

    void displayEstimatedWaitTime() const {
        cout << "Estimated wait time: " << waitTime << " minutes" << endl;
    }
};

int main() {
    HospitalQueue hospitalQueue;
    int choice;

    do {
        cout << "\nHospital Patient Queue Management System\n";
        cout << "1. Add Critical Patient\n";
        cout << "2. Add Regular Patient\n";
        cout << "3. Process Next Patient\n";
        cout << "4. Display Estimated Wait Time\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            string name;
            int severity;
            cout << "Enter patient name: ";
            cin >> name;
            cout << "Enter severity (1-10): ";
            cin >> severity;
            hospitalQueue.addCriticalPatient(name, severity);
        } else if (choice == 2) {
            string name;
            cout << "Enter patient name: ";
            cin >> name;
            hospitalQueue.addRegularPatient(name);
        } else if (choice == 3) {
            hospitalQueue.processNextPatient();
        } else if (choice == 4) {
            hospitalQueue.displayEstimatedWaitTime();
        }
    } while (choice != 5);

    cout << "Exiting the system." << endl;
    return 0;
}
