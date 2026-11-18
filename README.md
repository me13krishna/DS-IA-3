# Cold Drink Flavor Inventory System (Hash Table with Separate Chaining)

**Student Name**: Krishna  
**PRN**: `202501100133`  
**Course**: Data Structures (Internal Assessment 3 / IA-3)  
**Repository**: [https://github.com/me13krishna/DS-IA-3](https://github.com/me13krishna/DS-IA-3)  

---

## 1. Personalization Key Derivation

| Parameter | Derivation Rule | Calculation | Assigned Value |
| :--- | :--- | :--- | :--- |
| **Domain Scenario** | $\text{PRN} \pmod 3$ | $202501100133 \pmod 3 = 0$ | **Cold-drink flavours** |
| **Dataset (20 values)** | Seed $S = \text{Last 4 digits}$<br>$v[i] = (S + 13i) \pmod{100}$ | $S = 133$<br>$i = 0 \dots 19$ | **`[33, 46, 59, 72, 85, 98, 11, 24, 37, 50, 63, 76, 89, 2, 15, 28, 41, 54, 67, 80]`** |
| **Hash Function** | Parity of PRN | $202501100133$ is **ODD** | **Mid-Square Method** |
| **Collision Strategy** | $\text{PRN} \pmod 2$ | $202501100133 \pmod 2 = 1$ | **Separate Chaining** |
| **Table Size ($m$)** | Decimal modular size | Standard decimal radix | **$m = 10$** (Slots $0 \dots 9$) |

---

## 2. File Structure

- **`cold_drink_hash_table.cpp`**: Main C++ source code with full header comments, domain structs, mid-square hash function, separate chaining linked lists, insertion, duplicate rejection, search, deletion, and diagnostic metrics.
- **`DEBUGGING_LOG.md`**: Engineering & debugging log containing 1 paragraph per commit (what was tried, what broke, failed approaches abandoned, and how it was fixed).
- **`TRACE_MATCH_REPORT.md`**: Complete mathematical breakdown of all 20 keys, hand-predicted table state vs. actual console output, and discrepancy analysis.
- **`GIT_LOG.txt`**: Git history export (`git log --stat`) detailing 7 genuine incremental milestones with full timestamps and file diffs.
- **`README.md`**: Project overview, compilation instructions, and 4-minute screen recording narration guide.

---

## 3. How to Compile and Run

### Prerequisites
- GCC / MinGW C++ compiler supporting C++11 or higher.

### Compilation
```bash
g++ -std=c++11 -Wall cold_drink_hash_table.cpp -o cold_drink_app
```

### Execution
```bash
./cold_drink_app
```

---

## 4. Video Recording Narration Guide (Max 4-Minute Walkthrough)

When recording your live screen capture for Task 10, follow this 4-step narration flow:

1. **Introduction (0:00 - 0:45)**:
   - State your Name and PRN: `202501100133`.
   - Explain the personalization derivation:
     - PRN mod 3 = 0 $\rightarrow$ Cold-drink flavours.
     - Seed $S = 133$ $\rightarrow$ 20 keys generated using $(133 + 13i) \pmod{100}$.
     - PRN is odd $\rightarrow$ Mid-Square Hash Function.
     - PRN mod 2 = 1 $\rightarrow$ Separate Chaining collision handling.

2. **Compilation & Insertion Execution (0:45 - 2:00)**:
   - Compile the code and run `./cold_drink_app`.
   - Point out Phase 1: show how each key is squared, its middle digit extracted, and placed into its hash slot.
   - Highlight collisions being resolved via separate chaining (e.g. Slot 8 chaining Key 33 $\rightarrow$ 59 $\rightarrow$ 72 $\rightarrow$ 28 $\rightarrow$ 41 $\rightarrow$ 67).

3. **Table State & Performance Metrics (2:00 - 3:00)**:
   - Walk through Phase 2: Show the visual bucket chains and the load factor $\alpha = \frac{20}{10} = 2.0$.
   - Highlight the trace-match: Slot 4 contains Key 2 ($2^2 = 4$, middle digit 4).
   - Point out the duplicate check in Phase 3 where attempting to re-insert Key 33 (Diet Cola) is rejected.

4. **Search, Deletion & Conclusion (3:00 - 4:00)**:
   - Show Phase 4: Successful search for Key 2 (1 comparison) vs Key 67 (6 comparisons in chain).
   - Show Phase 5: Deleting interior node 59 from Slot 8 and verifying that the remaining chain ($33 \to 72 \to 28 \to 41 \to 67$) stays intact with zero dangling pointers.
   - Mention the 7 incremental git commits and the debugging log.
