#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "suppliers.h"

#define MAX 100
#define STR_LEN 50
#define PHONE_MIN 10
#define PHONE_MAX 10

typedef struct {
    int id;
    char name[STR_LEN];
    char email[STR_LEN];
    char phone[STR_LEN];
    char town[STR_LEN];
    char goodsSupplied[STR_LEN];
} Supplier;

static Supplier suppliers[MAX];
static int supplierCount = 0;
static int nextId = 1;


static void readLine(const char *prompt, char *dest, int size) {
    printf("%s", prompt);
    if (fgets(dest, size, stdin) == NULL) {
        dest[0] = '\0';
        return;
    }
    size_t len = strlen(dest);
    if (len > 0 && dest[len - 1] == '\n') {
        dest[len - 1] = '\0';
    } else {
       
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }
}

static int isBlank(const char *s) {
    while (*s) {
        if (!isspace((unsigned char)*s)) return 0;
        s++;
    }
    return 1;
}

static int readInt(const char *prompt) {
    char buf[32];
    int value;
    readLine(prompt, buf, sizeof buf);
    if (sscanf(buf, "%d", &value) != 1) return -1;
    return value;
}

static int findSupplier(int id) {
    for (int i = 0; i < supplierCount; i++) {
        if (suppliers[i].id == id) return i;
    }
    return -1;
}


static int isValidPhone(const char *s) {
    size_t len = strlen(s);
    if (len < PHONE_MIN || len > PHONE_MAX) return 0;
    for (size_t i = 0; i < len; i++) {
        if (!isdigit((unsigned char)s[i])) return 0;
    }
    return 1;
}


static int isValidEmail(const char *s) {
    for (int i = 0; s[i] != '\0'; i++) {
        if (isspace((unsigned char)s[i])) return 0;
    }

    const char *at = strchr(s, '@');
    if (at == NULL || at == s) return 0;         
    if (strchr(at + 1, '@') != NULL) return 0;   

    const char *dot = strrchr(at, '.');
    if (dot == NULL || dot == at + 1) return 0;   
    if (dot[1] == '\0') return 0;                 
    return 1;
}


static int containsIgnoreCase(const char *text, const char *term) {
    char a[STR_LEN], b[STR_LEN];
    int i;

    for (i = 0; text[i] != '\0' && i < STR_LEN - 1; i++)
        a[i] = (char)tolower((unsigned char)text[i]);
    a[i] = '\0';

    for (i = 0; term[i] != '\0' && i < STR_LEN - 1; i++)
        b[i] = (char)tolower((unsigned char)term[i]);
    b[i] = '\0';

    return strstr(a, b) != NULL;
}

static void printHeader(void) {
    printf("\n%-5s %-18s %-25s %-15s %-15s %-15s\n",
           "ID", "Name", "Email", "Phone", "Town", "Goods");
    printf("--------------------------------------------------------------------------------------------\n");
}

static void printSupplier(int i) {
    printf("%-5d %-18s %-25s %-15s %-15s %-15s\n",
           suppliers[i].id, suppliers[i].name, suppliers[i].email,
           suppliers[i].phone, suppliers[i].town, suppliers[i].goodsSupplied);
}


static void addSupplier(void) {
    if (supplierCount >= MAX) {
        printf("Supplier list is full.\n");
        return;
    }

    Supplier s;
    s.id = nextId;

    do {
        readLine("Name: ", s.name, STR_LEN);
        if (isBlank(s.name)) printf("Name cannot be empty.\n");
    } while (isBlank(s.name));

    do {
        readLine("Email: ", s.email, STR_LEN);
        if (!isValidEmail(s.email))
            printf("Invalid email. Example: name@company.com\n");
    } while (!isValidEmail(s.email));

    do {
        readLine("Telephone (digits only): ", s.phone, STR_LEN);
        if (!isValidPhone(s.phone))
            printf("Invalid number. Use digits only, %d to %d long.\n",
                   PHONE_MIN, PHONE_MAX);
    } while (!isValidPhone(s.phone));

    do {
        readLine("Town/Location: ", s.town, STR_LEN);
        if (isBlank(s.town)) printf("Town cannot be empty.\n");
    } while (isBlank(s.town));

    readLine("Goods supplied: ", s.goodsSupplied, STR_LEN);

    suppliers[supplierCount++] = s;
    nextId++;
    printf("Supplier added with ID %d.\n", s.id);
}

static void viewSuppliers(void) {
    if (supplierCount == 0) {
        printf("No suppliers recorded.\n");
        return;
    }
    printHeader();
    for (int i = 0; i < supplierCount; i++) {
        printSupplier(i);
    }
}

static void searchSuppliers(void) {
    if (supplierCount == 0) {
        printf("No suppliers recorded.\n");
        return;
    }

    printf("\nSearch by:\n");
    printf("1. ID\n");
    printf("2. Name\n");
    printf("3. Town\n");
    int option = readInt("Choice: ");

    int found = 0;

    if (option == 1) {
        int id = readInt("Enter supplier ID: ");
        int idx = findSupplier(id);
        if (idx != -1) {
            printHeader();
            printSupplier(idx);
            found = 1;
        }
    } else if (option == 2 || option == 3) {
        char term[STR_LEN];
        readLine(option == 2 ? "Enter name (or part of it): "
                             : "Enter town (or part of it): ", term, STR_LEN);

        if (isBlank(term)) {
            printf("Search text cannot be empty.\n");
            return;
        }

        for (int i = 0; i < supplierCount; i++) {
            const char *field = (option == 2) ? suppliers[i].name : suppliers[i].town;
            if (containsIgnoreCase(field, term)) {
                if (!found) printHeader();
                printSupplier(i);
                found = 1;
            }
        }
    } else {
        printf("Invalid choice.\n");
        return;
    }

    if (!found) printf("No matching suppliers found.\n");
}

static void editSupplier(void) {
    int id = readInt("Enter supplier ID to edit: ");
    int idx = findSupplier(id);
    if (idx == -1) {
        printf("Supplier not found.\n");
        return;
    }

    char buf[STR_LEN];
    printf("(Press Enter to keep the current value)\n");

    printf("Current name: %s\n", suppliers[idx].name);
    readLine("New name: ", buf, STR_LEN);
    if (!isBlank(buf)) strcpy(suppliers[idx].name, buf);

    printf("Current email: %s\n", suppliers[idx].email);
    do {
        readLine("New email: ", buf, STR_LEN);
        if (isBlank(buf)) break;                  
        if (isValidEmail(buf)) {
            strcpy(suppliers[idx].email, buf);
            break;
        }
        printf("Invalid email. Example: name@company.com\n");
    } while (1);

    printf("Current phone: %s\n", suppliers[idx].phone);
    do {
        readLine("New phone: ", buf, STR_LEN);
        if (isBlank(buf)) break;
        if (isValidPhone(buf)) {
            strcpy(suppliers[idx].phone, buf);
            break;
        }
        printf("Invalid number. Use digits only, %d to %d long.\n",
               PHONE_MIN, PHONE_MAX);
    } while (1);

    printf("Current town: %s\n", suppliers[idx].town);
    readLine("New town: ", buf, STR_LEN);
    if (!isBlank(buf)) strcpy(suppliers[idx].town, buf);

    printf("Current goods: %s\n", suppliers[idx].goodsSupplied);
    readLine("New goods: ", buf, STR_LEN);
    if (!isBlank(buf)) strcpy(suppliers[idx].goodsSupplied, buf);

    printf("Supplier updated.\n");
}

static void deleteSupplier(void) {
    int id = readInt("Enter supplier ID to delete: ");
    int idx = findSupplier(id);
    if (idx == -1) {
        printf("Supplier not found.\n");
        return;
    }

    for (int i = idx; i < supplierCount - 1; i++) {
        suppliers[i] = suppliers[i + 1];
    }
    supplierCount--;
    printf("Supplier deleted.\n");
}

void supplierMenu(void) {
    int choice;
    do {
        printf("\n--- Supplier Management ---\n");
        printf("1. Add supplier\n");
        printf("2. View suppliers\n");
        printf("3. Search suppliers\n");
        printf("4. Edit supplier\n");
        printf("5. Delete supplier\n");
        printf("0. Back\n");
        choice = readInt("Choice: ");

        switch (choice) {
            case 1: addSupplier();     break;
            case 2: viewSuppliers();   break;
            case 3: searchSuppliers(); break;
            case 4: editSupplier();    break;
            case 5: deleteSupplier();  break;
            case 0: break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 0);
}


int getSupplierCount(void) {
    return supplierCount;
}

void displaySupplier(void) {
    int i;
    if (supplierCount == 0) {
        printf("No suppliers registered.\n");
        return;
    }
    printHeader();
    for (i = 0; i < supplierCount; i++)
        printSupplier(i);
}
