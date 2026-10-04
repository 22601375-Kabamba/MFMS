#include <stdio.h>
#include <string.h>
#include "employees.h"
 
#define MAX_EMPLOYEES 100
#define NAME_SIZE 50
#define DEPT_SIZE 30
 
#define PINK  "\033[38;5;213m"
#define RESET "\033[0m"

#define TAX_LIMIT_1 5000.0
#define TAX_LIMIT_2 15000.0
#define TAX_LIMIT_3 30000.0
 
int employeeIds[MAX_EMPLOYEES];
char employeeNames[MAX_EMPLOYEES][NAME_SIZE];
char employeeDepts[MAX_EMPLOYEES][DEPT_SIZE];
double basicSalary[MAX_EMPLOYEES];
double housingAllowance[MAX_EMPLOYEES];
double transportAllowance[MAX_EMPLOYEES];
int employeeCount = 0;
 
void clearInputBuffer(void);
void pauseScreen(void);
int getInteger(char prompt[], int min, int max);
double getMoney(char prompt[], double min);
void getText(char prompt[], char text[], int size);
int findEmployeeById(int id);
double calculateGross(double basic, double housing, double transport);
double calculateTax(double gross);
double calculateNet(double gross, double tax);
void printTableHeader(void);
void printEmployeeRow(int index);
void addEmployee(void);
void displayEmployees(void);
void searchById(void);
void searchByName(void);
void searchByDepartment(void);
void searchEmployee(void);
void showSalary(void);
 
void clearInputBuffer(void)
{
    int ch;
 
    while ((ch = getchar()) != '\n' && ch != EOF)
    {
    }
}
 
void pauseScreen(void)
{
    printf("\nPress Enter to continue...");
    getchar();
}
 
int getInteger(char prompt[], int min, int max)
{
    int number;
    int result;
 
    while (1)
    {
        printf("%s", prompt);
        result = scanf("%d", &number);
 
        if (result == EOF)
        {
            return min;
        }
 
        clearInputBuffer();
 
        if (result == 1 && number >= min && number <= max)
        {
            return number;
        }
 
        printf("Invalid input. Enter a number from %d to %d.\n", min, max);
    }
}

double getMoney(char prompt[], double min)
{
    double amount;
    int result;
 
    while (1)
    {
        printf("%s", prompt);
        result = scanf("%lf", &amount);
 
        if (result == EOF)
        {
            return min;
        }
 
        clearInputBuffer();
 
        if (result == 1 && amount >= min)
        {
            return amount;
        }
 
        printf("Invalid amount. It must be a number of at least %.2f.\n", min);
    }
}

void getText(char prompt[], char text[], int size)
{
    while (1)
    {
        printf("%s", prompt);
 
        if (fgets(text, size, stdin) == NULL)
        {
            text[0] = '\0';
            return;
        }
 
        /* remove the newline left by fgets() */
        text[strcspn(text, "\n")] = '\0';
 
        if (strlen(text) > 0)
        {
            return;
        }
 
        printf("This field cannot be empty.\n");
    }
}
 
double calculateGross(double basic, double housing, double transport)
{
    return basic + housing + transport;
}
 
double calculateTax(double gross)
{
    if (gross <= TAX_LIMIT_1)
    {
        return 0;
    }
    else if (gross <= TAX_LIMIT_2)
    {
        return gross * 0.10;
    }
    else if (gross <= TAX_LIMIT_3)
    {
        return gross * 0.20;
    }
    else
    {
        return gross * 0.30;
    }
}
 
double calculateNet(double gross, double tax)
{
    return gross - tax;
}
 
int findEmployeeById(int id)
{
    for (int i = 0; i < employeeCount; i++)
    {
        if (employeeIds[i] == id)
        {
            return i;
        }
    }
 
    return -1;
}
 
void printTableHeader(void)
{
    printf("\n%-6s %-20s %-15s %12s\n", "ID", "Name", "Department", "Gross (N$)");
    printf("------ -------------------- --------------- ------------\n");
}
 
void printEmployeeRow(int index)
{
    double gross;
 
    gross = calculateGross(basicSalary[index], housingAllowance[index], transportAllowance[index]);
 
    printf("%-6d %-20s %-15s %12.2f\n", employeeIds[index], employeeNames[index], employeeDepts[index], gross);
}
 
void addEmployee(void)
{
    int id;
 
    printf(PINK "\n--- Add Employee ---\n" RESET);
 
    if (employeeCount >= MAX_EMPLOYEES)
    {
        printf("The employee list is full.\n");
        pauseScreen();
        return;
    }
 
    /* Ask again while the ID is already used */
    id = getInteger("Enter employee ID (1-999999): ", 1, 999999);
    while (findEmployeeById(id) != -1)
    {
        printf("That ID already exists.\n");
        id = getInteger("Enter employee ID (1-999999): ", 1, 999999);
    }
 
    employeeIds[employeeCount] = id;
    getText("Enter full name: ", employeeNames[employeeCount], NAME_SIZE);
    getText("Enter department: ", employeeDepts[employeeCount], DEPT_SIZE);
    basicSalary[employeeCount] = getMoney("Enter basic salary (N$): ", 1);
    housingAllowance[employeeCount] = getMoney("Enter housing allowance (N$): ", 0);
    transportAllowance[employeeCount] = getMoney("Enter transport allowance (N$): ", 0);
 
    employeeCount++;
 
    printf("\nEmployee added successfully.\n");
    pauseScreen();
}
 
void displayEmployees(void)
{
    printf(PINK "\n--- All Employees ---\n" RESET);
 
    if (employeeCount == 0)
    {
        printf("No employees have been added yet.\n");
        pauseScreen();
        return;
    }
 
    printTableHeader();
 
    for (int i = 0; i < employeeCount; i++)
    {
        printEmployeeRow(i);
    }
 
    printf("\nTotal employees: %d\n", employeeCount);
    pauseScreen();
}
 
 
/* ---------- Search ---------- */
 
void searchById(void)
{
    int id;
    int position;
 
    id = getInteger("Enter the employee ID to search for: ", 1, 999999);
    position = findEmployeeById(id);
 
    if (position == -1)
    {
        printf("Employee not found.\n");
    }
    else
    {
        printTableHeader();
        printEmployeeRow(position);
    }
}
 
void searchByName(void)
{
    char searchName[NAME_SIZE];
    int found = 0;
 
    getText("Enter the full name to search for: ", searchName, NAME_SIZE);
 
    for (int i = 0; i < employeeCount; i++)
    {
        if (strcmp(employeeNames[i], searchName) == 0)
        {
            if (found == 0)
            {
                printTableHeader();
            }
            printEmployeeRow(i);
            found = 1;
        }
    }
 
    if (found == 0)
    {
        printf("Employee not found.\n");
    }
}
 
void searchByDepartment(void)
{
    char searchDept[DEPT_SIZE];
    int found = 0;
 
    getText("Enter the department to search for: ", searchDept, DEPT_SIZE);
 
    for (int i = 0; i < employeeCount; i++)
    {
        if (strcmp(employeeDepts[i], searchDept) == 0)
        {
            if (found == 0)
            {
                printTableHeader();
            }
            printEmployeeRow(i);
            found = 1;
        }
    }
 
    if (found == 0)
    {
        printf("No employees found in that department.\n");
    }
}
 
void searchEmployee(void)
{
    int choice;
 
    printf(PINK "\n--- Search Employee ---\n" RESET);
 
    if (employeeCount == 0)
    {
        printf("No employees have been added yet.\n");
        pauseScreen();
        return;
    }
 
    printf("1. Search by ID\n");
    printf("2. Search by name\n");
    printf("3. Search by department\n");
    choice = getInteger("Enter your choice: ", 1, 3);
 
    switch (choice)
    {
        case 1:
            searchById();
            break;
        case 2:
            searchByName();
            break;
        case 3:
            searchByDepartment();
            break;
    }
 
    pauseScreen();
}
 
void showSalary(void)
{
    int id;
    int position;
    double gross;
    double tax;
    double net;
 
    printf(PINK "\n--- Salary Information ---\n" RESET);
 
    if (employeeCount == 0)
    {
        printf("No employees have been added yet.\n");
        pauseScreen();
        return;
    }
 
    id = getInteger("Enter the employee ID: ", 1, 999999);
    position = findEmployeeById(id);
 
    if (position == -1)
    {
        printf("Employee not found.\n");
        pauseScreen();
        return;
    }
 
    gross = calculateGross(basicSalary[position], housingAllowance[position], transportAllowance[position]);
    tax = calculateTax(gross);
    net = calculateNet(gross, tax);
 
    printf("\n========================================\n");
    printf("SALARY SLIP\n");
    printf("========================================\n");
    printf("Employee ID : %d\n", employeeIds[position]);
    printf("Name        : %s\n", employeeNames[position]);
    printf("Department  : %s\n", employeeDepts[position]);
    printf("----------------------------------------\n");
    printf("Basic Salary        : N$%10.2f\n", basicSalary[position]);
    printf("Housing Allowance   : N$%10.2f\n", housingAllowance[position]);
    printf("Transport Allowance : N$%10.2f\n", transportAllowance[position]);
    printf("Gross Salary        : N$%10.2f\n", gross);
    printf("Tax                 : N$%10.2f\n", tax);
    printf("Net Salary          : N$%10.2f\n", net);
    printf("========================================\n");
 
    if (net >= 20000)
    {
        printf("Income category: High Income\n");
    }
    else
    {
        printf("Income category: Standard Income\n");
    }
 
    pauseScreen();
}
 
int getEmployeeCount(void)
{
    return employeeCount;
}
 
void employeeReport(void)
{
    double gross;
    double total = 0;
    double highest;
    double lowest;
    int highestPosition = 0;
    int lowestPosition = 0;
 
    printf(PINK "\n--- Employee Report ---\n" RESET);
 
    if (employeeCount == 0)
    {
        printf("No employees have been added yet.\n");
        return;
    }
 
    highest = calculateGross(basicSalary[0], housingAllowance[0], transportAllowance[0]);
    lowest = highest;
 
    for (int i = 0; i < employeeCount; i++)
    {
        gross = calculateGross(basicSalary[i], housingAllowance[i], transportAllowance[i]);
        total = total + gross;
 
        if (gross > highest)
        {
            highest = gross;
            highestPosition = i;
        }
 
        if (gross < lowest)
        {
            lowest = gross;
            lowestPosition = i;
        }
    }
 
    printf("Total Employees      : %d\n", employeeCount);
    printf("Average Gross Salary : N$%.2f\n", total / employeeCount);
    printf("Highest Gross Salary : N$%.2f (%s)\n", highest, employeeNames[highestPosition]);
    printf("Lowest Gross Salary  : N$%.2f (%s)\n", lowest, employeeNames[lowestPosition]);
}
 
 
/* ---------- Employee menu ---------- */
 
void employeeMenu(void)
{
    int choice;
 
    do
    {
        printf(PINK "\n========================================\n");
        printf("EMPLOYEE MANAGEMENT\n");
        printf("========================================\n");
        printf("1. Add Employee\n");
        printf("2. Display Employees\n");
        printf("3. Search Employee\n");
        printf("4. Salary Information\n");
        printf("5. Employee Report\n");
        printf("6. Back to Main Menu\n" RESET);
        printf("\n");
 
        choice = getInteger("Enter your choice: ", 1, 6);
 
        switch (choice)
        {
            case 1:
                addEmployee();
                break;
            case 2:
                displayEmployees();
                break;
            case 3:
                searchEmployee();
                break;
            case 4:
                showSalary();
                break;
            case 5:
                employeeReport();
                pauseScreen();
                break;
        }
    } while (choice != 6);
}
 