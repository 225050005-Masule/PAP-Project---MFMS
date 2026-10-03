#include <stdio.h>
#include <string.h>
#include "utils.h"
int getValidInt(const char *prompt)
{
int value, result;
do
{
printf("%s", prompt);
result = scanf("%d", &value);
while (getchar() != '\n');
if (result != 1)
printf("Invalid input. Please enter a number.\n");
} while (result != 1);
return value;
}
float getValidFloat(const char *prompt)
{
float value;
int result;
do
{
printf("%s", prompt);
result = scanf("%f", &value);
while (getchar() != '\n');
if (result != 1)
printf("Invalid input. Please enter a number.\n");
} while (result != 1);
return value;
}
void getValidString(const char *prompt, char *value, int size)
{
printf("%s", prompt);
if (fgets(value, size, stdin) != NULL)
value[strcspn(value, "\n")] = '\0';
}