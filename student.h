#pragma once
#include <string>
using namespace std;

class student {
private:
    int id;
    string name;
    double grade;


public:
    student(); // default constructor
    student(int i, string n, double g); // constructor

    void setGrade(double g); // set grade

    string getStudent(); // get all Student info.

    int getId(); //get Id
    string getName(); //get Name
    double getGrade(); //get Grade
};