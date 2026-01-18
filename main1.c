#include <stdio.h>
#include <stdlib.h>

struct Account {
    int accNo;
    char name[50];
    float balance;
};

void createAccount();
void deposit();
void withdraw();
void balanceEnquiry();

int main() {
    int choice;

    do {
        printf("\n===== Bank Account Management System =====\n");
        printf("1. Create Account\n");
        printf("2. Deposit Money\n");
        printf("3. Withdraw Money\n");
        printf("4. Balance Enquiry\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: createAccount(); break;
            case 2: deposit(); break;
            case 3: withdraw(); break;
            case 4: balanceEnquiry(); break;
            case 0: printf("Thank you for using the banking system.\n"); break;
            default: printf("Invalid choice!\n");
        }
    } while (choice != 0);

    return 0;
}

void createAccount() {
    FILE *fp;
    struct Account a;

    fp = fopen("accounts.dat", "ab");
    if (fp == NULL) {
        printf("File error!\n");
        return;
    }

    printf("Enter Account Number: ");
    scanf("%d", &a.accNo);
    printf("Enter Account Holder Name: ");
    scanf(" %[^\n]", a.name);
    printf("Enter Initial Balance: ");
    scanf("%f", &a.balance);

    fwrite(&a, sizeof(a), 1, fp);
    fclose(fp);

    printf("Account created successfully.\n");
}

void deposit() {
    FILE *fp;
    struct Account a;
    int accNo, found = 0;
    float amount;

    fp = fopen("accounts.dat", "rb+");
    if (fp == NULL) {
        printf("File not found.\n");
        return;
    }

    printf("Enter Account Number: ");
    scanf("%d", &accNo);

    while (fread(&a, sizeof(a), 1, fp)) {
        if (a.accNo == accNo) {
            printf("Enter amount to deposit: ");
            scanf("%f", &amount);

            a.balance += amount;
            fseek(fp, -sizeof(a), SEEK_CUR);
            fwrite(&a, sizeof(a), 1, fp);

            printf("Deposit successful.\n");
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Account not found.\n");

    fclose(fp);
}

void withdraw() {
    FILE *fp;
    struct Account a;
    int accNo, found = 0;
    float amount;

    fp = fopen("accounts.dat", "rb+");
    if (fp == NULL) {
        printf("File not found.\n");
        return;
    }

    printf("Enter Account Number: ");
    scanf("%d", &accNo);

    while (fread(&a, sizeof(a), 1, fp)) {
        if (a.accNo == accNo) {
            printf("Enter amount to withdraw: ");
            scanf("%f", &amount);

            if (amount > a.balance) {
                printf("Insufficient balance.\n");
            } else {
                a.balance -= amount;
                fseek(fp, -sizeof(a), SEEK_CUR);
                fwrite(&a, sizeof(a), 1, fp);
                printf("Withdrawal successful.\n");
            }
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Account not found.\n");

    fclose(fp);
}

void balanceEnquiry() {
    FILE *fp;
    struct Account a;
    int accNo, found = 0;

    fp = fopen("accounts.dat", "rb");
    if (fp == NULL) {
        printf("File not found.\n");
        return;
    }

    printf("Enter Account Number: ");
    scanf("%d", &accNo);

    while (fread(&a, sizeof(a), 1, fp)) {
        if (a.accNo == accNo) {
            printf("\nAccount Holder: %s\n", a.name);
            printf("Current Balance: %.2f\n", a.balance);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Account not found.\n");

    fclose(fp);
}
