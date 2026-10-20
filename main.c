#include <stdio.h>
#include "employees.h"
#include "assets.h"
#include "budget.h"
#include "suppliers.h"
#include "reports.h"
#include "utils.h"

/* ---- Reports: copy the data from each module's structs into the
        plain arrays that the report functions expect ---- */

static void showEmployeeReport(Employee list[], int count)
{
    int ids[MAX_EMPLOYEES];
    char names[MAX_EMPLOYEES][NAME_LEN];
    char depts[MAX_EMPLOYEES][DEPT_LEN];
    float salaries[MAX_EMPLOYEES];

    for (int i = 0; i < count; i++)
    {
        ids[i] = list[i].id;
        snprintf(names[i], NAME_LEN, "%s", list[i].name);
        snprintf(depts[i], DEPT_LEN, "%s", list[i].department);
        salaries[i] = calculateTotalSalary(list[i]);
    }
    employeeReport(count, ids, names, depts, salaries);
}

static void showBudgetReport(Budget list[], int count)
{
    char depts[MAX_BUDGETS][DEPT_LEN];
    float allocated[MAX_BUDGETS];
    float spent[MAX_BUDGETS];

    for (int i = 0; i < count; i++)
    {
        snprintf(depts[i], DEPT_LEN, "%s", list[i].department);
        allocated[i] = list[i].allocatedBudget;
        spent[i] = list[i].expenditure;
    }
    budgetReport(count, depts, allocated, spent);
}

static void showSupplierReport(Supplier list[], int count)
{
    int ids[MAX_SUPPLIERS];
    char names[MAX_SUPPLIERS][NAME_LEN];
    char emails[MAX_SUPPLIERS][EMAIL_LEN];
    char phones[MAX_SUPPLIERS][PHONE_LEN];
    char towns[MAX_SUPPLIERS][TOWN_LEN];

    for (int i = 0; i < count; i++)
    {
        ids[i] = list[i].id;
        snprintf(names[i], NAME_LEN, "%s", list[i].name);
        snprintf(emails[i], EMAIL_LEN, "%s", list[i].email);
        snprintf(phones[i], PHONE_LEN, "%s", list[i].phone);
        snprintf(towns[i], TOWN_LEN, "%s", list[i].town);
    }
    supplierReport(count, ids, names, emails, phones, towns);
}

/* Assets are stored in the global array declared in assets.h.
   The Asset struct has no ID, department or condition, so the report
   shows the list position as the ID and "N/A" for the other two. */
static void showAssetReport(void)
{
    int ids[MAX_ASSETS];
    char names[MAX_ASSETS][NAME_LEN];
    char types[MAX_ASSETS][ASSET_TYPE_LEN];
    float values[MAX_ASSETS];
    char depts[MAX_ASSETS][DEPT_LEN];
    char conditions[MAX_ASSETS][CONDITION_LEN];

    for (int i = 0; i < asset_count; i++)
    {
        ids[i] = i + 1;
        snprintf(names[i], NAME_LEN, "%s", assets[i].name);
        snprintf(types[i], ASSET_TYPE_LEN, "%s", assets[i].type);
        values[i] = (float)assets[i].value;
        snprintf(depts[i], DEPT_LEN, "N/A");
        snprintf(conditions[i], CONDITION_LEN, "N/A");
    }
    assetReport(asset_count, ids, names, types, values, depts, conditions);
}

static void reportMenu(Employee employees[], int employeeCount,
                       Budget budgets[], int budgetCount,
                       Supplier suppliers[], int supplierCount)
{
    int choice;

    do
    {
        choice = displayReportsMenu();

        switch (choice)
        {
            case 1:
                showEmployeeReport(employees, employeeCount);
                break;
            case 2:
                showBudgetReport(budgets, budgetCount);
                break;
            case 3:
                showSupplierReport(suppliers, supplierCount);
                break;
            case 4:
                showAssetReport();
                break;
            case 5:
                showEmployeeReport(employees, employeeCount);
                showBudgetReport(budgets, budgetCount);
                showSupplierReport(suppliers, supplierCount);
                showAssetReport();
                break;
            case 6:
                printf("\nReturning to Main Menu...\n");
                break;
        }
    } while (choice != 6);
}

int main(void)
{
    Employee employees[MAX_EMPLOYEES];
    int employeeCount = 0;

    Budget budgets[MAX_BUDGETS];
    int budgetCount = 0;

    Supplier suppliers[MAX_SUPPLIERS];
    int supplierCount = 0;

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
                supplierMenu(suppliers, &supplierCount);
                break;

            case 4:
                displayAssetMenu();
                break;

            case 5:
                reportMenu(employees, employeeCount,
                           budgets, budgetCount,
                           suppliers, supplierCount);
                break;

            case 6:
                printf("\nExiting program...\n");
                break;

            default:
                printf("\nInvalid choice. Please choose 1-6.\n");
        }

    } while (choice != 6);

    return 0;
}
