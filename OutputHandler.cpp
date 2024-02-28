/*
	Nguyen, Elisha
    Guenneugues, Juliette
    Javadi, Amirali

	Project: Grade Report
	CS A250
	Fall 2023
*/

#include "OutputHandler.h"

#include "Course.h"
#include "Student.h"

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

void printAllStudentsToFile(
	const StudentList& studentList, double tuitionRate)
{
	//Declare stream object
	std::ofstream outfile;

	//Ask user how to name the file to write to
	std::string nameOfFile;
	std::cout << "Enter a name for a new file to write on "
		<< "(include extension.txt) : ";
	std::cin >> nameOfFile;
	std::cout << std::endl;

	outfile.open(nameOfFile);

	if (outfile.fail())
	{
		std::cerr << "Output file opening failed.\n";
	}
	else
	{
		outfile
			<< "-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-\n"
			<< "            UNOFFICIAL TRANSCRIPTS\n"
			<< "-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-\n\n";
		studentList.printStudentsToFile(outfile, tuitionRate);
	}
}