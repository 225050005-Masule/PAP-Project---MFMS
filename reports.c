#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "reports.h"

#define MAX_DEPARTMENTS 30
#define LINE_WIDTH 78

static void printLine(char c) {
    for(int i = 0; i < LINE_WIDTH; i++) {
        putchar(c);
    }
    putchar('\n');
}

static int readChoice(int min, int max) {
    char buffer[100];
    int choice;

    while(1) {
        if(fgets(buffer, sizeof(buffer), stdin) == NULL) {
            return max;
        }
        if(buffer[0] == '\n') continue;

        if(sscanf(buffer, "%d", &choice) == 1) {
            if(choice >= min && choice <= max) {
                return choice;
            }
        }
        printf("Invalid choice. Enter a number from %d to %d: ", min, max);
    }
}

double sumOf(const float values[], int count) {
    double sum = 0;
    for(int i = 0; i < count; i++) {
        sum = sum + values[i];
    }
    return sum;
}

double averageOf(const float values[], int count) {
    if(count <= 0) return 0.0;
    double total = sumOf(values, count);
    return total / count;
}

int indexOfMax(const float values[], int count) {
    if(count <= 0) return -1;

    int maxPos = 0;
    for(int i = 1; i < count; i++) {
        if(values[i] > values[maxPos]) {
            maxPos = i;
        }
    }
    return maxPos;
}

int indexOfMin(const float values[], int count) {
    if(count <= 0) return -1;

    int minPos = 0;
    for(int i = 1; i < count; i++) {
        if(values[i] < values[minPos]) {
            minPos = i;
        }
    }
    return minPos;
}

void formatMoney(double amount, char *out, size_t size) {
    
    snprintf(out, size, "N$%.2f", amount);
}

/* ---------------- Menu ---------------- */

int displayReportsMenu(void) {
    printf("\n");
    printLine('=');
    printf("REPORTS\n");
    printLine('=');
    printf("1. Employee Report\n");
    printf("2. Budget Report\n");
    printf("3. Supplier Report\n");
    printf("4. Asset Report\n");
    printf("5. All Reports\n");
    printf("6. Back to Main Menu\n");
    printf("Enter your choice: ");
    return readChoice(1, 6);
}

/* ---------------- 1. Employee report ---------------- */

void employeeReport(int count, const int ids[],
                    char names[][NAME_LEN],
                    char depts[][DEPT_LEN],
                    const float salaries[]) {
    
    char moneyText[32];
    char deptList[MAX_DEPARTMENTS][DEPT_LEN];
    int deptEmployees[MAX_DEPARTMENTS];
    double deptPayroll[MAX_DEPARTMENTS];
    int totalDepts = 0;

    printf("\n");
    printLine('=');
    printf("EMPLOYEE REPORT\n");
    printLine('=');

    if(count <= 0) {
        printf("No employees have been registered yet.\n");
        return;
    }

    int highestPaid = indexOfMax(salaries, count);
    int lowestPaid = indexOfMin(salaries, count);

    printf("Total Employees : %d\n", count);

    formatMoney(averageOf(salaries, count), moneyText, sizeof(moneyText));
    printf("Average Salary  : %s\n", moneyText);

    formatMoney(salaries[highestPaid], moneyText, sizeof(moneyText));
    printf("Highest Salary  : %s (%s)\n", moneyText, names[highestPaid]);

    formatMoney(salaries[lowestPaid], moneyText, sizeof(moneyText));
    printf("Lowest Salary   : %s (%s)\n", moneyText, names[lowestPaid]);

    formatMoney(sumOf(salaries, count), moneyText, sizeof(moneyText));
    printf("Total Payroll   : %s\n", moneyText);


    for(int i = 0; i < count; i++) {
        int pos = -1;

        for(int j = 0; j < totalDepts; j++) {
            if(strcmp(deptList[j], depts[i]) == 0) {
                pos = j;
                break;
            }
        }
        
        if(pos == -1 && totalDepts < MAX_DEPARTMENTS) {
            strcpy(deptList[totalDepts], depts[i]);
            deptEmployees[totalDepts] = 0;
            deptPayroll[totalDepts] = 0.0;
            pos = totalDepts;
            totalDepts++;
        }
        if(pos != -1) {
            deptEmployees[pos]++;
            deptPayroll[pos] += salaries[i];
        }
    }

    printf("\nEmployees per department\n");
    printLine('-');
    printf("%-24s %9s %18s\n", "Department", "Employees", "Total Salaries");
    printLine('-');
    for(int j = 0; j < totalDepts; j++) {
        formatMoney(deptPayroll[j], moneyText, sizeof(moneyText));
        printf("%-24s %9d %18s\n", deptList[j], deptEmployees[j], moneyText);
    }

    printf("\nEmployee listing\n");
    printLine('-');
    printf("%-6s %-22s %-18s %15s\n", "ID", "Name", "Department", "Gross Salary");
    printLine('-');
    for(int i = 0; i < count; i++) {
        formatMoney(salaries[i], moneyText, sizeof(moneyText));
        printf("%-6d %-22s %-18s %15s\n", ids[i], names[i], depts[i], moneyText);
    }
    printLine('-');
}

/* ---------------- 2. Budget report ---------------- */

void budgetReport(int count, char depts[][DEPT_LEN],
                  const float allocated[], const float spent[]) {
    
    char allocText[32], spentText[32], remainText[32];
    int overBudgetCount = 0;

    printf("\n");
    printLine('=');
    printf("BUDGET REPORT\n");
    printLine('=');

    if(count <= 0) {
        printf("No departmental budgets have been entered yet.\n");
        return;
    }

    double totalAlloc = sumOf(allocated, count);
    double totalSpent = sumOf(spent, count);

    formatMoney(totalAlloc, allocText, sizeof(allocText));
    formatMoney(totalSpent, spentText, sizeof(spentText));
    formatMoney(totalAlloc - totalSpent, remainText, sizeof(remainText));

    printf("Total Allocated Budget : %s\n", allocText);
    printf("Total Expenditure      : %s\n", spentText);
    printf("Remaining Budget       : %s\n", remainText);

    printf("\nDepartment breakdown\n");
    printLine('-');
    printf("%-16s %15s %15s %15s %-13s\n",
           "Department", "Allocated", "Spent", "Remaining", "Status");
    printLine('-');
    
    for(int i = 0; i < count; i++) {
        formatMoney(allocated[i], allocText, sizeof(allocText));
        formatMoney(spent[i], spentText, sizeof(spentText));
        formatMoney(allocated[i] - spent[i], remainText, sizeof(remainText));
        
        if(spent[i] > allocated[i]) {
            printf("%-16s %15s %15s %15s %-13s\n", depts[i], allocText, spentText, remainText, "OVER BUDGET");
            overBudgetCount++;
        } else {
            printf("%-16s %15s %15s %15s %-13s\n", depts[i], allocText, spentText, remainText, "WITHIN BUDGET");
        }
    }
    printLine('-');

    printf("\nDepartments exceeding budget: %d\n", overBudgetCount);
    for(int i = 0; i < count; i++) {
        if(spent[i] > allocated[i]) {
            formatMoney(spent[i] - allocated[i], allocText, sizeof(allocText));
            printf("  - %s (over by %s)\n", depts[i], allocText);
        }
    }
}

/* ---------------- 3. Supplier report ---------------- */

void supplierReport(int count, const int ids[],
                    char names[][NAME_LEN],
                    char emails[][EMAIL_LEN],
                    char phones[][PHONE_LEN],
                    char towns[][TOWN_LEN]) {
    
    printf("\n");
    printLine('=');
    printf("SUPPLIER REPORT\n");
    printLine('=');

    if(count <= 0) {
        printf("No suppliers have been registered yet.\n");
        return;
    }

    printf("Total Suppliers: %d\n\n", count);
    printLine('-');
    printf("%-5s %-20s %-24s %-12s %-12s\n", "ID", "Name", "Email", "Phone", "Town");
    printLine('-');
    
    for(int i = 0; i < count; i++) {
        printf("%-5d %-20s %-24s %-12s %-12s\n",
               ids[i], names[i], emails[i], phones[i], towns[i]);
    }
    printLine('-');
}


void assetReport(int count, const int ids[],
                 char names[][NAME_LEN],
                 char types[][ASSET_TYPE_LEN],
                 const float values[],
                 char depts[][DEPT_LEN],
                 char conditions[][CONDITION_LEN]) {
    
    char moneyText[32];

    printf("\n");
    printLine('=');
    printf("ASSET REPORT\n");
    printLine('=');

    if(count <= 0) {
        printf("No assets have been registered yet.\n");
        return;
    }

    int mostValuable = indexOfMax(values, count);

    printf("Total Assets        : %d\n", count);
    
    formatMoney(sumOf(values, count), moneyText, sizeof(moneyText));
    printf("Total Asset Value   : %s\n", moneyText);
    
    formatMoney(values[mostValuable], moneyText, sizeof(moneyText));
    printf("Most Valuable Asset : %s (%s)\n\n", names[mostValuable], moneyText);

    printLine('-');
    printf("%-6s %-16s %-12s %15s %-14s %-10s\n",
           "ID", "Name", "Type", "Value", "Department", "Condition");
    printLine('-');
    
    for(int i = 0; i < count; i++) {
        formatMoney(values[i], moneyText, sizeof(moneyText));
        printf("%-6d %-16s %-12s %15s %-14s %-10s\n",
               ids[i], names[i], types[i], moneyText, depts[i], conditions[i]);
    }
    printLine('-');
}
