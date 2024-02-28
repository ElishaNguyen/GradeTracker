/*
    Nguyen, Elisha
    Guenneugues, Juliette
    Javadi, Amirali

    Project: Grade Report
    CS A250
    Fall 2023
*/

#include "Student.h"

#include <iostream>
#include <iomanip>

using namespace std;

void Student::setStudent(const Student& aStudent)
{
    studentID = aStudent.studentID;
    firstName = aStudent.firstName;
    lastName = aStudent.lastName;
    numberOfCourses = static_cast<int>(
        aStudent.coursesCompleted.size());
    tuitionWasPaid = aStudent.tuitionWasPaid;
    coursesCompleted = aStudent.coursesCompleted;
}

void Student::setStudentInfo(int anID, const string& aFirstName, 
    const string& aLastName, bool wasTuitionPaid, 
    const multimap<Course, char>& courses)
{
    studentID = anID;
    firstName = aFirstName;
    lastName = aLastName;
    numberOfCourses = static_cast<int>(courses.size());
    tuitionWasPaid = wasTuitionPaid;
    coursesCompleted = courses;
}

int Student::getID() const
{
    return studentID;
}
string Student::getFirstName() const
{
    return firstName;
}
string Student::getLastName() const
{
    return lastName;
}

void Student::getName(string& aFirstName, string& aLastName) const
{
    aFirstName = firstName;
    aLastName = lastName;
}

int Student::getNumberOfCourses() const
{
    return numberOfCourses;
}

int Student::getUnitsCompleted() const
{
    int units = 0;
    for (auto& key : coursesCompleted)
    {
        units += key.first.getCourseUnits();
    }
    return units;
}

multimap<Course, char> Student::getCoursesCompleted()
{
    return coursesCompleted;
}

bool Student::isTuitionPaid() const
{
    return tuitionWasPaid;
}

bool Student::isCourseCompleted(const std::string& aCoursePrefix,
    int aCourseNumber) const
{
    if (numberOfCourses == 0)
        return false;
    else
    {
        bool found = false;
        auto iter = coursesCompleted.begin();
        auto end = coursesCompleted.end();

        while (iter != end && !found)
        {
            if (iter->first.getCoursePrefix() == aCoursePrefix &&
                iter->first.getCourseNumber() == aCourseNumber)
            {
                found = true;
            }
            else
            {
                ++iter;
            }
        }
        return found;
    }
}

void Student::changeGrade(const std::string& aCoursePrefix, 
    int aCourseNumber, char newGrade)
{
    bool found = false;
    auto iter = coursesCompleted.begin();
    auto end = coursesCompleted.end();

    while (iter != end && !found)
    {
        if (iter->first.getCoursePrefix() == aCoursePrefix &&
            iter->first.getCourseNumber() == aCourseNumber)
        {
            found = true;
            iter->second = newGrade;
        }
        else
        {
            ++iter;
        }
    }
}

double Student::calculateGPA() const
{
    if (numberOfCourses == 0)
        return 0;
    double gpa = 0.0;
    int units = 0;
    
   for (auto& key : coursesCompleted)
    {
        double grade = 0.0;
        switch (key.second)
        {
        case 'A':
            grade = 4;
            break;
        case 'B':
            grade = 3;
            break;
        case 'C':
            grade = 2;
            break;
        case 'D':
            grade = 1;
            break;
        default:
            grade = 0;
            break;
        }
        grade *= key.first.getCourseUnits();
        gpa += grade;
        units += key.first.getCourseUnits();
    }
    return gpa / units;
}

double Student::billingAmount(double tuitionRate) const
{
    return numberOfCourses * tuitionRate;
}

void Student::printStudent() const
{
    cout << studentID << " - " << lastName << ", " << firstName 
        << endl;
}

void Student::printStudentInfo(double tuitionRate) const
{
    cout << "Student Name: " << lastName << ", " << firstName
        << "\nStudent ID: " << studentID
        << "\nNumber of courses completed: " << numberOfCourses
        << '\n';

    cout << "\nCourseNo  Units  Grade\n";
    int totalCreditHours = 0;
    for (const auto& elem : coursesCompleted)
    {
        cout << setw(4) << left << elem.first.getCoursePrefix()
            << setw(4) << right << elem.first.getCourseNumber()
            << setw(5) << right << elem.first.getCourseUnits()
            << setw(7) << right << elem.second <<
            '\n';

        totalCreditHours += elem.first.getCourseUnits();
    }

    cout << "\nTotal Number of Credit Hours: " << totalCreditHours;
    if (tuitionWasPaid)
    {
        cout << "\nCurrent Term GPA: " << fixed << setprecision(2)
            << calculateGPA() << '\n';
    }
    else
    {
        cout << "\n*** Grades are being held for " 
            << "not paying the tuition. ***"
            << "\nAmount due: $" << fixed << setprecision(2)
            << billingAmount(tuitionRate) << '\n';
    }

    cout << "\n-*-*-*-*-*-*-*-*-*-*-*-*-*"
        << "-*-*-*-*-*-*-*-*-*-*-*-\n" << endl;

}