// MyCollege portal - student/faculty console app
// Faculty tools (attendance, announcements, performance) live in faculty_module,
// the login/profile/feed/connections part lives in kaushal_module.

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <cctype>
#include <limits>
using namespace std;

namespace faculty_module {

const int MAX_RECORDS = 100;

// reads an int safely, so typing a letter doesn't send the menu into an endless loop
int readInt(const string &prompt)
{
    int value;
    while (true)
    {
        cout << prompt;
        if (cin >> value)
            return value;
        cout << "Please enter a number.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

class StudentRecord
{
    string studentId, name, course, email, mobile, section;
    int performance;

public:
    StudentRecord() : performance(0) {}

    StudentRecord(string id, string name, string course, string email,
                  string mobile, int performance, string section)
        : studentId(id), name(name), course(course), email(email),
          mobile(mobile), section(section), performance(performance) {}

    string getId() const { return studentId; }
    string getName() const { return name; }
    string getSection() const { return section; }
    int getPerformance() const { return performance; }
    void setPerformance(int p) { performance = p; }

    void display() const
    {
        cout << "Student ID: " << studentId << endl;
        cout << "Name: " << name << endl;
        cout << "Course: " << course << endl;
        cout << "Email: " << email << endl;
        cout << "Mobile: " << mobile << endl;
        cout << "Performance: " << performance << endl;
        cout << "Section: " << section << endl;
    }

    void displayPerformance() const
    {
        cout << "Student ID: " << studentId << endl;
        cout << "Name: " << name << endl;
        cout << "Performance: " << performance << endl;
        cout << "Section: " << section << endl;
    }
};

struct AttendanceEntry
{
    string studentId;
    string date;
    char status; // 'P' or 'A'
};

class AttendanceSystem
{
    vector<AttendanceEntry> entries;

public:
    void markAttendance(StudentRecord students[], int count)
    {
        string section, date;
        cout << "Enter the section (e.g. CSE-A): ";
        cin >> section;
        cout << "Enter date (DD-MM-YY): ";
        cin >> date;

        bool anyFound = false;

        for (int i = 0; i < count; i++)
        {
            if (students[i].getSection() != section)
                continue;
            anyFound = true;

            cout << "\nStudent ID: " << students[i].getId() << endl;
            cout << "Name: " << students[i].getName() << endl;

            char answer;
            while (true)
            {
                cout << "Present (P) or Absent (A)? ";
                cin >> answer;
                answer = toupper(static_cast<unsigned char>(answer));
                if (answer == 'P' || answer == 'A')
                    break;
                cout << "Invalid input, try again.\n";
            }

            AttendanceEntry entry;
            entry.studentId = students[i].getId();
            entry.date = date;
            entry.status = answer;
            entries.push_back(entry);
        }

        if (anyFound)
            cout << "Attendance marked." << endl;
        else
            cout << "No students found in this section." << endl;
    }

    void showStudentAttendance()
    {
        string id;
        cout << "Enter student ID: ";
        cin >> id;

        int total = 0, present = 0, absent = 0;

        for (size_t i = 0; i < entries.size(); i++)
        {
            if (entries[i].studentId != id)
                continue;
            total++;
            cout << "Date: " << entries[i].date << "  Status: " << entries[i].status << endl;
            if (entries[i].status == 'P')
                present++;
            else
                absent++;
        }

        if (total == 0)
        {
            cout << "No attendance record found." << endl;
            return;
        }

        cout << "Total classes: " << total << endl;
        cout << "Present: " << present << endl;
        cout << "Absent: " << absent << endl;
        cout << "Attendance: " << (present * 100.0) / total << "%" << endl;
    }

    void showDateSummary()
    {
        string date;
        cout << "Enter date: ";
        cin >> date;

        int total = 0, present = 0, absent = 0;

        for (size_t i = 0; i < entries.size(); i++)
        {
            if (entries[i].date != date)
                continue;
            total++;
            if (entries[i].status == 'P')
                present++;
            else
                absent++;
        }

        if (total == 0)
        {
            cout << "No records found for that date." << endl;
            return;
        }

        cout << "Date: " << date << endl;
        cout << "Total students: " << total << endl;
        cout << "Present: " << present << endl;
        cout << "Absent: " << absent << endl;
        cout << "Attendance: " << (present * 100.0) / total << "%" << endl;
    }
};

class Announcement
{
    int id;
    string title, text, date;

public:
    Announcement() : id(0) {}

    void readFromUser()
    {
        id = readInt("Announcement ID: ");
        cout << "Title: ";
        getline(cin >> ws, title);
        cout << "Announcement: ";
        getline(cin, text);
        cout << "Date: ";
        getline(cin, date);
    }

    void display() const
    {
        cout << "ID: " << id << endl;
        cout << "Date: " << date << endl;
        cout << "Title: " << title << endl;
        cout << "Announcement: " << text << endl;
    }

    int getId() const { return id; }
};

class Faculty
{
    string name, password, facultyId, department, email;

public:
    Faculty(string name, string password, string facultyId, string department, string email)
        : name(name), password(password), facultyId(facultyId),
          department(department), email(email) {}

    bool login(const string &id, const string &pass) const
    {
        return id == facultyId && pass == password;
    }

    // returns the index of a student, or -1 if there is no match
    int findStudent(StudentRecord students[], int count, const string &id) const
    {
        for (int i = 0; i < count; i++)
            if (students[i].getId() == id)
                return i;
        return -1;
    }

    void searchStudent(StudentRecord students[], int count)
    {
        string id;
        cout << "Enter student ID: ";
        cin >> id;

        int pos = findStudent(students, count, id);
        if (pos == -1)
        {
            cout << "ID not found." << endl;
            return;
        }
        cout << "Student found." << endl;
        students[pos].display();
    }

    void addStudent(StudentRecord students[], int &count)
    {
        if (count == MAX_RECORDS)
        {
            cout << "Student list is full." << endl;
            return;
        }

        string id, name, course, email, mobile, section;

        cout << "Enter student ID: ";
        cin >> id;

        if (findStudent(students, count, id) != -1)
        {
            cout << "That student ID already exists." << endl;
            return;
        }

        cout << "Enter name: ";
        getline(cin >> ws, name);
        cout << "Enter course: ";
        getline(cin, course);
        cout << "Enter email: ";
        cin >> email;
        cout << "Enter mobile number: ";
        cin >> mobile;
        cout << "Enter section: ";
        cin >> section;

        int performance = readInt("Enter performance (0-100): ");
        if (performance < 0 || performance > 100)
        {
            cout << "Performance must be between 0 and 100." << endl;
            return;
        }

        students[count] = StudentRecord(id, name, course, email, mobile, performance, section);
        count++;
        cout << "Student added." << endl;
    }

    void viewStudentProfile(StudentRecord students[], int count,
                            StudentRecord recent[], int &top)
    {
        string id;
        cout << "Enter student ID: ";
        cin >> id;

        int pos = findStudent(students, count, id);
        if (pos == -1)
        {
            cout << "ID not found." << endl;
            return;
        }

        students[pos].display();

        // remember this view (used as a stack, latest on top)
        if (top < MAX_RECORDS - 1)
        {
            top++;
            recent[top] = students[pos];
        }
    }

    void viewStudentPerformance(StudentRecord students[], int count)
    {
        string id;
        cout << "Enter student ID: ";
        cin >> id;

        int pos = findStudent(students, count, id);
        if (pos == -1)
        {
            cout << "ID not found." << endl;
            return;
        }
        students[pos].displayPerformance();
    }

    // bubble sort, highest performance first
    void sortStudents(StudentRecord students[], int count)
    {
        for (int i = 0; i < count - 1; i++)
        {
            for (int j = 0; j < count - i - 1; j++)
            {
                if (students[j].getPerformance() < students[j + 1].getPerformance())
                    swap(students[j], students[j + 1]);
            }
        }

        cout << "Students sorted by performance:" << endl;
        for (int i = 0; i < count; i++)
        {
            students[i].displayPerformance();
            cout << endl;
        }
    }

    void showRecentStudents(StudentRecord recent[], int top)
    {
        if (top == -1)
        {
            cout << "No students viewed yet." << endl;
            return;
        }

        cout << "Recently viewed students:" << endl;
        for (int i = top; i >= 0; i--)
        {
            recent[i].display();
            cout << endl;
        }
    }

    void addStudentRequest(string requests[], int &front, int &rear)
    {
        if (rear == MAX_RECORDS - 1)
        {
            cout << "Request queue is full." << endl;
            return;
        }

        string id;
        cout << "Enter student ID: ";
        cin >> id;

        if (front == -1)
            front = 0;

        rear++;
        requests[rear] = id;
        cout << "Request added." << endl;
    }

    void processStudentRequest(string requests[], int &front, int &rear)
    {
        if (front == -1 || front > rear)
        {
            cout << "No requests to process." << endl;
            return;
        }

        cout << "Processing request of student " << requests[front] << endl;
        front++;

        // queue is empty again, reset it
        if (front > rear)
        {
            front = -1;
            rear = -1;
        }
    }

    void updatePerformance(StudentRecord students[], int count)
    {
        if (count == 0)
        {
            cout << "No students available." << endl;
            return;
        }

        string id;
        cout << "Enter student ID: ";
        cin >> id;

        int pos = findStudent(students, count, id);
        if (pos == -1)
        {
            cout << "ID not found." << endl;
            return;
        }

        cout << "Current record:" << endl;
        students[pos].displayPerformance();

        int newValue = readInt("Enter new performance (0-100): ");
        if (newValue < 0 || newValue > 100)
        {
            cout << "Invalid performance value." << endl;
            return;
        }

        students[pos].setPerformance(newValue);
        cout << "Performance updated." << endl;
    }

    void createAnnouncement(Announcement list[], int &count)
    {
        if (count == MAX_RECORDS)
        {
            cout << "Announcement list is full." << endl;
            return;
        }

        list[count].readFromUser();
        count++;
        cout << "Announcement created." << endl;
    }

    void viewAnnouncements(Announcement list[], int count)
    {
        if (count == 0)
        {
            cout << "No announcements yet." << endl;
            return;
        }

        cout << "ALL ANNOUNCEMENTS" << endl;
        for (int i = 0; i < count; i++)
        {
            cout << "\nAnnouncement " << i + 1 << endl;
            list[i].display();
        }
    }

    void searchAnnouncement(Announcement list[], int count)
    {
        if (count == 0)
        {
            cout << "No announcements yet." << endl;
            return;
        }

        int id = readInt("Announcement ID: ");

        for (int i = 0; i < count; i++)
        {
            if (list[i].getId() == id)
            {
                cout << "Announcement found." << endl;
                list[i].display();
                return;
            }
        }
        cout << "Announcement ID not found." << endl;
    }

    void deleteAnnouncement(Announcement list[], int &count)
    {
        if (count == 0)
        {
            cout << "No announcements yet." << endl;
            return;
        }

        int id = readInt("Announcement ID to delete: ");

        for (int i = 0; i < count; i++)
        {
            if (list[i].getId() == id)
            {
                // shift everything after it one step to the left
                for (int j = i; j < count - 1; j++)
                    list[j] = list[j + 1];
                count--;
                cout << "Announcement deleted." << endl;
                return;
            }
        }
        cout << "Announcement ID not found." << endl;
    }

    void dashboard(StudentRecord students[], int &studentCount,
                   StudentRecord recent[], int &top,
                   string requests[], int &front, int &rear,
                   AttendanceSystem &attendance,
                   Announcement announcements[], int &announcementCount)
    {
        int choice;

        do
        {
            cout << endl;
            cout << "FACULTY PORTAL" << endl;
            cout << "1. Search Student" << endl;
            cout << "2. Add Student" << endl;
            cout << "3. View Student Profile" << endl;
            cout << "4. View Student Performance" << endl;
            cout << "5. Sort Students by Performance" << endl;
            cout << "6. Recently Viewed Students" << endl;
            cout << "7. Add Student Request" << endl;
            cout << "8. Process Student Request" << endl;
            cout << "9. Update Student Performance" << endl;
            cout << "10. Mark Attendance" << endl;
            cout << "11. View Attendance by Student ID" << endl;
            cout << "12. Attendance Summary by Date" << endl;
            cout << "13. Create Announcement" << endl;
            cout << "14. View Announcements" << endl;
            cout << "15. Search Announcement" << endl;
            cout << "16. Delete Announcement" << endl;
            cout << "17. Log out" << endl;

            choice = readInt("Enter your choice: ");

            switch (choice)
            {
            case 1:  searchStudent(students, studentCount); break;
            case 2:  addStudent(students, studentCount); break;
            case 3:  viewStudentProfile(students, studentCount, recent, top); break;
            case 4:  viewStudentPerformance(students, studentCount); break;
            case 5:  sortStudents(students, studentCount); break;
            case 6:  showRecentStudents(recent, top); break;
            case 7:  addStudentRequest(requests, front, rear); break;
            case 8:  processStudentRequest(requests, front, rear); break;
            case 9:  updatePerformance(students, studentCount); break;
            case 10: attendance.markAttendance(students, studentCount); break;
            case 11: attendance.showStudentAttendance(); break;
            case 12: attendance.showDateSummary(); break;
            case 13: createAnnouncement(announcements, announcementCount); break;
            case 14: viewAnnouncements(announcements, announcementCount); break;
            case 15: searchAnnouncement(announcements, announcementCount); break;
            case 16: deleteAnnouncement(announcements, announcementCount); break;
            case 17: cout << "Logging out..." << endl; break;
            default: cout << "Invalid choice." << endl;
            }

        } while (choice != 17);
    }
};

void runFacultyPortalFor(const string &name, const string &password,
                         const string &facultyId, const string &department,
                         const string &email, StudentRecord students[], int studentCount)
{
    AttendanceSystem attendance;
    Faculty faculty(name, password, facultyId, department, email);

    Announcement announcements[MAX_RECORDS];
    int announcementCount = 0;

    StudentRecord recent[MAX_RECORDS];
    int top = -1;

    string requests[MAX_RECORDS];
    int front = -1, rear = -1;

    cout << "\nWelcome to the Faculty Portal, " << name << "!\n";
    faculty.dashboard(students, studentCount, recent, top, requests, front, rear,
                      attendance, announcements, announcementCount);
}

} // namespace faculty_module


namespace kaushal_module {

struct User
{
    int id, collegeId;
    string fullName, email, password, role, department;
};

struct Student
{
    int id, passingYear;
    string name, bio, branch, contact;
    float cgpa;
    vector<string> skills, achievements;

    static void printList(const vector<string> &items)
    {
        if (items.empty())
        {
            cout << "Not added";
            return;
        }
        for (size_t i = 0; i < items.size(); ++i)
            cout << (i ? ", " : "") << items[i];
    }

    void display() const
    {
        cout << "\n========================================\n";
        cout << "             STUDENT PROFILE\n";
        cout << "========================================\n";
        cout << "ID: " << id << "\nName: " << name << "\nBio: " << bio
             << "\nBranch: " << branch << "\nPassing Year: " << passingYear;
        cout << "\nSkills: ";
        printList(skills);
        cout << "\nAchievements: ";
        printList(achievements);
        cout << "\nCGPA: " << cgpa << "\nContact: " << contact << "\n";
        cout << "========================================\n";
    }
};

// small helpers for validated console input
class Input
{
public:
    static string text(const string &prompt)
    {
        string value;
        do
        {
            cout << prompt;
            getline(cin >> ws, value);
            if (value.empty())
                cout << "This field cannot be empty.\n";
        } while (value.empty());
        return value;
    }

    static int number(const string &prompt, int low, int high)
    {
        int value;
        while (true)
        {
            cout << prompt;
            if (cin >> value && value >= low && value <= high)
            {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return value;
            }
            cout << "Enter a number from " << low << " to " << high << ".\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    static float decimal(const string &prompt, float low, float high)
    {
        float value;
        while (true)
        {
            cout << prompt;
            if (cin >> value && value >= low && value <= high)
            {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return value;
            }
            cout << "Enter a value from " << low << " to " << high << ".\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    static string lower(string value)
    {
        transform(value.begin(), value.end(), value.begin(),
                  [](unsigned char c) { return static_cast<char>(tolower(c)); });
        return value;
    }
};

class StudentPortal
{
    vector<Student> students;

    void readSkills(Student &s)
    {
        s.skills.clear();
        int n = Input::number("Number of skills (0-5): ", 0, 5);
        for (int i = 0; i < n; ++i)
            s.skills.push_back(Input::text("Skill " + to_string(i + 1) + ": "));
    }

    void readAchievements(Student &s)
    {
        s.achievements.clear();
        int n = Input::number("Number of achievements (0-10): ", 0, 10);
        for (int i = 0; i < n; ++i)
            s.achievements.push_back(Input::text("Achievement " + to_string(i + 1) + ": "));
    }

public:
    StudentPortal()
    {
        // sample data so the portal isn't empty on first run
        students.push_back({1, 2027, "Aarav Sharma", "CSE student interested in problem solving.",
                            "CSE", "aarav@example.com", 8.4f,
                            {"C++", "DSA", "HTML"}, {"Hackathon participant"}});
        students.push_back({2, 2027, "Priya Verma", "Learning software development and databases.",
                            "CSE", "priya@example.com", 8.8f,
                            {"Java", "SQL", "Python"}, {"Coding contest finalist"}});
        students.push_back({3, 2026, "Rohan Mehta", "Interested in cloud and networking.",
                            "ECE", "rohan@example.com", 8.1f,
                            {"C", "Networking"}, {}});
    }

    void registerStudent(int id, const string &name)
    {
        Student s;
        s.id = id;
        s.name = name;

        cout << "\nLet's complete your student profile.\n";
        s.bio = Input::text("Short bio: ");
        s.branch = Input::text("Branch: ");
        s.passingYear = Input::number("Passing year: ", 2000, 2100);
        readSkills(s);
        s.cgpa = Input::decimal("CGPA (0-10): ", 0, 10);
        s.contact = Input::text("Contact details: ");
        readAchievements(s);

        students.push_back(s);
        cout << "\nProfile created successfully.\n";
        s.display();
    }

    void viewAll() const
    {
        if (students.empty())
        {
            cout << "\nNo student profiles available.\n";
            return;
        }
        for (size_t i = 0; i < students.size(); ++i)
            students[i].display();
    }

    void search() const
    {
        string key = Input::lower(Input::text("Enter student name: "));
        bool found = false;
        for (size_t i = 0; i < students.size(); ++i)
        {
            if (Input::lower(students[i].name).find(key) != string::npos)
            {
                students[i].display();
                found = true;
            }
        }
        if (!found)
            cout << "\nNo matching student found.\n";
    }

    Student *find(int id)
    {
        for (size_t i = 0; i < students.size(); ++i)
            if (students[i].id == id)
                return &students[i];
        return NULL;
    }

    void update(int id)
    {
        Student *s = find(id);
        if (!s)
        {
            cout << "\nNo student profile is linked to this account yet.\n";
            return;
        }

        int choice;
        do
        {
            cout << "\n========== UPDATE MY PROFILE ==========\n"
                 << "1. Name\n2. Bio\n3. Branch\n4. Passing year\n"
                 << "5. Skills\n6. CGPA\n7. Contact\n8. Achievements\n9. Back\n";
            choice = Input::number("Choose: ", 1, 9);

            switch (choice)
            {
            case 1: s->name = Input::text("New name: "); break;
            case 2: s->bio = Input::text("New bio: "); break;
            case 3: s->branch = Input::text("New branch: "); break;
            case 4: s->passingYear = Input::number("New passing year: ", 2000, 2100); break;
            case 5: readSkills(*s); break;
            case 6: s->cgpa = Input::decimal("New CGPA: ", 0, 10); break;
            case 7: s->contact = Input::text("New contact: "); break;
            case 8: readAchievements(*s); break;
            }

            if (choice != 9)
                cout << "\nProfile updated.\n";
        } while (choice != 9);
    }
};

struct FeedItem
{
    int id, authorId;
    string author, type, title, content;

    void display() const
    {
        cout << "\n----------------------------------------\n"
             << type << " | Content ID: " << id << "\nBy: " << author
             << " (User ID: " << authorId << ")\n";
        if (!title.empty())
            cout << "Title: " << title << '\n';
        cout << content << "\n----------------------------------------\n";
    }
};

class FeedManager
{
    vector<FeedItem> feed;
    int nextId;

public:
    FeedManager() : nextId(4)
    {
        feed.push_back({1, 1, "Aarav Sharma", "POST", "Welcome",
                        "Welcome to the MyCollege student community!"});
        feed.push_back({2, 2, "Priya Verma", "BLOG", "My DSA Journey",
                        "Consistency and regular practice are the keys to learning DSA."});
        feed.push_back({3, 3, "Rohan Mehta", "POST", "Tech Discussion",
                        "What technology are you learning this semester?"});
    }

    void create(const User &user, bool isBlog)
    {
        FeedItem item;
        item.id = nextId++;
        item.authorId = user.id;
        item.author = user.fullName;
        item.type = isBlog ? "BLOG" : "POST";
        item.title = isBlog ? Input::text("Blog title: ") : "Community Post";
        item.content = Input::text(isBlog ? "Write your blog: " : "Write your post: ");
        feed.push_back(item);
        cout << "\n" << item.type << " published successfully.\n";
    }

    void view() const
    {
        if (feed.empty())
        {
            cout << "\nThe feed is empty. Be the first to share something!\n";
            return;
        }
        cout << "\n=============== COMMUNITY FEED ===============\n";
        // newest first
        for (int i = static_cast<int>(feed.size()) - 1; i >= 0; --i)
            feed[i].display();
    }
};

class AuthManager
{
    vector<User> users;
    int nextId;

    bool emailTaken(const string &email) const
    {
        for (size_t i = 0; i < users.size(); ++i)
            if (Input::lower(users[i].email) == Input::lower(email))
                return true;
        return false;
    }

public:
    AuthManager() : nextId(4)
    {
        // demo accounts (passwords are plain text, fine for a demo only)
        users.push_back({1, 1001, "Aarav Sharma", "student@mycollege.edu",
                         "student123", "student", "CSE"});
        users.push_back({2, 1002, "Priya Verma", "priya@mycollege.edu",
                         "priya123", "student", "CSE"});
        users.push_back({3, 2001, "Dr. Ananya Rao", "faculty@mycollege.edu",
                         "faculty123", "faculty", "CSE"});
    }

    const vector<User> &all() const { return users; }

    bool registerUser()
    {
        User u;
        u.id = nextId;
        u.fullName = Input::text("Full name: ");

        while (true)
        {
            u.email = Input::text("Email: ");
            size_t at = u.email.find('@');
            if (at == string::npos || u.email.find('.', at) == string::npos)
            {
                cout << "Enter a valid email address.\n";
                continue;
            }
            if (emailTaken(u.email))
            {
                cout << "Email already registered. Try another.\n";
                continue;
            }
            break;
        }

        do
        {
            u.password = Input::text("Password (minimum 6 characters): ");
            if (u.password.size() < 6)
                cout << "Password must contain at least 6 characters.\n";
        } while (u.password.size() < 6);

        do
        {
            u.role = Input::lower(Input::text("Role (student/faculty): "));
            if (u.role != "student" && u.role != "faculty")
                cout << "Enter student or faculty.\n";
        } while (u.role != "student" && u.role != "faculty");

        u.collegeId = Input::number("College ID: ", 1, 99999999);
        for (size_t i = 0; i < users.size(); ++i)
        {
            if (users[i].collegeId == u.collegeId)
            {
                cout << "College ID already registered. Registration cancelled.\n";
                return false;
            }
        }

        u.department = Input::text("Department: ");
        users.push_back(u);
        nextId++;
        cout << "\nRegistration successful. Your user ID is " << u.id << ".\n";
        return true;
    }

    bool login(User &loggedIn) const
    {
        cout << "\n=============== LOGIN ===============\n";
        for (int attempt = 1; attempt <= 3; ++attempt)
        {
            string email = Input::text("Email: ");
            string password = Input::text("Password: ");

            for (size_t i = 0; i < users.size(); ++i)
            {
                if (Input::lower(users[i].email) == Input::lower(email) &&
                    users[i].password == password)
                {
                    loggedIn = users[i];
                    cout << "\nWelcome, " << loggedIn.fullName << "!\n";
                    return true;
                }
            }
            cout << "Incorrect email or password. Attempts remaining: " << 3 - attempt << '\n';
        }
        cout << "Too many failed attempts.\n";
        return false;
    }
};

class ConnectionManager
{
    map<int, vector<int>> connected; // user id -> list of connected user ids
    map<int, vector<int>> pending;   // user id -> ids of people who sent them a request

    bool contains(const vector<int> &values, int id) const
    {
        return find(values.begin(), values.end(), id) != values.end();
    }

public:
    void send(int from, int to)
    {
        if (from == to)
            cout << "You cannot connect with yourself.\n";
        else if (contains(connected[from], to))
            cout << "You are already connected.\n";
        else if (contains(pending[to], from))
            cout << "Request already sent.\n";
        else if (contains(pending[from], to))
            cout << "This user has already sent you a request. Check your requests.\n";
        else
        {
            pending[to].push_back(from);
            cout << "Connection request sent.\n";
        }
    }

    void requests(int id, const vector<User> &users)
    {
        vector<int> &list = pending[id];
        if (list.empty())
        {
            cout << "\nNo pending connection requests.\n";
            return;
        }

        size_t i = 0;
        while (i < list.size())
        {
            int sender = list[i];
            string name = "Unknown user";
            for (size_t j = 0; j < users.size(); ++j)
                if (users[j].id == sender)
                    name = users[j].fullName;

            cout << "\nRequest from " << name << " (ID " << sender << ")\n";
            cout << "1. Accept\n2. Reject\n3. Skip\n";
            int choice = Input::number("Choose: ", 1, 3);

            if (choice == 1)
            {
                connected[id].push_back(sender);
                connected[sender].push_back(id);
                list.erase(list.begin() + i);
                cout << "Request accepted. You are now connected.\n";
            }
            else if (choice == 2)
            {
                list.erase(list.begin() + i);
                cout << "Request rejected.\n";
            }
            else
            {
                ++i;
            }
        }
    }

    void view(int id, const vector<User> &users) const
    {
        map<int, vector<int>>::const_iterator it = connected.find(id);
        if (it == connected.end() || it->second.empty())
        {
            cout << "\nYou have no connections yet.\n";
            return;
        }

        cout << "\n=============== MY CONNECTIONS ===============\n";
        for (size_t i = 0; i < it->second.size(); ++i)
            for (size_t j = 0; j < users.size(); ++j)
                if (users[j].id == it->second[i])
                    cout << users[j].fullName << " | " << users[j].role
                         << " | " << users[j].department << '\n';
    }
};

void showAccount(const User &u)
{
    cout << "\n=============== MY ACCOUNT ===============\n"
         << "User ID: " << u.id << "\nName: " << u.fullName
         << "\nEmail: " << u.email << "\nRole: " << u.role
         << "\nCollege ID: " << u.collegeId << "\nDepartment: " << u.department << '\n';
}

void searchUsers(const User &current, const AuthManager &auth, ConnectionManager &links)
{
    string key = Input::lower(Input::text("Search user by name: "));
    bool found = false;
    const vector<User> &users = auth.all();

    for (size_t i = 0; i < users.size(); ++i)
    {
        if (Input::lower(users[i].fullName).find(key) == string::npos)
            continue;

        found = true;
        cout << "\nID: " << users[i].id << "\nName: " << users[i].fullName
             << "\nRole: " << users[i].role << "\nDepartment: " << users[i].department << '\n';

        if (users[i].id != current.id &&
            Input::number("Send connection request? (1=Yes, 2=No): ", 1, 2) == 1)
            links.send(current.id, users[i].id);
    }

    if (!found)
        cout << "\nNo matching users found.\n";
}

void studentMenu(const User &u, AuthManager &auth, StudentPortal &portal,
                 FeedManager &feed, ConnectionManager &links)
{
    int choice;
    do
    {
        cout << "\n============== STUDENT PORTAL ==============\n"
             << "Welcome, " << u.fullName << "\n"
             << "1. View all student profiles\n2. Search student profile\n"
             << "3. Update my profile\n4. Create post\n5. Create blog\n"
             << "6. View community feed\n7. Search users / Connect\n"
             << "8. View connection requests\n9. View my connections\n"
             << "10. View my account\n11. Logout\n";
        choice = Input::number("Choose an option: ", 1, 11);

        switch (choice)
        {
        case 1:  portal.viewAll(); break;
        case 2:  portal.search(); break;
        case 3:  portal.update(u.id); break;
        case 4:  feed.create(u, false); break;
        case 5:  feed.create(u, true); break;
        case 6:  feed.view(); break;
        case 7:  searchUsers(u, auth, links); break;
        case 8:  links.requests(u.id, auth.all()); break;
        case 9:  links.view(u.id, auth.all()); break;
        case 10: showAccount(u); break;
        case 11: cout << "Logged out successfully.\n"; break;
        }
    } while (choice != 11);
}

// Builds the student list the faculty module works with, using the
// accounts and profiles from this module.
int buildFacultyStudentList(const AuthManager &auth, StudentPortal &portal,
                            faculty_module::StudentRecord out[], int maxCount)
{
    const vector<User> &allUsers = auth.all();
    int count = 0;

    for (size_t i = 0; i < allUsers.size() && count < maxCount; ++i)
    {
        if (allUsers[i].role != "student")
            continue;

        string mobile = "Not provided";
        int performance = 0;
        string section = "CSE-A";

        Student *profile = portal.find(allUsers[i].id);
        if (profile != NULL)
        {
            mobile = profile->contact;
            performance = static_cast<int>(profile->cgpa * 10 + 0.5f); // CGPA out of 10 -> score out of 100
            section = profile->branch + "-A";
        }

        out[count++] = faculty_module::StudentRecord(
            to_string(allUsers[i].collegeId), allUsers[i].fullName,
            allUsers[i].department, allUsers[i].email, mobile, performance, section);
    }
    return count;
}

void facultyMenu(const User &u, AuthManager &auth, StudentPortal &portal,
                 FeedManager &feed, ConnectionManager &links)
{
    int choice;
    do
    {
        cout << "\n============== FACULTY PORTAL ==============\n"
             << "Welcome, " << u.fullName << "\n"
             << "1. View all student profiles\n2. Search student profile\n"
             << "3. Create post\n4. Create blog\n5. View community feed\n"
             << "6. Search users / Connect\n7. View connection requests\n"
             << "8. View my connections\n9. View my account\n"
             << "10. Attendance + Student Management\n11. Logout\n";
        choice = Input::number("Choose an option: ", 1, 11);

        switch (choice)
        {
        case 1:  portal.viewAll(); break;
        case 2:  portal.search(); break;
        case 3:  feed.create(u, false); break;
        case 4:  feed.create(u, true); break;
        case 5:  feed.view(); break;
        case 6:  searchUsers(u, auth, links); break;
        case 7:  links.requests(u.id, auth.all()); break;
        case 8:  links.view(u.id, auth.all()); break;
        case 9:  showAccount(u); break;
        case 10:
        {
            faculty_module::StudentRecord list[faculty_module::MAX_RECORDS];
            int count = buildFacultyStudentList(auth, portal, list, faculty_module::MAX_RECORDS);
            faculty_module::runFacultyPortalFor(u.fullName, u.password, to_string(u.collegeId),
                                                u.department, u.email, list, count);
            break;
        }
        case 11: cout << "Logged out successfully.\n"; break;
        }
    } while (choice != 11);
}

} // namespace kaushal_module


int main()
{
    kaushal_module::AuthManager auth;
    kaushal_module::StudentPortal portal;
    kaushal_module::FeedManager feed;
    kaushal_module::ConnectionManager links;

    cout << "\n============================================\n"
         << "          MYCOLLEGE INTEGRATED PORTAL\n"
         << "============================================\n"
         << "DEMO STUDENT: student@mycollege.edu / student123\n"
         << "DEMO FACULTY: faculty@mycollege.edu / faculty123\n";

    int choice;
    do
    {
        cout << "\n================ MAIN MENU ================\n"
             << "1. Register\n2. Login\n3. Exit\n";
        choice = kaushal_module::Input::number("Choose an option: ", 1, 3);

        if (choice == 1)
        {
            if (auth.registerUser())
            {
                const kaushal_module::User &u = auth.all().back();
                if (u.role == "student")
                    portal.registerStudent(u.id, u.fullName);
                else
                    cout << "\nFaculty account created. You can now log in.\n";
            }
        }
        else if (choice == 2)
        {
            kaushal_module::User loggedIn;
            if (auth.login(loggedIn))
            {
                if (loggedIn.role == "student")
                    kaushal_module::studentMenu(loggedIn, auth, portal, feed, links);
                else
                    kaushal_module::facultyMenu(loggedIn, auth, portal, feed, links);
            }
        }
        else
        {
            cout << "\nThank you for using MyCollege. Goodbye!\n";
        }
    } while (choice != 3);

    return 0;
}
