#include <stdio.h>
#include <string.h>
#include "budget.h"
#include "utils.h"
float calculateRemainingBudget(Budget budget)
{
    return budget.allocatedBudget - budget.expenditure;
}
void addBudget(Budget list[], int *count)
{
    if (*count >= MAX_BUDGETS)
    {
        printf("\nBudget list is full.\n");
        return;
    }
    printf("\n===== ADD BUDGET =====\n");
    list[*count].id = getValidInt("Enter Budget ID: ");
    getValidString("Enter Department: ",
                   list[*count].department,
                   sizeof(list[*count].department));
    do
    {
        list[*count].allocatedBudget =
            getValidFloat("Enter Allocated Budget: ");
        if (list[*count].allocatedBudget < 0)
            printf("Budget cannot be negative. Please try again.\n");
    } while (list[*count].allocatedBudget < 0);
    do
    {
        list[*count].expenditure =
            getValidFloat("Enter Expenditure: ");
        if (list[*count].expenditure < 0)
            printf("Expenditure cannot be negative. Please try again.\n");
    } while (list[*count].expenditure < 0);
    (*count)++;
    printf("\nBudget added successfully!\n");
}
void displayBudgets(Budget list[], int count)
{
    if (count == 0)
    {
        printf("\nNo budgets available.\n");
        return;
    }
    printf("\n========== BUDGET INFORMATION ==========\n");
    for (int i = 0; i < count; i++)
    {
        float remaining = calculateRemainingBudget(list[i]);
        printf("\nBudget ID: %d\n", list[i].id);
        printf("Department: %s\n", list[i].department);
        printf("Allocated Budget: N$%.2f\n", list[i].allocatedBudget);
        printf("Expenditure: N$%.2f\n", list[i].expenditure);
        printf("Remaining Budget: N$%.2f\n", remaining);
        if (list[i].expenditure <= list[i].allocatedBudget)
            printf("Status: WITHIN BUDGET\n");
        else
            printf("Status: OVER BUDGET\n");
        printf("----------------------------------------\n");
    }
}
void searchBudget(Budget list[], int count)
{
    char department[50];
    int found = 0;
    if (count == 0)
    {
        printf("\nNo budgets available.\n");
        return;
    }
    getValidString("\nEnter department to search: ",
                   department, sizeof(department));
    for (int i = 0; i < count; i++)
    {
        if (strcmp(list[i].department, department) == 0)
        {
            float remaining = calculateRemainingBudget(list[i]);
            printf("\n===== BUDGET FOUND =====\n");
            printf("Budget ID: %d\n", list[i].id);
            printf("Department: %s\n", list[i].department);
            printf("Allocated Budget: N$%.2f\n", list[i].allocatedBudget);
            printf("Expenditure: N$%.2f\n", list[i].expenditure);
            printf("Remaining Budget: N$%.2f\n", remaining);
            if (list[i].expenditure <= list[i].allocatedBudget)
                printf("Status: WITHIN BUDGET\n");
            else
                printf("Status: OVER BUDGET\n");
            found = 1;
            break;
        }
    }
    if (!found)
        printf("\nNo budget found for that department.\n");
}
void budgetMenu(Budget list[], int *count)
{
    int choice;
    do
    {
        printf("\n====================================\n");
        printf("        BUDGET MANAGEMENT\n");
        printf("====================================\n");
        printf("1. Add Budget\n");
        printf("2. Display Budgets\n");
        printf("3. Search Budget\n");
        printf("4. Back to Main Menu\n");
        printf("====================================\n");
        choice = getValidInt("Enter choice: ");
        switch (choice)
        {
            case 1:
                addBudget(list, count);
                break;
            case 2:
                displayBudgets(list, *count);
                break;
            case 3:
                searchBudget(list, *count);
                break;
            case 4:
                printf("\nReturning to Main Menu...\n");
                break;
            default:
                printf("\nInvalid choice. Please choose 1-4.\n");
        }
    } while (choice != 4);
}