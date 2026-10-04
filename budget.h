#ifndef BUDGET_H 
#define BUDGET_H 
#define MAX_BUDGETS 100 
typedef struct
 {   
     int id;   
    char department[50];    
    float allocatedBudget;    
    float expenditure; 
} Budget;

void addBudget(Budget list[], int *count);
 void displayBudgets(Budget list[], int count);
float calculateRemainingBudget(Budget budget);
void searchBudget(Budget list[], int count);
 void budgetMenu(Budget list[], int *count);

 #endif