#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

int getValidInt(const char *prompt)
{
    int value;

    printf("%s", prompt);

    while (scanf("%d", &value) != 1)
    {
        printf("Invalid input. Please enter a number: ");
        while (getchar() != '\n');
    }

    while (getchar() != '\n');

    return value;
}

float getValidFloat(const char *prompt)
{
    float value;

    printf("%s", prompt);

    while (scanf("%f", &value) != 1)
    {
        printf("Invalid input. Please enter a number: ");
        while (getchar() != '\n');
    }

    while (getchar() != '\n');

    return value;
}

void getValidString(const char *prompt, char *value, int size)
{
    printf("%s", prompt);

    if (fgets(value, size, stdin) != NULL)
    {
        value[strcspn(value, "\n")] = '\0';
    }
}