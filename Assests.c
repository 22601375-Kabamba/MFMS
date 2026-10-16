#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Assets.h"

static Asset assets[MAX_ASSETS];
static int assetCount = 0;


static void readLine(const char *prompt, char *buf, int size)
{
    size_t len;
    int c;

    printf("%s", prompt);
    if (fgets(buf, size, stdin) == NULL) {
        buf[0] = '\0';
        return;
    }
    len = strlen(buf);
    if (len > 0 && buf[len - 1] == '\n') {
        buf[len - 1] = '\0';
    } else {
        while ((c = getchar()) != '\n' && c != EOF) {
            
        }
    }
}


static int isBlank(const char *s)
{
    int i;
    for (i = 0; s[i] != '\0'; i++) {
        if (!isspace((unsigned char)s[i])) {
            return 0;
        }
    }
    return 1;
}


static void readNonEmpty(const char *prompt, char *buf, int size)
{
    do {
        readLine(prompt, buf, size);
        if (isBlank(buf)) {
            printf("  Error: this field cannot be empty.\n");
        }
    } while (isBlank(buf));
}


static double readPositiveDouble(const char *prompt)
{
    char tmp[40];
    char *end;
    double value;

    while (1) {
        readLine(prompt, tmp, (int)sizeof(tmp));
        value = strtod(tmp, &end);
        if (end == tmp || *end != '\0') {
            printf("  Error: please enter a valid number.\n");
        } else if (value <= 0) {
            printf("  Error: value must be greater than zero.\n");
        } else {
            return value;
        }
    }
}


static int readMenuChoice(const char *prompt, int min, int max)
{
    char tmp[20];
    char *end;
    long choice;

    while (1) {
        readLine(prompt, tmp, (int)sizeof(tmp));
        choice = strtol(tmp, &end, 10);
        if (end == tmp || *end != '\0' || choice < min || choice > max) {
            printf("  Invalid choice. Enter a number from %d to %d.\n", min, max);
        } else {
            return (int)choice;
        }
    }
}


static int containsIgnoreCase(const char *text, const char *keyword)
{
    char t[ASSET_NAME_LEN + ASSET_DEPT_LEN];
    char k[ASSET_NAME_LEN + ASSET_DEPT_LEN];
    int i;

    for (i = 0; text[i] != '\0' && i < (int)sizeof(t) - 1; i++) {
        t[i] = (char)tolower((unsigned char)text[i]);
    }
    t[i] = '\0';
    for (i = 0; keyword[i] != '\0' && i < (int)sizeof(k) - 1; i++) {
        k[i] = (char)tolower((unsigned char)keyword[i]);
    }
    k[i] = '\0';

    return strstr(t, k) != NULL;
}


static int findAssetById(const char *id)
{
    int i;
    for (i = 0; i < assetCount; i++) {
        if (strcmp(assets[i].id, id) == 0) {
            return i;
        }
    }
    return -1;
}



static void chooseType(char *dest)
{
    int choice;

    printf("\nAsset type:\n");
    printf("  1. Vehicle\n  2. Computer\n  3. Building\n");
    printf("  4. Equipment\n  5. Office Furniture\n  6. Other\n");
    choice = readMenuChoice("Select type (1-6): ", 1, 6);

    switch (choice) {
        case 1: strcpy(dest, "Vehicle");          break;
        case 2: strcpy(dest, "Computer");         break;
        case 3: strcpy(dest, "Building");         break;
        case 4: strcpy(dest, "Equipment");        break;
        case 5: strcpy(dest, "Office Furniture"); break;
        default: strcpy(dest, "Other");           break;
    }
}

static void chooseCondition(char *dest)
{
    int choice;

    printf("\nCondition:\n");
    printf("  1. Good\n  2. Fair\n  3. Poor\n");
    choice = readMenuChoice("Select condition (1-3): ", 1, 3);

    switch (choice) {
        case 1:  strcpy(dest, "Good"); break;
        case 2:  strcpy(dest, "Fair"); break;
        default: strcpy(dest, "Poor"); break;
    }
}


static void printHeader(void)
{
    printf("\n%-12s %-22s %-18s %-14s %-16s %-10s\n",
           "ID", "Name", "Type", "Value (N$)", "Department", "Condition");
    printf("-------------------------------------------------------"
           "-----------------------------------\n");
}

static void printAsset(const Asset *a)
{
    printf("%-12s %-22s %-18s %-14.2f %-16s %-10s\n",
           a->id, a->name, a->type, a->purchaseValue,
           a->department, a->condition);
}



void addAsset(void)
{
    Asset a;

    if (assetCount >= MAX_ASSETS) {
        printf("\nThe asset register is full (%d assets).\n", MAX_ASSETS);
        return;
    }

    printf("\n--- Add Asset ---\n");


    while (1) {
        readNonEmpty("Asset ID: ", a.id, ASSET_ID_LEN);
        if (findAssetById(a.id) != -1) {
            printf("  Error: an asset with ID '%s' already exists.\n", a.id);
        } else {
            break;
        }
    }

    readNonEmpty("Asset name: ", a.name, ASSET_NAME_LEN);
    chooseType(a.type);
    a.purchaseValue = readPositiveDouble("Purchase value (N$): ");
    readNonEmpty("Department: ", a.department, ASSET_DEPT_LEN);
    chooseCondition(a.condition);

    assets[assetCount] = a;
    assetCount++;

    printf("\nAsset '%s' added successfully.\n", a.name);
}

void displayAssets(void)
{
    int i;

    if (assetCount == 0) {
        printf("\nNo assets registered yet.\n");
        return;
    }

    printf("\n--- Asset Register (%d assets) ---", assetCount);
    printHeader();
    for (i = 0; i < assetCount; i++) {
        printAsset(&assets[i]);
    }
}

void searchAssets(void)
{
    char keyword[ASSET_NAME_LEN];
    int choice, i, found = 0;

    if (assetCount == 0) {
        printf("\nNo assets registered yet.\n");
        return;
    }

    printf("\n--- Search Assets ---\n");
    printf("  1. Search by Asset ID (exact)\n");
    printf("  2. Search by Name (partial match)\n");
    printf("  3. Search by Department (partial match)\n");
    choice = readMenuChoice("Select search type (1-3): ", 1, 3);
    readNonEmpty("Enter search text: ", keyword, ASSET_NAME_LEN);

    for (i = 0; i < assetCount; i++) {
        int match = 0;

        switch (choice) {
            case 1:
                match = (strcmp(assets[i].id, keyword) == 0);
                break;
            case 2:
                match = containsIgnoreCase(assets[i].name, keyword);
                break;
            default:
                match = containsIgnoreCase(assets[i].department, keyword);
                break;
        }

        if (match) {
            if (!found) {
                printHeader();
            }
            printAsset(&assets[i]);
            found++;
        }
    }

    if (found == 0) {
        printf("\nNo matching assets found.\n");
    } else {
        printf("\n%d asset(s) found.\n", found);
    }
}


int getAssetCount(void)
{
    return assetCount;
}

double getTotalAssetValue(void)
{
    double total = 0.0;
    int i;
    for (i = 0; i < assetCount; i++) {
        total += assets[i].purchaseValue;
    }
    return total;
}

void displayAssetReport(void)
{
    int i, poorCount = 0;

    printf("\n========================================\n");
    printf("              ASSET REPORT\n");
    printf("========================================\n");

    if (assetCount == 0) {
        printf("No assets registered yet.\n");
        return;
    }

    for (i = 0; i < assetCount; i++) {
        if (strcmp(assets[i].condition, "Poor") == 0) {
            poorCount++;
        }
    }

    printf("Total Assets      : %d\n", assetCount);
    printf("Total Value       : N$%.2f\n", getTotalAssetValue());
    printf("Average Value     : N$%.2f\n", getTotalAssetValue() / assetCount);
    printf("Assets in Poor condition: %d\n", poorCount);

    printHeader();
    for (i = 0; i < assetCount; i++) {
        printAsset(&assets[i]);
    }
}


void assetMenu(void)
{
    int choice;

    do {
        printf("\n========================================\n");
        printf("            ASSET MANAGEMENT\n");
        printf("========================================\n");
        printf("1. Add Asset\n");
        printf("2. Display All Assets\n");
        printf("3. Search Assets\n");
        printf("4. Back to Main Menu\n");
        choice = readMenuChoice("Enter your choice: ", 1, 4);

        switch (choice) {
            case 1: addAsset();      break;
            case 2: displayAssets(); break;
            case 3: searchAssets();  break;
            default: break;
        }
    } while (choice != 4);
}