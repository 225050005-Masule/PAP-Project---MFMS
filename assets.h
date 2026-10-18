#ifndef ASSETS_H
#define ASSETS_H

#define MAX_ASSETS 50
#define NAME_SIZE 50
#define TYPE_SIZE 30

typedef struct {
    char name[NAME_SIZE];
    char type[TYPE_SIZE];
    double value;
} Asset;

extern Asset assets[MAX_ASSETS];
extern int asset_count;

void displayAssetMenu(void);
void addAsset(void);
void assetsList(void);
void searchAsset(void);
void saveAssetsToFile(void);
void loadAssetsFromFile(void);

#endif
