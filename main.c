#include <stdio.h>
#include "employees.h"
#include "assets.h"
#include "budget.h"
#include "suppliers.h"
#include "reports.h"
#include "utils.h"

int main(void)
{
    Employee employees[MAX_EMPLOYEES];
    int employeeCount = 0;

    Budget budgets[MAX_BUDGETS];
    int budgetCount = 0;

    Supplier suppliers[MAX_SUPPLIERS];
    int supplierCount = 0;
    
    Reports report[MAX_REPORTS];
    int reportsCount = 0;


    int choice;

    do
    {
        printf("\n====================================\n");
        printf("          MAIN MENU\n");
        printf("====================================\n");
        printf("1. Employee Management\n");
        printf("2. Budget Management\n");
        printf("3. Supplier Management\n");
        printf("4. Asset Management\n");
        printf("5. Report\n");
        printf("6. Exit\n");
        printf("====================================\n");

        choice = getValidInt("Enter choice: ");

        switch (choice)
        {
            case 1:
                employeeMenu(employees, &employeeCount);
                break;

            case 2:
                budgetMenu(budgets, &budgetCount);
                break;

            case 3:
                supplierMenu(suppliers,&supplierCount);
                break;
            case 4:
                displayAssetMenu();
                break;
            
            case 5:
                reportMenu(report,&reportCount);
                break;

            case 6:
                printf("\nExiting program...\n");
                break;

            default:
                printf("\nInvalid choice. Please choose 1-5.\n");
        }

    } while (choice != 6);

    return 0;
}
 
