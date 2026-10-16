#include <stdio.h>
#include <string.h>
#include "budget.h"
#include "utils.h"

static Budget budgets[MAX_BUDGETS];
static int budgetCount = 0;

static int findBudgetIndex(const char *department)
{
    int i;
    for (i = 0; i < budgetCount; i++) {
        if (equalsIgnoreCase(budgets[i].department, department)) {
            return i;
        }
    }
    return -1;
}


double calculateRemaining(double allocated, double expenditure)
{
    return allocated - expenditure;
}

int isWithinBudget(double allocated, double expenditure)
{
    return expenditure <= allocated;
}

const char *budgetStatus(double allocated, double expenditure)
{
    if (!isWithinBudget(allocated, expenditure)) {
        return "OVER BUDGET";
    }
    if (expenditure >= allocated * 0.9) {
        return "WITHIN BUDGET (WARNING: >=90% USED)";
    }
    return "WITHIN BUDGET";
}

static void printBudget(const Budget *b)
{
    double remaining = calculateRemaining(b->allocated, b->expenditure);

    printf("\nDepartment       : %s\n", b->department);
    printf("Allocated Budget : N$%.2f\n", b->allocated);
    printf("Expenditure      : N$%.2f\n", b->expenditure);
    if (remaining >= 0) {
        printf("Remaining Budget : N$%.2f\n", remaining);
    } else {
        printf("Overspent By     : N$%.2f\n", -remaining);
    }
    printf("Status           : %s\n", budgetStatus(b->allocated, b->expenditure));
}


void addBudget(void)
{
    Budget b;

    printHeading("ENTER DEPARTMENTAL BUDGET");

    if (budgetCount >= MAX_BUDGETS) {
        printf("  [!] Budget list is full.\n");
        return;
    }

    readNonEmpty("Department name: ", b.department, sizeof(b.department));
    if (findBudgetIndex(b.department) != -1) {
        printf("  [!] A budget for '%s' already exists.\n", b.department);
        return;
    }
    b.allocated   = readDouble("Allocated budget (N$): ", 0.01, 1000000000.0);
    b.expenditure = 0.0;

    budgets[budgetCount] = b;
    budgetCount++;
    printf("\n  [OK] Budget saved.\n");
}

void recordExpenditure(void)
{
    char dept[BUDGET_DEPT_LEN];
    int idx;
    double amount;

    printHeading("ENTER EXPENDITURE");

    if (budgetCount == 0) {
        printf("No budgets captured yet. Add a department budget first.\n");
        return;
    }

    readNonEmpty("Department name: ", dept, sizeof(dept));
    idx = findBudgetIndex(dept);
    if (idx < 0) {
        printf("  [!] Department '%s' has no budget.\n", dept);
        return;
    }

    amount = readDouble("Expenditure amount to add (N$): ", 0.01, 1000000000.0);
    budgets[idx].expenditure += amount;

    printf("\n  [OK] Expenditure recorded.\n");
    printBudget(&budgets[idx]);
}

void displayBudgets(void)
{ 
    int i;

    printHeading("BUDGET INFORMATION");

    if (budgetCount == 0) {
        printf("No budgets captured yet.\n");
        return;
    }
    for (i = 0; i < budgetCount; i++) {
        printBudget(&budgets[i]);
    }
}

void showExceededBudgets(void)
{
    int i, count = 0;

    printHeading("DEPARTMENTS OVER BUDGET");

    for (i = 0; i < budgetCount; i++) {
        if (!isWithinBudget(budgets[i].allocated, budgets[i].expenditure)) {
            printBudget(&budgets[i]);
            count++;
        }
    }
    if (count == 0) {
        printf("No department has exceeded its budget.\n");
    } else {
        printf("\nDepartments over budget: %d\n", count);
    }
}

void budgetMenu(void)
{
    int choice;

    do {
        printHeading("BUDGET MANAGEMENT");
        printf("1. Enter departmental budget\n");
        printf("2. Enter expenditure\n");
        printf("3. Display budget information\n");
        printf("4. Show departments over budget\n");
        printf("5. Back to main menu\n");
        choice = readInt("Enter your choice: ", -2147483647 - 1, 2147483647);

        switch (choice) {
        case 1: addBudget();           pauseScreen(); break;
        case 2: recordExpenditure();   pauseScreen(); break;
        case 3: displayBudgets();      pauseScreen(); break;
        case 4: showExceededBudgets(); pauseScreen(); break;
        case 5: break;
        default:
            printf("  [!] Invalid choice. Please select 1-5.\n");
        }
    } while (choice != 5);
}

int getBudgetCount(void)
{
    return budgetCount;
}

const Budget *getBudgetAt(int index)
{
    if (index < 0 || index >= budgetCount) {
        return NULL;
    }
    return &budgets[index];
}

static void addSampleBudget(const char *dept, double allocated, double spent)
{
    strcpy(budgets[budgetCount].department, dept);
    budgets[budgetCount].allocated = allocated;
    budgets[budgetCount].expenditure = spent;
    budgetCount++;
}

void loadSampleBudgets(void)
{
    if (budgetCount > 0) {
        printf("  Budgets already contain data - sample skipped.\n");
        return;
    }
    addSampleBudget("Finance", 500000, 420000);
    addSampleBudget("Roads",   900000, 950000);
    addSampleBudget("Water",   700000, 310000);
    addSampleBudget("IT",      250000, 240000);
    printf("  [OK] 4 sample budgets loaded.\n");
}