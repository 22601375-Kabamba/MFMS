#include <stdio.h>
#include "reports.h"
#include "employees.h"
#include "budget.h"
#include "suppliers.h"
#include "assets.h"
#include "utils.h"

void employeeReport(void)
{
    int i, n = getEmployeeCount();
    double total = 0.0, gross, highest = 0.0, lowest = 0.0;
    const Employee *hi = NULL, *lo = NULL, *e;

    printHeading("EMPLOYEE REPORT");

    if (n == 0) {
        printf("No employees registered yet.\n");
        return;
    }

    for (i = 0; i < n; i++) {
        e = getEmployeeAt(i);
        gross = calculateGross(e);
        total += gross;
        if (hi == NULL || gross > highest) { highest = gross; hi = e; }
        if (lo == NULL || gross < lowest)  { lowest  = gross; lo = e; }
    }

    printf("Total Employees : %d\n", n);
    printf("Total Payroll   : N$%.2f (gross, monthly)\n", total);
    printf("Average Salary  : N$%.2f\n", total / n);
    printf("Highest Salary  : N$%.2f (%s)\n", highest, hi->name);
    printf("Lowest Salary   : N$%.2f (%s)\n", lowest, lo->name);
}

void budgetReport(void)
{
    int i, n = getBudgetCount(), over = 0;
    double allocated = 0.0, spent = 0.0;
    const Budget *b;

    printHeading("BUDGET REPORT");

    if (n == 0) {
        printf("No budgets captured yet.\n");
        return;
    }

    for (i = 0; i < n; i++) {
        b = getBudgetAt(i);
        allocated += b->allocated;
        spent += b->expenditure;
    }

    printf("Total Allocated Budget : N$%.2f\n", allocated);
    printf("Total Expenditure      : N$%.2f\n", spent);
    printf("Remaining Budget       : N$%.2f\n", calculateRemaining(allocated, spent));
    printLine('-', 60);
    printf("Departments exceeding budget:\n");

    for (i = 0; i < n; i++) {
        b = getBudgetAt(i);
        if (!isWithinBudget(b->allocated, b->expenditure)) {
            printf("  - %s (overspent by N$%.2f)\n", b->department,
                   b->expenditure - b->allocated);
            over++;
        }
    }
    if (over == 0) {
        printf("  None - all departments are within budget.\n");
    }
}

void supplierReport(void)
{
    int i, n = getSupplierCount();
    const Supplier *s;

    printHeading("SUPPLIER REPORT");

    if (n == 0) {
        printf("No suppliers registered yet.\n");
        return;
    }
    printf("%-9s %-24s %-26s %-12s\n", "ID", "Name", "Email", "Town");
    printLine('-', 74);
    for (i = 0; i < n; i++) {
        s = getSupplierAt(i);
        printf("%-9s %-24s %-26s %-12s\n", s->id, s->name, s->email, s->town);
    }
    printf("\nTotal suppliers: %d\n", n);
}

void assetReport(void)
{
    int i, n = getAssetCount(), poor = 0;
    const Asset *a;

    printHeading("ASSET REPORT");

    if (n == 0) {
        printf("No assets registered yet.\n");
        return;
    }
    printf("%-9s %-24s %-11s %14s %-9s\n", "ID", "Name", "Type", "Value (N$)", "Condition");
    printLine('-', 72);
    for (i = 0; i < n; i++) {
        a = getAssetAt(i);
        printf("%-9s %-24s %-11s %14.2f %-9s\n",
               a->id, a->name, a->type, a->purchaseValue, a->condition);
        if (equalsIgnoreCase(a->condition, "Poor")) poor++;
    }
    printf("\nTotal assets: %d | Total value: N$%.2f | Assets in poor condition: %d\n",
           n, calculateTotalAssetValue(), poor);
}

void displayReports(void)
{
    employeeReport();
    budgetReport();
    supplierReport();
    assetReport();
}

void reportsMenu(void)
{
    int choice;

    do {
        printHeading("REPORTS");
        printf("1. Employee report\n");
        printf("2. Budget report\n");
        printf("3. Supplier report\n");
        printf("4. Asset report\n");
        printf("5. All reports\n");
        printf("6. Back to main menu\n");
        choice = readInt("Enter your choice: ", -2147483647 - 1, 2147483647);

        switch (choice) {
        case 1: employeeReport();  pauseScreen(); break;
        case 2: budgetReport();    pauseScreen(); break;
        case 3: supplierReport();  pauseScreen(); break;
        case 4: assetReport();     pauseScreen(); break;
        case 5: displayReports();  pauseScreen(); break;
        case 6: break;
        default:
            printf("  [!] Invalid choice. Please select 1-6.\n");
        }
    } while (choice != 6);
}