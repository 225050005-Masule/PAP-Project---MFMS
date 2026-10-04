#include <stdio.h>
#include <string.h>
#include "suppliers.h"
#include "utils.h"

int isValidEmail(char email[])
{
    char *at;

    at = strchr(email, '@');
    if (at == NULL)
        return 0;
    if (at == email)
        return 0;
    if (strchr(at, '.') == NULL)
        return 0;
    return 1;
}

void addSupplier(Supplier list[], int *count)
{
    if (*count >= MAX_SUPPLIERS)
    {
        printf("\nSupplier list is full.\n");
        return;
    }

    printf("\n===== ADD SUPPLIER =====\n");
    list[*count].id = getValidInt("Enter Supplier ID: ");

    do
    {
        getValidString("Enter Supplier Name: ",
                       list[*count].name,
                       sizeof(list[*count].name));
        if (strlen(list[*count].name) == 0)
            printf("Name cannot be empty. Please try again.\n");
    } while (strlen(list[*count].name) == 0);

    do
    {
        getValidString("Enter Email: ",
                       list[*count].email,
                       sizeof(list[*count].email));
        if (!isValidEmail(list[*count].email))
            printf("Invalid email format. Please try again.\n");
    } while (!isValidEmail(list[*count].email));

    do
    {
        getValidString("Enter Phone Number: ",
                       list[*count].phone,
                       sizeof(list[*count].phone));
        if (strlen(list[*count].phone) == 0)
            printf("Phone cannot be empty. Please try again.\n");
    } while (strlen(list[*count].phone) == 0);

    do
    {
        getValidString("Enter Town: ",
                       list[*count].town,
                       sizeof(list[*count].town));
        if (strlen(list[*count].town) == 0)
            printf("Town cannot be empty. Please try again.\n");
    } while (strlen(list[*count].town) == 0);

    (*count)++;
    printf("\nSupplier added successfully!\n");
}

void displaySuppliers(Supplier list[], int count)
{
    if (count == 0)
    {
        printf("\nNo suppliers available.\n");
        return;
    }

    printf("\n========== SUPPLIER INFORMATION ==========\n");
    for (int i = 0; i < count; i++)
    {
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
    int id;
    int found = 0;

    if (count == 0)
    {
        printf("\nNo suppliers available.\n");
        return;
    }

    id = getValidInt("\nEnter supplier ID to search: ");

    for (int i = 0; i < count; i++)
    {
        if (list[i].id == id)
        {
            printf("\n===== SUPPLIER FOUND =====\n");
            printf("Supplier ID: %d\n", list[i].id);
            printf("Name: %s\n", list[i].name);
            printf("Email: %s\n", list[i].email);
            printf("Phone: %s\n", list[i].phone);
            printf("Town: %s\n", list[i].town);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("\nNo supplier found with that ID.\n");
}

void searchSupplierByTown(Supplier list[], int count)
{
    char town[SUPPLIER_TOWN_LEN];
    int found = 0;

    if (count == 0)
    {
        printf("\nNo suppliers available.\n");
        return;
    }

    getValidString("\nEnter town to search: ", town, sizeof(town));

    printf("\n===== SUPPLIERS IN %s =====\n", town);
    for (int i = 0; i < count; i++)
    {
        if (strcmp(list[i].town, town) == 0)
        {
            printf("\nSupplier ID: %d\n", list[i].id);
            printf("Name: %s\n", list[i].name);
            printf("Phone: %s\n", list[i].phone);
            printf("----------------------------------------\n");
            found = 1;
        }
    }

    if (!found)
        printf("\nNo suppliers found in that town.\n");
}

void supplierMenu(Supplier list[], int *count)
{
    int choice;

    do
    {
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

        switch (choice)
        {
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