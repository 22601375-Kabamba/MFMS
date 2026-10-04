#ifndef ASSETS_H
#define ASSETS_H

#define MAX_ASSETS 100

typedef struct {
  int assetID;
  char assetName[50];
  char assetType[30];
  float purchaseValue;
  char department[50];
  char condition[30];
} Assert;
void addAsset(Asset assets[], int *assetCount);
void displayAssets(const Asset assets[], int assetCount);
void searchAsset(const Asset assets[], int assetCount);

#endif
