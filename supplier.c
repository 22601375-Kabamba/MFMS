#include <stdio.h>
#include <string.h>
#include "suppliers.h"


Supplier supplierList[MAX_SUPPLIERS];
int supplierCount = 0;

void addSupplier() {
    
    if (supplierCount >= MAX_SUPPLIERS) {
        printf("\nError: System is full. Cannot add more suppliers.\n");
        return;
    }

    printf("\n--- Add New Supplier ---\n");
    int newID;
    int duplicate = 0;

    printf("Enter Supplier ID (positive number): ");
    scanf("%d", &newID);

    if (newID <= 0) {
        printf("Error: ID must be a positive number.\n");
        return;
    }

    for (int i = 0; i < supplierCount; i++) {
        if (supplierList[i].supplierID == newID) {
            duplicate = 1;
            break;
        }
    }
    if (duplicate) {
        printf("Error: A supplier with this ID already exists.\n");
        return;
    }

    supplierList[supplierCount].supplierID = newID;

    printf("Enter Supplier Name: ");
    scanf(" %[^\n]", supplierList[supplierCount].name); // Reads spaces
    
    // Using strlen() for validation
    if (strlen(supplierList[supplierCount].name) == 0) {
        printf("Error: Name cannot be empty.\n");
        return;
    }

    printf("Enter Email: ");
    scanf(" %[^\n]", supplierList[supplierCount].email);

    printf("Enter Telephone: ");
    scanf(" %[^\n]", supplierList[supplierCount].telephone);

    printf("Enter Town/Location: ");
    scanf(" %[^\n]", supplierList[supplierCount].town);

    supplierCount++;
    printf("Success: Supplier added successfully!\n");
}

void displaySuppliers() {
    if (supplierCount == 0) {
        printf("\nNo suppliers registered yet.\n");
        return;
    }

    printf("\n--- Registered Suppliers ---\n");
    for (int i = 0; i < supplierCount; i++) {
        printf("\nSupplier %d:\n", i + 1);
        printf("ID: %d\n", supplierList[i].supplierID);
        printf("Name: %s\n", supplierList[i].name);
        printf("Email: %s\n", supplierList[i].email);
        printf("Telephone: %s\n", supplierList[i].telephone);
        printf("Town: %s\n", supplierList[i].town);
        printf("-----------------------------\n");
    }
}

void searchSupplier() {
    if (supplierCount == 0) {
        printf("\nNo suppliers registered to search.\n");
        return;
    }

    int choice;
    int found = 0;

    printf("\n--- Search Supplier ---\n");
    printf("1. Search by ID\n");
    printf("2. Search by Name\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        // --- SEARCH BY ID ---
        int searchID;
        printf("Enter Supplier ID to search: ");
        scanf("%d", &searchID);

        for (int i = 0; i < supplierCount; i++) {
            if (supplierList[i].supplierID == searchID) {
                printf("\nSupplier Found!\n");
                printf("ID: %d\nName: %s\nEmail: %s\nPhone: %s\nTown: %s\n",
                       supplierList[i].supplierID, supplierList[i].name,
                       supplierList[i].email, supplierList[i].telephone,
                       supplierList[i].town);
                found = 1;
                break;
            }
        }
    } else if (choice == 2) {
        // --- SEARCH BY NAME (Uses strcmp) ---
        char searchName[100];
        printf("Enter Supplier Name to search: ");
        scanf(" %[^\n]", searchName);

        for (int i = 0; i < supplierCount; i++) {
            // USING strcmp() HERE: Returns 0 if strings are identical
            if (strcmp(supplierList[i].name, searchName) == 0) {
                printf("\nSupplier Found!\n");
                printf("ID: %d\nName: %s\nEmail: %s\nPhone: %s\nTown: %s\n",
                       supplierList[i].supplierID, supplierList[i].name,
                       supplierList[i].email, supplierList[i].telephone,
                       supplierList[i].town);
                found = 1;
                break; 
            }
        }
    } else {
        printf("Invalid search choice.\n");
        return;
    }

    if (!found) {
        printf("Error: Supplier not found.\n");
    }
}
