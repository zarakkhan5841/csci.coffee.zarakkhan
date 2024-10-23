#include <stdio.h>   // we use this for printf and scanf 
#include <stdlib.h> // we use this for rand function 
#include <time.h>   // we use this for time 

// coffee ingredients requried to make the cofee  and prices  as per the question 
#define ESPRESSO_BEANS 8
#define ESPRESSO_WATER 30
float ESPRESSO_COST = 3.5;

#define CAPPUCCINO_BEANS 8
#define CAPPUCCINO_WATER 30
#define CAPPUCCINO_MILK 70
float CAPPUCCINO_COST = 4.5;

#define MOCHA_BEANS 8
#define MOCHA_WATER 39
#define MOCHA_MILK 160
#define MOCHA_SYRUP 30
float MOCHA_COST = 5.5;

#define ADMIN_PASSWORD 1234
#define LOW_THRESHOLD 10  // lowest ingredient level the vending machine will store before giving a warning . 

// pre defined stock and sales as per the question 
float total_sales = 0.0;
int coffee_beans = 100;
int water = 500;
int milk = 300;
int syrup = 100;

// all of the function prototypes used 
void handleOrder();   
void adminPanel();
void refillStock();
void adjustPrices();
void displayInventory();
void updateTotalSales(float amount);

int main() {
    int menuChoice;

    while (1) {
        printf("\n    ==  Coffee Machine  ==   \n");  // displays the main menu of the machine 
        printf("1. Buy Coffee\n");
        printf("2. Admin Panel\n");
        printf("3. Exit\n");
        printf("Please select an option: ");
        scanf("%d", &menuChoice);

        switch (menuChoice) {         
            case 1:
                handleOrder();    // for ordering the coffee 
                break;
            case 2:
                adminPanel();     // for managing ingredients restock , coffee prices , reset total sales, view cofee prices etc 
                break;
            case 3:
                printf("Goodbye!\n");   // to exit the page 
                exit(0);
            default:
                printf("Invalid option. Try again.\n");
        }
    }

    return 0;
}

// to order a coffee the below function is used 
void handleOrder() {
    int coffeeChoice, confirmOrder;
    float coffeePrice = 0.0;

    printf("\n--- Coffee Menu ---\n");

    // the below if statment displays avaiable coffee and displays a warning is the coffee is not avaiable 
    if (coffee_beans >= ESPRESSO_BEANS && water >= ESPRESSO_WATER) {
        printf("1. Espresso - AED %.2f\n", ESPRESSO_COST);
    } else {
        printf("1. Espresso is Not available\n");
    }

    if (coffee_beans >= CAPPUCCINO_BEANS && water >= CAPPUCCINO_WATER && milk >= CAPPUCCINO_MILK) {
        printf("2. Cappuccino - AED %.2f\n", CAPPUCCINO_COST);
    } else {
        printf("2. Cappuccino is Not available\n");
    }

    if (coffee_beans >= MOCHA_BEANS && water >= MOCHA_WATER && milk >= MOCHA_MILK && syrup >= MOCHA_SYRUP) {
        printf("3. Mocha - AED %.2f\n", MOCHA_COST);
    } else {
        printf("3. Mocha is Not available\n");
    }

    printf("Select coffee (0 to cancel): "); 
    scanf("%d", &coffeeChoice);

    // the below switch statment checks the ingredient avablity and displays the prices 
    switch (coffeeChoice) {
        case 0:
            return; // No selection, exit function
        case 1:
            if (coffee_beans >= ESPRESSO_BEANS && water >= ESPRESSO_WATER) {
                coffeePrice = ESPRESSO_COST;
            } else {
                printf("Sorry, Espresso is out of stock.\n");
                return;
            }
            break;
        case 2:
            if (coffee_beans >= CAPPUCCINO_BEANS && water >= CAPPUCCINO_WATER && milk >= CAPPUCCINO_MILK) {
                coffeePrice = CAPPUCCINO_COST;
            } else {
                printf("Sorry, Cappuccino is out of stock.\n");
                return;
            }
            break;
        case 3:
            if (coffee_beans >= MOCHA_BEANS && water >= MOCHA_WATER && milk >= MOCHA_MILK && syrup >= MOCHA_SYRUP) {
                coffeePrice = MOCHA_COST;
            } else {
                printf("Sorry, Mocha is out of stock.\n");
                return;
            }
            break;
        default:
            printf("Invalid selection.\n");
            return;
    }

    // to confirm the order the below printf is printed 
    printf("Your coffee costs AED %.2f. Confirm order? (1 = Yes, 0 = No): ", coffeePrice);
    scanf("%d", &confirmOrder);

    if (confirmOrder == 1) {
        float paidAmount = 0.0, coin;

        // the below while loop keeps running and displays the insert coin option until the payment is completed 
        while (paidAmount < coffeePrice) {
            printf("Insert coin (1 or 0.5 AED): ");
            scanf("%f", &coin);

            if (coin == 1 || coin == 0.5) {
                paidAmount += coin;
                printf("Amount paid: AED %.2f\n", paidAmount);
            } else {
                printf("Invalid coin. Please insert a valid amount.\n");
            }
        }

        // the below switch statment subtracts( - ) the ingredients from the original ingredients level 
        switch (coffeeChoice) {
            case 1: // for Espresso
                coffee_beans -= ESPRESSO_BEANS;
                water -= ESPRESSO_WATER;
                break;
            case 2: // for Cappuccino
                coffee_beans -= CAPPUCCINO_BEANS;
                water -= CAPPUCCINO_WATER;
                milk -= CAPPUCCINO_MILK;
                break;
            case 3: // for  Mocha
                coffee_beans -= MOCHA_BEANS;
                water -= MOCHA_WATER;
                milk -= MOCHA_MILK;
                syrup -= MOCHA_SYRUP;
                break;
        }

        // this printf statment displays the leftover change and reciept 
        printf("Thank you for your purchase ,  You paid AED %.2f. \n", paidAmount);
        updateTotalSales(coffeePrice);

        // if the ingredients level is below the threshold value then the below if statments are printed 
        if (coffee_beans <= LOW_THRESHOLD) printf("Warning: Low coffee beans!\n");
        if (water <= LOW_THRESHOLD) printf("Warning: Low water!\n");
        if (milk <= LOW_THRESHOLD) printf("Warning: Low milk!\n");
        if (syrup <= LOW_THRESHOLD) printf("Warning: Low syrup!\n");
    }
}

// the below function is used for handeling the admin mode .
void adminPanel() {
    int passwordInput, adminChoice;

    printf("Enter admin password: ");    // this is displayed to enter the password 
    scanf("%d", &passwordInput);

    if (passwordInput != ADMIN_PASSWORD) {
        printf("Access denied: incorrect password.\n");    // this is displayed if the password is incorrect 
        return;
    }

    // after the correct password is entered the below menu is printed 
    while (1) {
        printf("\n--- Admin Menu ---\n");
        printf("1. View ingredient levels\n");
        printf("2. Restock ingredients\n");
        printf("3. Modify coffee prices\n");
        printf("4. Reset sales\n");
        printf("0. Exit admin menu\n");
        printf("Choose an option: ");
        scanf("%d", &adminChoice);

        switch (adminChoice) {     // this opens the function based on the admin menu selection 
            case 1:
                displayInventory();
                break;
            case 2:
                refillStock();
                break;
            case 3:
                adjustPrices();
                break;
            case 4:
                total_sales = 0.0;
                printf("Sales total reset. Please collect earnings.\n");
                break;
            case 0:
                return;
            default:
                printf("Invalid selection. Try again.\n");
        }
    }
}

// the below function displays the current ingredients level 
void displayInventory() {
    printf("\n--- Ingredient Levels ---\n");
    printf("Coffee Beans: %d grams\n", coffee_beans);
    printf("Water: %d ml\n", water);
    printf("Milk: %d ml\n", milk);
    printf("Syrup: %d ml\n", syrup);
    printf("Total Sales: AED %.2f\n", total_sales);
}

// the below function is used to refill the stock 
void refillStock() {
    srand(time(0));
    coffee_beans = rand() % 100 + 50; // refills coffee beans between 50g and 150g
    water = rand() % 500 + 200;       // refills the water between 200ml to 700ml 
    milk = rand() % 300 + 100;        // refills the milk between 100 ml to 400 ml 
    syrup = rand() % 100 + 50;        // refills the syrup between 50ml to 150 ml 
    printf("Ingredients have been restocked.\n");
}

// the below function is used to update total sales after the coffee is purchased 
void updateTotalSales(float amount) {
    total_sales += amount;
}

// the below function is used to adjust the prices 
void adjustPrices() {
    int coffeeChoice;
    float newPrice;

    printf("\n--- Adjust Coffee Prices ---\n");
    printf("1. Espresso (current price: AED %.2f)\n", ESPRESSO_COST);
    printf("2. Cappuccino (current price: AED %.2f)\n", CAPPUCCINO_COST);
    printf("3. Mocha (current price: AED %.2f)\n", MOCHA_COST);
    printf("Select the coffee you want to change the price for (0 to cancel): ");
    scanf("%d", &coffeeChoice);

    // using the switch statment we can change the price of specific coffee
    switch (coffeeChoice) {
        case 0:
            return; // the function is excited if 0 is pressed 
        case 1:
            printf("Enter the new price for Espresso: ");
            scanf("%f", &newPrice);
            if (newPrice > 0) { // if the new price is greater than 0  the espresso price will be updated 
                ESPRESSO_COST = newPrice;
                printf("New price for Espresso is set to AED %.2f\n", ESPRESSO_COST);
            } else {
                printf("Invalid price. Price must be greater than 0.\n");
            }
            break;
        case 2:
            printf("Enter the new price for Cappuccino: ");
            scanf("%f", &newPrice);
            if (newPrice > 0) { // if the new price is greater than 0 then cappuccino price will be updated 
                CAPPUCCINO_COST = newPrice;
                printf("New price for Cappuccino is set to AED %.2f\n", CAPPUCCINO_COST);
            } else {
                printf("Invalid price. Price must be greater than 0.\n");
            }
            break;
        case 3:
            printf("Enter the new price for Mocha: ");
            scanf("%f", &newPrice);
            if (newPrice > 0) { // if the new price is greater than 0 then mocha price will be updated 
                MOCHA_COST = newPrice;
                printf("New price for Mocha is set to AED %.2f\n", MOCHA_COST);
            } else {
                printf("Invalid price. Price must be greater than 0.\n");
            }
            break;
        default:
            printf("Invalid selection.\n");   // if wrong selection 
            return;
    }
}
