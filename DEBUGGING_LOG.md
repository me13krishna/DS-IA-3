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

---

### Commit 4: Implement Separate Chaining Collision Resolution
- **What I tried**: Implemented dynamic linked list chaining in `insert()`. When an incoming key hashes to an occupied bucket, the function traverses the existing chain using a pointer `curr` until reaching the last node (`curr->next == nullptr`), then attaches the new `HashNode`.
- **What broke / Why abandoned**: In an early iteration of the while loop, wrote `while (curr != nullptr) { curr = curr->next; } curr->next = newNode;`. Because `curr` became `nullptr` upon exiting the loop, dereferencing `curr->next` triggered an immediate Segmentation Fault / Access Violation exception.
- **How I fixed it**: Fixed the traversal invariant to check `while (curr->next != nullptr)` instead of `curr != nullptr`, keeping `curr` firmly pointing to the valid terminal node of the chain before appending `newNode`. Added an explicit check for empty buckets (`table[index] == nullptr`) to handle head initialization cleanly.

---

### Commit 5: Implement Search and Delete Operations with Chain Traversal
- **What I tried**: Implemented `searchFlavor(key, comparisons)` and `deleteFlavor(key)` by navigating linked lists within hashed buckets. For deletion, traversed until finding the matching flavor ID, deleted the node, and updated adjacent pointers.
- **What broke / Why abandoned**: In the first deletion implementation, I simply updated `curr = curr->next; delete curr;` without holding a reference to `prev`. When deleting an interior node (e.g. Key 59 positioned between Key 33 and Key 72 in Slot 8), deleting `curr` orphaned the subsequent chain (Key 72 was severed from the bucket), creating an irreversible dangling pointer and memory leak.
- **How I fixed it**: Maintained a trailing pointer `prev` initialized to `nullptr`. When `curr` matches the target key, the logic checks if `prev == nullptr` (head deletion: `table[index] = curr->next`) or `prev != nullptr` (interior/tail deletion: `prev->next = curr->next`). Verified by searching for Key 72 immediately following the deletion of Key 59 to ensure the chain remains fully intact.

---

### Commit 6: Populate 20 Personalized Keys and Test Duplicate Key Handling
- **What I tried**: Loaded the complete 20-value personalized dataset derived from PRN `202501100133` ($S=133$, $v[i]=(133+13i)\pmod{100}$) mapped to authentic cold-drink flavours. Executed batch insertion into the hash table and implemented duplicate key rejection.
- **What broke / Why abandoned**: During preliminary duplicate insertion testing, attempting to insert a duplicate flavor ID (Key 33 with a modified flavor name "Diet Cola") successfully appended to the end of bucket 8. This produced two differing entities with identical primary keys, violating relational and associative integrity in the table.
- **How I fixed it**: Integrated a pre-insertion traversal step within `insert()` that examines the existing linked list in `table[index]`. If `check->data.flavorID == drink.flavorID`, insertion immediately halts, returning `false` alongside an alert `[DUPLICATE REJECTED]`. Verified that duplicate Key 33 is blocked while valid unique keys chain seamlessly.





