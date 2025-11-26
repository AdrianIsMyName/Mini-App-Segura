// Mini App Segura.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include "student.h"
#include "input_validation.h"
#include <sodium.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <array>
using namespace std;


void writeLog(const string& message) {
	ofstream logs("logs.txt", ios::app);  // append mode
	if (!logs.is_open()) {
		cout << "Error opening log file!" << endl;
		return;
	}

	auto now = chrono::system_clock::now();
	time_t currentTime = chrono::system_clock::to_time_t(now);

	tm localTime;
	localtime_s(&localTime, &currentTime);

	logs << put_time(&localTime, "%Y-%m-%d %H:%M:%S") << " - " << message << endl;
}

int loginMenu(int& accountType, int& storedId) {

	string username;
	string storedUsername;
	string password;
	string storedPassword;
	string storedRole;

	ifstream users("users.txt");
	bool credentialsFound = false;

	//If the file can't be read.
	if (!users.is_open()) {
		cout << "Error opening users file." << endl;
		return -1;
	}

	// Prompt user for login
	cout << "Enter username: ";
	cin >> username;
	cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear leftover input


	if (!isSafeText(username)) {
		cout << "Invalid username!" << endl;
		system("pause");
		system("cls");
		writeLog("Rejected invalid username input");
		return loginMenu(accountType, storedId); // ask again
	}

	cout << "Enter password: ";
	cin >> password;
	

	if (!isSafeText(password)) {
		cout << "Invalid password!" << endl;
		system("pause");
		system("cls");
		writeLog("Rejected invalid password input");
		return loginMenu(accountType, storedId);
	}

	// Validate credentials
	while (users >> storedUsername >> storedPassword >> storedRole >> storedId)
	{
		if (username == storedUsername &&
			crypto_pwhash_str_verify(storedPassword.c_str(), password.c_str(), password.length()) == 0)
		{
			credentialsFound = true;
			break;
		}
	}

	if (credentialsFound) {
		writeLog("User '" + username + "' logged in as " + storedRole);
		cout << "Login successful" << endl;
		system("cls");
		if (storedRole == "teacher") {
			accountType = 1;
		}
		else if (storedRole == "student") {
			accountType = 2;
		}
	}
	else {
		writeLog("Failed login attempt for username '" + username + "'");
		cout << "Invalid User" << endl;
		system("pause");
		system("cls");
		return loginMenu(accountType, storedId);
	}
	
	return 0;
}


void loadStudents(student students[], int& count) {
	ifstream studentFile("students.txt");

	if (!studentFile.is_open()) {
		cout << "Error opening students file." << endl;
		return;
	}

	int id;
	string name;
	double grade;

	count = 0;

	while (studentFile >> id >> name >> grade && count < 3) {
		students[count] = student(id, name, grade);
		count++;
	}
}

void modifyGrade(student students[], int studentCount) {
	int id;
	double newGrade;
	bool found = false;

	cout << "Enter the ID of the student to modify: ";
	cin >> id;
	if (!isValidId(id)) {
		cout << "Invalid ID!" << endl;
		system("pause");
		return;
	}

	// Search for the student by ID
	for (int i = 0; i < studentCount; i++) {
		if (students[i].getId() == id) {
			found = true;
			cout << "Current info: " << students[i].getStudent() << endl;
			cout << "Enter new grade: ";
			cin >> newGrade;

			//If new grade is not valid
			if (!isValidGrade(newGrade)) {
				cout << "Invalid grade!" << endl;
				system("pause");
				return ; 
			}

			double oldGrade = students[i].getGrade();
			students[i].setGrade(newGrade);
			cout << "Grade updated successfully!" << endl;
			system("pause");
			writeLog("Teacher modified grade of student ID " + to_string(students[i].getId()) + " from " + to_string(oldGrade) + " to " + to_string(newGrade)); //Logs modification of grade.
			break;
		}
	}
}

void saveStudents(student students[], int studentCount) {
	ofstream file("students.txt");

	if (!file.is_open()) {
		cout << "Error opening students file for writing!" << endl;
		return;
	}

	for (int i = 0; i < studentCount; i++) {
		file << students[i].getId() << " "
			<< students[i].getName() << " "
			<< students[i].getGrade() << endl;
	}
}


int main()
{
	if (sodium_init() < 0) {
		//The library couldn't be initialized
		return 1;
	}

	//Writes a log date when someone opens the program.
	writeLog("Program opened");

	//Login Menu
	int accountType = 0;
	int storedId;
	loginMenu(accountType, storedId);

	const int MAX_STUDENTS = 3;
	student students[MAX_STUDENTS];
	int studentCount = 0;

	loadStudents(students, studentCount);

	if (accountType == 1) {
		// Teacher: show all students
		for (int i = 0; i < studentCount; i++) {
			cout << students[i].getStudent() << endl;
		}

		//Teacher: Options to Show grades, Change grade or exit.
		int choice;
		do {
			cout << "1. Show grades \n2. Modify student grade\n3. Exit\nChoice: ";
			cin >> choice;

			switch (choice) {
			case 1:
				system("cls");
				for (int i = 0; i < studentCount; i++)
					cout << students[i].getStudent() << endl;
				break;
			case 2:
				modifyGrade(students, studentCount); //Modify grade function.
				saveStudents(students, studentCount);//Saves new grade.
				system("cls");
				break;
			case 3:
				cout << "Logging out..." << endl;
				break;
			default:
				cout << "Invalid choice!" << endl;
				system("pause");
				system("cls");
			}
		} while (choice != 3);
	}
	else if (accountType == 2) {
		// Student: show only their grade
		for (int i = 0; i < studentCount; i++) {
			if (students[i].getId() == storedId) {  // match ID
				cout << "Your info:\n";
				cout << students[i].getStudent() << endl;
				break;
			}
		}
	}
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

/*
void loginMenu(int &userAccess) {



	cout << "Choose account type:" << endl;
	cout << "1: Teacher" << " " << "2: Student" << " " << "3: Guest " << endl;
	int accountType;
	cin >> accountType;

	switch (accountType) {
		case 1:
			teacherLogin();
			userAccess = 1;
			break;

		case 2:
			studentLogin();
			userAccess = 2;
			break;

		case 3:
			cout << "WIP";
			break;
	}




}







	s1.printStudent();
	s2.printStudent();
	s3.printStudent();
*/

/*array<student, 3> students = {{
	{1, "Adrian", 100.0},
	{2, "Miguel", 93.5},
	{3, "Andrea", 91.9}
} };*/