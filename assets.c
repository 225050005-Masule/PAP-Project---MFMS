#include <stdio.h>
#include <string.h>
#include "assets.h"


Asset assets[MAX_ASSETS];
int asset_count = 0;

void displayAssetMenu(void) {
    int choice = 0;
    do {
    printf("\n=== ASSET MANAGEMENT MODULE ===\n");
    printf("1. Add New Asset\n");
    printf("2. View All Assets\n");
    printf("3. Search Asset by Name\n");
    printf("4. Save Assets to File\n");
    printf("5. Load Assets from File\n");
    printf("6. Exit Asset Menu\n");
    printf("Enter choice: ");
        if (scanf("%d", &choice) != 1) {

            while (getchar() != '\n');
            continue;
        }
        getchar();

        switch (choice) {
            case 1:
                addAsset();
                break;
            case 2:
                assetsList();
                break;
            case 3:
                searchAsset();
                break;
            case 4:
                saveAssetsToFile();
                break;
            case 5:
                loadAssetsFromFile();
                break;
            case 6:
                printf("Exiting Asset Management Module...\n");
                break;
            default:
                printf("Invalid option! Please enter a number between 1 and 6.\n");
        }
    } while (choice != 6);
}


void addAsset(void) {
    if (asset_count >= MAX_ASSETS) {
        printf("Error: Asset list is full!\n");
        return;
    }

    printf("\nEnter Asset Name: ");
    fgets(assets[asset_count].name, NAME_SIZE, stdin);
    // Remove the newline character added by fgets
    assets[asset_count].name[strcspn(assets[asset_count].name, "\n")] = '\0';

    printf("Enter Asset Type (e.g., Vehicle, Equipment): ");
    fgets(assets[asset_count].type, TYPE_SIZE, stdin);
    assets[asset_count].type[strcspn(assets[asset_count].type, "\n")] = '\0';

    printf("Enter Asset Value (N$): ");
    scanf("%lf", &assets[asset_count].value);

    asset_count++;
    printf("Asset added successfully!\n");
}


void assetsList(void) {
    if (asset_count == 0) {
        printf("\nNo assets found. Try adding or loading some first.\n");
        return;
    }

    printf("\n--- LIST OF REGISTERED ASSETS ---\n");
    for (int i = 0; i < asset_count; i++) {
        printf("%d. Name: %s | Type: %s | Value: N$%.2f\n",
               i + 1, assets[i].name, assets[i].type, assets[i].value);
    }
}


void searchAsset(void) {
    char search[NAME_SIZE];
    int found = 0;

    if (asset_count == 0) {
        printf("\nNo assets to search.\n");
        return;
    }

    printf("\nEnter Asset Name to search for: ");
    fgets(search, NAME_SIZE, stdin);
    search[strcspn(search, "\n")] = '\0';

    for (int i = 0; i < asset_count; i++) {

        if (strcmp(assets[i].name, search) == 0) {
            printf("\n--- Asset Found --- \n");
            printf("Name: %s\n", assets[i].name);
            printf("Type: %s\n", assets[i].type);
            printf("Value: N$%.2f\n", assets[i].value);
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

    for (int i = 0; i < asset_count; i++) {

        fprintf(file, "%s|%s|%.2f\n", assets[i].name, assets[i].type, assets[i].value);
    }

    fclose(file);
    printf("Successfully saved %d assets to assets.txt!\n", asset_count);
}


void loadAssetsFromFile(void) {
    FILE *file = fopen("assets.txt", "r");

    if (file == NULL) {
        printf("Error: Could not open assets.txt (File might not exist yet).\n");
        return;
    }

    asset_count = 0;

    while (fscanf(file, " %49[^|]|%29[^|]|%lf\n",
                  assets[asset_count].name,
                  assets[asset_count].type,
                  &assets[asset_count].value) == 3) {
        asset_count++;
        if (asset_count >= MAX_ASSETS) {
            break;
        }
    }

    fclose(file);
    printf("Successfully loaded %d assets from assets.txt!\n", asset_count);
}


    fclose(file);
    printf("Successfully loaded %d assets from assets.txt!\n", assetCount);
}
