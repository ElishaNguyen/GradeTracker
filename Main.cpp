/*
    Nguyen, Elisha
    Guenneugues, Juliette
    Javadi, Amirali

    Project: Grade Report
    CS A250
    Fall 2023
*/

#include "StudentList.h"
#include "InputHandler.h"
#include "OutputHandler.h"

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

const string FILENAME = "student_data.txt";

void displayMenu();

void processChoice(StudentList& list, double tuitionRate);

int main()
{
    StudentList tester;
    double testDouble = 0.0;
    readStudentData(FILENAME, tester, testDouble);

    processChoice(tester, testDouble);
    system("Pause");
    cout << endl;

    return 0;
}

void displayMenu()
{
    cout << "*** MAIN MENU ***\n\n"
        << "Select one of the following:\n\n"
        << "    1: Print all students\n"
        << "    2: Print student information\n"
        << "    3: Search student by last name\n"
        << "    4: Print students by course\n"
        << "    5: Print students on hold\n"
        << "    6: Print students to file\n"
        << "    7: Change the grade of a student's class\n"
        << "    8: To exit\n"
        << endl;
}

void processChoice(StudentList& list, double tuitionRate)
{
    int numID = 0;
    char newGrade = '\0';
    string firstName;
    string lastName;
    string coursePrefix;
    int courseNumber = 0;
    Node* iter = nullptr;
    bool finish = false;

    while (!finish)
    {
        displayMenu();

        cout << "Enter your choice: ";
        int menuNum = 0;
        cin >> menuNum;
        cout << endl;

        switch (menuNum)
        {
        case 1:
            list.printAllStudents(tuitionRate);
            break;
        case 2:
            cout << "Please enter student's ID: ";
            cin >> numID;
            cout << endl;
            list.printStudentByID(numID, tuitionRate);
            break;
        case 3:
            cout << "Please enter the student's last name: ";
            cin >> lastName;
            cout << endl;
            list.printStudentByName(lastName);
            cout << endl;
            break;
        case 4:
            cout << "Please enter the course prefix: ";
            cin >> coursePrefix;
            cout << "Please enter the course number: ";
            cin >> courseNumber;
            cout << endl;
            list.printStudentsByCourse(
                coursePrefix, courseNumber);
            cout << endl;
            break;
        case 5:
            list.printStudentsOnHold(tuitionRate);
            cout << endl;
            break;
        case 6:
            printAllStudentsToFile(list, tuitionRate);
            break;
        case 7:
            cout << "Please enter student's ID: ";
            cin >> numID;
            cout << endl;

            if (list.findStudentByID(numID, iter))
            {
                cout << "Please enter student's first name: ";
                cin >> firstName;
                cout << endl;
                cout << "Please enter student's last name: ";
                cin >> lastName;
                cout << endl;

                if (iter->getStudent().getFirstName() == firstName &&
                    iter->getStudent().getLastName() == lastName)
                {
                    cout << "Please enter the course prefix: ";
                    cin >> coursePrefix;
                    cout << "Please enter the course number: ";
                    cin >> courseNumber;
                    cout << endl;

                    if (iter->getStudent().isCourseCompleted(
                        coursePrefix, courseNumber))
                    {
                        cout << "Enter the new grade for the course: ";
                        cin >> newGrade;
                        cout << endl;

                        if (newGrade != 'A' && newGrade != 'B' &&
                            newGrade != 'C' && newGrade != 'D' &&
                            newGrade != 'F')
                        {
                            cout << "Cannot change grade to " << newGrade
                                << ".\n\n";
                        }
                        else
                        {
                            iter->getStudent().changeGrade(coursePrefix,
                                courseNumber, newGrade);
                            cout << "Grade was changed!\n\n";
                        }
                    }
                    else
                    {
                        cout << "There is no record of this student "
                            << "having completed this course.\n\n";
                    }
                }
                else
                {
                    cout << "Name: \'" << firstName << " "
                        << lastName << "\' does not match "
                        << "the student ID \n\n";
                }
            }

            break;
        case 8:
            cout << "Thank you for using the OCC Gradebook. "
                << "Good-bye!\n\n";
            finish = true;
            break;
        default:
            cout << "Sorry. That is not an selection.\n\n";
            break;
        }
    }
}