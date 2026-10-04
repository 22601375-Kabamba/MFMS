#ifndef SUPPLIERS_H
#define SUPPLIERS_H

#define MAX_SUPPLIERS 100

typedef struct {
    int supplierID;
    char name[100];
    char email[100];
    char telephone[20];
    char town[50];
} Supplier;

// Function prototypes
void addSupplier();
void displaySuppliers();
void searchSupplier();

#endif
