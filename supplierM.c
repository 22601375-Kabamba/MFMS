#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 100
#define STR_LEN 50

typedef struct {
    int id;
    char name[STR_LEN];
    char contact[STR_LEN];
    char goodsSupplied[STR_LEN];
} Supplier;

Supplier suppliers[MAX];
int supplierCount = 0;
int nextId = 1;


void readLine(const char *prompt, char *dest, int size) {
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

int isBlank(const char *s) {
    while (*s) {
        if (!isspace((unsigned char)*s)) return 0;
        s++;
    }
    return 1;
}

int readInt(const char *prompt) {
    char buf[32];
    int value;
    readLine(prompt, buf, sizeof buf);
    if (sscanf(buf, "%d", &value) != 1) return -1;
    return value;
}

int findSupplier(int id) {
    for (int i = 0; i < supplierCount; i++) {
        if (suppliers[i].id == id) return i;
    }
    return -1;
}



void addSupplier(void) {
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
        readLine("Contact: ", s.contact, STR_LEN);
        if (isBlank(s.contact)) printf("Contact cannot be empty.\n");
    } while (isBlank(s.contact));

    readLine("Goods supplied: ", s.goodsSupplied, STR_LEN);

    suppliers[supplierCount++] = s;
    nextId++;
    printf("Supplier added with ID %d.\n", s.id);
}

void viewSuppliers(void) {
    if (supplierCount == 0) {
        printf("No suppliers recorded.\n");
        return;
    }
    printf("\n%-5s %-20s %-20s %-20s\n", "ID", "Name", "Contact", "Goods");
    printf("------------------------------------------------------------------\n");
    for (int i = 0; i < supplierCount; i++) {
        printf("%-5d %-20s %-20s %-20s\n",
               suppliers[i].id, suppliers[i].name,
               suppliers[i].contact, suppliers[i].goodsSupplied);
    }
}

void editSupplier(void) {
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

    printf("Current contact: %s\n", suppliers[idx].contact);
    readLine("New contact: ", buf, STR_LEN);
    if (!isBlank(buf)) strcpy(suppliers[idx].contact, buf);

    printf("Current goods: %s\n", suppliers[idx].goodsSupplied);
    readLine("New goods: ", buf, STR_LEN);
    if (!isBlank(buf)) strcpy(suppliers[idx].goodsSupplied, buf);

    printf("Supplier updated.\n");
}

void deleteSupplier(void) {
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
        printf("3. Edit supplier\n");
        printf("4. Delete supplier\n");
        printf("0. Back\n");
        choice = readInt("Choice: ");

        switch (choice) {
            case 1: addSupplier();    break;
            case 2: viewSuppliers();  break;
            case 3: editSupplier();   break;
            case 4: deleteSupplier(); break;
            case 0: break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 0);
}

int main(void) {
    supplierMenu();
    return 0;
}
