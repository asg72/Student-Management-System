#include <iostream>
#include <vector>
using namespace std;

class Student
{
protected:
    vector<string> names;
    vector<int> ages;
    vector<int> ids;

public:
    void stuInfo() // Method which ask user info
    {
        int id, age;
        string name;

        cout << "\nEnter details for student:" << endl;

        cout << "Enter Student Id:\n";
        cin >> id;
        cin.ignore();

        cout << "Enter Student name:\n";
        cin >> name;
        cin.ignore();

        cout << "Enter Student age:\n";
        cin >> age;
        cin.ignore();

        ids.push_back(id);
        names.push_back(name);
        ages.push_back(age);
    }
};

class Grades : virtual public Student
{
protected:
    vector<int> math;
    vector<int> physic;
    vector<int> chemistry;

public:
    void setGrade() // This method set respective subjects grades
    {
        int m, p, c;
        do
        {
            cout << "Enter Math grades (0-100):\n";
            cin >> m;
            cin.ignore();
        } while (m < 0 || m > 100);

        do
        {
            cout << "Enter Physic grades (0-100):\n";
            cin >> p;
            cin.ignore();
        } while (p < 0 || p > 100);

        do
        {
            cout << "Enter Chemistry grades (0-100):\n";
            cin >> c;
            cin.ignore();
        } while (c < 0 || c > 100);

        math.push_back(m);
        physic.push_back(p);
        chemistry.push_back(c);
    }
};

class Display : virtual public Student, public Grades
{
public:
    void Info()
    {
        stuInfo();
        setGrade();
    }
    void getInfo()
    {
        if (ids.empty())
        {
            cout << "No student records found. Please add a student first.\n";
            return;
        }

        cout << "--------------------------\n";
        cout << endl;
        cout << "Students list:\n";
        for (size_t i = 0; i < ids.size(); i++)
        {
            cout << "Name: " << names[i] << ", Id: " << ids[i] << ", Age: " << ages[i] << endl;
            cout << "Grades: ";
            cout << "Math: " << math[i] << ", Physic: " << physic[i] << ", Chemistry: " << chemistry[i] << endl;
            cout << endl;
        }
        cout << "--------------------------\n";
    }

    void searchById(int id)
    {
        bool found = false;
        for (size_t i = 0; i < ids.size(); i++)
        {
            if (ids[i] == id)
            {
                cout << "Student found:\n";
                cout << "Name: " << names[i] << ", Age: " << ages[i] << "\n";
                cout << "Grades - Math: " << math[i] << ", Physic: " << physic[i] << ", Chemistry: " << chemistry[i] << "\n";
                found = true;
                break;
            }
        }
        if (!found)
        {
            cout << "Student with ID " << id << " not found.\n";
        }
    }

    void deleteStudentInfo(int id)
    {
        // Search Student by Id
        for (size_t i = 0; i < ids.size(); i++)
        {
            if (ids[i] == id)
            {
                // Display student details
                cout << "Student found:\n";
                cout << "Name: " << names[i] << ", Age: " << ages[i] << "\n";
                cout << "Grades - Math: " << math[i] << ", Physic: " << physic[i] << ", Chemistry: " << chemistry[i] << "\n";

                // Confirm deletion
                char choice;
                cout << "Are you sure, you want to delete the Student ID: " << id << "? Enter 'Y' to confirm or 'N' to cancel.\n";
                cin >> choice;

                if (choice == 'y' || choice == 'Y')
                {
                    // Remove student from all vectors
                    ids.erase(ids.begin() + i);
                    names.erase(names.begin() + i);
                    ages.erase(ages.begin() + i);
                    math.erase(math.begin() + i);
                    physic.erase(physic.begin() + i);
                    chemistry.erase(chemistry.begin() + i);

                    cout << "Student with ID " << id << " has been deleted.\n";
                }
                else
                {
                    cout << "Deletion canceled.\n";
                }
                return; // Exit function after handling the student
            }
        }
        // If student not found, display an error message
        cout << "Student with ID " << id << " not found.\n";
    }
};

int menu()
{
    int choice;
    cout << "\nMenu:\n";
    cout << "1. Add Student Info" << endl;
    cout << "2. Display all Student Info" << endl;
    cout << "3. Get info by student Id" << endl;
    cout << "4. Delete Student Info" << endl;
    cout << "5. Exit\n";
    cout << "Enter your choice: ";
    cin >> choice;
    if (cin.fail() || choice < 1 || choice > 5)
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid choice. Please select a valid option.\n";
        return -1; // Return an invalid flag to handle it outside
    }

    return choice;
}

int main()
{
    Display asg;
    int option;
    do
    {
        option = menu();

        if (option == -1)
        {
            continue;
        }

        switch (option)
        {
        case 1:
            asg.Info();
            cout << "Successfully added!\n";
            break;
        case 2:
            cout << "\nDisplaying all students information:\n";
            asg.getInfo();
            break;
        case 3:
            int id;
            cout << "\nEnter Student ID to search:\n";
            cin >> id;
            asg.searchById(id);
            break;
        case 4:
            cout << "\nEnter Student ID to delete info:\n";
            cin >> id;
            asg.deleteStudentInfo(id);
            break;
        case 5:
            cout << "Exiting the program.\n";
            break;
        default:
            cout << "Invalid choice, please try again." << endl;
            break;
        }
    } while (option != 5);

    return 0;
}