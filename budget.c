#include <stdio.h>
#include <string.h>
#include "budget.h"

#define MAX_DEPARTMENTS 25
#define DEPT_NAME_SIZE  55

#define PINK  "\033[38;5;213m"
#define RESET "\033[0m"

static char   departments[MAX_DEPARTMENTS][DEPT_NAME_SIZE];
static double allocated[MAX_DEPARTMENTS];
static double expenditure[MAX_DEPARTMENTS];
static int    departmentCount = 0;


static void budgetClearBuffer(void)
{
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) { }
}

static void budgetPause(void)
{
    printf("\nPress Enter to continue...");
    getchar();
}

static int budgetGetInt(const char prompt[], int min, int max)
{
    int number, result;

    while (1) {
        printf("%s", prompt);
        result = scanf("%d", &number);
        if (result == EOF) return max;
        budgetClearBuffer();
        if (result == 1 && number >= min && number <= max) return number;
        printf("Invalid input. Enter a number from %d to %d.\n", min, max);
    }
}

static double budgetGetMoney(const char prompt[], double min)
{
    double amount;
    int result;

    while (1) {
        printf("%s", prompt);
        result = scanf("%lf", &amount);
        if (result == EOF) return min;
        budgetClearBuffer();
        if (result == 1 && amount >= min) return amount;
        printf("Invalid amount. It must be a number of at least %.2f.\n", min);
    }
}

static void budgetGetText(const char prompt[], char text[], int size)
{
    while (1) {
        printf("%s", prompt);
        if (fgets(text, size, stdin) == NULL) {
            text[0] = '\0';
            return;
        }
        text[strcspn(text, "\n")] = '\0';
        if (strlen(text) > 0) return;
        printf("This field cannot be empty.\n");
    }
}


double calculateRemaining(double budget, double spent)
{
    return budget - spent;
}

int isWithinBudget(double budget, double spent)
{
    return spent <= budget;
}

int getDepartmentCount(void)
{
    return departmentCount;
}

double getTotalAllocated(void)
{
    double total = 0;
    for (int i = 0; i < departmentCount; i++) total += allocated[i];
    return total;
}

double getTotalSpent(void)
{
    double total = 0;
    for (int i = 0; i < departmentCount; i++) total += expenditure[i];
    return total;
}

static int findDepartment(const char name[])
{
    for (int i = 0; i < departmentCount; i++) {
        if (strcmp(departments[i], name) == 0) return i;
    }
    return -1;
}

static void addDepartment(void)
{
    char name[DEPT_NAME_SIZE];

    printf(PINK "\n--- Add Department Budget ---\n" RESET);

    if (departmentCount >= MAX_DEPARTMENTS) {
        printf("Maximum department limit reached!\n");
        budgetPause();
        return;
    }

    budgetGetText("Enter department name: ", name, DEPT_NAME_SIZE);
    while (findDepartment(name) != -1) {
        printf("That department already exists.\n");
        budgetGetText("Enter department name: ", name, DEPT_NAME_SIZE);
    }

    strcpy(departments[departmentCount], name);
    allocated[departmentCount]   = budgetGetMoney("Enter allocated budget (N$): ", 0);
    expenditure[departmentCount] = budgetGetMoney("Enter current expenditure (N$): ", 0);
    departmentCount++;

    printf("\nDepartment budget added successfully.\n");
    budgetPause();
}

static void displayBudgets(void)
{
    printf(PINK "\n--- Department Budgets ---\n" RESET);

    if (departmentCount == 0) {
        printf("No budget records found.\n");
        budgetPause();
        return;
    }

    for (int i = 0; i < departmentCount; i++) {
        double rem = calculateRemaining(allocated[i], expenditure[i]);

        printf("\nDepartment: %s\n", departments[i]);
        printf("Allocated: N$%.2f | Spent: N$%.2f | Remaining: N$%.2f\n",
               allocated[i], expenditure[i], rem);

        if (isWithinBudget(allocated[i], expenditure[i])) {
            printf("Status: Within Budget\n");
        } else {
            printf("Status: OVER BUDGET!\n");
        }
    }

    printf("\nTotal allocated: N$%.2f | Total spent: N$%.2f\n",
           getTotalAllocated(), getTotalSpent());
    budgetPause();
}

static void recordExpenditure(void)
{
    char name[DEPT_NAME_SIZE];
    int position;
    double amount;

    printf(PINK "\n--- Record Expenditure ---\n" RESET);

    if (departmentCount == 0) {
        printf("No budget records found.\n");
        budgetPause();
        return;
    }

    budgetGetText("Enter department name: ", name, DEPT_NAME_SIZE);
    position = findDepartment(name);

    if (position == -1) {
        printf("Department not found.\n");
        budgetPause();
        return;
    }

    amount = budgetGetMoney("Enter amount spent (N$): ", 0);
    expenditure[position] += amount;

    printf("\nNew expenditure for %s: N$%.2f\n", departments[position], expenditure[position]);
    if (!isWithinBudget(allocated[position], expenditure[position])) {
        printf("WARNING: this department is now OVER BUDGET!\n");
    }
    budgetPause();
}

void budgetMenu(void)
{
    int choice;

    do {
        printf(PINK "\n========================================\n");
        printf("BUDGET MANAGEMENT\n");
        printf("========================================\n");
        printf("1. Add Department Budget\n");
        printf("2. Display All Budgets\n");
        printf("3. Record Expenditure\n");
        printf("4. Back to Main Menu\n" RESET);
        printf("\n");

        choice = budgetGetInt("Enter your choice: ", 1, 4);

        switch (choice) {
            case 1: addDepartment();     break;
            case 2: displayBudgets();    break;
            case 3: recordExpenditure(); break;
        }
    } while (choice != 4);
}