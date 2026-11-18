# Engineering & Debugging Log
**Student Name**: Krishna  
**PRN**: 202501100133  
**Subject**: Data Structures - Internal Assessment 3 (IA-3)  
**Topic**: Hash Table Implementation (Cold-Drink Flavours, Mid-Square Method, Separate Chaining)  
**Repository**: [https://github.com/me13krishna/DS-IA-3](https://github.com/me13krishna/DS-IA-3)  

---

### Commit 1: Project Setup and Cold-Drink Domain Model Definition
- **What I tried**: Initialized the project repository and modeled the domain entity `ColdDrink` containing the attributes `flavorID` (primary key), `flavorName`, `brand`, `volumeML`, and `price`. Initially considered a flat, static array `ColdDrink table[TABLE_SIZE]` with a sentinel ID (`-1`) to represent empty slots.
- **What broke / Why abandoned**: While a flat static array works for open addressing (linear probing), my assigned collision resolution strategy is **Separate Chaining** (PRN mod 2 = 1). A flat static array cannot support dynamic chains without fixed re-allocation or auxiliary overflow tables, which leads to rigid capacity limits and memory waste.
- **How I fixed it**: Restructured the storage architecture into a bucket array of linked list heads (`HashNode* table[TABLE_SIZE]`), where each `HashNode` holds a `ColdDrink` object and a `HashNode* next` pointer initialized to `nullptr`. This provides unbounded separate chaining per bucket.

---

### Commit 2: Mid-Square Hash Function Implementation
- **What I tried**: Implemented the mid-square hash method to map keys to table indices $[0 \dots 9]$. Initially used pure integer arithmetic: `int hash = (sq / 10) % TABLE_SIZE`, assuming all squares would be at least 2 or 3 digits and that dividing by 10 would peel off the units place to reveal the central tens digit.
- **What broke / Why abandoned (Failed Approach)**: When testing with key $v[13] = 2$, its square is $4$. The expression `(4 / 10) % 10` evaluated to $0$, incorrectly placing key $2$ into bucket $0$. Pure division failed on single-digit squares and was uneven across 3-digit vs. 4-digit squares (e.g. $121$ vs $1089$).
- **How I fixed it**: Replaced the fixed arithmetic formula with dynamic digit inspection using `to_string(sq)`. By selecting the central index `midIdx = len / 2`, for length 1 (key 2, square 4, len 1) it selects index 0 ($'4'$), yielding slot 4; for length 3 (key 11, square 121) it selects index 1 ($'2'$), yielding slot 2; and for length 4 (key 33, square 1089) it selects index 2 ($'8'$), yielding slot 8. Verified with diagnostics.

---

### Commit 3: Direct Table Insertion without Collision Resolution
- **What I tried**: Implemented `insertWithoutCollisionHandling()` to verify insertion flow from the hash function into table buckets. Placed elements directly into `table[index]` and printed immediate table status.
- **What broke / Why abandoned**: When inserting multiple items hashing to the same bucket (e.g., Key 33 "Classic Cola" and Key 59 "Mango Blast" both hashing to Slot 8), the second insertion detected the occupied slot and overwrote the previous pointer. Displaying the table showed "Classic Cola" was completely lost, confirming that without collision resolution, hash tables suffer severe data corruption and memory leaks upon collision.
- **How I fixed it**: Documented the data-loss failure in console logs as an educational milestone. Identified that each bucket must maintain an active linked list chain instead of a singular slot pointer to preserve colliding items.


