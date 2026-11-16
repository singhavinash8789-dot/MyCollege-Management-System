#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <limits>
using namespace std;

namespace faculty_module {
class Student {
    private:
    string studentId;
    string name;
    string course;
    string email;
    string mobile;
    int performance;
    string section;

    public:

    Student() {
        studentId = "";
        name = "";
        course = "";
        email = "";
        mobile = "";
        performance = 0;
        section = "";
    }

    Student(string id, string name, string course, string email, string mobile, int performance, string section) {

        this->studentId = id;
        this->name = name;
        this->course = course;
        this->email = email;
        this->mobile = mobile;
        this->performance = performance;
        this->section = section;

    }

    string getStudentId() {
        return studentId;
    }

    int getPerformance() {
        return performance;
    }

    void setPer(int p) {
        performance = p;
    }

    string getName() {
        return name;
    }

    string getSec() {
        return section;
    }

    void display() {
        cout<<"Student ID: "<<studentId<<endl;
        cout<<"Name: "<<name<<endl;
        cout<<"Course: "<<course<<endl;
        cout<<"Email: "<<email<<endl;
        cout<<"Mobile: "<<mobile<<endl;
        cout<<"Performance: "<<performance<<endl;
        cout<<"Section : "<<section<<endl;
    }

    void displayPerformance() {
        cout<<"Student ID: "<<studentId<<endl;
        cout<<"Name: "<<name<<endl;
        cout<<"Performance: "<<performance<<endl;
        cout<<"Section : "<<section<<endl;
    }
};

struct attendence{
    string stId;
    string date;
    char status;
};

class attendenceSys {
    private:
    vector<attendence> stdrecords;
    public:
    void markAtten(Student students[], int studentCount) {

        string section;
        cout<<"Enter the section like CSE-A or CSE-B"<<endl;
        cin>>section;

        string date;
        cout<<"Enter date in format(DD-MM-YY) : "<<endl;
        cin>>date;

        bool flag = false;

        for(int i=0; i<studentCount; i++) {

            if(students[i].getSec() != section) {
                continue;
            }
            flag = true;

            char ask;
            cout<<"Student Id : "<<students[i].getStudentId()<<endl;
            cout<<"Student name : "<<students[i].getName()<<endl;
            cout<<"Section : "<<students[i].getSec()<<endl;

            cout<<"Enter P(present) or A(absent) : "<<endl;
            cin>>ask;

            if(ask == 'P' || ask == 'p') {
                ask = 'P';
            } else if(ask == 'A' || ask == 'a') {
                ask = 'A';
            } else {
                cout<<"You typed wrongly"<<endl;
                i--;
                continue;
            }

            attendence newRec;
            newRec.stId = students[i].getStudentId();
            newRec.date = date;
            newRec.status = ask;
            stdrecords.push_back(newRec);
        }

            if(!flag) {
                cout<<"No student found in this section"<<endl;
            } else {
                cout<<"Attendece marked"<<endl;
            }
    }

    void seeAttendence()
    {
        string idAttendence;
        cout<<"Enter the id for which to see attendence : "<<endl;
        cin>>idAttendence;

        bool f = false;
        int total = 0;
        int present = 0;
        int absent = 0;

        for(attendence rec : stdrecords)
        {

            if(rec.stId == idAttendence)
            {
                total++;
                cout<<"Date : "<<rec.date<<endl;
                cout<<"Status : "<<rec.status<<endl;
                if(rec.status == 'P') {
                    present++;
                } else if(rec.status == 'A') {
                    absent++;
                }

                f = true;
            }
        }

        if(f == false)
        {
            cout<<"Attendence record not found"<<endl;
        } else {
            cout<<"Total classes : "<<total<<endl;
            cout<<"Total present : "<<present<<endl;
            cout<<"Total absent : "<<absent<<endl;
            double percentage = (present * 100.0)/total;
            cout<<"Percentage : "<<percentage<<endl;
        }
    }

    void seeAttendByDate()
    {
        string dateToSearch;
        cout<<"Enter the date : "<<endl;
        cin>>dateToSearch;

        int total = 0;
        int pres = 0;
        int absen = 0;

        for(attendence rec : stdrecords)
        {
            if(rec.date == dateToSearch) {
                total++;

                if(rec.status == 'P')
                {
                    pres++;
                } else if(rec.status == 'A')
                {
                    absen++;
                }
            }
        }

        if(total == 0) {
            cout<<"Invalid date or record of that date not found"<<endl;
        } else {
            cout<<"Date : "<<dateToSearch<<endl;
            cout<<"Total students : "<<total<<endl;
            cout<<"Total present : "<<pres<<endl;
            cout<<"Total absent : "<<absen<<endl;
            double percentage = (pres * 100.0) / total;
            cout<<"Percentage : "<<percentage<<endl;
        }
    }
};



class announcement{
    private:
    int id;
    string title;
    string ann;
    string date;

    public:
    announcement(){
        id=0;
        title="";
        ann="";
        date="";
    }

    void getannouncement(){
        cout<<"Enter Announcement Id : ";
        cin>>id;
        cout<<endl;
        cout<<"Enter Title : ";
        getline(cin>>ws, title);
        cout<<endl;
        cout<<"Enter Announcement : ";
        getline(cin, ann);
        cout<<endl;
        cout<<"Enter date : ";
        getline(cin, date);
        cout<<endl;
    }

    void display(){
        cout<<"ID : "<<id<<endl;
        cout<<"Date : "<<date<<endl;
        cout<<"Title : "<<title<<endl;
        cout<<"Announcement : "<<ann<<endl;
    }

    int get_id(){
        return id;
    }
};

class Faculty {
    private:
    string name;
    string password;
    string facultyId;
    string department;
    string email;

    public:

    Faculty(string name, string password, string facultyId, string department, string email) {
        this->name = name;
        this->password = password;
        this->facultyId = facultyId;
        this->department = department;
        this->email = email;
    }


    bool login(string id, string pass) {
        if(id == facultyId && pass == password) {
            return true;
        }

        return false;
    }


    void searchStudent(Student students[], int studentCount) {
        string searchId;

        cout<<"Enter the student ID"<<endl;
        cin>>searchId;

        for(int i=0; i<studentCount; i++) {
            if(searchId == students[i].getStudentId()) {
                cout<<"Student found"<<endl;
                students[i].display();
                return;
            }
        }

        cout<<"Id not found"<<endl;
    }

    void addStudent(Student students[], int &studentCount) {
        if(studentCount == 100) {
            cout<<"Student list is full"<<endl;
            return;
        }

        string id, name, course, email, mobile, section;
        int performance;

        cout<<"Enter student ID"<<endl;
        cin>>id;

        for(int i=0; i<studentCount; i++) {
            if(id == students[i].getStudentId()) {
                cout<<"Student ID already exists"<<endl;
                return;
            }
        }

        cout<<"Enter student name"<<endl;
        getline(cin>>ws, name);

        cout<<"Enter student course"<<endl;
        getline(cin, course);

        cout<<"Enter student email"<<endl;
        cin>>email;

        cout<<"Enter student mobile number"<<endl;
        cin>>mobile;

        cout<<"Enter student section"<<endl;
        cin>>section;

        cout<<"Enter student performance"<<endl;
        cin>>performance;

        if(performance < 0 || performance > 100) {
            cout<<"Performance entered is invalid"<<endl;
            return;
        }

        students[studentCount] = Student(id, name, course, email, mobile, performance, section);

        studentCount++;

        cout<<"Student added"<<endl;
    }


    void viewStudentProfile(Student students[], int studentCount, Student recentStudents[], int &top) {
        string searchId;

        cout<<"Enter the student ID"<<endl;
        cin>>searchId;

        for(int i=0; i<studentCount; i++) {
            if(searchId == students[i].getStudentId()) {
                students[i].display();

                if(top < 99) {
                    top++;
                    recentStudents[top] = students[i];
                }

                return;
            }
        }

        cout<<"Id not found"<<endl;
    }

    void viewStudentPerformance(Student students[], int studentCount) {
        string searchId;

        cout<<"Enter the student ID"<<endl;
        cin>>searchId;

        for(int i=0; i<studentCount; i++) {
            if(searchId == students[i].getStudentId()) {
                students[i].displayPerformance();
                return;
            }
        }

        cout<<"Id not found"<<endl;
    }


    void sortStudents(Student students[], int studentCount) {
        for(int i=0; i<studentCount-1; i++) {
            for(int j=0; j<studentCount-i-1; j++) {
                if(students[j].getPerformance() < students[j+1].getPerformance()) {
                    Student temp = students[j];
                    students[j] = students[j+1];
                    students[j+1] = temp;
                }
            }
        }

        cout<<"Students sorted by performance"<<endl;

        for(int i=0; i<studentCount; i++) {
            students[i].displayPerformance();
            cout<<endl;
        }
    }

    void showRecentStudents(Student recentStudents[], int top) {
        if(top == -1) {
            cout<<"No student viewed"<<endl;
            return;
        }

        cout<<"Recently viewed students"<<endl;

        for(int i=top; i>=0; i--) {
            recentStudents[i].display();
            cout<<endl;
        }
    }

    void addStudentRequest(string requests[], int &front, int &rear) {
        if(rear == 99) {
            cout<<"Request queue is full"<<endl;
            return;
        }

        string studentId;

        cout<<"Enter student ID"<<endl;
        cin>>studentId;

        if(front == -1) {
            front = 0;
        }

        rear++;
        requests[rear] = studentId;

        cout<<"Request added"<<endl;
    }

    void processStudentRequest(string requests[], int &front, int &rear) {
        if(front == -1 || front > rear) {
            cout<<"No requests available"<<endl;
            return;
        }

        cout<<"Processing request of student ";
        cout<<requests[front]<<endl;

        front++;

        if(front > rear) {
            front = -1;
            rear = -1;
        }
    }


    void updatePer(Student students[], int studentCount)
    {
        if(studentCount == 0)
        {
            cout<<"No students"<<endl;
            return;
        }

        string st_id;
        cout<<"Enter student id to update performance"<<endl;
        cin>>st_id;

        for(int i=0; i<studentCount; i++)
        {
            if(st_id == students[i].getStudentId())
            {
                int newPer;

                cout<<"Current record of the student"<<endl;
                students[i].displayPerformance();

                cout<<"Enter the new performace(0-100)"<<endl;
                cin>>newPer;

                if(newPer < 0 || newPer > 100)
                {
                    cout<<"Invalid performance"<<endl;
                    return;
                }

                students[i].setPer(newPer);
                cout<<"stud per updated"<<endl;
                return;
            }
        }

        cout<<"Id not founded"<<endl;
    }


    void createAnnouncement(announcement announcements[], int &ann_Count){
        if(ann_Count == 100){
            cout<<"Announcement list is full"<<endl;
            return;
        }

        announcements[ann_Count].getannouncement();
        ann_Count++;
        cout<<"Announcement created successfully"<<endl;
    }

    void viewAnnouncement(announcement announcements[], int ann_Count){
        if(ann_Count == 0){
            cout<<"No announcements available"<<endl;
            return;
        }

        cout<<"ALL ANNOUNCEMENTS"<<endl;
        for(int i=0; i<ann_Count; i++){
            cout<<"Announcement "<<i+1<<endl;
            announcements[i].display();
            cout<<endl;
        }
    }

    void viewAnnouncements(announcement announcements[], int ann_Count){
        viewAnnouncement(announcements, ann_Count);
    }

    void searchAnnouncement(announcement announcements[], int ann_Count){
        if(ann_Count == 0){
            cout<<"No announcements available"<<endl;
            return;
        }

        int searchId;
        cout<<"Enter Announcement ID : ";
        cin>>searchId;

        for(int i=0; i<ann_Count; i++){
            if(searchId == announcements[i].get_id()){
                cout<<"Announcement Found"<<endl;
                announcements[i].display();
                return;
            }
        }

        cout<<"Announcement ID not found"<<endl;
    }

    void deleteAnnouncement(announcement announcements[], int &ann_Count){
        if(ann_Count == 0){
            cout<<"No announcements available"<<endl;
            return;
        }

        int searchId;
        cout<<"Enter Announcement ID to delete : ";
        cin>>searchId;

        for(int i=0; i<ann_Count; i++){
            if(searchId == announcements[i].get_id()){
                for(int j=i; j<(ann_Count-1); j++){
                    announcements[j] = announcements[j+1];
                }

                ann_Count--;
                cout<<"Announcement deleted successfully"<<endl;
                return;
            }
        }

        cout<<"Announcement ID not found"<<endl;
    }

    void dashboard(Student students[], int &studentCount, Student recentStudents[], int &top, string requests[], int &front, int &rear,
    attendenceSys &attendence, announcement announcements[], int &ann_Count) {
        int choice;

        do {
            cout<<endl;
            cout<<"FACULTY PORTAL"<<endl;
            cout<<"1. Search Student"<<endl;
            cout<<"2. Add Student"<<endl;
            cout<<"3. View Student Profile"<<endl;
            cout<<"4. View Student Performance"<<endl;
            cout<<"5. Sort Students by Performance"<<endl;
            cout<<"6. Recently Viewed Students"<<endl;
            cout<<"7. Add Student Request"<<endl;
            cout<<"8. Process Student Request"<<endl;
            cout<<"9. Update student performance"<<endl;
            cout<<"10. Mark attendence"<<endl;
            cout<<"11. View attendence by student ID"<<endl;
            cout<<"12. Attendence summary by date"<<endl;
            cout<<"13. Create Announcement"<<endl;
            cout<<"14. View Announcement"<<endl;
            cout<<"15. Search Announcement"<<endl;
            cout<<"16. Delete Announcement"<<endl;
            cout<<"17. Log out"<<endl;

            cout<<"Enter the choice"<<endl;
            cin>>choice;

            switch(choice) {
                case 1:
                    searchStudent(students, studentCount);
                    break;

                case 2:
                    addStudent(students, studentCount);
                    break;

                case 3:
                    viewStudentProfile(students, studentCount, recentStudents, top);
                    break;

                case 4:
                    viewStudentPerformance(students, studentCount);
                    break;

                case 5:
                    sortStudents(students, studentCount);
                    break;

                case 6:
                    showRecentStudents(recentStudents, top);
                    break;

                case 7:
                    addStudentRequest(requests, front, rear);
                    break;

                case 8:
                    processStudentRequest(requests, front, rear);
                    break;

                case 9:
                    updatePer(students,studentCount);
                    break;

                case 10:
                    attendence.markAtten(students, studentCount);
                    break;

                case 11:
                    attendence.seeAttendence();
                    break;

                case 12:
                    attendence.seeAttendByDate();
                    break;

                case 13:
                    createAnnouncement(announcements, ann_Count);
                    break;

                case 14:
                    viewAnnouncement(announcements, ann_Count);
                    break;

                case 15:
                    searchAnnouncement(announcements, ann_Count);
                    break;

                case 16:
                    deleteAnnouncement(announcements, ann_Count);
                    break;

                case 17:
                    cout<<"Logging out"<<endl;
                    break;

                default:
                    cout<<"Invalid choice"<<endl;
            }

        } while(choice != 17);
    }
};

int runFacultyPortalFor(const string& name, const string& password, const string& facultyId, const string& department, const string& email, Student students[], int studentCount) {
    attendenceSys attendence;
    Faculty loggedFaculty(name, password, facultyId, department, email);

    announcement announcements[100];
    int ann_count = 0;

    Student recentStudents[100];
    int top = -1;
    string requests[100];
    int front = -1;
    int rear = -1;

    cout << "\nWelcome to Faculty Portal, " << name << "!\n";
    loggedFaculty.dashboard(students, studentCount, recentStudents, top, requests, front, rear, attendence, announcements, ann_count);
    return 0;
}

}


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

    void display() const
    {
        cout << "\n========================================\n";
        cout << "             STUDENT PROFILE\n";
        cout << "========================================\n";
        cout << "ID: " << id << "\nName: " << name << "\nBio: " << bio
             << "\nBranch: " << branch << "\nPassing Year: " << passingYear << "\nSkills: ";
        if (skills.empty())
            cout << "Not added";
        for (size_t i = 0; i < skills.size(); ++i)
            cout << (i ? ", " : "") << skills[i];
        cout << "\nAchievements: ";
        if (achievements.empty())
            cout << "Not added";
        for (size_t i = 0; i < achievements.size(); ++i)
            cout << (i ? ", " : "") << achievements[i];
        cout << "\nCGPA: " << cgpa << "\nContact: " << contact << "\n";
        cout << "========================================\n";
    }
};

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
                  [](unsigned char c)
                  { return static_cast<char>(tolower(c)); });
        return value;
    }
};

class StudentPortal
{
    vector<Student> students;

public:
    StudentPortal()
    {
        students.push_back({1, 2027, "Aarav Sharma", "CSE student interested in problem solving.", "CSE", "aarav@example.com", 8.4f, {"C++", "DSA", "HTML"}, {"Hackathon participant"}});
        students.push_back({2, 2027, "Priya Verma", "Learning software development and databases.", "CSE", "priya@example.com", 8.8f, {"Java", "SQL", "Python"}, {"Coding contest finalist"}});
        students.push_back({3, 2026, "Rohan Mehta", "Interested in cloud and networking.", "ECE", "rohan@example.com", 8.1f, {"C", "Networking"}, {}});
    }

    void registerStudent(int id, const string &name)
    {
        Student s;
        s.id = id;
        s.name = name;
        cout << "\nComplete your student profile\n";
        s.bio = Input::text("Short bio: ");
        s.branch = Input::text("Branch: ");
        s.passingYear = Input::number("Passing year: ", 2000, 2100);
        int n = Input::number("Number of skills (0-5): ", 0, 5);
        for (int i = 0; i < n; ++i)
            s.skills.push_back(Input::text("Skill " + to_string(i + 1) + ": "));
        s.cgpa = Input::decimal("CGPA (0-10): ", 0, 10);
        s.contact = Input::text("Contact details: ");
        n = Input::number("Number of achievements (0-10): ", 0, 10);
        for (int i = 0; i < n; ++i)
            s.achievements.push_back(Input::text("Achievement " + to_string(i + 1) + ": "));
        students.push_back(s);
        cout << "\nStudent profile created successfully.\n";
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
            case 1:
                s->name = Input::text("New name: ");
                break;
            case 2:
                s->bio = Input::text("New bio: ");
                break;
            case 3:
                s->branch = Input::text("New branch: ");
                break;
            case 4:
                s->passingYear = Input::number("New passing year: ", 2000, 2100);
                break;
            case 5:
            {
                s->skills.clear();
                int n = Input::number("Number of skills (0-5): ", 0, 5);
                for (int i = 0; i < n; ++i)
                    s->skills.push_back(Input::text("Skill " + to_string(i + 1) + ": "));
                break;
            }
            case 6:
                s->cgpa = Input::decimal("New CGPA: ", 0, 10);
                break;
            case 7:
                s->contact = Input::text("New contact: ");
                break;
            case 8:
            {
                s->achievements.clear();
                int n = Input::number("Number of achievements (0-10): ", 0, 10);
                for (int i = 0; i < n; ++i)
                    s->achievements.push_back(Input::text("Achievement " + to_string(i + 1) + ": "));
                break;
            }
            case 9:
                break;
            }
            if (choice != 9)
                cout << "\nProfile updated.\n";
        } while (choice != 9);
    }

    Student *find(int id)
    {
        for (size_t i = 0; i < students.size(); ++i)
            if (students[i].id == id)
                return &students[i];
        return NULL;
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

    void create(const User &user, bool blog)
    {
        FeedItem item;
        item.id = nextId++;
        item.authorId = user.id;
        item.author = user.fullName;
        item.type = blog ? "BLOG" : "POST";
        item.title = blog ? Input::text("Blog title: ") : "Community Post";
        item.content = Input::text(blog ? "Write your blog: " : "Write your post: ");
        feed.push_back(item);
        cout << "\n"
             << item.type << " published successfully.\n";
    }

    void view() const
    {
        if (feed.empty())
        {
            cout << "\nThe feed is empty. Be the first to share something!\n";
            return;
        }
        cout << "\n=============== COMMUNITY FEED ===============\n";
        for (int i = static_cast<int>(feed.size()) - 1; i >= 0; --i)
            feed[i].display();
    }
};

class AuthManager
{
    vector<User> users;
    int nextId;

public:
    AuthManager() : nextId(4)
    {
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
        u.id = nextId++;
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
            bool exists = false;
            for (size_t i = 0; i < users.size(); ++i)
                if (Input::lower(users[i].email) == Input::lower(u.email))
                    exists = true;
            if (exists)
                cout << "Email already registered. Try another.\n";
            else
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
                --nextId;
                return false;
            }
        }
        u.department = Input::text("Department: ");
        users.push_back(u);
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
        cout << "Login limit reached.\n";
        return false;
    }
};

class ConnectionManager
{
    map<int, vector<int>> connected;
    map<int, vector<int>> pending;

    bool has(const vector<int> &values, int id) const
    {
        return find(values.begin(), values.end(), id) != values.end();
    }

public:
    void send(int from, int to)
    {
        if (from == to)
            cout << "You cannot connect with yourself.\n";
        else if (has(connected[from], to))
            cout << "You are already connected.\n";
        else if (has(pending[to], from))
            cout << "Request already sent.\n";
        else if (has(pending[from], to))
            cout << "This user has already sent you a request. Check requests.\n";
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
                ++i;
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
        if (Input::lower(users[i].fullName).find(key) != string::npos)
        {
            found = true;
            cout << "\nID: " << users[i].id << "\nName: " << users[i].fullName
                 << "\nRole: " << users[i].role << "\nDepartment: " << users[i].department << '\n';
            if (users[i].id != current.id &&
                Input::number("Send connection request? (1=Yes, 2=No): ", 1, 2) == 1)
                links.send(current.id, users[i].id);
        }
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
        case 1:
            portal.viewAll();
            break;
        case 2:
            portal.search();
            break;
        case 3:
            portal.update(u.id);
            break;
        case 4:
            feed.create(u, false);
            break;
        case 5:
            feed.create(u, true);
            break;
        case 6:
            feed.view();
            break;
        case 7:
            searchUsers(u, auth, links);
            break;
        case 8:
            links.requests(u.id, auth.all());
            break;
        case 9:
            links.view(u.id, auth.all());
            break;
        case 10:
            showAccount(u);
            break;
        case 11:
            cout << "Logged out successfully.\n";
            break;
        }
    } while (choice != 11);
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
        case 1:
            portal.viewAll();
            break;
        case 2:
            portal.search();
            break;
        case 3:
            feed.create(u, false);
            break;
        case 4:
            feed.create(u, true);
            break;
        case 5:
            feed.view();
            break;
        case 6:
            searchUsers(u, auth, links);
            break;
        case 7:
            links.requests(u.id, auth.all());
            break;
        case 8:
            links.view(u.id, auth.all());
            break;
        case 9:
            showAccount(u);
            break;
        case 10:
        {
            faculty_module::Student sharedStudents[100];
            int sharedStudentCount = 0;
            const vector<User> &allUsers = auth.all();

            for (size_t i = 0; i < allUsers.size() && sharedStudentCount < 100; ++i)
            {
                if (allUsers[i].role == "student")
                {
                    kaushal_module::Student *profile = portal.find(allUsers[i].id);
                    string mobile = "Not provided";
                    int performance = 0;
                    string section = "CSE-A";

                    if (profile != NULL)
                    {
                        mobile = profile->contact;
                        performance = static_cast<int>(profile->cgpa * 10 + 0.5f);
                        section = profile->branch + "-A";
                    }

                    sharedStudents[sharedStudentCount] = faculty_module::Student(
                        to_string(allUsers[i].collegeId), allUsers[i].fullName,
                        allUsers[i].department, allUsers[i].email, mobile, performance, section);
                    sharedStudentCount++;
                }
            }

            faculty_module::runFacultyPortalFor(u.fullName, u.password, to_string(u.collegeId),
                                                u.department, u.email, sharedStudents, sharedStudentCount);
            break;
        }
        case 11:
            cout << "Logged out successfully.\n";
            break;
        }
    } while (choice != 11);
}

int runKaushalModule()
{
    AuthManager auth;
    StudentPortal portal;
    FeedManager feed;
    ConnectionManager links;

    cout << "\n============================================\n"
         << "          MYCOLLEGE STUDENT PORTAL\n"
         << "============================================\n"
         << "DEMO STUDENT: student@mycollege.edu / student123\n"
         << "DEMO FACULTY: faculty@mycollege.edu / faculty123\n";

    int choice;
    do
    {
        cout << "\n================ MAIN MENU ================\n"
             << "1. Register\n2. Login\n3. Exit\n";
        choice = Input::number("Choose an option: ", 1, 3);
        if (choice == 1)
        {
            if (auth.registerUser())
            {
                const User &u = auth.all().back();
                if (u.role == "student")
                    portal.registerStudent(u.id, u.fullName);
                else
                    cout << "\nFaculty account created. You can now log in.\n";
            }
        }
        else if (choice == 2)
        {
            User loggedIn;
            if (auth.login(loggedIn))
            {
                if (loggedIn.role == "student")
                    studentMenu(loggedIn, auth, portal, feed, links);
                else
                    facultyMenu(loggedIn, auth, portal, feed, links);
            }
        }
        else
        {
            cout << "\nThank you for using MyCollege Student Portal. Goodbye!\n";
        }
    } while (choice != 3);
    return 0;
}
}

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
