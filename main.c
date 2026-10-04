#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#endif

#define INPUT_SIZE 32

#define OPT_EMPLOYEES 1
#define OPT_BUDGET    2
#define OPT_SUPPLIERS 3
#define OPT_ASSETS    4
#define OPT_REPORTS   5
#define OPT_EXIT      6

#define PINK  "\033[38;5;213m"
#define BOLD  "\033[1m"
#define RESET "\033[0m"

void employeeMenu(void);
void budgetMenu(void);
void supplierMenu(void);
void assetMenu(void);
void reportsMenu(void);

void enableColours(void);
void displayMenu(void);
int  getMenuChoice(int min, int max);
int  confirmExit(void);

void enableColours(void)
{
#ifdef _WIN32
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD mode = 0;

    if (console != INVALID_HANDLE_VALUE && GetConsoleMode(console, &mode)) {
        SetConsoleMode(console, mode | 0x0004); 
    }
#endif
}

void displayMenu(void)
{
    printf("\n" PINK BOLD);
    printf("========================================\n");
    printf("MUNICIPAL FINANCIAL MANAGEMENT SYSTEM\n");
    printf("========================================\n" RESET PINK);
    printf("1. Employee Management\n");
    printf("2. Budget Management\n");
    printf("3. Supplier Management\n");
    printf("4. Asset Management\n");
    printf("5. Reports\n");
    printf("6. Exit\n" RESET);
    printf("\n");
}

int getMenuChoice(int min, int max)
{
    char buffer[INPUT_SIZE];
    char *end;
    long value;

    printf("Enter your choice: ");

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return max;  
    }

    if (strchr(buffer, '\n') == NULL) {
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {
            
        }
        return -1;
    }

    value = strtol(buffer, &end, 10);

    if (end == buffer) {
        return -1;  
    }

    while (*end == ' ' || *end == '\t') {
        end++;  
    }

    if (*end != '\n' && *end != '\0') {
        return -1; 
    }

    if (value < min || value > max) {
        return -1;
    }

    return (int)value;
}

int confirmExit(void)
{
    char buffer[INPUT_SIZE];

    while (1) {
        printf("Are you sure you want to exit? (y/n): ");
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            return 1;
        }
        if (buffer[0] == 'y' || buffer[0] == 'Y') {
            return 1;
        }
        if (buffer[0] == 'n' || buffer[0] == 'N') {
            return 0;
        }
        printf("Please enter y or n.\n");
    }
}

int main(void)
{
    int choice = 0;
    int running = 1;

    enableColours();

    while (running) {
        displayMenu();
        choice = getMenuChoice(OPT_EMPLOYEES, OPT_EXIT);

        switch (choice) {
            case OPT_EMPLOYEES:
                employeeMenu();
                break;
            case OPT_BUDGET:
                budgetMenu();
                break;
            case OPT_SUPPLIERS:
                supplierMenu();
                break;
            case OPT_ASSETS:
                assetMenu();
                break;
            case OPT_REPORTS:
                reportsMenu();
                break;
            case OPT_EXIT:
                if (confirmExit()) {
                    running = 0;
                }
                break;
            default:
                printf("\nInvalid choice. Please enter a number from 1 to 6.\n");
                break;
        }
    }

    printf("\nThank you for using the MFMS. Goodbye!\n");
    return 0;
}

void budgetMenu(void)   { printf("\n[Budget Management - coming soon]\n"); }
void supplierMenu(void) { printf("\n[Supplier Management - coming soon]\n"); }
void assetMenu(void)    { printf("\n[Asset Management - coming soon]\n"); }
void reportsMenu(void)  { printf("\n[Reports - coming soon]\n"); }
