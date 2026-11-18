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
        // Clean up dynamically allocated chain nodes
        for (int i = 0; i < TABLE_SIZE; ++i) {
            HashNode* curr = table[i];
            while (curr != nullptr) {
                HashNode* temp = curr;
                curr = curr->next;
                delete temp;
            }
            table[i] = nullptr;
        }
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

    // Milestone 3: Insertion without collision resolution (direct assignment)
    bool insertWithoutCollisionHandling(const ColdDrink& drink) {
        int index = midSquareHash(drink.flavorID);
        if (table[index] != nullptr) {
            cout << "[COLLISION DETECTED at Slot " << index << "] Key " << drink.flavorID 
                 << " collides with existing Key " << table[index]->data.flavorID 
                 << "! Overwriting existing record (Data Loss)." << endl;
            delete table[index]; // Overwriting
        } else {
            cout << "[INSERTED at Slot " << index << "] Key " << drink.flavorID 
                 << " (" << drink.flavorName << ")" << endl;
        }
        table[index] = new HashNode(drink);
        return true;
    }

    /**
     * Milestone 4: Separate Chaining Collision Resolution
     * Appends new colliding elements to the tail of the bucket's linked list.
     */
    void insert(const ColdDrink& drink) {
        int index = midSquareHash(drink.flavorID);
        HashNode* newNode = new HashNode(drink);

        if (table[index] == nullptr) {
            table[index] = newNode;
            cout << "[INSERT] Slot " << index << " (Head) -> ID: " << setw(2) << drink.flavorID 
                 << " | " << drink.flavorName << endl;
        } else {
            // Collision occurred - append to chain tail
            HashNode* curr = table[index];
            int chainPos = 1;
            while (curr->next != nullptr) {
                curr = curr->next;
                chainPos++;
            }
            curr->next = newNode;
            cout << "[COLLISION -> CHAINED] Slot " << index << " (Pos " << (chainPos + 1) 
                 << ") -> ID: " << setw(2) << drink.flavorID << " | " << drink.flavorName 
                 << " (chained after ID " << curr->data.flavorID << ")" << endl;
        }
    }

    void display() {
        cout << "\n================== Cold Drink Flavor Hash Table (Separate Chaining) ==================" << endl;
        for (int i = 0; i < TABLE_SIZE; ++i) {
            cout << "Slot [" << i << "]: ";
            if (table[i] == nullptr) {
                cout << "EMPTY" << endl;
            } else {
                HashNode* curr = table[i];
                while (curr != nullptr) {
                    cout << " -> [ID: " << setw(2) << curr->data.flavorID 
                         << " | " << curr->data.flavorName 
                         << " (" << curr->data.brand << ", Rs." << curr->data.price << ")]";
                    curr = curr->next;
                }
                cout << " -> NULL" << endl;
            }
        }
        cout << "======================================================================================\n" << endl;
    }
};

int main() {
    cout << "========================================================" << endl;
    cout << " Cold Drink Flavor Inventory System (Hash Table)" << endl;
    cout << " PRN: 202501100133 | Scenario: Cold-drink flavours" << endl;
    cout << "========================================================" << endl;

    HashTable ht;

    cout << "\n[Milestone 4] Testing Separate Chaining Collision Resolution:" << endl;
    // Keys 33, 59, and 72 all hash to Slot 8 under Mid-Square
    ht.insert(ColdDrink(33, "Classic Cola", "Coca-Cola", 500, 40.0));
    ht.insert(ColdDrink(46, "Lemon Lime Fizz", "Sprite", 500, 35.0));
    ht.insert(ColdDrink(59, "Mango Blast", "Maaza", 600, 38.0));
    ht.insert(ColdDrink(72, "Orange Sunset", "Mirinda", 500, 35.0));

    ht.display();

    return 0;
}
