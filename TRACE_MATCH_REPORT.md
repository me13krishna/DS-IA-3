# Trace-Match Report: Hash Table Verification
**Student Name**: Krishna  
**PRN**: 202501100133  
**Subject**: Data Structures - Internal Assessment 3 (IA-3)  
**Topic**: Hash Table Implementation (Cold-Drink Flavours, Mid-Square Method, Separate Chaining)  
**Repository**: [https://github.com/me13krishna/DS-IA-3](https://github.com/me13krishna/DS-IA-3)  

---

## 1. Personalization Key Derivation Summary

| Parameter | Rule / Derivation | Calculation | Assigned Outcome |
| :--- | :--- | :--- | :--- |
| **Domain Scenario** | $\text{PRN} \pmod 3$ | $202501100133 \pmod 3 = 0$ | **Cold-drink flavours** |
| **Dataset Seed ($S$)** | Last 4 digits of PRN | Last 4 digits of $202501100133$ | $S = 133$ |
| **Dataset ($20$ values)** | $v[i] = (S + 13 \times i) \pmod{100}$ | For $i = 0, \dots, 19$ | **[33, 46, 59, 72, 85, 98, 11, 24, 37, 50, 63, 76, 89, 2, 15, 28, 41, 54, 67, 80]** |
| **Hash Function** | PRN parity | $202501100133$ is **ODD** | **Mid-Square Method** |
| **Collision Policy** | $\text{PRN} \pmod 2$ | $202501100133 \pmod 2 = 1$ | **Separate Chaining** |
| **Table Size ($m$)** | Standard modular bucket count | Standard decimal radix | $m = 10$ (Slots $0 \dots 9$) |

---

## 2. Mid-Square Mathematical Derivation (All 20 Keys)

For each key $k \in v$:
1. Compute the square: $k^2$.
2. Inspect the digit representation of $k^2$ of length $L$.
3. Extract the middle digit at zero-based index $\lfloor L / 2 \rfloor$.
4. Compute slot index: $\text{Hash}(k) = \text{mid\_digit} \pmod{10}$.

| Step $i$ | Key ($k$) | Flavor Name | $k^2$ | Length ($L$) | Mid Index $\lfloor L/2 \rfloor$ | Middle Digit | Hash Slot |
| :---: | :---: | :--- | :---: | :---: | :---: | :---: | :---: |
| 0 | **33** | Classic Cola | $1089$ | 4 | 2 | **8** | **Slot 8** |
| 1 | **46** | Lemon Lime Fizz | $2116$ | 4 | 2 | **1** | **Slot 1** |
| 2 | **59** | Mango Blast | $3481$ | 4 | 2 | **8** | **Slot 8** |
| 3 | **72** | Orange Sunset | $5184$ | 4 | 2 | **8** | **Slot 8** |
| 4 | **85** | Ginger Beer Ale | $7225$ | 4 | 2 | **2** | **Slot 2** |
| 5 | **98** | Wild Cherry Soda | $9604$ | 4 | 2 | **0** | **Slot 0** |
| 6 | **11** | Green Apple Sparkle | $121$ | 3 | 1 | **2** | **Slot 2** |
| 7 | **24** | Grape Punch | $576$ | 3 | 1 | **7** | **Slot 7** |
| 8 | **37** | Peach Ice Soda | $1369$ | 4 | 2 | **6** | **Slot 6** |
| 9 | **50** | Watermelon Chill | $2500$ | 4 | 2 | **0** | **Slot 0** |
| 10 | **63** | Pineapple Twist | $3969$ | 4 | 2 | **6** | **Slot 6** |
| 11 | **76** | Blue Raspberry Fizz | $5776$ | 4 | 2 | **7** | **Slot 7** |
| 12 | **89** | Strawberry Sparkle | $7921$ | 4 | 2 | **2** | **Slot 2** |
| 13 | **2** | Fresh Lime Soda | $4$ | 1 | 0 | **4** | **Slot 4** |
| 14 | **15** | Lychee Pop | $225$ | 3 | 1 | **2** | **Slot 2** |
| 15 | **28** | Passion Fruit Punch | $784$ | 3 | 1 | **8** | **Slot 8** |
| 16 | **41** | Blackcurrant Crush | $1681$ | 4 | 2 | **8** | **Slot 8** |
| 17 | **54** | Guava Zing | $2916$ | 4 | 2 | **1** | **Slot 1** |
| 18 | **67** | Cream Vanilla Soda | $4489$ | 4 | 2 | **8** | **Slot 8** |
| 19 | **80** | Mint Mojito Cooler | $6400$ | 4 | 2 | **0** | **Slot 0** |

---

## 3. Hand-Predicted vs. Actual Table State

### A. Hand Prediction (Prior to Program Run)
*Predicted using chronological tail-insertion (FIFO) separate chaining:*
- **Slot 0**: `[ID: 98] -> [ID: 50] -> [ID: 80] -> NULL`
- **Slot 1**: `[ID: 46] -> [ID: 54] -> NULL`
- **Slot 2**: `[ID: 85] -> [ID: 11] -> [ID: 89] -> [ID: 15] -> NULL`
- **Slot 3**: `EMPTY`
- **Slot 4**: `[ID: 2] -> NULL` *(or `EMPTY` under naive division)*
- **Slot 5**: `EMPTY`
- **Slot 6**: `[ID: 37] -> [ID: 63] -> NULL`
- **Slot 7**: `[ID: 24] -> [ID: 76] -> NULL`
- **Slot 8**: `[ID: 33] -> [ID: 59] -> [ID: 72] -> [ID: 28] -> [ID: 41] -> [ID: 67] -> NULL`
- **Slot 9**: `EMPTY`

---

### B. Actual Program Console Output (Captured)

```text
================== Cold Drink Flavor Hash Table (Separate Chaining) ==================
Slot [0]:  -> [ID: 98 | Wild Cherry Soda (Dr Pepper, Rs.60.00)] -> [ID: 50 | Watermelon Chill (Slice Summer, Rs.42.00)] -> [ID: 80 | Mint Mojito Cooler (Ocean Breeze, Rs.48.00)] -> NULL
Slot [1]:  -> [ID: 46 | Lemon Lime Fizz (Sprite, Rs.35.00)] -> [ID: 54 | Guava Zing (Real Spiced Guava, Rs.45.00)] -> NULL
Slot [2]:  -> [ID: 85 | Ginger Beer Ale (Schweppes, Rs.50.00)] -> [ID: 11 | Green Apple Sparkle (Appy Fizz, Rs.40.00)] -> [ID: 89 | Strawberry Sparkle (Crush Berry, Rs.40.00)] -> [ID: 15 | Lychee Pop (Frooti Lychee, Rs.35.00)] -> NULL
Slot [3]: EMPTY
Slot [4]:  -> [ID: 2  | Fresh Lime Soda (Kinley Club, Rs.25.00)] -> NULL
Slot [5]: EMPTY
Slot [6]:  -> [ID: 37 | Peach Ice Soda (Lipton Sparkle, Rs.45.00)] -> [ID: 63 | Pineapple Twist (Limca Tropical, Rs.35.00)] -> NULL
Slot [7]:  -> [ID: 24 | Grape Punch (Fanta Grape, Rs.45.00)] -> [ID: 76 | Blue Raspberry Fizz (Mountain Dew Blue, Rs.45.00)] -> NULL
Slot [8]:  -> [ID: 33 | Classic Cola (Coca-Cola, Rs.40.00)] -> [ID: 59 | Mango Blast (Maaza, Rs.38.00)] -> [ID: 72 | Orange Sunset (Mirinda, Rs.35.00)] -> [ID: 28 | Passion Fruit Punch (Paper Boat Spark, Rs.50.00)] -> [ID: 41 | Blackcurrant Crush (Sting Berry, Rs.30.00)] -> [ID: 67 | Cream Vanilla Soda (A&W Cream Soda, Rs.55.00)] -> NULL
Slot [9]: EMPTY
======================================================================================
```

---

## 4. Trace-Match Comparison & Discrepancy Analysis

| Slot | Hand-Predicted Chain | Actual Program Output Chain | Match Status | Notes / Discrepancies |
| :---: | :--- | :--- | :---: | :--- |
| **0** | $98 \to 50 \to 80$ | $98 \to 50 \to 80$ | **PERFECT MATCH** | All 3 keys have square mid-digit 0. |
| **1** | $46 \to 54$ | $46 \to 54$ | **PERFECT MATCH** | Keys 46 ($2116$) and 54 ($2916$) both yield mid-digit 1. |
| **2** | $85 \to 11 \to 89 \to 15$ | $85 \to 11 \to 89 \to 15$ | **PERFECT MATCH** | Keys 85, 11, 89, 15 all yield mid-digit 2. |
| **3** | `EMPTY` | `EMPTY` | **PERFECT MATCH** | No key produced middle digit 3. |
| **4** | $2$ *(or naive $0$)* | $2$ | **RESOLVED DISCREPANCY** | **See Discrepancy 1 below.** |
| **5** | `EMPTY` | `EMPTY` | **PERFECT MATCH** | No key produced middle digit 5. |
| **6** | $37 \to 63$ | $37 \to 63$ | **PERFECT MATCH** | Keys 37 ($1369$) and 63 ($3969$) yield mid-digit 6. |
| **7** | $24 \to 76$ | $24 \to 76$ | **PERFECT MATCH** | Keys 24 ($576$) and 76 ($5776$) yield mid-digit 7. |
| **8** | $33 \to 59 \to 72 \to 28 \to 41 \to 67$ | $33 \to 59 \to 72 \to 28 \to 41 \to 67$ | **PERFECT MATCH** | Heaviest bucket (chain length 6). |
| **9** | `EMPTY` | `EMPTY` | **PERFECT MATCH** | No key produced middle digit 9. |

---

### Detailed Analysis of Identified Discrepancies

#### Discrepancy 1: Key 2 Placement (Naive Integer Division vs. String Digit Extraction)
- **Observed Phenomenon**: In preliminary hand calculations, a simplified arithmetic formula `(sq / 10) % 10` was initially tested. For Key $2$, $2^2 = 4$. Evaluating $(4 / 10) \pmod{10}$ yielded $0$, which incorrectly predicted Key $2$ residing in **Slot 0** (forming chain $98 \to 50 \to 2 \to 80$).
- **Actual Program Output**: Key $2$ is placed in **Slot 4**.
- **Root Cause & Resolution**: Mid-square extraction mathematically requires isolating the center of the number's digit string. For the single-digit square $4$, its string length is $1$, and its middle character index is $\lfloor 1 / 2 \rfloor = 0$, giving the digit $'4'$ ($\text{Slot } 4$). Pure integer division `(sq / 10)` assumed the number has at least 2 digits and incorrectly truncated $4$ to $0$. The implementation was updated to inspect digit length dynamically, resolving the mismatch and placing Key $2$ into Slot 4.

#### Discrepancy 2: Node Order within Chains (LIFO Head vs. FIFO Tail Insertion)
- **Observed Phenomenon**: If hand prediction is performed assuming classic singly-linked-list head insertion ($O(1)$ prepend), the predicted chain for Slot 8 would appear in reverse order:
  $$\text{LIFO (Head)}: 67 \to 41 \to 28 \to 72 \to 59 \to 33$$
- **Actual Program Output**:
  $$\text{FIFO (Tail)}: 33 \to 59 \to 72 \to 28 \to 41 \to 67$$
- **Root Cause & Resolution**: Head insertion reverses insertion order. To maintain chronological flavor intake order in inventory logs, the C++ implementation appends incoming collided elements to the tail of the list. Once the hand prediction is adjusted for tail insertion, the predicted and actual chains match identically across all slots.

---

## 5. Summary Statistics

- **Total Buckets ($m$)**: 10
- **Total Records ($n$)**: 20
- **Load Factor ($\alpha = n/m$)**: $\frac{20}{10} = 2.00$
- **Non-Empty Buckets**: 7 / 10
- **Empty Buckets**: 3 / 10 (Slots 3, 5, 9)
- **Longest Chain**: Slot 8 (6 elements: 33, 59, 72, 28, 41, 67)
- **Duplicate Prevention**: Verified (Key 33 re-insertion blocked)
- **Search Complexity**: Average successful search length $= \frac{1 + 2 + \dots + 6}{20} \approx 2.45$ comparisons.
