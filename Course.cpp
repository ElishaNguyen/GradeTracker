/*
    Nguyen, Elisha
    Guenneugues, Juliette
    Javadi, Amirali

    Project: Grade Report
    CS A250
    Fall 2023
*/

#include "Course.h"

#include <iostream>

using namespace std;

void Course::setCourseInfo(const string& prefix, 
    int number, int units)
{
    coursePrefix = prefix;
    courseNumber = number;
    courseUnits = units;
}

string Course::getCoursePrefix() const
{
    return coursePrefix;
}

int Course::getCourseNumber() const
{
    return courseNumber;
}

int Course::getCourseUnits() const
{
    return courseUnits;
}

bool Course::operator<(const Course& otherCourse) const
{
    if (coursePrefix < otherCourse.coursePrefix)
    {
        return true;
    }
    else if (coursePrefix == otherCourse.coursePrefix)
    {
        return courseNumber < otherCourse.courseNumber;
    }
    else
    {
        return coursePrefix < otherCourse.coursePrefix;
    }
}