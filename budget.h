#ifndef BUDGET_H
#define BUDGET_H

#define MAX_BUDGETS 100
#define BUDGET_DEPT_LEN 50

// This structure matches your code's department data
typedef struct {
    char department[BUDGET_DEPT_LEN];
    double allocated;
    double expenditure;
} Budget;

// These match the functions from your code
void addBudget(void);
void recordExpenditure(void);
void displayBudgets(void);
void showExceededBudgets(void);
void budgetMenu(void);
int getBudgetCount(void);
const Budget *getBudgetAt(int index);
void loadSampleBudgets(void);

#endif // BUDGET_H