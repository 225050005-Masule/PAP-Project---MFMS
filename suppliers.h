#ifndef SUPPLIERS_H
#define SUPPLIERS_H

#define MAX_SUPPLIERS 100
#define SUPPLIER_NAME_LEN 64
#define SUPPLIER_EMAIL_LEN 64
#define SUPPLIER_PHONE_LEN 20
#define SUPPLIER_TOWN_LEN 64

typedef struct
{
    int id;
    char name[SUPPLIER_NAME_LEN];
    char email[SUPPLIER_EMAIL_LEN];
    char phone[SUPPLIER_PHONE_LEN];
    char town[SUPPLIER_TOWN_LEN];
} Supplier;

int isValidEmail(char email[]);
void addSupplier(Supplier list[], int *count);
void displaySuppliers(Supplier list[], int count);
void searchSupplier(Supplier list[], int count);
void searchSupplierByTown(Supplier list[], int count);
void supplierMenu(Supplier list[], int *count);

#endif