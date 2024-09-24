#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct STUDENT_DATA {
    string first_name;
    string last_name;
};

// Function to read student data from file and return a vector of STUDENT_DATA objects
vector<STUDENT_DATA> readStudentData(const string& filename) {
    vector<STUDENT_DATA> students;
    ifstream infile(filename);
    string line;

    if (!infile) {
        cerr << "Error opening file: " << filename << endl;
        return students;
    }

    while (getline(infile, line)) {
        istringstream ss(line);
        string last_name, first_name;

        if (getline(ss, last_name, ',') && getline(ss, first_name)) {
            last_name.erase(0, last_name.find_first_not_of(" \t"));
            last_name.erase(last_name.find_last_not_of(" \t") + 1);
            first_name.erase(0, first_name.find_first_not_of(" \t"));
            first_name.erase(first_name.find_last_not_of(" \t") + 1);

            students.push_back({ first_name, last_name });
        }
    }

    infile.close();
    return students;
}

int main() {
    string filename = "StudentData.txt";

    vector<STUDENT_DATA> students = readStudentData(filename);

    for (const auto& student : students) {
        cout << "First Name: " << student.first_name << ", Last Name: " << student.last_name << endl;
    }

    return 0;
}