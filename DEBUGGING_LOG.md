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
