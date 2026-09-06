// The Microsoft Project--
// Members: Sanchu, Sam, WaghoBa, Jaggi;
// Basic typing
#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;
// Section 1 : Enum
enum class Branch
{
    CO, // Computer Engg
    CM, // Computer Technology
    EJ, // ENTC
    EE, // Electrical Engg
    ME, // Mechanical Egg
    IS, // Instrumentation Engg
    PG, // Production Engg
    CE  // Civil Engg
};
enum class Day
{
    MONDAY,
    TUESDAY,
    WEDNESDAY,
    THURSDAY,
    FRIDAY,
    SATURDAY,
    SUNDAY
};
enum class SessionType
{
    LECTURE,
    PRACTICAL
};
// Section 3 : Item
// Encapsulation
class Item
{
private:
    string name;
    string category;
    bool isPacked;

public:
    Item()
    {
        name = "";
        category = "";
        isPacked = false;
    }
    Item(string Iname, string Icategory)
    {
        this->name = Iname;
        this->category = Icategory;
    }
    string getname()
    {
        return name;
    }
    string getcategory()
    {
        return category;
    }
    bool isitempacked()
    {
        return isPacked;
    }
    void markPacked()
    {
        isPacked = true;
    }
    void markUnpacked()
    {
        isPacked = false;
    }
    bool operator==(const Item &);
    friend ostream &operator<<(ostream &, const Item &);
};
// Section 4 :Session Hierarchy (abstract class)
// Abstract class is use for Lecture and Practical share a lot in common, but different parts that actually matter for your features
class Session
{
protected:
    Day day;
    string startTime;
    string subjectName;
    string roomNumber;

public:
    Session(Day Sday, string SstartTime, string SsubjectName, string SroomNumber)
    {
        this->day = Sday;
        this->startTime = SstartTime;
        this->subjectName = SsubjectName;
        this->roomNumber = SroomNumber;
    }
    virtual ~Session()
    {
    }
    virtual vector<Item> getItemToCarry() = 0;
    virtual string getAlertMessage() = 0;
    virtual SessionType getType() = 0;
    Day getDay()
    {
        return day;
    }
    string getStartTime()
    {
        return startTime;
    }
    string getSubjectName()
    {
        return subjectName;
    }
    string getRoomNumber()
    {
        return roomNumber;
    }
    virtual void display() = 0;
};
// Inheritace and Polymorphism
class Lecture : public Session
{
private:
    vector<Item> defaultItem;

public:
    Lecture(Day sessionday, string sessionStartTime, string sessionSubject, string sessionRoom, vector<Item> itemlist) : Session(sessionday, sessionStartTime, sessionSubject, sessionRoom)
    {

        defaultItem = itemlist;
    }
    vector<Item> getItemToCarry()
    {
        return defaultItem;
    }
    string getAlertMessage()
    {
        return "Lecture: " + subjectName + " at " + startTime + " in " + roomNumber;
    }
    SessionType getType()
    {
        return SessionType::LECTURE;
    }
    void display()
    {
        cout << "Subject: " << subjectName << endl
             << "Time: " << startTime << endl
             << "Room: " << roomNumber << endl;
    }
};
class Practical : public Session
{
private:
    vector<Item> labItem;
    int alertLeadMinutes;

public:
    Practical(Day sessionday, string sessionStartTime, string sessionSubjectName, string sessionRoom, vector<Item> sessionlabItem, int sessionLeadMinutes) : Session(sessionday, sessionStartTime, sessionSubjectName, sessionRoom)
    {
        labItem = sessionlabItem;
        alertLeadMinutes = sessionLeadMinutes;
    }
    vector<Item> getItemToCarry()
    {
        return labItem;
    }
    string getAlertMessage()
    {
        return "Practical: " + subjectName + " at " + startTime + " in " + roomNumber;
    }
    SessionType getType()
    {
        return SessionType::PRACTICAL;
    }
    void display()
    {
        cout << "Subject: " << subjectName << endl
             << "Time: " << startTime << endl
             << "Room: " << roomNumber << endl;
    }
};
// Section 5: Student
// Encapsulation
class Student
{
private:
    string name;
    string rollnumber;
    Branch branch;
    string batchname;
    int semester;

public:
    Student(string Sname, string Srollnumber, Branch Sbranch, string Sbatchname, int Ssemester)
    {
        this->name = Sname;
        this->rollnumber = Srollnumber;
        this->branch = Sbranch;
        this->batchname = Sbatchname;
        this->semester = Ssemester;
    }
    string getname()
    {
        return name;
    }
    string getRollNumber()
    {
        return rollnumber;
    }
    Branch getBranch()
    {
        return branch;
    }
    string getBatchName()
    {
        return batchname;
    }
    int getSemester()
    {
        return semester;
    }
    void setName(string newName)
    {
        name = newName;
    }
    void setBranch(Branch newBranch)
    {
        branch = newBranch;
    }
    void setBatchName(string newBatchName)
    {
        batchname = newBatchName;
    }
    void setSemester(int newSemester)
    {
        semester = newSemester;
    }

    friend ostream &operator<<(ostream &, const Student &);
};
// Section:6 Time table ; uses Session*
//  Composition
//  the map's subscript operator, map indexing map access operator to be used
class TimeTable
{
private:
    map<Day, vector<Session *>> weekSchedule;

public:
    TimeTable()
    {
    }
    ~TimeTable()
    {
        for (pair<Day, vector<Session *>> entry : weekSchedule)
        {
            for (Session *s : entry.second)
            {
                delete s;
            }
        }
    }
    void addSession(Day day, Session *session)
    {
        weekSchedule[day].push_back(session);
    }
    vector<Session *> getSessionForDay(Day day)
    {
        return weekSchedule[day];
    }
    void display()
    {
        for (pair<Day, vector<Session *>> entry : weekSchedule)
        {
            for (Session *s : entry.second)
            {
                s->display();
            }
        }
    }
};
int main()
{
    return 0;
}
