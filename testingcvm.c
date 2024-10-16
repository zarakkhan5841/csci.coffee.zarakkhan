#include <stdio.h>
#include <stdlib.h>
#include <time.h>   


// Use variables for prices instead of #define
float espresso_price = 3.5;
float cappuccino_price = 4.5;
float mocha_price = 5.5;

#define ESPRESSO_BEANS 8
#define ESPRESSO_WATER 30

#define CAPPUCCINO_BEANS 8
#define CAPPUCCINO_WATER 30
#define CAPPUCCINO_MILK 70

#define MOCHA_BEANS 8
#define MOCHA_WATER 39
#define MOCHA_MILK 160
#define MOCHA_SYRUP 30

#define ADMIN_PASSWORD 1234
#define LOW_THRESHOLD 10  

float total_sales = 0.0;
int coffee_beans = 100;
int water = 500;
int milk = 300;
int syrup = 100;


void orderCoffee();
void adminMode();
void replenishIngredients();
void changePrices();
void displayIngredients();
void updateSales(float amount);

int main() {
    int choice;
    while (1) {
        printf("\n--- Coffee Maker Simulator ---\n");
        printf("1. Order a coffee\n");
        printf("2. Admin mode\n");
        printf("3. Exit\n");
        printf("Select an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                orderCoffee();
                break;
            case 2:
                adminMode();
                break;
            case 3:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}


void orderCoffee() {
    int selection, confirm;
    float price = 0.0;
    printf("\n--- Coffee Menu ---\n");

    if (coffee_beans >= ESPRESSO_BEANS && water >= ESPRESSO_WATER) {
        printf("1. Espresso - AED %.2f\n", espresso_price);
    } else {
        printf("1. Espresso - Unavailable\n");
    }

    if (coffee_beans >= CAPPUCCINO_BEANS && water >= CAPPUCCINO_WATER && milk >= CAPPUCCINO_MILK) {
        printf("2. Cappuccino - AED %.2f\n", cappuccino_price);
    } else {
        printf("2. Cappuccino - Unavailable\n");
    }

    if (coffee_beans >= MOCHA_BEANS && water >= MOCHA_WATER && milk >= MOCHA_MILK && syrup >= MOCHA_SYRUP) {
        printf("3. Mocha - AED %.2f\n", mocha_price);
    } else {
        printf("3. Mocha - Unavailable\n");
    }

    printf("Select coffee (0 to exit): ");
    scanf("%d", &selection);

    switch (selection) {
        case 0:
            return;
        case 1:
            if (coffee_beans >= ESPRESSO_BEANS && water >= ESPRESSO_WATER) {
                price = espresso_price;
            } else {
                printf("Espresso unavailable.\n");
                return;
            }
            break;
        case 2:
            if (coffee_beans >= CAPPUCCINO_BEANS && water >= CAPPUCCINO_WATER && milk >= CAPPUCCINO_MILK) {
                price = cappuccino_price;
            } else {
                printf("Cappuccino unavailable.\n");
                return;
            }
            break;
        case 3:
            if (coffee_beans >= MOCHA_BEANS && water >= MOCHA_WATER && milk >= MOCHA_MILK && syrup >= MOCHA_SYRUP) {
                price = mocha_price;
            } else {
                printf("Mocha unavailable.\n");
                return;
            }
            break;
        default:
            printf("Invalid selection.\n");
            return;
    }

    printf("You selected coffee priced at AED %.2f. Confirm? (1 for yes, 0 for no): ", price);
    scanf("%d", &confirm);
    if (confirm == 1) {
        float paid = 0.0, coin;
        while (paid < price) {
            printf("Insert coin (1 or 0.5 AED): ");
            scanf("%f", &coin);
            if (coin == 1 || coin == 0.5) {
                paid += coin;
                printf("Total paid: AED %.2f\n", paid);
            } else {
                printf("Invalid coin. Please insert valid coin.\n");
            }
        }

        if (selection == 1) { 
            coffee_beans -= ESPRESSO_BEANS;
            water -= ESPRESSO_WATER;
        } else if (selection == 2) { 
            coffee_beans -= CAPPUCCINO_BEANS;
            water -= CAPPUCCINO_WATER;
            milk -= CAPPUCCINO_MILK;
        } else if (selection == 3) { 
            coffee_beans -= MOCHA_BEANS;
            water -= MOCHA_WATER;
            milk -= MOCHA_MILK;
            syrup -= MOCHA_SYRUP;
        }

        printf("Coffee purchased. You paid AED %.2f. Change: AED %.2f\n", paid, paid - price);
        updateSales(price);

        if (coffee_beans <= LOW_THRESHOLD) printf("Alert: Low coffee beans!\n");
        if (water <= LOW_THRESHOLD) printf("Alert: Low water!\n");
        if (milk <= LOW_THRESHOLD) printf("Alert: Low milk!\n");
        if (syrup <= LOW_THRESHOLD) printf("Alert: Low syrup!\n");
    }
}


void adminMode() {
    int password, choice;
    printf("Enter admin password: ");
    scanf("%d", &password);

    if (password != ADMIN_PASSWORD) {
        printf("Incorrect password!\n");
        return;
    }

    while (1) {
        printf("\n--- Admin Menu ---\n");
        printf("1. Display ingredient levels\n");
        printf("2. Replenish ingredients\n");
        printf("3. Change coffee prices\n");
        printf("4. Reset total sales\n");
        printf("0. Exit admin mode\n");
        printf("Select an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayIngredients();
                break;
            case 2:
                replenishIngredients();
                break;
            case 3:
                changePrices();
                break;
            case 4:
                total_sales = 0.0;
                printf("Total sales reset. Don't forget to collect the money!\n");
                break;
            case 0:
                return;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
}


void displayIngredients() {
    printf("\n--- Ingredient Levels ---\n");
    printf("Coffee Beans: %d grams\n", coffee_beans);
    printf("Water: %d ml\n", water);
    printf("Milk: %d ml\n", milk);
    printf("Syrup: %d ml\n", syrup);
    printf("Total sales: AED %.2f\n", total_sales);
}


void replenishIngredients() {
    srand(time(0));
    coffee_beans = rand() % 100 + 50;
    water = rand() % 500 + 200;
    milk = rand() % 300 + 100;
    syrup = rand() % 100 + 50;
    printf("Ingredients replenished.\n");
}


void changePrices() {
    
    printf("Enter new price for Espresso (current: AED %.2f): ", espresso_price);
    scanf("%f", &espresso_price);

    printf("Enter new price for Cappuccino (current: AED %.2f): ", cappuccino_price);
    scanf("%f", &cappuccino_price);

    printf("Enter new price for Mocha (current: AED %.2f): ", mocha_price);
    scanf("%f", &mocha_price);

    printf("Prices updated successfully!\n");
}


void updateSales(float amount) {
    total_sales += amount;
}
