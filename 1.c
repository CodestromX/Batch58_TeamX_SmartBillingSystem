#include <stdio.h>
#include <string.h>

#define TOTAL_ITEMS 6

/* Structure to hold each food item's details */
struct FoodItem {
    int id;
    char name[25];
    float price;
    int stock;
    int cartQty;   // how many plates/cups are currently in the cart
};

/* Menu data (starts with 0 items in cart) */
struct FoodItem menu[TOTAL_ITEMS] = {
    {1, "Masala Maggi",      50.0,  40, 0},
    {2, "Cheese Sandwich",   70.0,  30, 0},
    {3, "Paneer Kathi Roll", 120.0, 25, 0},
    {4, "Rajma Chawal",      110.0, 35, 0},
    {5, "Cold Coffee",       80.0,  40, 0},
    {6, "Masala Chai",       20.0,  60, 0}
};

/* Daily tracking variables */
int tokenNo = 101;
int totalOrders = 0;
float totalSales = 0.0;

/* Function declarations */
int readNumber();
void showMenu();
void addItem();
void viewOrRemoveCart();
void printBill();
void showSalesSummary();

/* ==================== MAIN PROGRAM ==================== */
int main() {
    int choice;

    printf("========================================\n");
    printf("     UPES SMART CANTEEN BILLING APP     \n");
    printf("========================================\n");

    do {
        printf("\n-------------- MAIN MENU ---------------\n");
        printf("1. View Menu\n");
        printf("2. Add Item to Cart\n");
        printf("3. View / Remove Cart Items\n");
        printf("4. Generate Bill\n");
        printf("5. View Daily Sales Summary\n");
        printf("6. Exit\n");
        printf("----------------------------------------\n");
        printf("Enter choice (1-6): ");

        choice = readNumber();

        switch (choice) {
            case 1:
                showMenu();
                break;
            case 2:
                addItem();
                break;
            case 3:
                viewOrRemoveCart();
                break;
            case 4:
                printBill();
                break;
            case 5:
                showSalesSummary();
                break;
            case 6:
                printf("\nThank you for using UPES Smart Canteen!\n");
                break;
            default:
                printf("Wrong choice! Please enter 1 to 6.\n");
        }
    } while (choice != 6);

    return 0;
}

/* Helper: Reads a number safely (prevents crash if letters are typed) */
int readNumber() {
    int num;
    while (scanf("%d", &num) != 1) {
        while (getchar() != '\n');   // clears wrong text input
        printf("Invalid input! Enter a number: ");
    }
    return num;
}

/* Option 1: Print all items with price and stock */
void showMenu() {
    printf("\n=========== UPES CANTEEN MENU ===========\n");
    printf("ID  Item Name             Price     Stock\n");
    printf("-----------------------------------------\n");

    for (int i = 0; i < TOTAL_ITEMS; i++) {
        printf("%-3d %-20s  Rs.%-6.2f %d\n",
               menu[i].id, menu[i].name, menu[i].price, menu[i].stock);
    }

    printf("=========================================\n");
    printf("* 10%% Student Discount on bills >= Rs.250!\n");
}

/* Option 2: Add an item to the cart */
void addItem() {
    showMenu();

    printf("\nEnter Item ID to add (0 to cancel): ");
    int id = readNumber();

    if (id == 0) {
        return;
    }
    if (id < 1 || id > TOTAL_ITEMS) {
        printf("Invalid ID! Choose between 1 and %d.\n", TOTAL_ITEMS);
        return;
    }

    int i = id - 1; // ID 1 is stored at index 0

    if (menu[i].stock == 0) {
        printf("Sorry, %s is out of stock!\n", menu[i].name);
        return;
    }

    printf("Enter quantity for %s (Available: %d): ", menu[i].name, menu[i].stock);
    int qty = readNumber();

    if (qty < 1 || qty > menu[i].stock) {
        printf("Invalid quantity! Enter between 1 and %d.\n", menu[i].stock);
        return;
    }

    /* Update cart and reduce available stock */
    menu[i].cartQty = menu[i].cartQty + qty;
    menu[i].stock = menu[i].stock - qty;

    printf("Added %d x %s to cart!\n", qty, menu[i].name);
}

/* Option 3: Show cart and optionally remove an item */
void viewOrRemoveCart() {
    float subtotal = 0.0;
    int hasItems = 0;

    printf("\n=============== YOUR CART ===============\n");
    printf("ID  Item Name             Qty   Amount\n");
    printf("-----------------------------------------\n");

    for (int i = 0; i < TOTAL_ITEMS; i++) {
        if (menu[i].cartQty > 0) {
            float amount = menu[i].price * menu[i].cartQty;
            subtotal = subtotal + amount;
            hasItems = 1;

            printf("%-3d %-20s  %-5d Rs.%.2f\n",
                   menu[i].id, menu[i].name, menu[i].cartQty, amount);
        }
    }

    if (hasItems == 0) {
        printf("Your cart is empty!\n");
        return;
    }

    printf("-----------------------------------------\n");
    printf("Subtotal: Rs.%.2f\n", subtotal);

    printf("\nEnter Item ID to remove (0 to go back): ");
    int id = readNumber();

    if (id == 0) {
        return;
    }
    if (id < 1 || id > TOTAL_ITEMS || menu[id - 1].cartQty == 0) {
        printf("That item is not in your cart!\n");
        return;
    }

    int i = id - 1;
    menu[i].stock = menu[i].stock + menu[i].cartQty; // put stock back
    menu[i].cartQty = 0;                             // remove from cart
    printf("Removed %s from cart.\n", menu[i].name);
}

/* Option 4: Apply discount + GST and print the final receipt */
void printBill() {
    float subtotal = 0.0;

    /* Calculate subtotal from all items in cart */
    for (int i = 0; i < TOTAL_ITEMS; i++) {
        subtotal = subtotal + (menu[i].price * menu[i].cartQty);
    }

    if (subtotal == 0.0) {
        printf("\nCart is empty! Add items before billing.\n");
        return;
    }

    char customerName[30];
    char sapId[20];
    char paymentMode[15];

    printf("\nEnter Customer First Name: ");
    scanf("%29s", customerName);

    /* Ask if customer is a UPES student */
    printf("Are you a UPES Student? (1 = Yes, 0 = No): ");
    int isStudent = readNumber();

    if (isStudent == 1) {
        while (1) {
            printf("Enter 9-digit SAP ID: ");
            scanf("%19s", sapId);

            /* Check length is 9 and every character is a digit */
            int valid = 1;
            if (strlen(sapId) != 9) {
                valid = 0;
            } else {
                for (int i = 0; i < 9; i++) {
                    if (sapId[i] < '0' || sapId[i] > '9') {
                        valid = 0;
                        break;
                    }
                }
            }

            if (valid == 1) {
                break;
            } else {
                printf("Invalid SAP ID! Must be 9 digits (e.g., 500123456).\n");
            }
        }
    } else {
        strcpy(sapId, "Guest");
    }

    /* Choose payment method */
    printf("Payment Mode (1. UPI  2. Cash  3. Campus Card): ");
    int pay = readNumber();

    if (pay == 1) {
        strcpy(paymentMode, "UPI");
    } else if (pay == 2) {
        strcpy(paymentMode, "Cash");
    } else {
        strcpy(paymentMode, "Campus Card");
    }

    /* Calculate discount, GST, and final total */
    float discount = 0.0;
    if (isStudent == 1 && subtotal >= 250.0) {
        discount = subtotal * 0.10; // 10% student discount
    }

    float afterDiscount = subtotal - discount;
    float gst = afterDiscount * 0.05; // 5% GST
    float grandTotal = afterDiscount + gst;

    /* Print receipt */
    printf("\n=========================================\n");
    printf("        UPES UNIVERSITY FOOD COURT       \n");
    printf("              CANTEEN RECEIPT            \n");
    printf("=========================================\n");
    printf("Token No. : #%d\n", tokenNo);
    printf("Customer  : %s\n", customerName);
    printf("SAP ID    : %s\n", sapId);
    printf("Payment   : %s\n", paymentMode);
    printf("-----------------------------------------\n");
    printf("Item Name             Qty   Total\n");
    printf("-----------------------------------------\n");

    for (int i = 0; i < TOTAL_ITEMS; i++) {
        if (menu[i].cartQty > 0) {
            printf("%-20s  %-5d Rs.%.2f\n",
                   menu[i].name, menu[i].cartQty, menu[i].price * menu[i].cartQty);
        }
    }

    printf("-----------------------------------------\n");
    printf("Subtotal              : Rs.%.2f\n", subtotal);
    if (discount > 0) {
        printf("Student Discount (10%%):-Rs.%.2f\n", discount);
    }
    printf("GST (5%%)              : Rs.%.2f\n", gst);
    printf("=========================================\n");
    printf("GRAND TOTAL           : Rs.%.2f\n", grandTotal);
    printf("=========================================\n");
    printf("Collect your order at Counter 1 on Token #%d!\n", tokenNo);

    /* Save daily totals and empty the cart for the next order */
    tokenNo++;
    totalOrders++;
    totalSales = totalSales + grandTotal;

    for (int i = 0; i < TOTAL_ITEMS; i++) {
        menu[i].cartQty = 0;
    }
}

/* Option 5: Show total orders and money earned today */
void showSalesSummary() {
    printf("\n========== DAILY SALES SUMMARY ==========\n");
    printf("Total Orders Served : %d\n", totalOrders);
    printf("Total Revenue       : Rs.%.2f\n", totalSales);
    printf("=========================================\n");
}