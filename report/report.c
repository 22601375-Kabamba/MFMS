/* Rewritten by Kennedy for integration (original draft by Samy/Aishe/Shaningwa) */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "report.h"
#include "employees.h"
#include "budget.h"
#include "suppliers.h"
#include "assets.h"

/* Validated menu input: rejects letters, empty lines, out-of-range numbers */
static int readChoice(int min, int max)
{
    char buf[64];
    char *end;
    long v;

    for (;;) {
        printf("Enter choice (%d-%d): ", min, max);
        if (fgets(buf, sizeof buf, stdin) == NULL)
            return min;                         /* EOF: go back */

        if (strchr(buf, '\n') == NULL) {        /* line too long: discard rest */
            int c;
            while ((c = getchar()) != '\n' && c != EOF)
                ;
            printf("Invalid input. Try again.\n");
            continue;
        }

        v = strtol(buf, &end, 10);
        if (end == buf) {
            printf("Invalid input. Enter a number.\n");
            continue;
        }
        while (*end == ' ' || *end == '\t')
            end++;
        if (*end != '\n' && *end != '\0') {
            printf("Invalid input. Enter a number only.\n");
            continue;
        }
        if (v < min || v > max) {
            printf("Choice must be between %d and %d.\n", min, max);
            continue;
        }
        return (int)v;
    }
}

void budgetReport(void)
{
    int i, n = getBudgetCount();
    double totalAlloc = 0.0, totalSpent = 0.0;
    int exceeded = 0;

    printf("\n===== BUDGET REPORT =====\n");
    if (n == 0) {
        printf("No budgets recorded.\n");
        return;
    }

    printf("%-20s %12s %12s %12s  %s\n",
           "Department", "Allocated", "Spent", "Remaining", "Status");
    for (i = 0; i < n; i++) {
        const Budget *b = getBudgetAt(i);
        double remaining;
        if (b == NULL)
            continue;
        remaining = b->allocated - b->expenditure;
        printf("%-20.20s %12.2f %12.2f %12.2f  %s\n",
               b->department, b->allocated, b->expenditure, remaining,
               remaining < 0 ? "EXCEEDED" : "OK");
        totalAlloc += b->allocated;
        totalSpent += b->expenditure;
        if (remaining < 0)
            exceeded++;
    }
    printf("\nTotal allocated : %.2f\n", totalAlloc);
    printf("Total spent     : %.2f\n", totalSpent);
    printf("Total remaining : %.2f\n", totalAlloc - totalSpent);
    printf("Departments over budget: %d\n", exceeded);
}

void supplierReport(void)
{
    printf("\n===== SUPPLIER REPORT =====\n");
    printf("Total suppliers: %d\n", getSupplierCount());
    displaySupplier();
}

void assetReport(void)
{
    printf("\n===== ASSET REPORT =====\n");
    displayAssetReport();
}

void displayReports(void)
{
    printf("\n===== EMPLOYEE REPORT =====\n");
    employeeReport();
    budgetReport();
    supplierReport();
    assetReport();
}

void reportsMenu(void)
{
    int choice;

    do {
        printf("\n===== REPORTS MENU =====\n");
        printf("1. Employee report\n");
        printf("2. Budget report\n");
        printf("3. Supplier report\n");
        printf("4. Asset report\n");
        printf("5. All reports\n");
        printf("0. Back to main menu\n");

        choice = readChoice(0, 5);

        switch (choice) {
            case 1: printf("\n===== EMPLOYEE REPORT =====\n"); employeeReport(); break;
            case 2: budgetReport();   break;
            case 3: supplierReport(); break;
            case 4: assetReport();    break;
            case 5: displayReports(); break;
            case 0: break;
        }
    } while (choice != 0);
}
