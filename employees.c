#include <stdio.h>
#include <string.h>
#include "employees.h"
#include "utils.h"
float calculateTotalSalary(Employee e)
{
return e.basicSalary + e.housingAllowance + e.transportAllowance;
}
void addEmployee(Employee list[], int *count)
{
if (*count >= MAX_EMPLOYEES)
{
printf("Employee list is full.\n");
return;
}
list[*count].id = getValidInt("Employee ID: ");
getValidString("Name: ", list[*count].name, 50);
getValidString("Department: ", list[*count].department, 30);
list[*count].basicSalary = getValidFloat("Basic Salary: ");
list[*count].housingAllowance = getValidFloat("Housing Allowance: ");
list[*count].transportAllowance = getValidFloat("Transport Allowance: ");
(*count)++;
printf("Employee added successfully.\n");
}
void displayEmployees(Employee list[], int count)
{
int i;
if (count == 0)
{
printf("No employees found.\n");
return;
}
for (i = 0; i < count; i++)
{
printf("\nID: %d\n", list[i].id);
printf("Name: %s\n", list[i].name);
printf("Department: %s\n", list[i].department);
printf("Total Salary: %.2f\n",
calculateTotalSalary(list[i]));
}
}
void searchEmployee(Employee list[], int count)
{
char name[50];
int i;
getValidString("Enter name to search: ", name, 50);
for (i = 0; i < count; i++)
{
if (strcmp(list[i].name, name) == 0)
{
printf("\nID: %d\n", list[i].id);
printf("Name: %s\n", list[i].name);
printf("Department: %s\n", list[i].department);
printf("Basic Salary: %.2f\n", list[i].basicSalary);
printf("Housing Allowance: %.2f\n", list[i].housingAllowance);
printf("Transport Allowance: %.2f\n", list[i].transportAllowance);
printf("Total Salary: %.2f\n",
calculateTotalSalary(list[i]));
return;
}
}
printf("No employee found with that name.\n");
}
void employeeMenu(Employee list[], int *count)
{
int choice;
do
{
printf("\n===== EMPLOYEE MANAGEMENT =====\n");
printf("1. Add Employee\n");
printf("2. Display Employees\n");
printf("3. Search Employee\n");
printf("4. Back to Main Menu\n");
choice = getValidInt("Enter choice: ");
switch (choice)
{
case 1: addEmployee(list, count); break;
case 2: displayEmployees(list, *count); break;
case 3: searchEmployee(list, *count); break;
case 4: printf("Returning to main menu...\n"); break;
default: printf("Invalid choice.\n");
}
} while (choice != 4);
}