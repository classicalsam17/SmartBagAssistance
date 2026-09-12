// The Microsoft Project--
// Members: Sanchu, Sam, WaghoBa, Jaggi;
// Basic typing
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <algorithm>
#include <cstdio>
#include <cctype>
#include <limits>
using namespace std;

// Safely reads an int from cin. If the user types something that
// is not a number, this clears cin's fail state and discards the
// bad input, and returns false instead of leaving cin permanently
// broken (which would otherwise make every later cin >> fail too).
bool readInt(int &value)
{
    cin >> value;
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    }
    return true;
}
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
    void markUnpacked() { isPacked = false; }
    bool operator==(const Item &);
    friend ostream &operator<<(ostream &, const Item &);
};
bool Item::operator==(const Item &other)
{
    // Same equality rule already used for duplicate detection in Bag::addItem:
    // items are "equal" if they have the same name, case-insensitively.
    string a = name, b = other.name;
    transform(a.begin(), a.end(), a.begin(), ::tolower);
    transform(b.begin(), b.end(), b.begin(), ::tolower);
    return a == b;
}
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
    string professorName;

public:
    Session(Day Sday, string SstartTime, string SsubjectName, string SroomNumber, string SprofessorName)
    {
        this->day = Sday;
        this->startTime = SstartTime;
        this->subjectName = SsubjectName;
        this->roomNumber = SroomNumber;
        this->professorName = SprofessorName;
    }
    virtual ~Session() {}
    virtual vector<Item> getItemToCarry() = 0;
    virtual string getAlertMessage() = 0;
    virtual SessionType getType() = 0;
    Day getDay() const { return day; }
    string getStartTime() const { return startTime; }
    string getSubjectName() const { return subjectName; }
    string getRoomNumber() const { return roomNumber; }
    string getProfessorName() const { return professorName; }
    virtual void display() = 0;
};
// Inheritace and Polymorphism
class Lecture : public Session
{
private:
    vector<Item> defaultItem;

public:
    Lecture(Day sessionday, string sessionStartTime, string sessionSubject, string sessionRoom, string sessionProfessor, vector<Item> itemlist) : Session(sessionday, sessionStartTime, sessionSubject, sessionRoom, sessionProfessor)
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
    string practicalBatch;

public:
    Practical(Day sessionday, string sessionStartTime, string sessionSubjectName, string sessionRoom, string sessionProfessor, vector<Item> sessionlabItem, int sessionLeadMinutes, string sessionPracticalBatch) : Session(sessionday, sessionStartTime, sessionSubjectName, sessionRoom, sessionProfessor)
    {
        labItem = sessionlabItem;
        alertLeadMinutes = sessionLeadMinutes;
        practicalBatch = sessionPracticalBatch;
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
    string getPracticalBatch() const
    {
        return practicalBatch;
    }
    void setPracticalBatch(string newBatch)
    {
        practicalBatch = newBatch;
    }
    void display()
    {
        cout << "Subject: " << subjectName << endl
             << "Time: " << startTime << endl
             << "Room: " << roomNumber << endl;
    }
    int getAlertLeadMinutes() const
    {
        return alertLeadMinutes;
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
    string practicalBatch;
    int semester;

public:
    Student(string Sname, string Srollnumber, Branch Sbranch, string SpracticalBatch, int Ssemester)
    {
        this->name = Sname;
        this->rollnumber = Srollnumber;
        this->branch = Sbranch;
        this->practicalBatch = SpracticalBatch;
        this->semester = Ssemester;
    }
    string getname() const
    {
        return name;
    }
    string getRollNumber() const
    {
        return rollnumber;
    }
    Branch getBranch() const
    {
        return branch;
    }
    string getPracticalBatch() const
    {
        return practicalBatch;
    }
    int getSemester() const
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
    void setPracticalBatch(string newPracticalBatch)
    {
        practicalBatch = newPracticalBatch;
    }
    void setSemester(int newSemester)
    {
        semester = newSemester;
    }
    void setRollNumber(string newRollNumber)
    {
        rollnumber = newRollNumber;
    }
    friend ostream &operator<<(ostream &, const Student &);
};
ostream &operator<<(ostream &os, const Student &student)
{
    os << "Name            : " << student.name << endl;
    os << "Roll Number     : " << student.rollnumber << endl;
    os << "Practical Batch : " << student.practicalBatch << endl;
    os << "Semester        : " << student.semester << endl;
    return os;
}
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
    void deleteSession(Day day, int index)
    {
        if (weekSchedule.find(day) == weekSchedule.end())
            return;

        vector<Session *> &sessions = weekSchedule[day];

        if (index < 0 || static_cast<size_t>(index) >= sessions.size())
            return;

        delete sessions[index];
        sessions.erase(sessions.begin() + index);
    }
    void updatePracticalBatch(string newBatch)
    {
        for (pair<const Day, vector<Session *>> &entry : weekSchedule)
        {
            for (Session *s : entry.second)
            {
                if (s->getType() == SessionType::PRACTICAL)
                {
                    Practical *practical =
                        dynamic_cast<Practical *>(s);

                    practical->setPracticalBatch(newBatch);
                }
            }
        }
    }
    vector<Session *> getSessionForDay(Day day)
    {
        auto it = weekSchedule.find(day);
        if (it == weekSchedule.end())
        {
            return vector<Session *>(); // no sessions for this day; map stays untouched
        }
        return it->second;
    }
    void display()
    {
        cout << left
             << setw(12) << "Day"
             << setw(15) << "Type"
             << setw(12) << "Batch"
             << setw(25) << "Subject"
             << setw(15) << "Time"
             << setw(12) << "Room"
             << setw(20) << "Professor"
             << endl;
        cout << string(111, '-') << endl;
        for (const pair<const Day, vector<Session *>> &entry : weekSchedule)
        {
            string dayName;
            switch (entry.first)
            {
            case Day::MONDAY:
                dayName = "Monday";
                break;
            case Day::TUESDAY:
                dayName = "Tuesday";
                break;
            case Day::WEDNESDAY:
                dayName = "Wednesday";
                break;
            case Day::THURSDAY:
                dayName = "Thursday";
                break;
            case Day::FRIDAY:
                dayName = "Friday";
                break;
            case Day::SATURDAY:
                dayName = "Saturday";
                break;
            case Day::SUNDAY:
                dayName = "Sunday";
                break;
            }
            for (Session *s : entry.second)
            {
                string type;
                string batch = "-";
                if (s->getType() == SessionType::LECTURE)
                {
                    type = "Lecture";
                }
                else
                {
                    type = "Practical";
                    Practical *practical =
                        dynamic_cast<Practical *>(s);
                    batch = practical->getPracticalBatch();
                }
                cout << left
                     << setw(12) << dayName
                     << setw(15) << type
                     << setw(12) << batch
                     << setw(25) << s->getSubjectName()
                     << setw(15) << s->getStartTime()
                     << setw(12) << s->getRoomNumber()
                     << setw(20) << s->getProfessorName()
                     << endl;
            }
        }
    }
    map<Day, vector<Session *>> getAllSessions()
    {
        return weekSchedule;
    }
};
string toLowerCase(string text) // helper fuction
{
    transform(text.begin(), text.end(), text.begin(), ::tolower);
    return text;
}
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
    bool addItem(Item newItem)
    {
        for (Item &i : items)
        {
            if (toLowerCase(i.getname()) == toLowerCase(newItem.getname()))
            {
                return false;
            }
        }

        items.push_back(newItem);
        return true;
    }
    int marksItemPacked(string itemName)
    {
        for (Item &i : items)
        {
            if (toLowerCase(i.getname()) == toLowerCase(itemName))
            {
                if (i.isitempacked())
                    return 2;

                i.markPacked();
                return 1;
            }
        }

        return 0;
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
        cout << left
             << setw(5) << "No."
             << setw(25) << "Item Name"
             << setw(15) << "Category"
             << setw(12) << "Status"
             << endl;
        cout << string(57, '-') << endl;
        int itemNo = 1;
        for (Item i : items)
        {
            cout << left
                 << setw(5) << (to_string(itemNo++) + ".")
                 << setw(25) << i.getname()
                 << setw(15) << i.getcategory()
                 << setw(12) << (i.isitempacked() ? "Packed" : "Not Packed")
                 << endl;
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
            if (s->getType() == SessionType::PRACTICAL)
            {
                Practical *practical = dynamic_cast<Practical *>(s);
                if (practical->getPracticalBatch() != student->getPracticalBatch())
                {
                    continue;
                }
            }
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
            if (s->getType() == SessionType::PRACTICAL)
            {
                Practical *practical = dynamic_cast<Practical *>(s);
                if (practical->getPracticalBatch() != student->getPracticalBatch())
                {
                    continue;
                }
            }
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
// Exception
class FileNotFoundException : public exception
{
private:
    string message;

public:
    FileNotFoundException(string Fmessage)
    {
        message = Fmessage;
    }
    const char *what() const noexcept
    {
        return message.c_str();
    }
};
class InvalidSessionDataException : public exception
{
private:
    string message;

public:
    InvalidSessionDataException(string Imessage)
    {
        message = Imessage;
    }
    const char *what() const noexcept
    {
        return message.c_str();
    }
};
string getBranchCode(Branch branch)
{
    switch (branch)
    {
    case Branch::CO:
        return "CO";
    case Branch::CM:
        return "CM";
    case Branch::EJ:
        return "EJ";
    case Branch::EE:
        return "EE";
    case Branch::ME:
        return "ME";
    case Branch::IS:
        return "IS";
    case Branch::PG:
        return "PG";
    case Branch::CE:
        return "CE";
    default:
        return "";
    }
}
// File Handling
class FileHandler
{
public:
    string getFilePrefix(Student *studentPtr)
    {
        string branchCode = getBranchCode(studentPtr->getBranch());
        return branchCode + "_" + studentPtr->getRollNumber();
    }
    bool studentExists(string branchCode, string rollNumber)
    {
        string filename = "student_" + branchCode + "_" + rollNumber + ".txt";

        ifstream file(filename);

        if (file)
        {
            file.close();
            return true;
        }

        return false;
    }
    void saveStudent(Student *studentPtr)
    {
        string filename = "student_" + getFilePrefix(studentPtr) + ".txt";
        ofstream file(filename);
        if (!file)
        {
            throw FileNotFoundException("Unable to open student file!");
        }
        file << studentPtr->getname() << endl;
        file << studentPtr->getRollNumber() << endl;
        file << static_cast<int>(studentPtr->getBranch()) << endl;
        file << studentPtr->getPracticalBatch() << endl;
        file << studentPtr->getSemester() << endl;
        file.close();
    }
    void deleteStudentFiles(string branchCode, string rollNumber)
    {
        string studentFile = "student_" + branchCode + "_" + rollNumber + ".txt";
        string timetableFile = "timetable_" + branchCode + "_" + rollNumber + ".txt";

        remove(studentFile.c_str());
        remove(timetableFile.c_str());
    }
    void saveTimeTable(TimeTable *timeTablePtr, Student *studentPtr)
    {
        string filename = "timetable_" + getFilePrefix(studentPtr) + ".txt";
        ofstream file(filename);
        if (!file)
        {
            throw FileNotFoundException("Unable to Open TimeTable File!");
        }
        map<Day, vector<Session *>> allSessions = timeTablePtr->getAllSessions();
        for (const pair<const Day, vector<Session *>> &entry : allSessions)
        {
            for (Session *s : entry.second)
            {
                file << static_cast<int>(s->getDay()) << endl;
                file << static_cast<int>(s->getType()) << endl;
                file << s->getStartTime() << endl;
                file << s->getSubjectName() << endl;
                file << s->getRoomNumber() << endl;
                file << s->getProfessorName() << endl;
                vector<Item> items = s->getItemToCarry();
                file << items.size() << endl;
                for (Item item : items)
                {
                    file << item.getname() << endl;
                    file << item.getcategory() << endl;
                }
                if (s->getType() == SessionType::PRACTICAL)
                {
                    Practical *practical = dynamic_cast<Practical *>(s);
                    file << practical->getPracticalBatch() << endl;
                    file << practical->getAlertLeadMinutes() << endl;
                }
            }
        }
    }
    Student *loadStudent(string branchCode, string rollNumber)
    {
        string filename = "student_" + branchCode + "_" + rollNumber + ".txt";

        ifstream file(filename);

        if (!file)
        {
            throw FileNotFoundException("Student data not found!");
        }

        string name;
        string savedRollNumber;
        int branchValue;
        string practicalBatch;
        int semester;

        getline(file, name);
        getline(file, savedRollNumber);
        file >> branchValue;
        file.ignore();
        getline(file, practicalBatch);
        file >> semester;
        file.close();

        Branch branch = static_cast<Branch>(branchValue);

        return new Student(
            name,
            savedRollNumber,
            branch,
            practicalBatch,
            semester);
    }
    void loadTimeTable(TimeTable *timeTablePtr, string branchCode, string rollNumber)
    {
        string filename = "timetable_" + branchCode + "_" + rollNumber + ".txt";
        ifstream file(filename);
        if (!file)
        {
            throw FileNotFoundException("Timetable data not found!");
        }
        int dayValue;
        int typeValue;
        while (file >> dayValue)
        {
            file >> typeValue;
            file.ignore();
            string startTime;
            string subjectName;
            string roomNumber;
            string professorName;
            getline(file, startTime);
            getline(file, subjectName);
            getline(file, roomNumber);
            getline(file, professorName);
            int itemCount;
            file >> itemCount;
            file.ignore();
            vector<Item> items;
            for (int i = 0; i < itemCount; i++)
            {
                string itemName;
                string category;
                getline(file, itemName);
                getline(file, category);
                items.push_back(Item(itemName, category));
            }
            Day day = static_cast<Day>(dayValue);
            SessionType type = static_cast<SessionType>(typeValue);
            if (type == SessionType::LECTURE)
            {
                Session *session = new Lecture(day, startTime, subjectName, roomNumber, professorName, items);
                timeTablePtr->addSession(day, session);
            }
            else if (type == SessionType::PRACTICAL)
            {
                string practicalBatch;
                getline(file, practicalBatch);
                int alertLeadMinutes;
                file >> alertLeadMinutes;
                file.ignore();
                Session *session = new Practical(day, startTime, subjectName, roomNumber, professorName, items, alertLeadMinutes, practicalBatch);
                timeTablePtr->addSession(day, session);
            }
        }
        file.close();
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
int showLoginPage()
{
    int Choice;
    cout << endl;
    cout << "===== LOGIN PAGE =====" << endl;
    cout << "Enter your Choice: " << endl;
    cout << right << setw(2) << 1 << ". New User" << endl
         << right << setw(2) << 2 << ". Existing User" << endl
         << right << setw(2) << 3 << ". Exit" << endl;
    if (!readInt(Choice))
    {
        cout << "Invalid input! Please enter a number." << endl;
        return -1;
    }
    return Choice;
}
Day getDayFromDate(int day, int month, int year)
{
    tm date = {};
    date.tm_mday = day;
    date.tm_mon = month - 1;
    date.tm_year = year - 1900;
    mktime(&date);

    return static_cast<Day>(date.tm_wday == 0 ? 6 : date.tm_wday - 1);
}
bool isValidDate(int day, int month, int year)
{
    if (year < 2000 || month < 1 || month > 12 || day < 1)
        return false;

    int daysInMonth[] = {
        31, 28, 31, 30, 31, 30,
        31, 31, 30, 31, 30, 31};

    if ((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0))
        daysInMonth[1] = 29;

    if (day > daysInMonth[month - 1])
        return false;

    return true;
}

string getPracticalBatch(Branch branch)
{
    string branchCode = getBranchCode(branch);
    cout << endl;
    cout << "Select Your Practical Batch:" << endl;
    cout << "1. " << branchCode << "1" << endl;
    cout << "2. " << branchCode << "2" << endl;
    cout << "3. " << branchCode << "3" << endl;
    int choice;
    cout << "Enter Batch Choice: ";
    if (!readInt(choice))
    {
        throw InvalidSessionDataException("Invalid Practical Batch!");
    }
    if (choice >= 1 && choice <= 3)
    {
        return branchCode + to_string(choice);
    }
    throw InvalidSessionDataException("Invalid Practical Batch!");
}
void setupProfile(Student *&studentPtr, FileHandler &fileHandeler)
{
    cin.ignore();
    string name;
    cout << "Enter Your Name: ";
    getline(cin, name);
    if (name.empty())
    {
        cout << "Name cannot be empty!" << endl;
        return;
    }
    string rollnumber;
    cout << "Enter Your Roll Number: ";
    cin >> rollnumber;
    if (rollnumber.empty())
    {
        cout << "Invalid Roll Number!" << endl;
        return;
    }
    for (char c : name)
    {
        if (!isalpha(c) && c != ' ')
        {
            cout << "Name can contain only letters and spaces!" << endl;
            return;
        }
    }
    bool onlySpacesName = true;

    for (char c : name)
    {
        if (!isspace(c))
        {
            onlySpacesName = false;
            break;
        }
    }

    if (onlySpacesName)
    {
        cout << "Name cannot contain only spaces!" << endl;
        return;
    }
    for (char c : rollnumber)
    {
        if (!isdigit(c))
        {
            cout << "Roll Number must contain only numbers!" << endl;
            return;
        }
    }
    cout << "Enter Your Branch:" << endl;
    cout << "1. Computer Engineering" << endl;
    cout << "2. Computer Technology" << endl;
    cout << "3. Electronics And Telecommunication" << endl;
    cout << "4. Electrical Engineering" << endl;
    cout << "5. Mechanical Engineering" << endl;
    cout << "6. Instrumentation Engineering" << endl;
    cout << "7. Production Engineering" << endl;
    cout << "8. Civil Engineering" << endl;
    int choiceB;
    cout << "Enter Branch Choice: ";
    if (!readInt(choiceB))
    {
        cout << "Invalid input! Please enter a number." << endl;
        return;
    }
    Branch selectedBranch;
    if (choiceB == 1)
        selectedBranch = Branch::CO;
    else if (choiceB == 2)
        selectedBranch = Branch::CM;
    else if (choiceB == 3)
        selectedBranch = Branch::EJ;
    else if (choiceB == 4)
        selectedBranch = Branch::EE;
    else if (choiceB == 5)
        selectedBranch = Branch::ME;
    else if (choiceB == 6)
        selectedBranch = Branch::IS;
    else if (choiceB == 7)
        selectedBranch = Branch::PG;
    else if (choiceB == 8)
        selectedBranch = Branch::CE;
    else
    {
        cout << "Invalid Branch Choice!" << endl;
        return;
    }
    string branchCode = getBranchCode(selectedBranch);
    if (fileHandeler.studentExists(branchCode, rollnumber))
    {
        cout << "This Roll Number already exists in this branch!" << endl;
        return;
    }
    cout << endl;
    cout << "Select Your Practical Batch:" << endl;
    cout << "1. " << branchCode << "1" << endl;
    cout << "2. " << branchCode << "2" << endl;
    cout << "3. " << branchCode << "3" << endl;
    int batchChoice;
    cout << "Enter Batch Choice: ";
    if (!readInt(batchChoice))
    {
        cout << "Invalid input! Please enter a number." << endl;
        return;
    }
    string practicalBatch;
    if (batchChoice == 1)
        practicalBatch = branchCode + "1";
    else if (batchChoice == 2)
        practicalBatch = branchCode + "2";
    else if (batchChoice == 3)
        practicalBatch = branchCode + "3";
    else
    {
        cout << "Invalid Batch Choice!" << endl;
        return;
    }
    int semester;
    cout << "Enter Your Current Semester: 1/2/3/4/5/6" << endl;
    if (!readInt(semester))
    {
        cout << "Invalid input! Please enter a number." << endl;
        return;
    }
    if (semester < 1 || semester > 6)
    {
        cout << "Invalid Semester!" << endl;
        return;
    }
    studentPtr = new Student(
        name,
        rollnumber,
        selectedBranch,
        practicalBatch,
        semester);
    cout << endl;
    cout << "Profile Created Successfully!" << endl;
}
bool setupTimeTable(TimeTable *&timeTablePtr, Student *studentPtr)
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
    if (!readInt(choiceD))
    {
        cout << "Invalid input! Please enter a number." << endl;
        return false;
    }
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
        return false;
    }
    int typeChoice;
    cout << "Enter Choice for 1. Lecture / 2. Practical: " << endl;
    if (!readInt(typeChoice))
    {
        cout << "Invalid input! Please enter a number." << endl;
        return false;
    }
    if (typeChoice == 1)
    {
        string subjectName;
        cout << "Enter Subject Name of Lecture: " << endl;
        cin.ignore();
        getline(cin, subjectName);
        if (subjectName.empty())
        {
            cout << "Subject Name cannot be empty!" << endl;
            return false;
        }
        bool onlySpacesSubject = true;

        for (char c : subjectName)
        {
            if (!isspace(c))
            {
                onlySpacesSubject = false;
                break;
            }
        }

        if (onlySpacesSubject)
        {
            cout << "Subject Name cannot contain only spaces!" << endl;
            return false;
        }
        string startTime;
        cout << "Enter Start Time of Lecture For Subject: " << endl;
        getline(cin, startTime);
        if (startTime.empty())
        {
            cout << "Start Time cannot be empty!" << endl;
            return false;
        }
        bool onlySpacesTime = true;

        for (char c : startTime)
        {
            if (!isspace(c))
            {
                onlySpacesTime = false;
                break;
            }
        }

        if (onlySpacesTime)
        {
            cout << "Start Time cannot contain only spaces!" << endl;
            return false;
        }
        string roomNumber;
        cout << "Enter Room Number of Lecture: " << endl;
        getline(cin, roomNumber);
        if (roomNumber.empty())
        {
            cout << "Room Number cannot be empty!" << endl;
            return false;
        }
        bool onlySpacesRoom = true;

        for (char c : roomNumber)
        {
            if (!isspace(c))
            {
                onlySpacesRoom = false;
                break;
            }
        }

        if (onlySpacesRoom)
        {
            cout << "Room Number cannot contain only spaces!" << endl;
            return false;
        }
        string professorName;
        cout << "Enter Professor Name: " << endl;
        getline(cin, professorName);
        if (professorName.empty())
        {
            cout << "Professor Name cannot be empty!" << endl;
            return false;
        }
        bool onlySpacesProf = true;

        for (char c : professorName)
        {
            if (!isspace(c))
            {
                onlySpacesProf = false;
                break;
            }
        }

        if (onlySpacesProf)
        {
            cout << "Professor Name cannot contain only spaces!" << endl;
            return false;
        }
        vector<Item> defaultItems;
        cout << "How many Items you want to add?" << endl;
        int itemCount;
        cout << "Enter Number of Items: ";
        if (!readInt(itemCount))
        {
            cout << "Invalid input! Please enter a number." << endl;
            return false;
        }

        if (itemCount < 0)
        {
            cout << "Invalid Number of Items!" << endl;
            return false;
        }
        cin.ignore();
        for (int i = 0; i < itemCount; i++)
        {
            string itemName;
            cout << "Enter Item Name: " << endl;
            getline(cin, itemName);
            if (itemName.empty())
            {
                cout << "Item Name cannot be empty!" << endl;
                return false;
            }
            bool onlySpacesItemName = true;

            for (char c : itemName)
            {
                if (!isspace(c))
                {
                    onlySpacesItemName = false;
                    break;
                }
            }

            if (onlySpacesItemName)
            {
                cout << "Item Name cannot contain only spaces!" << endl;
                return false;
            }

            string itemCategory;
            cout << "Enter Item Category: " << endl;
            getline(cin, itemCategory);
            if (itemCategory.empty())
            {
                cout << "Item Category cannot be empty!" << endl;
                return false;
            }
            bool onlySpacesItemCategory = true;

            for (char c : itemCategory)
            {
                if (!isspace(c))
                {
                    onlySpacesItemCategory = false;
                    break;
                }
            }

            if (onlySpacesItemCategory)
            {
                cout << "Item Category cannot contain only spaces!" << endl;
                return false;
            }

            Item newItem(itemName, itemCategory);
            defaultItems.push_back(newItem);
        }
        Lecture *newLecture = new Lecture(sessionDay, startTime, subjectName, roomNumber, professorName, defaultItems);
        timeTablePtr->addSession(sessionDay, newLecture);
    }
    else if (typeChoice == 2)
    {
        string subjectName;
        string practicalBatch;
        string branchCode = getBranchCode(studentPtr->getBranch());
        cout << "Select Practical Batch:" << endl;
        cout << "1. " << branchCode << "1" << endl;
        cout << "2. " << branchCode << "2" << endl;
        cout << "3. " << branchCode << "3" << endl;
        int batchChoice;
        cout << "Enter Batch Choice: ";
        if (!readInt(batchChoice))
        {
            cout << "Invalid input! Please enter a number." << endl;
            return false;
        }
        if (batchChoice == 1)
            practicalBatch = branchCode + "1";
        else if (batchChoice == 2)
            practicalBatch = branchCode + "2";
        else if (batchChoice == 3)
            practicalBatch = branchCode + "3";
        else
        {
            cout << "Invalid Batch Choice!" << endl;
            return false;
        }
        cout << "Enter Subject Name of Practical: " << endl;
        cin.ignore();
        getline(cin, subjectName);
        if (subjectName.empty())
        {
            cout << "Subject Name cannot be empty!" << endl;
            return false;
        }
        bool onlySpacesPracticalSubject = true;

        for (char c : subjectName)
        {
            if (!isspace(c))
            {
                onlySpacesPracticalSubject = false;
                break;
            }
        }

        if (onlySpacesPracticalSubject)
        {
            cout << "Subject Name cannot contain only spaces!" << endl;
            return false;
        }
        string startTime;
        cout << "Enter Start Time of Practical: " << endl;
        getline(cin, startTime);
        if (startTime.empty())
        {
            cout << "Start Time cannot be empty!" << endl;
            return false;
        }
        bool onlySpacesPracticalStartTime = true;

        for (char c : startTime)
        {
            if (!isspace(c))
            {
                onlySpacesPracticalStartTime = false;
                break;
            }
        }

        if (onlySpacesPracticalStartTime)
        {
            cout << "Start Time cannot contain only spaces!" << endl;
            return false;
        }
        string roomNumber;
        cout << "Enter Room Number of Practical: " << endl;
        getline(cin, roomNumber);
        if (roomNumber.empty())
        {
            cout << "Room Number cannot be empty!" << endl;
            return false;
        }
        bool onlySpacesPracticalRoomNumber = true;

        for (char c : roomNumber)
        {
            if (!isspace(c))
            {
                onlySpacesPracticalRoomNumber = false;
                break;
            }
        }

        if (onlySpacesPracticalRoomNumber)
        {
            cout << "Room Number cannot contain only spaces!" << endl;
            return false;
        }
        string professorName;
        cout << "Enter Professor Name: " << endl;
        getline(cin, professorName);
        if (professorName.empty())
        {
            cout << "Professor Name cannot be empty!" << endl;
            return false;
        }
        bool onlySpacesPracticalProfName = true;

        for (char c : professorName)
        {
            if (!isspace(c))
            {
                onlySpacesPracticalProfName = false;
                break;
            }
        }

        if (onlySpacesPracticalProfName)
        {
            cout << "Professor Name cannot contain only spaces!" << endl;
            return false;
        }
        vector<Item> defaultItem;
        cout << "How many Items you want to add? " << endl;
        int itemCount;
        cout << "Enter Number of Items: ";
        if (!readInt(itemCount))
        {
            cout << "Invalid input! Please enter a number." << endl;
            return false;
        }

        if (itemCount < 0)
        {
            cout << "Invalid Number of Items!" << endl;
            return false;
        }

        cin.ignore();
        for (int i = 0; i < itemCount; i++)
        {
            string labItemName;
            cout << "Enter Lab Item: " << endl;
            getline(cin, labItemName);
            if (labItemName.empty())
            {
                cout << "Lab Item Name cannot be empty!" << endl;
                return false;
            }
            bool onlySpacesPracticalItemName = true;

            for (char c : labItemName)
            {
                if (!isspace(c))
                {
                    onlySpacesPracticalItemName = false;
                    break;
                }
            }

            if (onlySpacesPracticalItemName)
            {
                cout << "Lab Item Name cannot contain only spaces!" << endl;
                return false;
            }
            string labItemCategory;
            cout << "Enter Lab Item Category: " << endl;
            getline(cin, labItemCategory);
            if (labItemCategory.empty())
            {
                cout << "Lab Item Category cannot be empty!" << endl;
                return false;
            }
            bool onlySpacesPracticalItemCategory = true;

            for (char c : labItemCategory)
            {
                if (!isspace(c))
                {
                    onlySpacesPracticalItemCategory = false;
                    break;
                }
            }

            if (onlySpacesPracticalItemCategory)
            {
                cout << "Lab Item Category cannot contain only spaces!" << endl;
                return false;
            }
            Item newItem(labItemName, labItemCategory);
            defaultItem.push_back(newItem);
        }
        int alertLeadMinutes;
        cout << "Enter Alert Lead Minutes: " << endl;
        if (!readInt(alertLeadMinutes))
        {
            cout << "Invalid input! Please enter a number." << endl;
            return false;
        }

        if (alertLeadMinutes < 0)
        {
            cout << "Invalid Alert Lead Minutes!" << endl;
            return false;
        }
        Practical *newPractical = new Practical(sessionDay, startTime, subjectName, roomNumber, professorName, defaultItem, alertLeadMinutes, practicalBatch);
        timeTablePtr->addSession(sessionDay, newPractical);
    }
    else
    {
        cout << "Invalid Session Type!" << endl;
        return false;
    }
    return true;
}
bool editProfile(Student *studentPtr, TimeTable *timeTablePtr, FileHandler &fileHandeler)
{
    int choice;
    cout << "===== EDIT PROFILE =====" << endl;
    cout << "1. Edit Name" << endl;
    cout << "2. Edit Roll Number" << endl;
    cout << "3. Edit Branch" << endl;
    cout << "4. Edit Practical Batch" << endl;
    cout << "5. Edit Semester" << endl;
    cout << "6. Back" << endl;
    cout << "Enter your choice: ";
    if (!readInt(choice))
    {
        cout << "Invalid input! Please enter a number." << endl;
        return false;
    }
    switch (choice)
    {
    case 1:
    {
        cin.ignore();
        string newName;
        cout << "Enter New Name: ";
        getline(cin, newName);
        if (newName.empty())
        {
            cout << "Name cannot be empty!" << endl;
            break;
        }
        bool onlySpaces = true;
        bool validName = true;

        for (char c : newName)
        {
            if (!isalpha(c) && c != ' ')
            {
                validName = false;
                break;
            }
        }

        if (!validName)
        {
            cout << "Name can contain only letters and spaces!" << endl;
            break;
        }
        for (char c : newName)
        {
            if (!isspace(c))
            {
                onlySpaces = false;
                break;
            }
        }

        if (onlySpaces)
        {
            cout << "Name cannot contain only spaces!" << endl;
            break;
        }
        studentPtr->setName(newName);
        cout << "Name Updated Successfully!" << endl;
        return true;
    }
    case 2:
    {
        string oldRollNumber = studentPtr->getRollNumber();
        string oldBranchCode = getBranchCode(studentPtr->getBranch());

        string newRollNumber;
        cout << "Enter New Roll Number: ";
        cin >> newRollNumber;
        bool validRollNumber = true;

        for (char c : newRollNumber)
        {
            if (!isdigit(c))
            {
                validRollNumber = false;
                break;
            }
        }

        if (!validRollNumber)
        {
            cout << "Roll Number must contain only numbers!" << endl;
            break;
        }

        if (newRollNumber == oldRollNumber)
        {
            cout << "New Roll Number is same as old Roll Number!" << endl;
            break;
        }

        string branchCode = getBranchCode(studentPtr->getBranch());

        if (fileHandeler.studentExists(branchCode, newRollNumber))
        {
            cout << "This Roll Number already exists in this branch!" << endl;
            break;
        }
        studentPtr->setRollNumber(newRollNumber);

        fileHandeler.saveStudent(studentPtr);
        fileHandeler.saveTimeTable(timeTablePtr, studentPtr);

        fileHandeler.deleteStudentFiles(oldBranchCode, oldRollNumber);

        cout << "Roll Number Updated Successfully!" << endl;
        return true;
    }
    case 3:
    {
        string oldBranchCode = getBranchCode(studentPtr->getBranch());

        int branchChoice;

        cout << "Enter New Branch:" << endl;
        cout << "1. Computer Engineering" << endl;
        cout << "2. Computer Technology" << endl;
        cout << "3. Electronics And Telecommunication" << endl;
        cout << "4. Electrical Engineering" << endl;
        cout << "5. Mechanical Engineering" << endl;
        cout << "6. Instrumentation Engineering" << endl;
        cout << "7. Production Engineering" << endl;
        cout << "8. Civil Engineering" << endl;

        if (!readInt(branchChoice))
        {
            cout << "Invalid input! Please enter a number." << endl;
            break;
        }

        Branch newBranch;

        if (branchChoice == 1)
            newBranch = Branch::CO;
        else if (branchChoice == 2)
            newBranch = Branch::CM;
        else if (branchChoice == 3)
            newBranch = Branch::EJ;
        else if (branchChoice == 4)
            newBranch = Branch::EE;
        else if (branchChoice == 5)
            newBranch = Branch::ME;
        else if (branchChoice == 6)
            newBranch = Branch::IS;
        else if (branchChoice == 7)
            newBranch = Branch::PG;
        else if (branchChoice == 8)
            newBranch = Branch::CE;
        else
        {
            cout << "Invalid Branch Choice!" << endl;
            break;
        }

        if (newBranch == studentPtr->getBranch())
        {
            cout << "New Branch is same as old Branch!" << endl;
            break;
        }

        string newBranchCode = getBranchCode(newBranch);
        if (fileHandeler.studentExists(newBranchCode, studentPtr->getRollNumber()))
        {
            cout << "This Roll Number already exists in the selected branch!" << endl;
            break;
        }

        string newPracticalBatch;

        try
        {
            newPracticalBatch = getPracticalBatch(newBranch);
        }
        catch (const InvalidSessionDataException &e)
        {
            cout << e.what() << endl;
            break;
        }

        studentPtr->setBranch(newBranch);
        studentPtr->setPracticalBatch(newPracticalBatch);
        timeTablePtr->updatePracticalBatch(studentPtr->getPracticalBatch());

        fileHandeler.saveStudent(studentPtr);
        fileHandeler.saveTimeTable(timeTablePtr, studentPtr);

        fileHandeler.deleteStudentFiles(
            oldBranchCode,
            studentPtr->getRollNumber());

        cout << "Branch Updated Successfully!" << endl;

        return true;
    }
    case 4:
    {
        string newBatch;

        try
        {
            newBatch = getPracticalBatch(studentPtr->getBranch());
        }
        catch (const InvalidSessionDataException &e)
        {
            cout << e.what() << endl;
            break;
        }

        studentPtr->setPracticalBatch(newBatch);
        timeTablePtr->updatePracticalBatch(newBatch);

        fileHandeler.saveStudent(studentPtr);
        fileHandeler.saveTimeTable(timeTablePtr, studentPtr);

        cout << "Practical Batch Updated Successfully!" << endl;
        return true;
    }
    case 5:
    {
        int newSemester;
        cout << "Enter New Semester (1-6): ";
        if (!readInt(newSemester))
        {
            cout << "Invalid input! Please enter a number." << endl;
            break;
        }

        if (newSemester < 1 || newSemester > 6)
        {
            cout << "Invalid Semester!" << endl;
            break;
        }

        studentPtr->setSemester(newSemester);
        cout << "Semester Updated Successfully!" << endl;
        return true;
    }
    case 6:
        return false;
    default:
        cout << "Invalid Choice!" << endl;
        return false;
    }
    // Any validation-failure "break;" above lands here.
    // Without this, the function would fall off the end without
    // returning a value, which is undefined behavior.
    return false;
}
void editTimetable(TimeTable *timeTablePtr, FileHandler &fileHandler, Student *studentPtr)
{
    int choice;
    cout << endl;
    cout << "===== EDIT TIMETABLE =====" << endl;
    cout << right << setw(2) << 1 << ". Add Session" << endl;
    cout << right << setw(2) << 2 << ". Delete Session" << endl;
    cout << right << setw(2) << 3 << ". View Timetable" << endl;
    cout << right << setw(2) << 4 << ". Back" << endl;
    cout << "Enter your choice: ";
    if (!readInt(choice))
    {
        cout << "Invalid input! Please enter a number." << endl;
        return;
    }
    switch (choice)
    {
    case 1:
    {
        bool result = setupTimeTable(timeTablePtr, studentPtr);
        if (result)
        {
            fileHandler.saveTimeTable(timeTablePtr, studentPtr);
            cout << "Session Added Successfully!" << endl;
        }
        break;
    }
    case 2: // Delete Session
    {
        int dayChoice;
        cout << "Select Day:" << endl;
        cout << "1. Monday" << endl;
        cout << "2. Tuesday" << endl;
        cout << "3. Wednesday" << endl;
        cout << "4. Thursday" << endl;
        cout << "5. Friday" << endl;
        cout << "6. Saturday" << endl;
        cout << "7. Sunday" << endl;
        cout << "Enter Day Choice: ";
        if (!readInt(dayChoice))
        {
            cout << "Invalid input! Please enter a number." << endl;
            break;
        }
        Day selectedDay;
        if (dayChoice == 1)
            selectedDay = Day::MONDAY;
        else if (dayChoice == 2)
            selectedDay = Day::TUESDAY;
        else if (dayChoice == 3)
            selectedDay = Day::WEDNESDAY;
        else if (dayChoice == 4)
            selectedDay = Day::THURSDAY;
        else if (dayChoice == 5)
            selectedDay = Day::FRIDAY;
        else if (dayChoice == 6)
            selectedDay = Day::SATURDAY;
        else if (dayChoice == 7)
            selectedDay = Day::SUNDAY;
        else
        {
            cout << "Invalid Day Choice!" << endl;
            break;
        }
        vector<Session *> sessions =
            timeTablePtr->getSessionForDay(selectedDay);
        if (sessions.empty())
        {
            cout << "No sessions found for this day." << endl;
            break;
        }
        cout << endl;
        cout << "Sessions for selected day:" << endl;
        cout << left
             << setw(5) << "No."
             << setw(25) << "Subject"
             << setw(12) << "Time"
             << setw(10) << "Room"
             << endl;
        cout << string(52, '-') << endl;
        for (size_t i = 0; i < sessions.size(); i++)
        {
            cout << left
                 << setw(5) << (to_string(i + 1) + ".")
                 << setw(25) << sessions[i]->getSubjectName()
                 << setw(12) << sessions[i]->getStartTime()
                 << setw(10) << sessions[i]->getRoomNumber()
                 << endl;
        }
        int sessionChoice;
        cout << "Enter Session Number to Delete: ";
        if (!readInt(sessionChoice))
        {
            cout << "Invalid input! Please enter a number." << endl;
            break;
        }
        if (sessionChoice < 1 || static_cast<size_t>(sessionChoice) > sessions.size())
        {
            cout << "Invalid Session Choice!" << endl;
            break;
        }
        timeTablePtr->deleteSession(
            selectedDay, sessionChoice - 1);
        fileHandler.saveTimeTable(timeTablePtr, studentPtr);
        cout << "Session Deleted Successfully!" << endl;
        break;
    }
    case 3:
    {
        if (timeTablePtr == nullptr)
        {
            cout << "Please set up your Timetable first." << endl;
        }
        else
        {
            timeTablePtr->display();
        }
        break;
    }
    case 4:
        break;
    default:
        cout << "Invalid Choice!" << endl;
    }
}
void showBagForDay(TimeTable *timeTablePtr, Student *studentPtr, Bag *&bagPtr)
{
    if (studentPtr == nullptr || timeTablePtr == nullptr)
    {
        cout << "Please set up your Profile and Timetable first." << endl;
        return;
    }
    int day, month, year;
    cout << endl;
    cout << "===== SHOW BAG =====" << endl;
    cout << "Enter Date (DD MM YYYY): ";
    if (!readInt(day) || !readInt(month) || !readInt(year))
    {
        cout << "Invalid input! Please enter numbers only." << endl;
        return;
    }
    if (!isValidDate(day, month, year))
    {
        cout << "Invalid Date!" << endl;
        return;
    }
    Day sessionDay = getDayFromDate(day, month, year);
    string dayName;
    switch (sessionDay)
    {
    case Day::MONDAY:
        dayName = "Monday";
        break;
    case Day::TUESDAY:
        dayName = "Tuesday";
        break;
    case Day::WEDNESDAY:
        dayName = "Wednesday";
        break;
    case Day::THURSDAY:
        dayName = "Thursday";
        break;
    case Day::FRIDAY:
        dayName = "Friday";
        break;
    case Day::SATURDAY:
        dayName = "Saturday";
        break;
    case Day::SUNDAY:
        dayName = "Sunday";
        break;
    }
    cout << "Day: " << dayName << endl;
    cout << endl;
    BagManager manager(timeTablePtr, studentPtr);
    delete bagPtr;
    bagPtr = new Bag(manager.generatebagForDay(sessionDay));
    cout << "===== REQUIRED BAG ITEMS =====" << endl;
    bagPtr->display();
    cout << endl;
    vector<string> alerts = manager.getAlertsForDay(sessionDay);
    cout << "===== SESSION ALERTS =====" << endl;
    int alertNo = 1;
    for (string a : alerts)
    {
        cout << right << setw(2) << alertNo++ << ". " << a << endl;
    }
}
void markItemPacked(Bag *bagPtr)
{
    if (bagPtr == nullptr)
    {
        cout << "Please generate today's bag first." << endl;
        return;
    }
    string itemName;
    cout << "Enter Item Name to Mark as Packed: ";
    cin.ignore();
    getline(cin, itemName);
    int result = bagPtr->marksItemPacked(itemName);
    if (result == 1)
        cout << "Item marked as Packed!" << endl;
    else if (result == 2)
        cout << "Item is already Packed!" << endl;
    else
        cout << "Item not Found in Today's bag!" << endl;
}
void addItemToBag(Bag *bagPtr)
{
    if (bagPtr == nullptr)
    {
        cout << "Please generate today's bag first." << endl;
        return;
    }
    string itemName;
    string category;
    cout << "Enter Item Name: ";
    cin.ignore();
    getline(cin, itemName);
    cout << "Enter Item Category: ";
    getline(cin, category);
    Item newItem(itemName, category);
    bool result = bagPtr->addItem(newItem);
    if (result)
        cout << "Item Added To Bag Successfully!" << endl;
    else
        cout << "Item Already Exists in Today's Bag!" << endl;
}
void showProfile(Student *studentPtr)
{
    if (studentPtr == nullptr)
    {
        cout << "Please set up your Profile first." << endl;
        return;
    }
    cout << endl;
    cout << "===== STUDENT PROFILE =====" << endl;
    cout << left << setw(16) << "Name" << " : " << studentPtr->getname() << endl;
    cout << left << setw(16) << "Roll Number" << " : " << studentPtr->getRollNumber() << endl;
    cout << left << setw(16) << "Branch" << " : " << getBranchName(studentPtr->getBranch()) << endl;
    cout << left << setw(16) << "Practical Batch" << " : " << studentPtr->getPracticalBatch() << endl;
    cout << left << setw(16) << "Semester" << " : " << studentPtr->getSemester() << endl;
}
int main()
{
    FileHandler fileHandeler;
    while (true)
    {
        Student *studentPtr = nullptr;
        TimeTable *timeTablePtr = nullptr;
        Bag *bagPtr = nullptr;
        int loginChoice = showLoginPage();
        switch (loginChoice) // LOGIN PAGE
        {
        case 1:
        {
            cout << "New User" << endl;
            setupProfile(studentPtr, fileHandeler);
            if (studentPtr == nullptr)
            {
                cout << "Profile setup failed." << endl;
                continue;
            }
            bool timetableResult = setupTimeTable(timeTablePtr, studentPtr);
            if (!timetableResult)
            {
                cout << "Timetable setup failed." << endl;
                delete studentPtr;
                studentPtr = nullptr;
                delete timeTablePtr;
                timeTablePtr = nullptr;
                continue;
            }
            fileHandeler.saveStudent(studentPtr);
            fileHandeler.saveTimeTable(timeTablePtr, studentPtr);
            cout << "New User Setup Completed Successfully!" << endl;
            break;
        }
        case 2:
        {
            cout << "Existing User" << endl;
            int branchChoice;
            cout << "Select Your Branch:" << endl
                 << "1. Computer Engineering" << endl
                 << "2. Computer Technology" << endl
                 << "3. Electronics And Telecommunication" << endl
                 << "4. Electrical Engineering" << endl
                 << "5. Mechanical Engineering" << endl
                 << "6. Instrumentation Engineering" << endl
                 << "7. Production Engineering" << endl
                 << "8. Civil Engineering" << endl;
            cout << "Enter Branch Choice: ";
            if (!readInt(branchChoice))
            {
                cout << "Invalid input! Please enter a number." << endl;
                continue;
            }
            Branch selectedBranch;
            if (branchChoice == 1)
                selectedBranch = Branch::CO;
            else if (branchChoice == 2)
                selectedBranch = Branch::CM;
            else if (branchChoice == 3)
                selectedBranch = Branch::EJ;
            else if (branchChoice == 4)
                selectedBranch = Branch::EE;
            else if (branchChoice == 5)
                selectedBranch = Branch::ME;
            else if (branchChoice == 6)
                selectedBranch = Branch::IS;
            else if (branchChoice == 7)
                selectedBranch = Branch::PG;
            else if (branchChoice == 8)
                selectedBranch = Branch::CE;
            else
            {
                cout << "Invalid Branch Choice!" << endl;
                continue;
            }
            string rollNumber;
            cout << "Enter Roll Number: ";
            cin >> rollNumber;
            string branchCode = getBranchCode(selectedBranch);
            try
            {
                studentPtr = fileHandeler.loadStudent(branchCode, rollNumber);
                timeTablePtr = new TimeTable();
                fileHandeler.loadTimeTable(
                    timeTablePtr,
                    branchCode,
                    rollNumber);
                cout << "Login Successful!" << endl;
                cout << "Welcome, " << studentPtr->getname() << "!" << endl;
            }
            catch (const FileNotFoundException &e)
            {
                cout << e.what() << endl;
                delete studentPtr;
                studentPtr = nullptr;
                delete timeTablePtr;
                timeTablePtr = nullptr;
                continue;
            }
            break;
        }
        case 3:
            cout << "Exited!!" << endl;
            return 0;
        default:
            cout << "Invalid choice" << endl;
            continue;
        }
        while (true) // MAIN MENU
        {
            cout << endl;
            cout << "===== SMART BAG MENU =====" << endl;
            cout << right << setw(2) << 1 << ". Edit Profile" << endl
                 << right << setw(2) << 2 << ". Edit Timetable" << endl
                 << right << setw(2) << 3 << ". Show Today's Bag" << endl
                 << right << setw(2) << 4 << ". Mark Item Packed" << endl
                 << right << setw(2) << 5 << ". Add Item To Bag" << endl
                 << right << setw(2) << 6 << ". Show Profile" << endl
                 << right << setw(2) << 7 << ". Show Timetable" << endl
                 << right << setw(2) << 8 << ". Save Data" << endl
                 << right << setw(2) << 9 << ". Logout" << endl
                 << right << setw(2) << 10 << ". EXIT" << endl;
            cout << "Enter Your Choice: ";
            int choice;
            if (!readInt(choice))
            {
                cout << "Invalid input! Please enter a number." << endl;
                continue;
            }
            switch (choice)
            {
            case 1:
            {
                bool result = editProfile(studentPtr, timeTablePtr, fileHandeler);
                if (result)
                {
                    fileHandeler.saveStudent(studentPtr);
                    fileHandeler.saveTimeTable(timeTablePtr, studentPtr);
                    cout << "Profile Saved Successfully!" << endl;
                }
                break;
            }
            case 2:
            {
                editTimetable(timeTablePtr, fileHandeler, studentPtr);
                break;
            }
            case 3:
            {
                showBagForDay(timeTablePtr, studentPtr, bagPtr);
                break;
            }
            case 4:
            {
                markItemPacked(bagPtr);
                break;
            }
            case 5:
            {
                addItemToBag(bagPtr);
                break;
            }
            case 6:
            {
                showProfile(studentPtr);
                break;
            }
            case 7:
            {
                if (timeTablePtr == nullptr)
                {
                    cout << "Please set up your Timetable first." << endl;
                }
                else
                {
                    cout << endl;
                    cout << "===== YOUR TIMETABLE =====" << endl;
                    timeTablePtr->display();
                }
                break;
            }
            case 8:
            {
                if (studentPtr == nullptr || timeTablePtr == nullptr)
                {
                    cout << "Please set up your Profile and Timetable first." << endl;
                }
                else
                {
                    fileHandeler.saveStudent(studentPtr);
                    fileHandeler.saveTimeTable(timeTablePtr, studentPtr);
                    cout << "All Data Saved Successfully!" << endl;
                }
                break;
            }
            case 9:
            {
                cout << "Logging Out..." << endl;
                delete bagPtr;
                bagPtr = nullptr;
                delete timeTablePtr;
                timeTablePtr = nullptr;
                delete studentPtr;
                studentPtr = nullptr;
                cout << "Logged Out Successfully!" << endl;
                break; // Go back to Login Page
            }
            case 10:
            {
                cout << "Exiting Smart Bag..." << endl;
                delete bagPtr;
                bagPtr = nullptr;
                delete timeTablePtr;
                timeTablePtr = nullptr;
                delete studentPtr;
                studentPtr = nullptr;
                cout << "Thank You for using Smart Bag!" << endl;
                return 0;
            }
            default:
            {
                cout << "Invalid Choice!" << endl;
                break;
            }
            }
            if (choice == 9)
            {
                break;
            } // Exit main menu after Logout
        }
    }
    return 0;
}