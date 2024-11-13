#include <stdio.h>

void Transactions(int numberoftransactions, int transactions[]);

void Transactions(int numberoftransactions, int transactions[]) {
    int balance = 1000; // pre defined balance 
    int notperformed[50]; // an array that  stores  transactions that didnt get performed 
    int notperformedCount = 0; // counting the number of  unperformed transactions

    printf("initial  balance: %d AED\n", balance);

    // Processing every transaction 
    for (int i = 0; i < numberoftransactions; i++) {
        int originalTransaction = transactions[i];
        printf("Transaction %d: %d AED\n", i + 1, originalTransaction);

        // the following code checks  if the transaction is a taking the MONEY OUT  or  and if there's enough balance
        if (originalTransaction < 0 && balance + originalTransaction < 0) {
            printf("not enough balance for transaction %d. Adding to unperformed transactions.\n", i + 1);
            notperformed[notperformedCount++] = originalTransaction;
            continue;
        }

        // Updating the balance 
        balance += originalTransaction;
        printf(" after updating  your balance is : %d AED\n", balance);

        // Stop if balance reaches 0 or goes in negative value 
        if (balance <= 0) {
            printf("your balance is 0 .\n");
            break;
        }
    }

    printf("\nyour final  balance is: %d AED\n", balance);

    // Displaying any  unperformed  transactions
    if (notperformedCount > 0) {
        printf("Unperformed transactions: ");
        for (int i = 0; i < notperformedCount; i++) {
            printf("%d AED ", notperformed[i]);
        }
        printf("\n");
    } else {
        printf("all of the  transactions became  successfully.\n");
    }
}

int main() {
    int numberoftransactions;

    // Getting number of transactions
    printf("give the  number of transactions: ");
    scanf("%d", &numberoftransactions);

    int transactions[numberoftransactions]; // an array that  stores all  transactions

    // Inputing the  transactions
    printf("give the transactions that you want to do  (positive for deposits, negative for withdrawals):\n");
    for (int i = 0; i < numberoftransactions; i++) {
        printf("Transaction %d: ", i + 1);
        scanf("%d", &transactions[i]);
    }

    //  final Processing of all  transactions 
    Transactions(numberoftransactions, transactions);

    return 0;
}
