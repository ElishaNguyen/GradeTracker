/*
    Nguyen, Elisha
    Guenneugues, Juliette
    Javadi, Amirali

    Project: Grade Report
    CS A250
    Fall 2023
*/

#ifndef STUDENTLIST_H
#define STUDENTLIST_H

#include "Student.h"

#include <fstream>
#include <string>

class Node
{
public:
    Node() : next(nullptr) {}
    Node(Student aStudent, Node* nextLink)
        : student(aStudent), next(nextLink) {}
    Student& getStudent() { return student; }
    Node* getNext() const { return next; }
    void setStudent(const Student& theData) { student = theData; }
    void setNext(Node* nextLink) { next = nextLink; }
    ~Node() {}
private:
    Student student;
    Node* next;
};

class StudentList
{
public:
    StudentList() : first(nullptr), last(nullptr), count(0) {}
    StudentList(const StudentList& otherList);
    StudentList& operator=(const StudentList&);

    void addStudent(const Student& student);
    int getNoOfStudents() const;
    bool findStudentByID(int numID, Node*& iter);

    void printStudentByID(int numID, double tuitionRate) const;
    void printStudentByName(const std::string& alastName) const;
    void printStudentsByCourse(const std::string& aCoursePrefix, 
        int aCourseNumber) const;
    void printAllStudents(double tuitionRate) const;
    std::ofstream& printStudentsToFile(std::ofstream& out, 
        double tuitionRate) const;
    void printStudentsOnHold(double tuitionRate) const;

    void clearStudentList();

    ~StudentList();

private:
    Node* first;
    Node* last;
    int count;
    void copyCallingObjIsEmpty(const StudentList&);
    void copyObjectsSameLength(const StudentList&);
    void copyCallingObjLonger(const StudentList&);
    void copyCallingObjShorter(const StudentList&);
};

#endif