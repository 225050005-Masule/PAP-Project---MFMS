#include <stdio.h>
#include <stdlib.h>
#include "reports.h"

static void employee_report(void) {
    int index;
    float total_salary = 0;

    for (index = 0; index < employee_count; index++) {
        total_salary += employees[index].salary;
    }
    printf("\nEmployee Report\nTotal employees: %d\nTotal salary: %.2f\n",
           employee_count, total_salary);
    if (employee_count == 0) {
        printf("No employees found.\n");
    }
    for (index = 0; index < employee_count; index++) {
        printf("ID: %d | %s | %s | Salary: %.2f\n", employees[index].id,
               employees[index].name, employees[index].position,
               employees[index].salary);
    }
}


static void budget_report(void) {
    int index;
    float total_allocated = 0;
    float total_spent = 0;

    printf("\nBudget Report\n");
    if (budget_count == 0) {
        printf("No budgets found.\n");
    }
    for (index = 0; index < budget_count; index++) {
        printf("%s | Allocated: %.2f | Spent: %.2f | Remaining: %.2f\n",
               budgets[index].department, budgets[index].allocated_amount,
               budgets[index].spent_amount,
               budgets[index].allocated_amount - budgets[index].spent_amount);
        total_allocated += budgets[index].allocated_amount;
        total_spent += budgets[index].spent_amount;
    }
    printf("Total allocated: %.2f\nTotal spent: %.2f\n",
           total_allocated, total_spent);
}


static void asset_report(void) {
    int index;
    float total_value = 0;

    for (index = 0; index < asset_count; index++) {
        total_value += assets[index].value;
    }
    printf("\nAsset Report\nTotal assets: %d\nTotal asset value: %.2f\n",
           asset_count, total_value);
}


void reports_menu(void) {
    int choice;

    while (1) {
        printf("\nReports\n1. Employee Report\n2. Budget Report\n3. Asset Report\n4. Back\n");
        if (!read_int("Choose an option: ", &choice)) {
            return;
        }
        switch (choice) {
            case 1: employee_report(); break;
            case 2: budget_report(); break;
            case 3: asset_report(); break;
            case 4: return;
            default: printf("Invalid choice.\n");
        }
    }
}
