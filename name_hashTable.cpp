#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>

using namespace std;

// HashTable Class 
// Quadratic Probing for Collision Resolution
// Hash Function: ASCII values of each character % Table Size
struct HashNode {
    string name;
    int count;
    HashNode* next;

    HashNode(const string& mName, int mCount) {
        name = mName;
        count = mCount;
    }
};

class HashTable {
private:
    // Store nodes / buckets
    vector<HashNode*> table;
    int size;
    int capacity;

    // Hash Function: (ASCII values of each character)* % Table Size
    int hash(const string& key) {
        int result = 0;
        for (char c : key) {
            result += static_cast<int>(c);
        }
        return result % capacity;
    }

public:
    HashTable() {
        // Initialize with a table size of 200000, and loadFactor of 0.6
        size = 0;
        capacity = 200000;
        table.resize(capacity, nullptr);
    }

    void insert(const string& name, int count) {
        int b = hash(name);
        int i = 0;

        while (true) {
            int index = (b + i * i) % capacity;
            HashNode* curr = table[index];

            if (curr == nullptr) {
                HashNode* newNode = new HashNode(name, count);
                table[index] = newNode;
                size++;
                break;
            }

            if (curr->name == name) {
                curr->count += count;
                return;
            }

            i++;
        }
    }

    // Retrieve popularity given name from hash table
    // O(1) - Average Case
    // O(1 + a) - Worst case given quadratic probing
    int nameCount(const string& name) {
        // Check initial bucket for name
        int b = hash(name);
        int i = 0;

        // If index is not found with hash function:
        // Quadratic probing to find valid bucket
        while (true) {
            int curr = (b + i * i) % capacity;
            HashNode* currNode = table[curr];

            if (currNode == nullptr) {
                return 0;
            }

            if (currNode->name == name) {
                return currNode->count;
            }
            i++;
        }
    }

    int getSize() {
        return size;
    }

    int getCapacity() {
        return capacity;
    }
};

// Sample use of extractNameAndNumber() function using "names_by_birth_year.csv"