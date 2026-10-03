#include <stdio.h>
#include "employees.h"
int main(void)
{
Employee employees[MAX_EMPLOYEES];
int employeeCount = 0;
employeeMenu(employees, &employeeCount);
return 0;
}