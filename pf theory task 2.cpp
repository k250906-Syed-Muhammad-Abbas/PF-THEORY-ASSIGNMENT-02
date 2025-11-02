#include <string.h> 
#include <stdio.h>
#include <stdlib.h>

char customerCNIC[20];
char customerName[50];
char productCode[4][4] = {"001", "002", "003", "004"};
int productCount[4] = {50, 10, 20, 8};
int productPrice[4] = {100, 200, 300, 150};
char cartProductCode[10][4];
int cartProductCount[10] = {0}; 
int cartSize = 0;
float appliedDiscount = 0.0;
float finalTotal = 0.0;

void getCustomerDetails();
void displayInventory();
void addItemToCart();
void updateInventory();
void displayTotalBill();
void showInvoice();
void displayCart();

void getCustomerDetails() {
    printf("\n===== CUSTOMER INFORMATION =====\n");
    printf("PLEASE ENTER YOUR CNIC NUMBER(NO SPACES):\t");
    scanf("%s", customerCNIC);
    printf("PLEASE ENTER YOUR NAME:\t");
    scanf(" %[^\n]", customerName);
    printf("\nWELCOME, %s!\n", customerName);
}

void displayInventory() {
    printf("\n===== CURRENT INVENTORY =====\n");
    printf("-----------------------------------------------\n");
    printf("| %-14s | %-13s | %-8s |\n", "PRODUCT CODE", "PRICE (RS.)", "STOCK");
    printf("-----------------------------------------------\n");
    for (int i = 0; i < 4; i++) {
        printf("| %-14s | %-13d | %-8d |\n", productCode[i], productPrice[i], productCount[i]);
    }
    printf("-----------------------------------------------\n");
}

void displayCart() {
    if (cartSize == 0) {
        printf("\nYOUR CART IS EMPTY.\n");
        return;
    }
    printf("\n===== YOUR CART =====\n");
    printf("-----------------------------------------------\n");
    printf("| %-14s | %-13s | %-8s |\n", "PRODUCT CODE", "PRICE (RS.)", "QUANTITY");
    printf("-----------------------------------------------\n");
    for (int i = 0; i < cartSize; i++) {
        for (int j = 0; j < 4; j++) {
            if (strcmp(cartProductCode[i], productCode[j]) == 0) {
                printf("| %-14s | %-13d | %-8d |\n", cartProductCode[i], productPrice[j], cartProductCount[i]);
                break;
            }
        }
    }
    printf("-----------------------------------------------\n");
}

void addItemToCart() {
    char inputCode[4];
    int quantity;
    int productIndex = -1;
    int cartIndex = -1;

    printf("\n===== ADD ITEM TO CART =====\n");
    printf("ENTER PRODUCT CODE:\t");
    scanf("%s", inputCode);

    for (int i = 0; i < 4; i++) {
        if (strcmp(productCode[i], inputCode) == 0) {
            productIndex = i;
            break;
        }
    }

    if (productIndex == -1) {
        printf("ERROR: PRODUCT CODE '%s' NOT FOUND!\n", inputCode);
        return;
    }

    for (int i = 0; i < cartSize; i++) {
        if (strcmp(cartProductCode[i], inputCode) == 0) {
            cartIndex = i;
            break;
        }
    }

    printf("ENTER QUANTITY: ");
    scanf("%d", &quantity);

    if (quantity <= 0) {
        printf("ERROR: QUANTITY MUST BE GREATER THAN 0!\n");
        return;
    }

    if (quantity > productCount[productIndex]) {
        printf("ERROR: ONLY %d ITEMS AVAILABLE IN STOCK!\n", productCount[productIndex]);
        return;
    }

    if (cartIndex == -1) {
        strcpy(cartProductCode[cartSize], inputCode);
        cartProductCount[cartSize] = quantity;
        cartSize++;
    } else {
        cartProductCount[cartIndex] += quantity;
    }

    productCount[productIndex] -= quantity;

    printf("? SUCCESSFULLY ADDED %d UNIT(S) OF %s TO CART!\n", quantity, inputCode);
    displayCart();
}

void updateInventory() {
    char inputCode[4];
    int newQuantity;
    int found = 0;

    printf("\n===== UPDATE INVENTORY =====\n");
    printf("ENTER PRODUCT CODE TO UPDATE:\t");
    scanf("%s", inputCode);

    for (int i = 0; i < 4; i++) {
        if (strcmp(productCode[i], inputCode) == 0) {
            found = 1;
            printf("CURRENT QUANTITY OF %s: %d\n", inputCode, productCount[i]);
            printf("ENTER NEW QUANTITY:\t");
            scanf("%d", &newQuantity);

            if (newQuantity < 0) {
                printf("ERROR: QUANTITY CANNOT BE NEGATIVE!\n");
                return;
            }

            productCount[i] = newQuantity;
            printf("? INVENTORY UPDATED SUCCESSFULLY!\n");
            printf("NEW QUANTITY OF %s: %d\n", inputCode, productCount[i]);
            break;
        }
    }

    if (!found) {
        printf("ERROR: PRODUCT CODE '%s' NOT FOUND!\n", inputCode);
    }
}

void displayTotalBill() {
    float totalBill = 0.0;
    char promoCode[20];

    if (cartSize == 0) {
        printf("\nYOUR CART IS EMPTY! ADD ITEMS FIRST.\n");
        return;
    }

    printf("\n===== BILL SUMMARY =====\n");
    printf("---------------------------------------------------------------\n");
    printf("| %-12s | %-10s | %-8s | %-12s |\n", "PRODUCT", "PRICE (RS.)", "QTY", "SUBTOTAL");
    printf("---------------------------------------------------------------\n");

    for (int i = 0; i < cartSize; i++) {
        for (int j = 0; j < 4; j++) {
            if (strcmp(cartProductCode[i], productCode[j]) == 0) {
                float subtotal = cartProductCount[i] * productPrice[j];
                printf("| %-12s | %-10d | %-8d | %-12.2f |\n", cartProductCode[i], productPrice[j], cartProductCount[i], subtotal);
                totalBill += subtotal;
                break;
            }
        }
    }

    printf("---------------------------------------------------------------\n");
    printf("SUBTOTAL: RS. %.2f\n", totalBill);

    printf("\nDO YOU HAVE A PROMO CODE? (ENTER CODE OR TYPE 'NO'): ");
    scanf("%s", promoCode);

    if (strcmp(promoCode, "Eid2025") == 0) {
        appliedDiscount = totalBill * 0.25;
        finalTotal = totalBill - appliedDiscount;
        printf("\n? PROMO CODE 'Eid2025' APPLIED SUCCESSFULLY!\n");
        printf("DISCOUNT (25%%): RS. %.2f\n", appliedDiscount);
        printf("\n========================================\n");
        printf("   FINAL TOTAL: RS. %.2f\n", finalTotal);
        printf("========================================\n");
    } else {
        appliedDiscount = 0.0;
        finalTotal = totalBill;
        if (strcmp(promoCode, "NO") != 0 && strcmp(promoCode, "no") != 0) {
            printf("\n? INVALID PROMO CODE.\n");
        }
        printf("\n========================================\n");
        printf("   TOTAL: RS. %.2f\n", finalTotal);
        printf("========================================\n");
    }
}

void showInvoice() {
    if (cartSize == 0) {
        printf("\nNO ITEMS TO SHOW IN INVOICE! ADD ITEMS TO CART FIRST.\n");
        return;
    }

    float totalWithoutDiscount = 0.0;

    printf("\n================================================================\n");
    printf("                           INVOICE                              \n");
    printf("================================================================\n");
    printf("CUSTOMER NAME: %s\n", customerName);
    printf("CUSTOMER CNIC: %s\n", customerCNIC);
    printf("================================================================\n");
    printf("| %-12s | %-10s | %-8s | %-12s |\n", "PRODUCT", "PRICE (RS.)", "QTY", "SUBTOTAL");
    printf("----------------------------------------------------------------\n");

    for (int i = 0; i < cartSize; i++) {
        for (int j = 0; j < 4; j++) {
            if (strcmp(cartProductCode[i], productCode[j]) == 0) {
                float subtotal = cartProductCount[i] * productPrice[j];
                printf("| %-12s | %-10d | %-8d | %-12.2f |\n", cartProductCode[i], productPrice[j], cartProductCount[i], subtotal);
                totalWithoutDiscount += subtotal;
                break;
            }
        }
    }

    printf("================================================================\n");
    printf("TOTAL (WITHOUT DISCOUNT): RS. %.2f\n", totalWithoutDiscount);
    if (appliedDiscount > 0) {
        printf("DISCOUNT APPLIED (25%%):   RS. %.2f\n", appliedDiscount);
        printf("----------------------------------------------------------------\n");
        printf("FINAL AMOUNT (WITH DISCOUNT): RS. %.2f\n", finalTotal);
    } else {
        printf("DISCOUNT APPLIED:         RS. 0.00\n");
        printf("----------------------------------------------------------------\n");
        printf("FINAL AMOUNT:             RS. %.2f\n", finalTotal);
    }
    printf("================================================================\n");
    printf("       THANK YOU FOR SHOPPING WITH US!                          \n");
    printf("================================================================\n");
}

int main() {
    int choice;
    getCustomerDetails();

    do {
        printf("\n\n===== SUPERMARKET INVENTORY SYSTEM =====\n");
        printf("1. DISPLAY INVENTORY\n");
        printf("2. ADD ITEM TO CART\n");
        printf("3. UPDATE INVENTORY\n");
        printf("4. DISPLAY TOTAL BILL\n");
        printf("5. SHOW INVOICE\n");
        printf("6. VIEW CART\n");
        printf("7. EXIT\n");
        printf("========================================\n");
        printf("ENTER YOUR CHOICE: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                system("cls");
                displayInventory();
                break;
            case 2:
                system("cls");
                addItemToCart();
                break;
            case 3:
                system("cls");
                updateInventory();
                break;
            case 4:
                system("cls");
                displayTotalBill();
                break;
            case 5:
                system("cls");
                showInvoice();
                break;
            case 6:
                system("cls");
                displayCart();
                break;
            case 7:
                system("cls");
                printf("\nTHANK YOU FOR USING OUR SYSTEM!\n");
                printf("GOODBYE, %s!\n", customerName);
                break;
            default:
                system("cls");
                printf("\n? INVALID CHOICE! PLEASE SELECT 1–7.\n");
        }
    } while (choice != 7);
    
    return 0;
}

