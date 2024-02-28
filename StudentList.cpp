/*
    Nguyen, Elisha
    Guenneugues, Juliette
    Javadi, Amirali

    Project: Grade Report
    CS A250
    Fall 2023
*/

#include "StudentList.h"

#include <iomanip>
#include <iostream>

using namespace std;

void StudentList::addStudent(const Student& student)
{
    if (first == nullptr)
    {
        first = new Node(student, nullptr);
        last = first;
    }
    else
    {
        last->setNext(new Node(student, nullptr));
        last = last->getNext();
    }
    count++;
}

int StudentList::getNoOfStudents() const
{
    return count;
}

bool StudentList::findStudentByID(int numID, Node*& iter)
{
    Node* current = first;
    bool found = false;
    while (current != nullptr && !found)
    {
        if (current->getStudent().getID() == numID)
            found = true;
        else
            current = current->getNext();
    }
    if (found)
    {
        iter = current;
        return true;
    }
    else
    {
        cout << "No students with ID " << numID 
            << " found in the list.\n";
        return false;
    }
}

void StudentList::printStudentByID(int numID, 
    double tuitionRate) const
{
    Node* current = first;
    bool found = false;
    while (current != nullptr && !found)
    {
        if (current->getStudent().getID() == numID)
            found = true;
        else
            current = current->getNext();
    }
    if (found)
        current->getStudent().printStudentInfo(tuitionRate);
    else
        cout << "No students with ID " << numID 
        << " found in the list.\n\n";
}

void StudentList::printStudentByName(const string& aLastName) const
{
    Node* current = first;
    bool found = false;

    while (current != nullptr)
    {
        if (current->getStudent().getLastName() == aLastName)
        {
            current->getStudent().printStudent();
            found = true;
        }
        current = current->getNext();
    }
    if (!found)
        cout << "No student with last name " << aLastName 
        << " is on the list.\n";
}

void StudentList::printStudentsByCourse(const string& 
    aCoursePrefix, int aCourseNumber) const
{
    Node* current = first;
    bool found = false;

    while (current != nullptr)
    {
        if (current->getStudent().isCourseCompleted(aCoursePrefix, 
            aCourseNumber))
        {
            current->getStudent().printStudent();
            found = true;
        }
        current = current->getNext();
    }

    if (!found)
        cout << "No students enrolled in " << aCoursePrefix << " " 
        << aCourseNumber << ".\n";
}

void StudentList::printAllStudents(double tuitionRate) const
{
    Node* current = first;
    while (current != nullptr)
    {
        current->getStudent().printStudentInfo(tuitionRate);
        current = current->getNext();
    }
}

ofstream& StudentList::printStudentsToFile(ofstream& out, 
    double tuitionRate) const
{
    Node* current = first;
    while (current != nullptr)
    {
        Student currStudent = current->getStudent();
        out << "Student Name: " << currStudent.getLastName() << ", "
            << currStudent.getFirstName()
            << "\nStudent ID: " << currStudent.getID()
            << "\nNumber of courses completed: " 
            << currStudent.getNumberOfCourses()
            << '\n';

        out << "\nCourseNo  Units  Grade\n";
        int totalCreditHours = 0;
        for (const auto& elem : currStudent.getCoursesCompleted())
        {
            out << setw(4) << left << elem.first.getCoursePrefix()
                << setw(4) << right << elem.first.getCourseNumber()
                << setw(5) << right << elem.first.getCourseUnits()
                << setw(7) << right << elem.second <<
                '\n';

            totalCreditHours += elem.first.getCourseUnits();
        }

        out << "\nTotal Number of Credit Hours: " << totalCreditHours;
        if (currStudent.isTuitionPaid())
        {
            out << "\nCurrent Term GPA: " << fixed << setprecision(2)
                << currStudent.calculateGPA() << '\n';
        }
        else
        {
            out << "\n*** Grades are being held for "
                << "not paying the tuition. ***"
                << "\nAmount due: $" << fixed << setprecision(2)
                << currStudent.billingAmount(tuitionRate) << '\n';
        }

        out << "\n-*-*-*-*-*-*-*-*-*-*-*-*"
            << "-*-*-*-*-*-*-*-*-*-*-*-*-\n" << endl;

        current = current->getNext();
    }
    return out;
}

void StudentList::printStudentsOnHold(double tuitionRate) const
{
    Node* current = first;
    while (current != nullptr)
    {
        if (!current->getStudent().isTuitionPaid())
        {
            current->getStudent().printStudent();
            cout << setprecision(2) << fixed <<  "    Amount Due: $"
                << current->getStudent().billingAmount(tuitionRate)
                << endl;
        }
        current = current->getNext();
    }
}

void StudentList::clearStudentList()
{
    Node* temp = first;
    while (temp != nullptr)
    {
        first = first->getNext();
        delete temp;
        temp = first;
    }
    count = 0;
    last = nullptr;
}

StudentList::~StudentList()
{
    clearStudentList();
}
