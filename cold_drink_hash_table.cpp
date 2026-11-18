/**
 * ============================================================================
 * DATA STRUCTURES - INTERNAL ASSESSMENT 3 (IA-3)
 * ============================================================================
 * Student Name   : Krishna
 * PRN            : 202501100133
 * Repository     : https://github.com/me13krishna/DS-IA-3
 * 
 * ----------------------------------------------------------------------------
 * PERSONALIZATION KEY DERIVATION:
 * ----------------------------------------------------------------------------
 * Parameter                 | Rule                   | Evaluation       | Assigned Value
 * --------------------------+------------------------+------------------+------------------------------
 * 1. Domain Scenario        | PRN mod 3              | 202501100133 % 3 | 0 -> Cold-drink flavours
 * 2. Dataset Seed S         | Last 4 digits of PRN   | "0133"           | S = 133
 *    Dataset (20 values)    | (S + 13*i) mod 100     | i = 0..19        | [33, 46, 59, 72, 85, 98, 11,
 *                           |                        |                  |  24, 37, 50, 63, 76, 89, 2,
 *                           |                        |                  |  15, 28, 41, 54, 67, 80]
 * 3. Hash Function          | PRN odd/even           | PRN is ODD (3)   | Mid-Square Method
 * 4. Collision Strategy     | PRN mod 2              | 202501100133 % 2 | 1 -> Separate Chaining
 * ============================================================================
 */

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

// Domain Entity: Cold Drink Flavor Record
struct ColdDrink {
    int flavorID;           // Hash Key (from personalized dataset)
    string flavorName;      // e.g., "Classic Cola", "Mango Blast"
    string brand;           // e.g., "Coca-Cola", "Maaza"
    int volumeML;           // e.g., 500 ml
    double price;           // e.g., 40.0 INR

    ColdDrink(int id = 0, string name = "", string b = "", int vol = 0, double p = 0.0)
        : flavorID(id), flavorName(name), brand(b), volumeML(vol), price(p) {}
};

// Node structure for Separate Chaining (Linked List per Bucket)
struct HashNode {
    ColdDrink data;
    HashNode* next;

    HashNode(const ColdDrink& drink) : data(drink), next(nullptr) {}
};

// Hash Table Class Declaration
class HashTable {
private:
    static const int TABLE_SIZE = 10; // Standard modulus table size m = 10
    HashNode* table[TABLE_SIZE];

public:
    HashTable() {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            table[i] = nullptr;
        }
    }

    ~HashTable() {
        // Will implement memory cleanup when chaining is active
    }

    /**
     * Mid-Square Hash Function:
     * 1. Compute square of the key: K^2
     * 2. Extract middle digit(s) based on table size (m = 10 -> single digit [0-9])
     * 3. Handle single/odd/even digit squares accurately.
     */
    int midSquareHash(int key) const {
        long long sq = (long long)key * key;
        string s = to_string(sq);
        int len = (int)s.length();
        
        // Middle index is len / 2
        int midIdx = len / 2;
        int middleDigit = s[midIdx] - '0';
        int hashIndex = middleDigit % TABLE_SIZE;

        return hashIndex;
    }

    // Diagnostic method to display mid-square computation step-by-step
    void printHashBreakdown(int key) const {
        long long sq = (long long)key * key;
        string s = to_string(sq);
        int len = (int)s.length();
        int midIdx = len / 2;
        int middleDigit = s[midIdx] - '0';
        int hashIndex = middleDigit % TABLE_SIZE;

        cout << "Key: " << setw(2) << key 
             << " | Square: " << setw(4) << sq 
             << " | Digits: " << len 
             << " | MidDigit: " << middleDigit 
             << " -> Slot: " << hashIndex << endl;
    }

    void display() {
        cout << "\n=== Cold Drink Flavor Hash Table (Size " << TABLE_SIZE << ") ===" << endl;
        for (int i = 0; i < TABLE_SIZE; ++i) {
            cout << "Slot [" << i << "]: ";
            if (table[i] == nullptr) {
                cout << "EMPTY" << endl;
            } else {
                cout << "[ID: " << table[i]->data.flavorID << " | " 
                     << table[i]->data.flavorName << "]" << endl;
            }
        }
    }
};

int main() {
    cout << "========================================================" << endl;
    cout << " Cold Drink Flavor Inventory System (Hash Table)" << endl;
    cout << " PRN: 202501100133 | Scenario: Cold-drink flavours" << endl;
    cout << "========================================================" << endl;

    HashTable ht;

    cout << "\n[Milestone 2] Testing Mid-Square Hash Function on sample keys:" << endl;
    ht.printHashBreakdown(33); // 33^2 = 1089 -> mid digit 8
    ht.printHashBreakdown(46); // 46^2 = 2116 -> mid digit 1
    ht.printHashBreakdown(2);  // 2^2  =    4 -> mid digit 4
    ht.printHashBreakdown(11); // 11^2 =  121 -> mid digit 2
    ht.printHashBreakdown(98); // 98^2 = 9604 -> mid digit 0

    return 0;
}
