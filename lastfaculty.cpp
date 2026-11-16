#include<iostream>
#include<string>
#include<vector>
using namespace std;

class Student { // The details we are taking for the student
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

    Student(string id, string n, string c, string em, string mob, int per, string sec) {
        // parameterized constructor
        studentId = id;
        name = n;
        course = c;
        email = em;
        mobile = mob;
        performance = per;
        section = sec;

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



//            ANNOUNCEMENT

class announcement{
    private:
    int id;
    string title;
    string ann;
    string date;

    public:
    announcement(){   // Default constructor
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

// Faculty portal
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

    // 3rd phase
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


//      From here i have added announcement management functions



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

int main() {
    attendenceSys attendence;
    Faculty f[3] = {
        Faculty("Rahul", "Rahul@123", "Rahul25101", "CSE", "rahul@gehu.com"),
        Faculty("Deepak", "Deepak@123", "Deepak25102", "CSE", "deepak@gehu.com"),
        Faculty("Ajay", "Ajay@123", "Ajay25103", "CSE", "ajay@gehu.com")
    };

    Student students[100];
    int studentCount = 3;

    announcement announcements[100];
    int ann_count=0;

    students[0] = Student("E101", "Mayank Pandey", "BTECH CSE", "mayankpandey0091@gmail.com", "8532845194", 90, "CSE-A");

    students[1] = Student("E102", "Ayush Negi", "BTECH CSE", "ayush90@gmail.com", "7890453218", 80, "CSE-B");

    students[2] = Student("E103", "Harsh Bansal", "BTECH CSE", "harshbansal89@gmail.com", "7865786719", 79, "CSE-A");

    Student recentStudents[100];
    int top = -1;

    string requests[100];
    int front = -1;
    int rear = -1;

    string id, password;

    cout<<"FACULTY LOGIN"<<endl;

    cout<<"Enter the id"<<endl;
    cin>>id;

    cout<<"Enter the password"<<endl;
    cin>>password;

    bool logged = false;

    for(int i=0; i<3; i++) {
        if(f[i].login(id, password)) {
            logged = true;

            f[i].dashboard(students, studentCount, recentStudents, top, requests, front, rear, attendence, announcements, ann_count);

            break;
        }
    }

    if(!logged) {
        cout<<"Invalid Credentials"<<endl;
    }

    return 0;
}
