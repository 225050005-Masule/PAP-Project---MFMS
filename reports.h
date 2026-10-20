#ifndef REPORTS_H
#define REPORTS_H

#include <stddef.h>

/* Array sizes. The #ifndef guards let the other modules define the same
   names first without causing a redefinition warning. Make sure the values
   match the ones used in the employee, supplier and asset modules. */
#ifndef NAME_LEN
#define NAME_LEN 50
#endif
#ifndef DEPT_LEN
#define DEPT_LEN 30
#endif
#ifndef EMAIL_LEN
#define EMAIL_LEN 50
#endif
#ifndef PHONE_LEN
#define PHONE_LEN 20
#endif
#ifndef TOWN_LEN
#define TOWN_LEN 30
#endif
#ifndef ASSET_TYPE_LEN
#define ASSET_TYPE_LEN 30
#endif
#ifndef CONDITION_LEN
#define CONDITION_LEN 20
#endif

/* Helper functions */
double sumOf(const float values[], int count);
double averageOf(const float values[], int count);
int indexOfMax(const float values[], int count);
int indexOfMin(const float values[], int count);
void formatMoney(double amount, char *out, size_t size);

/* Menu: returns the option chosen (1 to 6) */
int displayReportsMenu(void);

/* Reports */
void employeeReport(int count, const int ids[],
                    char names[][NAME_LEN],
                    char depts[][DEPT_LEN],
                    const float salaries[]);

void budgetReport(int count, char depts[][DEPT_LEN],
                  const float allocated[], const float spent[]);

void supplierReport(int count, const int ids[],
                    char names[][NAME_LEN],
                    char emails[][EMAIL_LEN],
                    char phones[][PHONE_LEN],
                    char towns[][TOWN_LEN]);

void assetReport(int count, const int ids[],
                 char names[][NAME_LEN],
                 char types[][ASSET_TYPE_LEN],
                 const float values[],
                 char depts[][DEPT_LEN],
                 char conditions[][CONDITION_LEN]);

#endif
