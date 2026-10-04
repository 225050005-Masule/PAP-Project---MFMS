#include <stdio.h>
#include "employees.h"
#include "budget.h"
#include "utils.h"

int main(void)
{
    Employee employees[MAX_EMPLOYEES];
    int employeeCount = 0;

    Budget budgets[MAX_BUDGETS];
    int budgetCount = 0;

    int choice;

    do
    {
        printf("\n====================================\n");
        printf("          MAIN MENU\n");
        printf("====================================\n");
        printf("1. Employee Management\n");
        printf("2. Budget Management\n");
        printf("3. Exit\n");
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
                printf("\nExiting program...\n");
                break;

            default:
                printf("\nInvalid choice. Please choose 1-3.\n");
        }

    } while (choice != 3);

    return 0;
}