#include <stdio.h>
#include <string.h>
#include "suppliers.h"
#include "utils.h"

void addSupplier(Supplier list[], int *count)
{
    if (*count >= MAX_SUPPLIERS) {
        printf("\nSupplier list is full.\n");
        return;
    }

    printf("\n===== ADD SUPPLIER =====\n");
    list[*count].id = getValidInt("Enter Supplier ID: ");
    
    getValidString("Enter Supplier Name: ", list[*count].name, 50);
    while (strlen(list[*count].name) == 0) {
        printf("Name cannot be empty. Please try again.\n");
        getValidString("Enter Supplier Name: ", list[*count].name, 50);
    }

    getValidString("Enter Email: ", list[*count].email, 50);
    while (strchr(list[*count].email, '@') == NULL || strchr(list[*count].email, '.') == NULL) {
        printf("Invalid email format. Please try again.\n");
        getValidString("Enter Email: ", list[*count].email, 50);
    }

    getValidString("Enter Phone Number: ", list[*count].phone, 20);
    while (strlen(list[*count].phone) == 0) {
        printf("Phone cannot be empty. Please try again.\n");
        getValidString("Enter Phone Number: ", list[*count].phone, 20);
    }

    getValidString("Enter Town: ", list[*count].town, 30);
    while (strlen(list[*count].town) == 0) {
        printf("Town cannot be empty. Please try again.\n");
        getValidString("Enter Town: ", list[*count].town, 30);
    }

    (*count)++;
    printf("\nSupplier added successfully!\n");
}

void displaySuppliers(Supplier list[], int count)
{
    if (count == 0) {
        printf("\nNo suppliers available.\n");
        return;
    }

    printf("\n========== SUPPLIER INFORMATION ==========\n");
    for (int i = 0; i < count; i++) {
        printf("\nSupplier ID: %d\n", list[i].id);
        printf("Name: %s\n", list[i].name);
        printf("Email: %s\n", list[i].email);
        printf("Phone: %s\n", list[i].phone);
        printf("Town: %s\n", list[i].town);
        printf("----------------------------------------\n");
    }
}

void searchSupplier(Supplier list[], int count)
{
    if (count == 0) {
        printf("\nNo suppliers available.\n");
        return;
    }

    int id = getValidInt("\nEnter supplier ID to search: ");
    int found = 0;

    for (int i = 0; i < count; i++) {
        if (list[i].id == id) {
            printf("\n===== SUPPLIER FOUND =====\n");
            printf("Supplier ID: %d\n", list[i].id);
            printf("Name: %s\n", list[i].name);
            printf("Email: %s\n", list[i].email);
            printf("Phone: %s\n", list[i].phone);
            printf("Town: %s\n", list[i].town);
            found = 1;
        }
    }

    if (found == 0) {
        printf("\nNo supplier found with that ID.\n");
    }
}

void searchSupplierByTown(Supplier list[], int count)
{
    if (count == 0) {
        printf("\nNo suppliers available.\n");
        return;
    }

    char town[30];
    getValidString("\nEnter town to search: ", town, 30);
    
    printf("\n===== SUPPLIERS IN %s =====\n", town);
    int found = 0;

    for (int i = 0; i < count; i++) {
        if (strcmp(list[i].town, town) == 0) {
            printf("\nSupplier ID: %d\n", list[i].id);
            printf("Name: %s\n", list[i].name);
            printf("Phone: %s\n", list[i].phone);
            printf("----------------------------------------\n");
            found = 1;
        }
    }

    if (found == 0) {
        printf("\nNo suppliers found in that town.\n");
    }
}

void supplierMenu(Supplier list[], int *count)
{
    int choice;

    do {
        printf("\n====================================\n");
        printf("       SUPPLIER MANAGEMENT\n");
        printf("====================================\n");
        printf("1. Add Supplier\n");
        printf("2. Display Suppliers\n");
        printf("3. Search Supplier by ID\n");
        printf("4. Search Suppliers by Town\n");
        printf("5. Back to Main Menu\n");
        printf("====================================\n");

        choice = getValidInt("Enter choice: ");

        switch (choice) {
            case 1:
                addSupplier(list, count);
                break;
            case 2:
                displaySuppliers(list, *count);
                break;
            case 3:
                searchSupplier(list, *count);
                break;
            case 4:
                searchSupplierByTown(list, *count);
                break;
            case 5:
                printf("\nReturning to Main Menu...\n");
                break;
            default:
                printf("\nInvalid choice. Please choose 1-5.\n");
        }
    } while (choice != 5);
}
