#include <stdio.h>

void processTransactions(int numTransactions, int transactions[]);

void processTransactions(int numTransactions, int transactions[]) {
    int balance = 1000; // Initial balance
    int unprocessed[50]; // Array to store unprocessed transactions
    int unprocessedCount = 0; // Count of unprocessed transactions

    printf("initial  balance: %d AED\n", balance);

    // Process each transaction
    for (int i = 0; i < numTransactions; i++) {
        int currentTransaction = transactions[i];
        printf("Transaction %d: %d AED\n", i + 1, currentTransaction);

        // Checking if the transaction is a withdrawal and if there's enough balance
        if (currentTransaction < 0 && balance + currentTransaction < 0) {
            printf("Insufficient balance for transaction %d. Adding to unprocessed transactions.\n", i + 1);
            unprocessed[unprocessedCount++] = currentTransaction;
            continue;
        }

        // Update balance
        balance += currentTransaction;
        printf(" balance after updating : %d AED\n", balance);

        // Stop if balance reaches 0 or goes negative
        if (balance <= 0) {
            printf("Balance has reached zero.\n");
            break;
        }
    }

    printf("\nFinal balance: %d AED\n", balance);

    // Display any unprocessed transactions
    if (unprocessedCount > 0) {
        printf("Unprocessed transactions: ");
        for (int i = 0; i < unprocessedCount; i++) {
            printf("%d AED ", unprocessed[i]);
        }
        printf("\n");
    } else {
        printf("All transactions processed successfully.\n");
    }
}

int main() {
    int numTransactions;

    // Get the number of transactions
    printf("give the  number of transactions: ");
    scanf("%d", &numTransactions);

    int transactions[numTransactions]; // Array to store transactions

    // Input transactions
    printf("give the transactions that you want to do  (positive for deposits, negative for withdrawals):\n");
    for (int i = 0; i < numTransactions; i++) {
        printf("Transaction %d: ", i + 1);
        scanf("%d", &transactions[i]);
    }

    // Processing all the transactions 
    processTransactions(numTransactions, transactions);

    return 0;
}
