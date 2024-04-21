#include <iostream>
#include <chrono>
#include "ReadFunction.h"
#include "RBTree.h"
#include "name_hashTable.cpp"

int main() {

    RBTree nameTree;
    HashTable nameTable;

    string filename1 = "names_by_birth_year.csv";
    ifstream file1(filename1);

    map<string, int> nameData1;

    // Skip header line
    string header1;
    getline(file1, header1);

    //Loop through every line in the CSV and use the
    string line1;

    clock_t start;
    double timeBuildTree;
    double timeBuildTable;

    //Gets the time needed to build the red black tree
    start = clock();
    while (getline(file1,line1)) {
        auto [name, count] = extractNameAndNumber(line1);
        nameTree.insert(name, count);
    }
    timeBuildTree = (clock() - start) / (double) CLOCKS_PER_SEC;

    //Repeats the file reading to run through it again,
    //only this time building the hash table
    string filename2 = "names_by_birth_year.csv";
    ifstream file2(filename2);

    map<string, int> nameData2;

    // Skip header line
    string header2;
    getline(file2, header2);

    //Loop through every line in the CSV and use the
    string line2;

    //Gets the time needed to build the hash table
    start = clock();
    while (getline(file2,line2)) {
        auto [name, count] = extractNameAndNumber(line2);
        nameTable.insert(name, count);
    }
    timeBuildTable = (clock() - start) / (double) CLOCKS_PER_SEC;

    //Prints the time to build each data structure
    cout << "It took " << timeBuildTree;
    cout << " seconds to build the red black tree." << endl;
    cout << "It took " << timeBuildTable;
    cout << " seconds to build the hash table." << endl;

    //Takes name input

    bool running = true;

    //loops the name searching section until user ends the program
    while(running) {

        string name;
        cout << "Input the name you would like to search for. The first letter must be capitalized." << endl;
        cout << "To end the program, input 'Stop' or 'stop'." << endl;
        cin >> name;
        if (name == "Stop" or name == "stop") {
            running = false;
        }
        else {
            //Gets the time needed to search each data structure for the name
            //Because this happens very quickly, a more precise clock is needed
            //to compare the search times
            auto begin = std::chrono::high_resolution_clock::now();
            treeNode *resultNode = nameTree.search(nameTree.getRoot(), name);
            auto end = std::chrono::high_resolution_clock::now();
            auto timeSearchTree = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);

            begin = std::chrono::high_resolution_clock::now();
            int count = nameTable.nameCount(name);
            end = std::chrono::high_resolution_clock::now();
            auto timeSearchTable = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);

            //This should never occur, but on the off change it does,
            //this prints an error message when the tree and table disagree.
            if (resultNode != nullptr) {
                if (count != resultNode->value) {
                    cout << "Error. Hash table and red black tree disagree.";
                }
            }
            else
            {
                //If resultNode is nullptr, it's not in the tree,
                //and so its count as determined by the table should be 0
                if (count != 0) {
                    cout << "Error. Hash table and red black tree disagree.";
                }
            }

            //prints results. If a name appears zero times,
            // it is not in either data structure
            cout << "The name " + name + " has appeared ";
            cout << count << " times." << endl;
            //By this point, it has been confirmed that the hash table
            //and red black tree agree on the count, so the table's count
            //is the result from both structures.

            cout << "It took the red black tree " << timeSearchTree.count();
            cout << " microseconds to find this name." << endl;
            cout << "It took the hash table " << timeSearchTable.count();
            cout << " microseconds to find this name." << endl << endl;
        }
    }
}

