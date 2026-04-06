#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

class Student {
private:
    string name;
    int id;
    vector<float> grades;

public:
    Student(string name, int id) : name(name), id(id) {}

    void addGrade(float g) {
        grades.push_back(g);
    }

    float average() const {
        if (grades.empty()) return 0.0f;
        float sum = 0;
        for (float g : grades) sum += g;
        return sum / grades.size();
    }

    int getId() const { return id; }
    string getName() const { return name; }

    void print() const {
        cout << left << setw(15) << name
             << setw(10) << id
             << "Average: " << average() << endl;
    }

    // Save student to file
    void save(ofstream& out) const {
        out << name << endl;
        out << id << endl;
        out << grades.size() << endl;
        for (float g : grades) out << g << endl;
    }

    // Load student from file
    static Student load(ifstream& in) {
        string name;
        int id;
        int count;

        getline(in, name);
        in >> id;
        in >> count;

        Student s(name, id);

        for (int i = 0; i < count; i++) {
            float g;
            in >> g;
            s.addGrade(g);
        }

        string dummy;
        getline(in, dummy); // clear newline

        return s;
    }
};

class GradeManager {
private:
    vector<Student> students;

public:
    void addStudent() {
        string name;
        int id;

        cout << "Enter student name: ";
        cin.ignore();
        getline(cin, name);

        cout << "Enter student ID: ";
        cin >> id;

        students.emplace_back(name, id);
        cout << "Student added.\n";
    }

    void addGrade() {
        int id;
        float grade;

        cout << "Enter student ID: ";
        cin >> id;

        for (auto& s : students) {
            if (s.getId() == id) {
                cout << "Enter grade: ";
                cin >> grade;
                s.addGrade(grade);
                cout << "Grade added.\n";
                return;
            }
        }
        cout << "Student not found.\n";
    }

    void listStudents() const {
        cout << "\n--- Student List ---\n";
        for (const auto& s : students) {
            s.print();
        }
    }

    void saveToFile() {
        ofstream out("students.txt");
        out << students.size() << endl;
        for (const auto& s : students) s.save(out);
        cout << "Data saved to students.txt\n";
    }

    void loadFromFile() {
        ifstream in("students.txt");
        if (!in) {
            cout << "No saved data found.\n";
            return;
        }

        int count;
        in >> count;
        string dummy;
        getline(in, dummy);

        students.clear();
        for (int i = 0; i < count; i++) {
            students.push_back(Student::load(in));
        }

        cout << "Data loaded from students.txt\n";
    }
};

int main() {
    GradeManager gm;
    int choice;

    while (true) {
        cout << "\n--- Student Grade Manager ---\n";
        cout << "1. Add Student\n";
        cout << "2. Add Grade\n";
        cout << "3. List Students\n";
        cout << "4. Save to File\n";
        cout << "5. Load from File\n";
        cout << "6. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;

        switch (choice) {
            case 1: gm.addStudent(); break;
            case 2: gm.addGrade(); break;
            case 3: gm.listStudents(); break;
            case 4: gm.saveToFile(); break;
            case 5: gm.loadFromFile(); break;
            case 6: return 0;
            default: cout << "Invalid choice.\n";
        }
    }
}
