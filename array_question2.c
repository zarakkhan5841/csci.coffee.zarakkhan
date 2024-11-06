#include <stdio.h>

void process_transactions(int transactions[], int num_transactions) {
    
    int balance = 1000;
    int tobeprocessed[100];  
    int tobeprocessed_count = 0; 

   
    for (int i = 0; i < num_transactions; i++) {
        int transaction = transactions[i];

        if (transaction < 0) {  
            if (balance + transaction < 0) {  
                printf("Invalid transaction: Withdrawal of %d AED exceeds current balance of %d AED.\n", -transaction, balance);
                tobeprocessed[tobeprocessed_count++] = transaction;  
                continue; 
            } else {
                balance += transaction;  
            }
        } else {  
            balance += transaction;  
        }

        
        if (balance == 0) {
            printf("Balance has reached 0. No further transactions will be processed.\n");
            
            for (int j = i + 1; j < num_transactions; j++) {
                tobeprocessed[tobeprocessed_count++] = transactions[j];
            }
            break;
        }
    }

    
    printf("\nFinal Balance: %d AED\n", balance);

    if (tobeprocessed_count > 0) {
        printf("\nUnprocessed Transactions:\n");
        for (int i = 0; i < tobeprocessed_count; i++) {
            printf("%d AED\n", tobeprocessed[i]);
        }
    }
}

int main() {
    
    int transactions[] = {200, -150, -500, -400, -50, -200, 300};
    int num_transactions = sizeof(transactions) / sizeof(transactions[0]);

    
    process_transactions(transactions, num_transactions);

    return 0;
}
