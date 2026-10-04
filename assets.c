#include <stdio.h>
#include <string.h>
#include "assets.h"


#define MAX_ASSETS 50
#define NAME_SIZE 50
#define TYPE_SIZE 30


char assetName[MAX_ASSETS][NAME_SIZE];
char assetType[MAX_ASSETS][TYPE_SIZE];
double assetValue[MAX_ASSETS];
int assetCount = 0;


void displayAssetMenu(void) {
    printf("\n=== ASSET MANAGEMENT MODULE ===\n");
    printf("1. Add New Asset\n");
    printf("2. View All Assets\n");
    printf("3. Search Asset by Name\n");
    printf("4. Save Assets to File\n");
    printf("5. Load Assets from File\n");
    printf("6. Exit Asset Menu\n");
    printf("Enter choice: ");
}


void addAsset(void) {
    if (assetCount >= MAX_ASSETS) {
        printf("Error: Asset list is full!\n");
        return;
    }

    
    getchar();

    printf("\nEnter Asset Name: ");
    fgets(assetName[assetCount], NAME_SIZE, stdin);
    // Remove the newline character added by fgets
    assetName[assetCount][strcspn(assetName[assetCount], "\n")] = '\0';

    printf("Enter Asset Type (e.g., Vehicle, Equipment): ");
    fgets(assetType[assetCount], TYPE_SIZE, stdin);
    assetType[assetCount][strcspn(assetType[assetCount], "\n")] = '\0';

    printf("Enter Asset Value (N$): ");
    scanf("%lf", &assetValue[assetCount]);

    assetCount++;
    printf("Asset added successfully!\n");
}


void assetsList(void) {
    if (assetCount == 0) {
        printf("\nNo assets found. Try adding or loading some first.\n");
        return;
    }

    printf("\n--- LIST OF REGISTERED ASSETS ---\n");
    for (int i = 0; i < assetCount; i++) {
        printf("%d. Name: %s | Type: %s | Value: N$%.2f\n", 
               i + 1, assetName[i], assetType[i], assetValue[i]);
    }
}


void searchAsset(void) {
    char search[NAME_SIZE];
    int found = 0;

    if (assetCount == 0) {
        printf("\nNo assets to search.\n");
        return;
    }

    getchar(); 
    printf("\nEnter Asset Name to search for: ");
    fgets(search, NAME_SIZE, stdin);
    search[strcspn(search, "\n")] = '\0';

    for (int i = 0; i < assetCount; i++) {
        
        if (strcmp(assetName[i], search) == 0) {
            printf("\n--- Asset Found --- \n");
            printf("Name: %s\n", assetName[i]);
            printf("Type: %s\n", assetType[i]);
            printf("Value: N$%.2f\n", assetValue[i]);
            found = 1;
            break;
        }
    }

    if (found == 0) {
        printf("Asset '%s' not found in records.\n", search);
    }
}


void saveAssetsToFile(void) {
    FILE *file = fopen("assets.txt", "w");

    if (file == NULL) {
        printf("Error: Could not open file for writing.\n");
        return;
    }

    for (int i = 0; i < assetCount; i++) {
        
        fprintf(file, "%s|%s|%.2f\n", assetName[i], assetType[i], assetValue[i]);
    }

    fclose(file);
    printf("Successfully saved %d assets to assets.txt!\n", assetCount);
}


void loadAssetsFromFile(void) {
    FILE *file = fopen("assets.txt", "r");

    if (file == NULL) {
        printf("Error: Could not open assets.txt (File might not exist yet).\n");
        return;
    }

    assetCount = 0; 
    
    while (fscanf(file, " %49[^|]|%29[^|]|%lf\n", 
                  assetName[assetCount], 
                  assetType[assetCount], 
                  &assetValue[assetCount]) == 3) {
        assetCount++;
        if (assetCount >= MAX_ASSETS) {
            break;
        }
    }

    fclose(file);
    printf("Successfully loaded %d assets from assets.txt!\n", assetCount);
}