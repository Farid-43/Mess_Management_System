#include <bits/stdc++.h>
using namespace std;

class student;
class studentRecord;
class house;
class houseRecord;

class student
{
private:
    int id;
    string name;
    int houseID;

public:
    student(){};
    student(string name, int id, int houseID)
    {
        this->name = name;
        this->id = id;
        this->houseID = houseID;
    }
    int getid()
    {
        return id;
    }
    int gethouseID()
    {
        return houseID;
    }
    friend class studentRecord;
};

class studentRecord
{
private:
    student students[100];
    int count = 0;

public:
    void addstudent(student s, int houseid)
    {
        if (count < 100)
        {
            students[count++] = s;
        }
    }
    bool exists(int id, int houseId)
    {
        for (int i = 0; i < count; i++)
        {
            if (students[i].getid() == id && students[i].gethouseID() == houseId)
            {
                return true;
            }
        }
        return false;
    }

    void leave(int id, int houseid)
    {
        for (int i = 0; i < count; i++)
        {
            if (students[i].getid() == id && students[i].gethouseID() == houseid)
            {
                for (int j = i + 1; j < count; j++)
                {
                    students[j - 1] = students[j];
                }
                count--;
                break;
            }
        }
    }
};
class house
{
    int id;
    bool water;
    int floor;
    int cost;
    bool vacant;

public:
    house(){};
    house(int id, bool water, int floor, int cost, bool vacant)
    {
        this->id = id;
        this->water = water;
        this->floor = floor;
        this->cost = cost;
        this->vacant = vacant;
    }
    int getID()
    {
        return id;
    }
    bool getvacant()
    {
        return vacant;
    }
    bool setvacant(bool ok)
    {
        vacant = ok;
        return vacant;
    }
    void show()
    {
        cout << id << "\t" << (water ? "GOOD" : "SALTY") << "\t" << floor << "\t" << cost << "\t" << (vacant ? "YES" : "NO") << endl;
    }

    friend void search(houseRecord &);
};
class houseRecord
{
    house houses[100];
    int count = 0;

public:
    void addHouse(int id, bool water, int floor, int cost, bool vacant)
    {
        if (count < 100)
        {
            house h(id, water, floor, cost, vacant);
            houses[count++] = h;
        }
        else
        {
            cout << "House Record is full.Cannot add more house" << endl;
        }
    }
    houseRecord()
    {
        addHouse(1, 1, 3, 4500, 1);
        addHouse(2, 1, 2, 4000, 1);
        addHouse(3, 0, 1, 3700, 1);
        addHouse(4, 1, 0, 5000, 1);
        addHouse(5, 0, 0, 4000, 1);
        addHouse(6, 1, 0, 5000, 1);
        addHouse(7, 0, 1, 5500, 1);
        addHouse(8, 1, 1, 5000, 1);
        addHouse(9, 0, 2, 4600, 1);
        addHouse(10, 1, 1, 3500, 1);
    }
    void showAll()
    {
        cout << "HouseId\tWater\tFloor\tCost\tVacancy\n";
        for (int i = 0; i < count; i++)
        {
            houses[i].show();
        }
    }
    void RemoveHouse()
    {
        int id;
        cout << " -----------------------------" << endl;
        cout << "|         Remove a House      |" << endl;
        cout << " -----------------------------" << endl;
        cout << "Enter house id: ";
        cin >> id;
        for (int i = 0; i < count; i++)
        {
            if (houses[i].getID() == id)
            {
                for (int j = i + 1; j < count; j++)
                {
                    houses[j - 1] = houses[j];
                }

                count--;
                cout << "\nHouse successfully removed!\n\n";
                return;
            }
        }
        cout << "\nThis house doesn't exist in the record\n\n";
    }
    void setvacant(int id, bool ok)
    {
        for (int i = 0; i < count; i++)
        {
            if (houses[i].getID() == id)
            {
                houses[i].setvacant(ok);
                return;
            }
        }
    }
    bool isVacant(int id)
    {
        for (int i = 0; i < count; i++)
        {
            if (houses[i].getID() == id && houses[i].getvacant())
            {
                return true;
            }
        }
        return false;
    }
    friend void search(houseRecord &);
};
void rent(studentRecord &s, houseRecord &h)
{
    int id, houseId;
    string name;
    cout << " -----------------------------" << endl;
    cout << "|         Rent a house        |" << endl;
    cout << " -----------------------------" << endl;
    cout << "Enter student name: ";
    cin.ignore();
    cin >> name;
    cout << "Enter student id: ";
    cin >> id;
    cout << "Enter house id: ";
    cin >> houseId;
    if (h.isVacant(houseId))
    {
        h.setvacant(houseId, false);
        student x(name, id, houseId);
        s.addstudent(x, houseId);
        cout << "\nHouse rented successfully!\n\n";
    }
    else
    {
        cout << "\nThe house is not vacant\n\n";
    }
}
void leave(studentRecord &s, houseRecord &h)
{
    int id, houseId;
    cout << " -----------------------------" << endl;
    cout << "|          Leave house        |" << endl;
    cout << " -----------------------------" << endl;
    cout << "Enter student id: ";
    cin >> id;
    cout << "Enter house id: ";
    cin >> houseId;
    if (s.exists(id, houseId))
    {
        h.setvacant(houseId, true);
        s.leave(id, houseId);
        cout << "Thank you\n";
    }
    else
    {
        cout << "The house is not rented\n";
    }
    cout << "\n";
}

void search(houseRecord &h)
{
    int floor, maxCost;
    bool water;
    cout << " -----------------------------" << endl;
    cout << "|         Search house        |" << endl;
    cout << " -----------------------------" << endl;
    cout << "Water condition: [1(Good), 0(Salty)] ";
    cin >> water;
    cout << "Floor: [0(Ground Floor), 1(DownRoof), Others] ";
    cin >> floor;
    cout << "Maximum cost: ";
    cin >> maxCost;
    bool found = false;
    cout << "\n---------------------------------------\n";
    cout << "HouseId\tWater\tFloor\tCost\tVacancy\n";
    for (int i = 0; i < h.count; i++)
    {
        if (h.houses[i].water == water && h.houses[i].floor == floor && h.houses[i].cost <= maxCost && h.houses[i].getvacant())
        {
            found = true;
            h.houses[i].show();
        }
    }
    if (!found)
    {
        cout << "\nNo house found!" << endl;
        cout << "---------------------------------------" << endl
             << endl;
    }
}

int main()
{
    houseRecord h;
    studentRecord s;
    while (1)
    {
        cout << "********************************" << endl;
        cout << "*    Student Mess Management   *" << endl;
        cout << "********************************" << endl;
        cout << "| 1.Show All house\n| 2.Register new house\n| 3.Search House\n| 4.Rent house\n| 5.Leave house\n| 6.Remove House\n| 0.Exit\n\nYour choice: ";
        int i;
        cin >> i;
        if (i == 1)
        {
            h.showAll();
        }
        else if (i == 2)
        {
            int id, floor, cost;
            bool vacant, water;
            cout << "Enter house id: ";
            cin >> id;
            cout << "Enter water condition[1(Good), 0(Salty)]: ";
            cin >> water;
            cout << "Enter floor[0(Ground), 1(DownRoof), 2(Others)]: ";
            cin >> floor;
            cout << "Enter cost: ";
            cin >> cost;
            cout << "Enter vacant status[1(Yes), 0(No)]: ";
            cin >> vacant;
            h.addHouse(id, water, floor, cost, vacant);
        }
        else if (i == 3)
        {
            search(h);
        }
        else if (i == 4)
        {
            rent(s, h);
        }
        else if (i == 5)
        {
            leave(s, h);
        }
        else if (i == 6)
        {
            h.RemoveHouse();
        }
        else if (i == 0)
        {
            cout << "Thanks for using our service" << endl;
            break;
        }
        else
        {
            cout << "Error! Invalid Input\n";
        }
    }
    return 0;
}
