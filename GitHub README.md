# Smart Billing System: UPES Campus Canteen & Token Management

> **C Programming Lab – Mini Hackathon Project**  
> **Repository Naming Convention:** `Batch58_Team_SmartBillingSystem`

---

## 👥 Team Details

* **Batch:** `[Batch Number 58]`  
* **Team Number:** `[Enter Team Number, e.g., Team 04]`  
* **Team Members:**  
  1. `[Pratham ]` – `[590032909]`  
  2. `[Raman Bhatia]` – `[590035675]`  
  3. `[Soumil Batra]` – `[590036185]`

---

## 📌 Problem Statement & Objective

Traditional manual billing in busy university food courts leads to slow queues, calculation errors, unmonitored food stock, and difficulty verifying student-only discounts.

**Objective:**  
To design and implement a fast, menu-driven **Smart Billing System** in C that automates order taking, tracks real-time item inventory, validates 9-digit UPES Student SAP IDs for automatic discount eligibility, calculates GST, issues sequential counter pickup tokens, and summarizes daily canteen sales.

---

## ✨ Key Features

* **Live Inventory Tracking:** Automatically deducts stock when items are added to the cart and restores stock if items are removed before checkout.  
* **Interactive Cart Management:** View subtotal in real time or remove unwanted items before generating the final bill.  
* **UPES Student Verification:** Validates 9-digit numeric SAP IDs and automatically applies a **10% Student Discount** on orders of `Rs. 250` or above.  
* **Automated Tax & Token Generation:** Computes `5% GST` on the discounted total and assigns an auto-incrementing order token (`#101`, `#102`, ...) for counter pickup.  
* **Multiple Payment Modes:** Supports **UPI**, **Cash**, and **Campus Card** logging on the receipt.  
* **Crash-Proof Input Validation:** Safely handles non-numeric characters entered into numeric prompts without causing infinite loops or crashes.  
* **Daily Sales Summary:** Tracks total orders served and cumulative revenue earned during the session.

---

## 🛠️ C Programming Concepts Used

| Concept | Implementation in Project |
| :---- | :---- |
| **Structures (`struct`)** | `struct FoodItem` groups item ID, name, price, available stock, and cart quantity. |
| **Arrays of Structures** | `menu[TOTAL_ITEMS]` stores and updates the complete canteen catalog in memory. |
| **User-Defined Functions** | Modular functions (`showMenu()`, `addItem()`, `viewOrRemoveCart()`, `printBill()`, `showSalesSummary()`, `readNumber()`) separate core responsibilities. |
| **Loops (`do-while`, `for`, `while`)** | Drives the main interactive menu, iterates through cart/menu items, and re-prompts on invalid SAP IDs or inputs. |
| **Conditional Statements (`if-else`, `switch`)** | Controls menu routing, stock availability checks, student discount rules, and payment mode selection. |
| **Strings (`<string.h>`)** | Uses `strlen()` and `strcpy()` to validate SAP ID length and store customer/payment metadata. |
| **Input Buffer Handling** | Uses `scanf()` return checking and `getchar()` buffer clearing inside `readNumber()` for robust input validation. |

---

## 🧠 Program Logic / Algorithm

1. **Initialize:** Load the predefined menu array with item IDs, names, prices, initial stock, and `0` cart quantity. Set `tokenNo = 101`, `totalOrders = 0`, and `totalSales = 0.0`.  
2. **Display Main Menu:** Present options `1` through `6` inside a `do-while` loop until the user chooses to exit.  
3. **Add to Cart (Option 2):**  
   * Validate item ID (`1` to `6`) and check if `stock > 0`.  
   * Validate requested quantity (`1 <= qty <= stock`).  
   * Increment `cartQty` and decrement `stock`.  
4. **View / Remove Cart (Option 3):**  
   * Display all items where `cartQty > 0` and calculate the running subtotal.  
   * If the user chooses to remove an item, add `cartQty` back to `stock` and reset `cartQty = 0`.  
5. **Generate Bill (Option 4):**  
   * Ensure cart is non-empty. Read customer name and student status.  
   * If student (`1`), validate that SAP ID has exact length `9` and contains only digits (`0–9`).  
   * Select payment mode (`UPI`, `Cash`, or `Campus Card`).  
   * If `isStudent == 1` and `subtotal >= 250.0`, apply `10%` discount.  
   * Calculate `5%` GST on the post-discount amount and print the formatted receipt with `tokenNo`.  
   * Increment `tokenNo` and `totalOrders`, add `grandTotal` to `totalSales`, and reset all `cartQty` values to `0`.  
6. **Sales Summary (Option 5):** Display `totalOrders` and `totalSales`.

---

## 🚀 How to Compile and Run

### Prerequisites

* A C compiler such as **GCC** (MinGW on Windows, GCC on Linux/macOS) or an IDE like Code::Blocks / Dev-C++ / VS Code.

### Compilation & Execution (Terminal / Command Prompt)

```c
# 1. Clone the repository
git clone https://github.com/CodestromX/Batch58_TeamX_SmartBillingSystem.git

# 2. Navigate into the project directory
cd Batch58_TeamX_SmartBillingSystem

# 3. Compile the C source file
gcc 1.c -o smart_billing

# 4. Run the executable
./smart_billing        # On Linux / macOS
smart_billing.exe      # On Windows
```

---

## 🧪 Sample Test Cases

| Test Case ID | Scenario | Input Provided | Expected Output | Status |
| :---- | :---- | :---- | :---- | :---- |
| **TC-01** | View Menu | Choice: `1` | Displays all 6 items with prices, current stock, and discount note. | Pass |
| **TC-02** | Add Valid Item | Choice: `2` $\rightarrow$ ID: `3` $\rightarrow$ Qty: `2` | Adds `2 x Paneer Kathi Roll` (`Rs. 240.00`) to cart; reduces stock from `25` to `23`. | Pass |
| **TC-03** | Boundary Stock Check | Choice: `2` $\rightarrow$ ID: `3` $\rightarrow$ Qty: `24` (when stock is `23`) | Displays `"Invalid quantity! Enter between 1 and 23."` | Pass |
| **TC-04** | Invalid Non-Numeric Input | Choice: `abc` | Clears buffer and prompts `"Invalid input! Enter a number: "` without crashing. | Pass |
| **TC-05** | Invalid SAP ID Validation | Student: `1` $\rightarrow$ SAP ID: `50012A` (6 chars / letter) | Rejects input and prompts `"Invalid SAP ID! Must be 9 digits (e.g., 500123456)."` | Pass |
| **TC-06** | Student Discount Applied | Cart Subtotal: `Rs. 260.00`, Student: `1`, Valid 9-digit SAP ID | Applies `10%` discount (`-Rs. 26.00`), adds `5%` GST (`Rs. 11.70`), Grand Total: `Rs. 245.70`, assigns Token `#101`. | Pass |
| **TC-07** | Checkout with Empty Cart | Choice: `4` (with 0 items in cart) | Displays `"Cart is empty! Add items before billing."` | Pass |

---

## 📸 Sample Output

```
=========================================
        UPES UNIVERSITY FOOD COURT       
              CANTEEN RECEIPT            
=========================================
Token No. : #101
Customer  : Aarav
SAP ID    : 500123456
Payment   : UPI
-----------------------------------------
Item Name             Qty   Total
-----------------------------------------
Paneer Kathi Roll     2     Rs.240.00
Masala Chai           1     Rs.20.00
-----------------------------------------
Subtotal              : Rs.260.00
Student Discount (10%):-Rs.26.00
GST (5%)              : Rs.11.70
=========================================
GRAND TOTAL           : Rs.245.70
=========================================
Collect your order at Counter 1 on Token #101!
```

---

## 📂 Repository Structure

```
BatchXX_TeamXX_SmartBillingSystem/
├── README.md
├── 1.c
└── presentation.pptx
```

&nbsp;