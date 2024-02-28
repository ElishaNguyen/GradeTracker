/*
    Nguyen, Elisha
    Guenneugues, Juliette
    Javadi, Amirali

    Project: Grade Report
    CS A250
    Fall 2023
*/

#include "StudentList.h"

#include <iostream>

using namespace std;

StudentList::StudentList(const StudentList& myObj)
{
    first = nullptr;
    last = nullptr;
    count = 0;
    Node* temp = myObj.first;
    while (temp != nullptr)
    {
        addStudent(temp->getStudent());
        temp = temp->getNext();
    }
}

void StudentList::copyCallingObjIsEmpty(const StudentList& myObj)
{
    Node* temp = myObj.first;
    while (temp != nullptr)
    {
        addStudent(temp->getStudent());
        temp = temp->getNext();
    }
}

void StudentList::copyObjectsSameLength(const StudentList& myObj)
{
    Node* calltemp = first;
    Node* prmtemp = myObj.first;

    while (calltemp != nullptr)
    {
        calltemp->setStudent(prmtemp->getStudent());
        calltemp = calltemp->getNext();
        prmtemp = prmtemp->getNext();
    }
}

void StudentList::copyCallingObjLonger(const StudentList& myObj)
{
    Node* temp = first;
    int diff = count - myObj.count;
    for (int i = 0; i < diff; i++)
    {
        first = first->getNext();
        delete temp;
        temp = first;
    }

    Node* calltemp = first;
    Node* prmtemp = myObj.first;

    while (calltemp != nullptr)
    {
        calltemp->setStudent(prmtemp->getStudent());
        calltemp = calltemp->getNext();
        prmtemp = prmtemp->getNext();
    }
}

void StudentList::copyCallingObjShorter(const StudentList& myObj)
{
    Node* cltemp = first;
    Node* prtemp = myObj.first;

    while (cltemp != nullptr)
    {
        cltemp->setStudent(prtemp->getStudent());
        cltemp = cltemp->getNext();
        prtemp = prtemp->getNext();
    }
    while (prtemp != nullptr)
    {
        addStudent(prtemp->getStudent());
        prtemp = prtemp->getNext();
    }
}

StudentList& StudentList::operator=(const StudentList& myObj)
{
    if (last == myObj.last && first == myObj.first)
        cerr << "Attempted assignment to itself." << endl;
    else if (count == 0)
        copyCallingObjIsEmpty(myObj);
    else if (count == myObj.count)
        copyObjectsSameLength(myObj);
    else if (count > myObj.count)
        copyCallingObjLonger(myObj);
    else if (myObj.count == 0)
        clearStudentList();
    else
        copyCallingObjShorter(myObj);

    return *this;
}