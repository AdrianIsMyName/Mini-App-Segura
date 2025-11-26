# Mini App Segura (C++)
A simple C++ console app with secure login, student grade management, and basic role-based access.

Features:
  Secure Login using libsodium for password verification.
  Role System
  Teacher: view all students, modify grades.
  Student: view only their own grade.
  Grade Management (load, display, update, save).
  Input Validation for usernames, passwords, IDs, and grades.
  Activity Logging saved to logs.txt.

File Overview
main.cpp               -> program logic + menus
student.h/.cpp         -> Student class
input_validation.h     -> validation functions
users.txt              -> username, hashed password, role, ID
students.txt           -> ID, name, grade
logs.txt               -> auto-generated logs

Requirements
  C++17+
  libsodium installed and linked

How It Works
  Program logs when it starts and every login attempt.
  Credentials are checked against users.txt.
  Student info is read from students.txt.
  Teachers can update grades and save them back to the file.


Build and run.
## Author
Adrian Díaz
