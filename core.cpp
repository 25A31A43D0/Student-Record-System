#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

class Student {
public:
    int rollNo;
    string name;
    float marks;

    void addStudent() {
        cout << "Enter Roll Number: ";
        cin >> rollNo;

        cin.ignore();

        cout << "Enter Name: ";
        getline(cin, name);

        cout << "Enter Marks: ";
        cin >> marks;
    }

    void displayStudent() {
        cout << "\nRoll Number: " << rollNo;
        cout << "\nName: " << name;
        cout << "\nMarks: " << marks << endl;
    }
};

vector<Student> students;

void saveToFile() {
    ofstream file("students.txt");

    for (auto &student : students) {
        file << student.rollNo << endl;
        file << student.name << endl;
        file << student.marks << endl;
    }

    file.close();
}

void loadFromFile() {
    ifstream file("students.txt");

    Student student;

    while (file >> student.rollNo) {
        file.ignore();

        getline(file, student.name);

        file >> student.marks;

        students.push_back(student);
    }

    file.close();
}

void addStudent() {
    Student student;

    student.addStudent();

    students.push_back(student);

    saveToFile();

    cout << "Student Added Successfully\n";
}

void displayStudents() {
    if (students.empty()) {
        cout << "No Records Found\n";
        return;
    }

    for (auto &student : students) {
        student.displayStudent();
    }
}

void searchStudent() {
    int roll;

    cout << "Enter Roll Number: ";
    cin >> roll;

    for (auto &student : students) {
        if (student.rollNo == roll) {
            student.displayStudent();
            return;
        }
    }

    cout << "Student Not Found\n";
}

void updateMarks() {
    int roll;
    float newMarks;

    cout << "Enter Roll Number: ";
    cin >> roll;

    for (auto &student : students) {
        if (student.rollNo == roll) {
            cout << "Enter New Marks: ";
            cin >> newMarks;

            student.marks = newMarks;

            saveToFile();

            cout << "Marks Updated Successfully\n";
            return;
        }
    }

    cout << "Student Not Found\n";
}

void deleteStudent() {
    int roll;

    cout << "Enter Roll Number: ";
    cin >> roll;

    for (int i = 0; i < students.size(); i++) {
        if (students[i].rollNo == roll) {
            students.erase(students.begin() + i);

            saveToFile();

            cout << "Student Deleted Successfully\n";
            return;
        }
    }

    cout << "Student Not Found\n";
}

int main() {
    loadFromFile();

    int choice;

    do {
        cout << "\n===== STUDENT RECORD SYSTEM =====\n";
        cout << "1. Add Student\n";
        cout << "2. Display Students\n";
        cout << "3. Search Student\n";
        cout << "4. Update Marks\n";
        cout << "5. Delete Student\n";
        cout << "6. Exit\n";
        cout << "Enter Choice: ";

        cin >> choice;

        switch (choice) {
            case 1:
                addStudent();
                break;

            case 2:
                displayStudents();
                break;

            case 3:
                searchStudent();
                break;

            case 4:
                updateMarks();
                break;

            case 5:
                deleteStudent();
                break;

            case 6:
                cout << "Thank You\n";
                break;

            default:
                cout << "Invalid Choice\n";
        }

    } while (choice != 6);

    return 0;
}