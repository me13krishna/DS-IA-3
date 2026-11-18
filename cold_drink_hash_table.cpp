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
     * Milestone 4 & 6: Separate Chaining with Duplicate Key Handling
     * Appends new colliding elements to the tail of the bucket's linked list.
     * Prevents duplicate Primary Keys (Flavor IDs).
     */
    bool insert(const ColdDrink& drink) {
        int index = midSquareHash(drink.flavorID);

        // Check for duplicate key in the bucket
        HashNode* check = table[index];
        while (check != nullptr) {
            if (check->data.flavorID == drink.flavorID) {
                cout << "[DUPLICATE REJECTED] Flavor ID " << drink.flavorID 
                     << " already exists in Slot " << index 
                     << " (" << check->data.flavorName << "). Insertion aborted." << endl;
                return false;
            }
            check = check->next;
        }

        HashNode* newNode = new HashNode(drink);

        if (table[index] == nullptr) {
            table[index] = newNode;
            cout << "[INSERT] Slot " << index << " (Head) -> ID: " << setw(2) << drink.flavorID 
                 << " | " << setw(20) << left << drink.flavorName 
                 << " | " << setw(18) << drink.brand 
                 << " | Rs. " << fixed << setprecision(2) << drink.price << endl;
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
                 << ") -> ID: " << setw(2) << drink.flavorID 
                 << " | " << setw(20) << left << drink.flavorName 
                 << " | (chained after ID " << curr->data.flavorID << ")" << endl;
        }
        return true;
    }

    // Prints chain metrics, bucket distribution, and load factor
    void printStatistics() const {
        int totalElements = 0;
        int maxChain = 0;
        int emptySlots = 0;

        cout << "\n---------------- Hash Table Performance Statistics ----------------" << endl;
        cout << setw(10) << "Slot" << setw(15) << "Chain Length" << "  Visual Representation" << endl;
        cout << "------------------------------------------------------------------" << endl;
        for (int i = 0; i < TABLE_SIZE; ++i) {
            int chainLen = 0;
            HashNode* curr = table[i];
            while (curr != nullptr) {
                chainLen++;
                curr = curr->next;
            }
            totalElements += chainLen;
            if (chainLen > maxChain) maxChain = chainLen;
            if (chainLen == 0) emptySlots++;

            cout << setw(8) << i << setw(14) << chainLen << "    ";
            for (int k = 0; k < chainLen; ++k) cout << "#";
            if (chainLen == 0) cout << "(empty)";
            cout << endl;
        }
        cout << "------------------------------------------------------------------" << endl;
        cout << "Total Slots (m)        : " << TABLE_SIZE << endl;
        cout << "Total Elements (n)     : " << totalElements << endl;
        cout << "Load Factor (alpha=n/m): " << fixed << setprecision(2) << (double)totalElements / TABLE_SIZE << endl;
        cout << "Max Chain Length       : " << maxChain << endl;
        cout << "Empty Buckets          : " << emptySlots << " / " << TABLE_SIZE << endl;
        cout << "------------------------------------------------------------------\n" << endl;
    }

    /**
     * Milestone 5: Search Operation with Comparison Counting
     */
    ColdDrink* searchFlavor(int flavorID, int& comparisons) const {
        int index = midSquareHash(flavorID);
        comparisons = 0;
        HashNode* curr = table[index];

        while (curr != nullptr) {
            comparisons++;
            if (curr->data.flavorID == flavorID) {
                return &(curr->data);
            }
            curr = curr->next;
        }
        return nullptr;
    }

    /**
     * Milestone 5: Delete Operation with Pointer Rewiring
     */
    bool deleteFlavor(int flavorID) {
        int index = midSquareHash(flavorID);
        HashNode* curr = table[index];
        HashNode* prev = nullptr;

        while (curr != nullptr && curr->data.flavorID != flavorID) {
            prev = curr;
            curr = curr->next;
        }

        if (curr == nullptr) {
            cout << "[DELETE FAILED] Flavor ID " << flavorID << " not found in Slot " << index << "." << endl;
            return false;
        }

        if (prev == nullptr) {
            // Deleting head node
            table[index] = curr->next;
        } else {
            // Deleting interior or tail node
            prev->next = curr->next;
        }

        cout << "[DELETED] Flavor ID " << flavorID << " (" << curr->data.flavorName 
             << ") successfully removed from Slot " << index << "." << endl;
        delete curr;
        return true;
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
    cout << "==========================================================================" << endl;
    cout << " DATA STRUCTURES IA-3: HASH TABLE IMPLEMENTATION" << endl;
    cout << " Student: Krishna | PRN: 202501100133" << endl;
    cout << " Domain Scenario  : Cold-Drink Flavours (PRN % 3 = 0)" << endl;
    cout << " Hash Function    : Mid-Square Method (PRN is ODD)" << endl;
    cout << " Collision Policy : Separate Chaining (PRN % 2 = 1)" << endl;
    cout << " Seed S = 133     : v[i] = (133 + 13*i) mod 100 for i = 0..19" << endl;
    cout << "==========================================================================" << endl;

    HashTable ht;

    // Personalized 20-value dataset mapped to Cold Drink Flavors
    vector<ColdDrink> dataset = {
        ColdDrink(33, "Classic Cola",        "Coca-Cola",         500, 40.0),
        ColdDrink(46, "Lemon Lime Fizz",     "Sprite",            500, 35.0),
        ColdDrink(59, "Mango Blast",         "Maaza",             600, 38.0),
        ColdDrink(72, "Orange Sunset",       "Mirinda",           500, 35.0),
        ColdDrink(85, "Ginger Beer Ale",     "Schweppes",         330, 50.0),
        ColdDrink(98, "Wild Cherry Soda",    "Dr Pepper",         350, 60.0),
        ColdDrink(11, "Green Apple Sparkle", "Appy Fizz",         500, 40.0),
        ColdDrink(24, "Grape Punch",         "Fanta Grape",       400, 45.0),
        ColdDrink(37, "Peach Ice Soda",      "Lipton Sparkle",    450, 45.0),
        ColdDrink(50, "Watermelon Chill",    "Slice Summer",      500, 42.0),
        ColdDrink(63, "Pineapple Twist",     "Limca Tropical",    500, 35.0),
        ColdDrink(76, "Blue Raspberry Fizz", "Mountain Dew Blue", 500, 45.0),
        ColdDrink(89, "Strawberry Sparkle",  "Crush Berry",       350, 40.0),
        ColdDrink( 2, "Fresh Lime Soda",     "Kinley Club",       600, 25.0),
        ColdDrink(15, "Lychee Pop",          "Frooti Lychee",     300, 35.0),
        ColdDrink(28, "Passion Fruit Punch", "Paper Boat Spark",  250, 50.0),
        ColdDrink(41, "Blackcurrant Crush",  "Sting Berry",       250, 30.0),
        ColdDrink(54, "Guava Zing",          "Real Spiced Guava", 500, 45.0),
        ColdDrink(67, "Cream Vanilla Soda",  "A&W Cream Soda",    355, 55.0),
        ColdDrink(80, "Mint Mojito Cooler",  "Ocean Breeze",      500, 48.0)
    };

    cout << "\n>>> PHASE 1: SEQUENTIAL INSERTION OF PERSONALIZED 20-VALUE DATASET <<<" << endl;
    cout << "--------------------------------------------------------------------------" << endl;
    for (size_t i = 0; i < dataset.size(); ++i) {
        cout << "[Step " << setw(2) << (i + 1) << "/20] ";
        ht.insert(dataset[i]);
    }

    cout << "\n>>> PHASE 2: DISPLAY FULL HASH TABLE AFTER 20 INSERTIONS <<<" << endl;
    ht.display();
    ht.printStatistics();

    cout << ">>> PHASE 3: DUPLICATE KEY INSERTION TEST <<<" << endl;
    cout << "Attempting to insert duplicate Key 33 (Diet Cola):" << endl;
    ht.insert(ColdDrink(33, "Diet Cola", "Coca-Cola Zero", 500, 45.0));

    cout << "\n>>> PHASE 4: SEARCH OPERATIONS (HITS AND MISSES) <<<" << endl;
    int testSearchKeys[] = {2, 67, 85, 99};
    for (int key : testSearchKeys) {
        int comparisons = 0;
        ColdDrink* found = ht.searchFlavor(key, comparisons);
        if (found) {
            cout << "[SEARCH HIT ] Key " << setw(2) << key << " -> Found: " 
                 << setw(20) << left << found->flavorName 
                 << " | Brand: " << setw(18) << found->brand 
                 << " | Price: Rs." << found->price 
                 << " | Comparisons: " << comparisons << endl;
        } else {
            cout << "[SEARCH MISS] Key " << setw(2) << key << " -> Not found in table" 
                 << " | Comparisons: " << comparisons << endl;
        }
    }

    cout << "\n>>> PHASE 5: DELETION AND TABLE RE-VERIFICATION <<<" << endl;
    cout << "Deleting Key 59 (Interior node in Slot 8 chain)..." << endl;
    ht.deleteFlavor(59);

    cout << "\nVerifying table state after deletion:" << endl;
    ht.display();

    return 0;
}
