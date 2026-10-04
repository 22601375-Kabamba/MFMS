#ifndef BUDGET_H
#define BUDGET_H

void   budgetMenu(void);
double calculateRemaining(double budget, double spent);
int    isWithinBudget(double budget, double spent);

int    getDepartmentCount(void);
double getTotalAllocated(void);
double getTotalSpent(void);

#endif