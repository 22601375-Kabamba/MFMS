#include <stdio.h>

double calculateRemaining(double budget, double spent);
int isWithinBudget(double budget, double spent);

int main() {
    char departments[20][50];
    double allocated[20];
    double expenditure[20];
    int count = 0;
    int choice;

    do {
        printf("\n=== MUNICIPAL BUDGET MANAGEMENT ===\n");
        printf("1. Add Department Budget\n");
        printf("2. Display All Budgets\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            if (count < 20) {
                printf("\nEnter department name: ");
                scanf("%s", departments[count]);

                printf("Enter allocated budget: ");
                scanf("%lf", &allocated[count]);

                printf("Enter current expenditure: ");
                scanf("%lf", &expenditure[count]);

                count++;
            } else {
                printf("\nMaximum department limit reached!\n");
            }
        } else if (choice == 2) {
            if (count == 0) {
                printf("\nNo budget records found.\n");
            } else {
                printf("\n--- Department Budgets ---\n");
                for (int i = 0; i < count; i++) {
                    double rem = calculateRemaining(allocated[i], expenditure[i]);
                    printf("\nDepartment: %s\n", departments[i]);
                  printf("Allocated: (%.2f ) | Spent: $%.2f | Remaining: $%.2f\n", 
                          allocated[i], expenditure[i], rem);

                    if (isWithinBudget(allocated[i], expenditure[i])) {
                        printf("Status: Within Budget\n");
                    } else {
                        printf("Status: OVER BUDGET!\n");
                    }
                }
            }
        } else if (choice == 3) {
            printf("\nExiting program...\n");
        } else {
            printf("\nInvalid choice. Try again.\n");
        }

    } while (choice != 3);

    return 0;
}

double calculateRemaining(double budget, double spent) {
    return budget - spent;
}

int isWithinBudget(double budget, double spent) {
    if (spent <= budget) {
        return 1;
    } else {
        return 0;
    }
}