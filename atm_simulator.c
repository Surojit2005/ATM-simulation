#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_TRANSACTIONS 100


typedef struct {
    int account_number;
    char name[50];
    float balance;
    int pin;
    char transactions[MAX_TRANSACTIONS][100];
    int transaction_count;
} Account;


void checkBalance(Account *acc);
void deposit(Account *acc);
void withdraw(Account *acc);
void transfer(Account *acc, Account *recipient);
void transactionHistory(Account *acc);
int verifyPIN(Account *acc);
void setPIN(Account *acc);

int main() {
    Account user = {123456, "Surojit Paul", 8500.0, 0, {"Account Created"}, 1};
    Account recipient = {654321, "Steve Smith", 5500.0, 5678, {"Account Created"}, 1};
    int choice;

    printf("Set your 4-digit PIN");
    setPIN(&user);

    while (1) {
        printf("\nATM Menu:\n");
        printf("1. Check Balance\n");
        printf("2. Deposit\n");
        printf("3. Withdraw\n");
        printf("4. Transfer\n");
        printf("5. Transaction History\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                checkBalance(&user);
                break;
            case 2:
                deposit(&user);
                break;
            case 3:
                withdraw(&user);
                break;
            case 4:
                transfer(&user, &recipient);
                break;
            case 5:
                transactionHistory(&user);
                break;
            case 6:
                printf("Thank you for using the ATM. Goodbye!\n");
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    return 0;
}

void checkBalance(Account *acc) {
    printf("\nCurrent Balance: Rs. %.2f", acc->balance);
}

void deposit(Account *acc) {
    float amount;
    printf("\nEnter deposit amount (Rs.): ");
    scanf("%f", &amount);
    if (amount <= 0) {
        printf("Invalid amount!\n");
        return;
    }
    acc->balance += amount;
    snprintf(acc->transactions[acc->transaction_count++], 100, "Deposited: Rs. %.2f", amount);
    printf("Deposit successful! New balance: Rs. %.2f\n", acc->balance);
}

void withdraw(Account *acc) {
    if (!verifyPIN(acc)) return;

    float amount;
    printf("\nEnter withdrawal amount (Rs.): ");
    scanf("%f", &amount);
    if (amount <= 0 || amount > acc->balance) {
        printf("Invalid amount or insufficient funds!\n");
        return;
    }
    acc->balance -= amount;
    snprintf(acc->transactions[acc->transaction_count++], 100, "Withdrew: Rs. %.2f", amount);
    printf("Withdrawal successful! New balance: Rs. %.2f\n", acc->balance);
}

void transfer(Account *acc, Account *recipient) {
    if (!verifyPIN(acc)) return;

    float amount;
    printf("\nEnter transfer amount (Rs.): ");
    scanf("%f", &amount);
    if (amount <= 0 || amount > acc->balance) {
        printf("Invalid amount or insufficient funds!\n");
        return;
    }
    acc->balance -= amount;
    recipient->balance += amount;
    snprintf(acc->transactions[acc->transaction_count++], 100, "Transferred: Rs. %.2f to %s", amount, recipient->name);
    snprintf(recipient->transactions[recipient->transaction_count++], 100, "Received: Rs. %.2f from %s", amount, acc->name);
    printf("Transfer successful! New balance: Rs. %.2f\n", acc->balance);
}

void transactionHistory(Account *acc) {
    printf("\nTransaction History:\n");
    for (int i = 0; i < acc->transaction_count; i++) {
        printf("%d. %s\n", i + 1, acc->transactions[i]);
    }
}

int verifyPIN(Account *acc) {
    int enteredPin;
    printf("\nEnter 4-digit PIN: ");
    scanf("%d", &enteredPin);
    if (enteredPin == acc->pin) {
        return 1;
    } else {
        printf("Incorrect PIN!\n");
        return 0;
    }
}

void setPIN(Account *acc) {
    int pin;
    do {
        printf("\nEnter a 4-digit PIN: ");
        scanf("%d", &pin);
    } while (pin < 1000 || pin > 9999);
    acc->pin = pin;
    printf("PIN set successfully!\n");
}
