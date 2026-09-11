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
        isPacked = false;
        this->name = Iname;
        this->category = Icategory;
    }
    string getname() const
    {
        return name;
    }
    string getcategory() const
    {
        return category;
    }
    bool isitempacked() const
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
ostream &operator<<(ostream &os, const Item &item)
{
    os << item.getname() << "(" << item.getcategory() << ") - ";
    if (item.isitempacked())
    {
        os << "Packed";
    }
    else
    {
        os << "Not Packed";
    }
    return os;
}

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
// section 7 : Bag
// Composition
class Bag
{
private:
    vector<Item> items;

public:
    Bag()
    {
    }
    void addItem(Item newItem)
    {
        items.push_back(newItem);
    }
    void marksItemPacked(string itemName)
    {
        for (Item &i : items)
        {
            if (i.getname() == itemName)
            {
                i.markPacked();
            }
        }
    }
    vector<Item> getPendingItems()
    {
        vector<Item> pendingItems;
        for (Item &i : items)
        {
            if (!i.isitempacked())
            {
                pendingItems.push_back(i);
            }
        }
        return pendingItems;
    }
    vector<Item> getAllItems()
    {
        return items;
    }
    void display()
    {
        for (Item i : items)
        {
            cout << i << endl;
        }
    }
};
// Section 8 - BagManager
class BagManager
{
private:
    TimeTable *timeTable;
    Student *student;

public:
    BagManager(TimeTable *Btimetable, Student *Bstudent)
    {
        this->timeTable = Btimetable;
        this->student = Bstudent;
    }
    Bag generatebagForDay(Day day)
    {
        vector<Session *> todaySessions = timeTable->getSessionForDay(day);
        Bag bag;

        for (Session *s : todaySessions)
        {
            vector<Item> requiredItem = s->getItemToCarry();
            for (Item i : requiredItem)
            {
                bag.addItem(i);
            }
        }
        return bag;
    }
    vector<string> getAlertsForDay(Day day)
    {
        vector<Session *> todaySessions = timeTable->getSessionForDay(day);
        vector<string> alerts;
        for (Session *s : todaySessions)
        {
            alerts.push_back(s->getAlertMessage());
        }
        return alerts;
    }
    void displayTodaySummary(Day day)
    {
        Bag bag = generatebagForDay(day);
        bag.display();
        vector<string> alert = getAlertsForDay(day);
        for (string a : alert)
        {
            cout << a << endl;
        }
    }
};
string getBranchName(Branch b)
{

    switch (b)
    {
    case Branch::CO:
        return "Computer Engineering";
    case Branch::CM:
        return "Computer Technology";
    case Branch::EJ:
        return "Electronics and Telecommunication Engineering";
    case Branch::EE:
        return "Electrical Engineering";
    case Branch::ME:
        return "Mechanical Engineering";
    case Branch::IS:
        return "Instrumentation Engineering";
    case Branch::PG:
        return "Production Engineering";
    case Branch::CE:
        return "Civil Engineering";
    }
    return "Unkown";
}
int main()
{
    Student *studentPtr = nullptr;
    TimeTable *timeTablePtr = nullptr;
    Bag *bagPtr = nullptr;

    while (true)
    {
        cout << "Enter Your Choice:" << endl;
        cout << "1. Setup Profile" << endl
             << "2. Setup Timetable" << endl
             << "3. Show Todays's Bag" << endl
             << "4. Mark Item Packed" << endl
             << "5. EXIT" << endl;
        int choice;
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            cin.ignore();
            cout << "Enter Your Name: ";
            string name;
            getline(cin, name);
            cout << "Enter Your Roll Number: ";
            string rollnumber;
            cin >> rollnumber;
            cout << "Enter Your Branch: " << endl;
            cout << "Enter a number for Your Branch: " << endl;
            cout << "1. Computer Engineering" << endl
                 << "2.Computer Technology" << endl
                 << "3.Electronics And Telecomunication" << endl
                 << "4.Electrical Engineering" << endl
                 << "5.Mechanical Engineering" << endl
                 << "6.Instrumention Engineering" << endl
                 << "7.Production Engineering" << endl
                 << "8. Civil Engineering" << endl;
            int choiceB;
            cin >> choiceB;

            Branch selectedBranch;
            if (choiceB == 1)
            {
                selectedBranch = Branch::CO;
            }
            else if (choiceB == 2)
            {
                selectedBranch = Branch::CM;
            }
            else if (choiceB == 3)
            {
                selectedBranch = Branch::EJ;
            }
            else if (choiceB == 4)
            {
                selectedBranch = Branch::EE;
            }
            else if (choiceB == 5)
            {
                selectedBranch = Branch::ME;
            }
            else if (choiceB == 6)
            {
                selectedBranch = Branch::IS;
            }
            else if (choiceB == 7)
            {
                selectedBranch = Branch::PG;
            }

            else if (choiceB == 8)
            {
                selectedBranch = Branch::CE;
            }
            else
            {
                cout << "Enter Correct Choice! " << endl;
            }
            cin.ignore();
            int semester;
            string batchname = getBranchName(selectedBranch);
            cout << "Enter Your Current Semester: 1/2/3/4/5/6" << endl;
            cin >> semester;
            studentPtr = new Student(name, rollnumber, selectedBranch, batchname, semester);
            break;
        }
        case 2:
        {
            if (timeTablePtr == nullptr)
            {
                timeTablePtr = new TimeTable();
            }

            int choiceD;
            cout << "Enter Choice for Current Day: " << endl
                 << "1. MONDAY" << endl
                 << "2. TUESDAY" << endl
                 << "3. WEDNESDAY" << endl
                 << "4. THURSDAY" << endl
                 << "5. FRIDAY" << endl
                 << "6. SATURDAY" << endl
                 << "7. SUNDAY" << endl;
            Day sessionDay;
            cin >> choiceD;
            if (choiceD == 1)
            {
                sessionDay = Day::MONDAY;
            }
            else if (choiceD == 2)
            {
                sessionDay = Day::TUESDAY;
            }
            else if (choiceD == 3)
            {
                sessionDay = Day::WEDNESDAY;
            }
            else if (choiceD == 4)
            {
                sessionDay = Day::THURSDAY;
            }
            else if (choiceD == 5)
            {
                sessionDay = Day::FRIDAY;
            }
            else if (choiceD == 6)
            {
                sessionDay = Day::SATURDAY;
            }
            else if (choiceD == 7)
            {
                sessionDay = Day::SUNDAY;
            }
            else
            {
                cout << "Invalid Choice!" << endl;
            }
            int typeChoice;
            cout << "Enter Choice for 1. Lecture / 2. Practical: " << endl;
            cin >> typeChoice;
            if (typeChoice == 1)
            {
                string subjectName;
                cout << "Enter Subject Name of Lecture: " << endl;
                cin.ignore();
                getline(cin, subjectName);
                string startTime;
                cout << "Enter Start Time of Lecture For Subject: " << endl;
                getline(cin, startTime);
                string roomNumber;
                cout << "Enter Room Number of Lecture: " << endl;
                getline(cin, roomNumber);
                vector<Item> defaultItems;

                cout << "How many Items you want to add?" << endl;
                int itemCount;
                cin >> itemCount;
                cin.ignore();
                for (int i = 0; i < itemCount; i++)
                {
                    string itemName;
                    cout << "Enter Item Name: " << endl;
                    getline(cin, itemName);
                    string itemCategory;
                    getline(cin, itemCategory);
                    Item newItem(itemName, itemCategory);
                    defaultItems.push_back(newItem);
                }
                Lecture *newLecture = new Lecture(sessionDay, startTime, subjectName, roomNumber, defaultItems);
                timeTablePtr->addSession(sessionDay, newLecture);
            }
            else if (typeChoice == 2)
            {
                string subjectName;
                cout << "Enter Subject Name of Practical: " << endl;
                cin.ignore();
                getline(cin, subjectName);
                string startTime;
                cout << "Enter Start Time of Lecture For Subject: " << endl;
                getline(cin, startTime);
                string roomNumber;
                cout << "Enter Room Number of Lecture: " << endl;
                getline(cin, roomNumber);
                string labItemName;
                vector<Item> defaultItem;
                cout << "How many Items you want to add? " << endl;
                int itemCount;
                cin >> itemCount;
                cin.ignore();
                for (int i = 0; i < itemCount; i++)
                {
                    cout << "Enter Lab Item: " << endl;
                    getline(cin, labItemName);
                    string labItemCategory;
                    cout << "Enter Lab Item Category: " << endl;
                    getline(cin, labItemCategory);
                    Item newItem(labItemName, labItemCategory);
                    defaultItem.push_back(newItem);
                }

                int alertLeadMinutes;
                cout << "Enter Alert Lead Minutes: " << endl;
                cin >> alertLeadMinutes;

                Practical *newPractical = new Practical(sessionDay, startTime, subjectName, roomNumber, defaultItem, alertLeadMinutes);
                timeTablePtr->addSession(sessionDay, newPractical);
            }
            else
            {
                cout << "Invalid Choice!" << endl;
            }
            break;
        }
        case 3:
        {
            Day sessionDay;
            int choiceD;
            cout << "Enter Choice for a Day You want? " << endl
                 << "1. MONDAY" << endl
                 << "2. TUESDAY" << endl
                 << "3. WEDNESDAY" << endl
                 << "4. THURSDAY" << endl
                 << "5. FRIDAY" << endl
                 << "6. SATURDAY" << endl
                 << "7. SUNDAY" << endl;
            cin >> choiceD;
            cin.ignore();
            if (choiceD == 1)
            {
                sessionDay = Day::MONDAY;
            }
            else if (choiceD == 2)
            {
                sessionDay = Day::TUESDAY;
            }
            else if (choiceD == 3)
            {
                sessionDay = Day::WEDNESDAY;
            }
            else if (choiceD == 4)
            {
                sessionDay = Day::THURSDAY;
            }
            else if (choiceD == 5)
            {
                sessionDay = Day::FRIDAY;
            }
            else if (choiceD == 6)
            {
                sessionDay = Day::SATURDAY;
            }
            else if (choiceD == 7)
            {
                sessionDay = Day::SUNDAY;
            }
            else
            {
                cout << "Invalid Choice!" << endl;
            }
            if (studentPtr == nullptr || timeTablePtr == nullptr)
            {
                cout << "Please set uo your Profile and Timetable first " << endl;
            }
            else
            {
                BagManager manager(timeTablePtr, studentPtr);
                if (bagPtr == nullptr)
                {
                    bagPtr = new Bag(manager.generatebagForDay(sessionDay));
                }
                bagPtr->display();

                vector<string> alerts = manager.getAlertsForDay(sessionDay);
                for (string a : alerts)
                {
                    cout << a << endl;
                }
            }

            break;
        }
        case 4:
        {
            if (bagPtr == nullptr)
            {
                cout << "Please view today's bag first (option 3) before marking items packed!";
            }
            else
            {
                for (Item i : bagPtr->getAllItems())
                {
                    cout << i << endl;
                }
                cin.ignore();
                string itemNametoMark;
                cout << "Enter the name of the item to mark as packed: " << endl;
                getline(cin, itemNametoMark);
                bagPtr->marksItemPacked(itemNametoMark);
            }
            break;
        }

        case 5:
            cout << "Program successfully Ended!" << endl;
            return 0;
        }
    }

    return 0;
}
