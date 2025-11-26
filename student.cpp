#include "student.h"
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

//Default constructor
student::student() {
	id = 0; 
	name = "N/A";
	grade = 0.0;
}

// Parameterized constructor
student::student(int i, string n, double g) {
	id = i;
	name = n;
	grade = g;
}




// Setter (Only for Grades)
void student::setGrade(double g) {
	grade = g;
}


// Getter
string student::getStudent() {
	stringstream ss;
	ss << "ID:" << id << " Name:" << name << " Grade:" << fixed << setprecision(2) << grade; 
	return ss.str();
}

int student::getId() {
	return id;
}

string student::getName() {
	return name;
}

double student::getGrade() {
	return grade;
}