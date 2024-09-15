#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

class Student {
private:
    int studentID;
    string name;
    int age;
    string gender;
    string address;
    string phoneNumber;
    string email;
    vector<string> courses;

public:
    Student(int id = 0, const string& n = "", int a = 0, const string& g = "", const string& addr = "", const string& phone = "", const string& mail = "") 
        : studentID(id), name(n), age(a), gender(g), address(addr), phoneNumber(phone), email(mail) {}

    void addCourse(const string& course) { courses.push_back(course); }

    // Getter methods
    int getStudentID() const { return studentID; }
    string getName() const { return name; }
    int getAge() const { return age; }
    string getGender() const { return gender; }
    string getAddress() const { return address; }
    string getPhoneNumber() const { return phoneNumber; }
    string getEmail() const { return email; }
    const vector<string>& getCourses() const { return courses; }

    // Setter methods
    void setStudentID(int id) { studentID = id; }
    void setName(const string& n) { name = n; }
    void setAge(int a) { age = a; }
    void setGender(const string& g) { gender = g; }
    void setAddress(const string& addr) { address = addr; }
    void setPhoneNumber(const string& phone) { phoneNumber = phone; }
    void setEmail(const string& mail) { email = mail; }

    void displayInfo() const {
        cout << "Student ID: " << studentID << endl;
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "Gender: " << gender << endl;
        cout << "Address: " << address << endl;
        cout << "Phone Number: " << phoneNumber << endl;
        cout << "Email: " << email << endl;
        cout << "Courses: "<<endl;
        cout<<"Press Enter To Continue "<<endl; 
	    for (const auto& course : courses) {
            cout << course << " ";
        }
        cout << endl;
    }
};

class Course {
private:
    int courseID;
    string courseName;
    int credits;

public:
    Course(int id = 0, const string& name = "", int c = 0) 
        : courseID(id), courseName(name), credits(c) {}

    // Getter methods
    int getCourseID() const { return courseID; }
    string getCourseName() const { return courseName; }
    int getCredits() const { return credits; }

    // Setter methods
    void setCourseID(int id) { courseID = id; }
    void setCourseName(const string& name) { courseName = name; }
    void setCredits(int c) { credits = c; }

    void displayInfo() const {
        cout << "Course ID: " << courseID << endl;
        cout << "Course Name: " << courseName << endl;
        cout << "Credits: " << credits << endl;
    }
};

class Grade {
private:
    int studentID;
    int courseID;
    double grade;

public:
    Grade(int sid = 0, int cid = 0, double g = 0.0) 
        : studentID(sid), courseID(cid), grade(g) {}

    // Getter methods
    int getStudentID() const { return studentID; }
    int getCourseID() const { return courseID; }
    double getGrade() const { return grade; }

    // Setter methods
    void setStudentID(int sid) { studentID = sid; }
    void setCourseID(int cid) { courseID = cid; }
    void setGrade(double g) { grade = g; }

    void displayInfo() const {
        cout << "Student ID: " << studentID << endl;
        cout << "Course ID: " << courseID << endl;
        cout << "Grade: " << grade << endl;
        cout<<"Press Enter To Continue "<<endl;                
    }
};

class StudentManagementSystem {
	private:
    vector<Student> students;
    vector<Course> courses;
    vector<Grade> grades;

public:
    void addStudent() {
        int id;
        string name, gender, address, phone, email;
        int age;

        cout << "Enter Student ID: ";
        cin >> id;
        cout << "Enter Name: ";
        cin.ignore(); // Ignore newline left in input buffer
        getline(cin, name);
        cout << "Enter Age: ";
        cin >> age;
        cout << "Enter Gender: ";
        cin >> gender;
        cout << "Enter Address: ";
        cin.ignore();
        getline(cin, address);
        cout << "Enter Phone Number: ";
        cin >> phone;
        cout << "Enter Email: ";
        cin >> email;

        Student newStudent(id, name, age, gender, address, phone, email);
        students.push_back(newStudent);

        saveStudentsToFile();
    }

    void displayAllStudents() const {
        for (const auto& student : students) {
            student.displayInfo();
            cout << endl;
        }
    }

    void addCourse() {
        int id;
        string name;
        int credits;

        cout << "Enter Course ID: ";
        cin >> id;
        cout << "Enter Course Name: ";
        cin.ignore(); // Ignore newline left in input buffer
        getline(cin, name);
        cout << "Enter Credits: ";
        cin >> credits;

        Course newCourse(id, name, credits);
        courses.push_back(newCourse);

        saveCoursesToFile();
    }

    void displayAllCourses() const {
        for (const auto& course : courses) {
            course.displayInfo();
            cout << endl;
        }
    }

    void addGrade() {
        int studentID, courseID;
        double grade;

        cout << "Enter Student ID: ";
        cin >> studentID;
        cout << "Enter Course ID: ";
        cin >> courseID;
        cout << "Enter Grade: ";
        cin >> grade;

        Grade newGrade(studentID, courseID, grade);
        grades.push_back(newGrade);

        saveGradesToFile();
    }

    void displayAllGrades() const {
        for (const auto& grade : grades) {
            grade.displayInfo();
            cout << endl;
        }
    }

    void saveStudentsToFile() const {
        ofstream outFile("students.txt", ios::binary | ios::out);
        if (!outFile.is_open()) {
            cerr << "Error opening students file for writing." << endl;
            return;
        }

        size_t studentCount = students.size();
        outFile.write(reinterpret_cast<const char*>(&studentCount), sizeof(studentCount));

        for (const auto& student : students) {
            // Write StudentID
            int studentId = student.getStudentID();
            outFile.write(reinterpret_cast<const char*>(&studentId), sizeof(int));

            // Write Name
            const std::string& name = student.getName();
            size_t nameLen = name.length();
            outFile.write(reinterpret_cast<const char*>(&nameLen), sizeof(size_t));
            outFile.write(name.c_str(), nameLen);

            // Write Age
            int age = student.getAge();
            outFile.write(reinterpret_cast<const char*>(&age), sizeof(int));

            // Write Gender
            const std::string& gender = student.getGender();
            size_t genderLen = gender.length();
            outFile.write(reinterpret_cast<const char*>(&genderLen), sizeof(size_t));
            outFile.write(gender.c_str(), genderLen);

            // Write Address
            const std::string& address = student.getAddress();
            size_t addressLen = address.length();
            outFile.write(reinterpret_cast<const char*>(&addressLen), sizeof(size_t));
            outFile.write(address.c_str(), addressLen);

            // Write PhoneNumber
            const std::string& phone = student.getPhoneNumber();
            size_t phoneLen = phone.length();
            outFile.write(reinterpret_cast<const char*>(&phoneLen), sizeof(size_t));
            outFile.write(phone.c_str(), phoneLen);

            // Write Email
            const std::string& email = student.getEmail();
            size_t emailLen = email.length();
            outFile.write(reinterpret_cast<const char*>(&emailLen), sizeof(size_t));
            outFile.write(email.c_str(), emailLen);

            // Write Courses
            const vector<string>& courses = student.getCourses();
            size_t courseCount = courses.size();
            outFile.write(reinterpret_cast<const char*>(&courseCount), sizeof(size_t));
            for (const auto& course : courses) {
                size_t courseLen = course.length();
                outFile.write(reinterpret_cast<const char*>(&courseLen), sizeof(size_t));
                outFile.write(course.c_str(), courseLen);
            }
        }

        outFile.close();
    }

    void loadStudentsFromFile() {
        ifstream inFile("students.txt", ios::binary | ios::in);
        if (!inFile.is_open()) {
            cerr << "Error opening students file for reading." << endl;
            return;
        }

        size_t studentCount;
        inFile.read(reinterpret_cast<char*>(&studentCount), sizeof(studentCount));

        for (size_t i = 0; i < studentCount; ++i) {
            int studentID;
            string name, gender, address, phone, email;
            int age;
            vector<string> courses;

            inFile.read(reinterpret_cast<char*>(&studentID), sizeof(studentID));
            
            size_t nameLen;
            inFile.read(reinterpret_cast<char*>(&nameLen), sizeof(nameLen));
            name.resize(nameLen);
            inFile.read(&name[0], nameLen);

            inFile.read(reinterpret_cast<char*>(&age), sizeof(age));

            inFile.read(reinterpret_cast<char*>(&gender), sizeof(gender));
            gender.resize(nameLen);
            inFile.read(&gender[0], nameLen);

            inFile.read(reinterpret_cast<char*>(&address), sizeof(address));
            address.resize(nameLen);
            inFile.read(&address[0], nameLen);

            inFile.read(reinterpret_cast<char*>(&phone), sizeof(phone));
            phone.resize(nameLen);
            inFile.read(&phone[0], nameLen);

            inFile.read(reinterpret_cast<char*>(&email), sizeof(email));
            email.resize(nameLen);
            inFile.read(&email[0], nameLen);

            size_t courseCount;
            inFile.read(reinterpret_cast<char*>(&courseCount), sizeof(courseCount));

            for (size_t j = 0; j < courseCount; ++j) {
                size_t courseLen;
                inFile.read(reinterpret_cast<char*>(&courseLen), sizeof(courseLen));
                string course;
                course.resize(courseLen);
                inFile.read(&course[0], courseLen);
                courses.push_back(course);
            }

            students.emplace_back(studentID, name, age, gender, address, phone, email);
            
            // Add courses individually
            for (const auto& course : courses) {
                students.back().addCourse(course);
            }
        }

        inFile.close();
    }

    void loadCoursesFromFile() {
        ifstream inFile("courses.txt", ios::binary | ios::in);
        if (!inFile.is_open()) {
            cerr << "Error opening courses file for reading." << endl;
            return;
        }

        size_t courseCount;
        inFile.read(reinterpret_cast<char*>(&courseCount), sizeof(courseCount));

        for (size_t i = 0; i < courseCount; ++i) {
            int courseID;
            string courseName;
            int credits;

            inFile.read(reinterpret_cast<char*>(&courseID), sizeof(courseID));
            size_t nameLen;
            inFile.read(reinterpret_cast<char*>(&nameLen), sizeof(nameLen));
            courseName.resize(nameLen);
            inFile.read(&courseName[0], nameLen);
            inFile.read(reinterpret_cast<char*>(&credits), sizeof(credits));

            courses.emplace_back(courseID, courseName, credits);
        }

        inFile.close();
    }

    void loadGradesFromFile() {
        ifstream inFile("grades.txt", ios::binary | ios::in);
        if (!inFile.is_open()) {
            cerr << "Error opening grades file for reading." << endl;
            return;
        }

        size_t gradeCount;
        inFile.read(reinterpret_cast<char*>(&gradeCount), sizeof(gradeCount));

        for (size_t i = 0; i < gradeCount; ++i) {
            int studentID, courseID;
            double grade;

            inFile.read(reinterpret_cast<char*>(&studentID), sizeof(studentID));
            inFile.read(reinterpret_cast<char*>(&courseID), sizeof(courseID));
            inFile.read(reinterpret_cast<char*>(&grade), sizeof(grade));

            grades.emplace_back(studentID, courseID, grade);
        }

        inFile.close();
    }

    void saveCoursesToFile() const {
        ofstream outFile("courses.txt", ios::binary | ios::out);
        if (!outFile.is_open()) {
            cerr << "Error opening courses file for writing." << endl;
            return;
        }

        size_t courseCount = courses.size();
        outFile.write(reinterpret_cast<const char*>(&courseCount), sizeof(courseCount));

        for (const auto& course : courses) {
            // Write CourseID
            int courseID = course.getCourseID();
            outFile.write(reinterpret_cast<const char*>(&courseID), sizeof(int));

            // Write CourseName
            const std::string& courseName = course.getCourseName();
            size_t nameLen = courseName.length();
            outFile.write(reinterpret_cast<const char*>(&nameLen), sizeof(size_t));
            outFile.write(courseName.c_str(), nameLen);

            // Write Credits
            int credits = course.getCredits();
            outFile.write(reinterpret_cast<const char*>(&credits), sizeof(int));
        }

        outFile.close();
    }
void saveGradesToFile() const {
    ofstream outFile("grades.txt", ios::binary | ios::out);
    if (!outFile.is_open()) {
        cerr << "Error opening grades file for writing." << endl;
        return;
    }

    size_t gradeCount = grades.size();
    outFile.write(reinterpret_cast<const char*>(&gradeCount), sizeof(gradeCount));

    for (const auto& grade : grades) {
        // Write StudentID
        int studentID = grade.getStudentID();
        outFile.write(reinterpret_cast<const char*>(&studentID), sizeof(int));

        // Write CourseID
        int courseID = grade.getCourseID();
        outFile.write(reinterpret_cast<const char*>(&courseID), sizeof(int));

        // Write Grade
        double gradeValue = grade.getGrade();
        outFile.write(reinterpret_cast<const char*>(&gradeValue), sizeof(double));
    }

    outFile.close();
}

void displayMenu() const {
    cout << "\nStudent Management System Menu:" << endl;
    cout << "1. Add Student" << endl;
    cout << "2. Display All Students" << endl;
    cout << "3. Add Course" << endl;
    cout << "4. Display All Courses" << endl;
    cout << "5. Add Grade" << endl;
    cout << "6. Display All Grades" << endl;
    cout << "7. Exit" << endl;
}

void run() {
    loadStudentsFromFile();
    loadCoursesFromFile();
    loadGradesFromFile();

    int choice;
    do {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                displayAllStudents();
                break;
            case 3:
                addCourse();
                break;
            case 4:
                displayAllCourses();
                break;
            case 5:
                addGrade();
                break;
            case 6:
                displayAllGrades();
                break;
            case 7:
                cout << "Exiting the program." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }

        cin.ignore(); // Ignore newline left in input buffer
        cin.get(); // Wait for user to press Enter before continuing
    } while (choice != 7);

    saveStudentsToFile();
    saveCoursesToFile();
    saveGradesToFile();
}
};

int main() {
    StudentManagementSystem sms;
    sms.run();

    return 0;
}

        
