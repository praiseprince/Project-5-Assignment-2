#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct STUDENT_DATA {
    string first_name;
    string last_name;
    string email;
};

// Function to read student data from file and return a vector of STUDENT_DATA objects
vector<STUDENT_DATA> readStudentData(const string& filename, bool includeEmails = false) {
    vector<STUDENT_DATA> students;
    ifstream infile(filename);
    string line;

    if (!infile) {
        cerr << "Error opening file: " << filename << endl;
        return students;
    }

    while (getline(infile, line)) {
        istringstream ss(line);
        string last_name, first_name, email;

        if (includeEmails) {
            if (getline(ss, last_name, ',') && getline(ss, first_name, ',') && getline(ss, email)) {
                last_name.erase(0, last_name.find_first_not_of(" \t"));
                last_name.erase(last_name.find_last_not_of(" \t") + 1);
                first_name.erase(0, first_name.find_first_not_of(" \t"));
                first_name.erase(first_name.find_last_not_of(" \t") + 1);
                email.erase(0, email.find_first_not_of(" \t"));
                email.erase(email.find_last_not_of(" \t") + 1);

                students.push_back({ first_name, last_name, email });
            }
        }
        else {
            if (getline(ss, last_name, ',') && getline(ss, first_name)) {
                last_name.erase(0, last_name.find_first_not_of(" \t"));
                last_name.erase(last_name.find_last_not_of(" \t") + 1);
                first_name.erase(0, first_name.find_first_not_of(" \t"));
                first_name.erase(first_name.find_last_not_of(" \t") + 1);

                students.push_back({ first_name, last_name, "" });
            }
        }
    }

    infile.close();
    return students;
}

int main() {
    string filename;

#ifdef PRE_RELEASE
    cout << "Running Pre-Release version..." << endl;
    filename = "StudentData_Emails.txt";
#else
    cout << "Running Standard version..." << endl;
    filename = "StudentData.txt";
#endif

    bool includeEmails = false;

#ifdef PRE_RELEASE
    includeEmails = true;
#endif

    vector<STUDENT_DATA> students = readStudentData(filename, includeEmails);

#ifdef _DEBUG
    cout << "Debug Mode: Printing student data..." << endl;
    for (const auto& student : students) {
        cout << "First Name: " << student.first_name << ", Last Name: " << student.last_name;
        if (includeEmails) {
            cout << ", Email: " << student.email;
        }
        cout << endl;
    }
#endif

    cout << "Student data loaded successfully." << endl;

    return 0;
}