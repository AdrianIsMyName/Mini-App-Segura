#pragma once
#include <string>
using namespace std; 

bool isSafeText(const string& s, int maxLen = 20) {
    if (s.length() == 0 || s.length() > maxLen) return false;
    for (char c : s) {
        if (!isalnum(c)) return false; // only letters and numbers
    }
    return true;
}

bool isValidGrade(double g) {
    return (g >= 0 && g <= 100);
}

bool isValidId(int id) {
    return (id > 0 && id < 4);
}