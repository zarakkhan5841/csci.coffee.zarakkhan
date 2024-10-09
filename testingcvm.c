#include <stdio.h>
#include <stdlib.h>

#define ESPRESSO_BEANS 8
#define ESPRESSO_WATER 30
#define ESPRESSO_PRICE 3.5
#define CAPPUCCINO_BEANS 8
#define CAPPUCCINO_WATER 30
#define CAPPUCCINO_MILK 70
#define CAPPUCCINO_PRICE 4.5
#define MOCHA_BEANS 8
#define MOCHA_WATER 39
#define MOCHA_MILK 160
#define MOCHA_SYRUP 30
#define MOCHA_PRICE 5.5
#define ADMIN_PASSWORD 1234
#define LOW_THRESHOLD 10  

float total_sales = 0.0;
int coffee_beans = 200;
int water = 300;
int milk = 350;
int syrup = 150;

void orderCoffee();
void adminMode();
void replenishIngredients();
void changePrices();
void displayIngredients();
void updateSales(float amount);

int main() {
    int choice;
    while (1) {
        printf("\n-- Coffee Vending Machine --\n");
        printf("1. Give coffee\n");
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
                printf("Quitting...\n");
                exit(0);
            default:
                printf("Wrong Input. Please try again.\n");
        }
    }
    return 0;
}

void orderCoffee() {
    int selection, confirm;
    float price = 0.0;
    printf("\n--- Coffee Menu ---\n");

    if (coffee_beans >= ESPRESSO_BEANS && water >= ESPRESSO_WATER) {
        printf("1. Espresso - AED %.2f\n", ESPRESSO_PRICE);
    } else {
        printf("1. Espresso - Unavailable\n");
    }

    if (coffee_beans >= CAPPUCCINO_BEANS && water >= CAPPUCCINO_WATER && milk >= CAPPUCCINO_MILK) {
        printf("2. Cappuccino - AED %.2f\n", CAPPUCCINO_PRICE);
    } else {
        printf("2. Cappuccino - Unavailable\n");
    }

    if (coffee_beans >= MOCHA_BEANS && water >= MOCHA_WATER && milk >= MOCHA_MILK && syrup >= MOCHA_SYRUP) {
        printf("3. Mocha - AED %.2f\n", MOCHA_PRICE);
    } else {
        printf("3. Mocha - Unavailable\n");
    }

    printf("Select the coffee that you want to order (0 to quit): ");
    scanf("%d", &selection);

    switch (selection) {
        case 0:
            return; 
        case 1:
            if (coffee_beans >= ESPRESSO_BEANS && water >= ESPRESSO_WATER) {
                price = ESPRESSO_PRICE;
            } else {
                printf("Espresso is not available.\n");
                return;
            }
            break;
        case 2:
            if (coffee_beans >= CAPPUCCINO_BEANS && water >= CAPPUCCINO_WATER && milk >= CAPPUCCINO_MILK) {
                price = CAPPUCCINO_PRICE;
            } else {
                printf("Cappuccino is not available.\n");
                return;
            }
            break;
        case 3:
            if (coffee_beans >= MOCHA_BEANS && water >= MOCHA_WATER && milk >= MOCHA_MILK && syrup >= MOCHA_SYRUP) {
                price = MOCHA_PRICE;
            } else {
                printf("Mocha is not available.\n");
                return;
            }
            break;
        default:
            printf("YOUR SELECTION IS WRONG.\n");
            return;
    }

    printf("The price of your coffee is AED %.2f. Confirm? (1 for yes, 0 for no): ", price);
    scanf("%d", &confirm);
    if (confirm == 1) {
        float paid = 0.0, coin;
        while (paid < price) {
            printf("INSERT MONEY, only put - 1 or 0.5 AED: ");
            scanf("%f", &coin);
            if (coin == 1 || coin == 0.5) {
                paid += coin;
                printf("Total paid: AED %.2f\n", paid);
            } else {
                printf("INVALID COIN TYPE. Please insert a valid coin.\n");
            }
        }
        
        if (selection == 1) { // Espresso
            coffee_beans -= ESPRESSO_BEANS;
            water -= ESPRESSO_WATER;
        } else if (selection == 2) { // Cappuccino
            coffee_beans -= CAPPUCCINO_BEANS;
            water -= CAPPUCCINO_WATER;
            milk -= CAPPUCCINO_MILK;
        } else if (selection == 3) { // Mocha
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

