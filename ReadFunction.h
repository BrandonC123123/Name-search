
#ifndef COP3530PROJECT3_READFUNCTION_H
#define COP3530PROJECT3_READFUNCTION_H

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <map>

using namespace std;

// Returns the name and popularity from a single column
// Input: Line from csv; Assumes line is in "YEAR,NAME,G,COUNT" format
// Output: Pair (string containing name + int containing popularity of name)
pair<string, int> extractNameAndNumber(const string& line) {
    istringstream iss(line);
    string k;
    pair<string, int> result;

    // Skip the first column
    getline(iss, k, ',');
    // Retrieve name from second column
    getline(iss, k, ',');
    result.first = k;

    // Skip third column
    getline(iss, k, ',');
    // Retrieve populairty from the second column and store as int
    getline(iss, k, ',');
    result.second = stoi(k);

    return result;
}


#endif //COP3530PROJECT3_READFUNCTION_H
