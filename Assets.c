#include <stdio.h>
#include <string.h>
#include "assets.h"

Asset assets[MAX_ASSETS];

int assetCount = 0;

/*Add a new asset*/
void addAsset()
{
    if (assetCount >= MAX_ASSETS)
    {
        printf("\nAsset register is full.\n");
        return;
    }

    printf("\n========== Add Asset ==========\n");

    printf("Enter assetID: ");
    scanf("%d", &assets[assetCount].assetID);
    getchar();

    printf("Enter asset name: ");
    fgets(assets[assetCount].assetName, sizeof(assets[assetCount].assetName), stdin);
    assets[assetCount].assetName[strcspn(assets[assetCount].assetName, "\n")] = '\0';

    printf("Enter asset type: ");
    fgets(assets[assetCount].assetType, sizeof(assets[assetCount].assetType), stdin);
    assets[assetCount].assetType[strcspn(assets[assetCount].assetType, "\n")] = '\0';
    printf("Enter asset purchase value: ");
    scanf("%f", &assets[assetCount].purchaseValue);
    getchar();

    if (assets[assetCount].purchaseValue < 0)
    {
        printf("Purchase value cannot be negative. Asset not added.\n");
        return;
    }
    printf("Enter department: ");
    fgets(assets[assetCount].department, sizeof(assets[assetCount].department), stdin); 
    assets[assetCount].department[strcspn(assets[assetCount].department, "\n")] = '\0';
    printf("Enter condition: ");
    fgets(assets[assetCount].condition, sizeof(assets[assetCount].condition), stdin);
    assets[assetCount].condition[strcspn(assets[assetCount].condition, "\n")] = '\0';
    assetCount++;
    printf("Asset added successfully.\n");

}

/* Display all assets */
void displayAssets()
{
    int i;
    if (assetCount == 0)
    {
        printf("\nNo assets have been registered.\n");
        return;
    }
    printf("\n========== Display Assets ==========\n");
    for (i = 0; i < assetCount; i++)
    {
        printf("Asset %d:\n", i + 1);
    
    
    printf("----------------------------------------\n");
        printf("Asset ID: %d\n", assets[i].assetID);
        printf("Asset Name: %s\n", assets[i].assetName);
        printf("Asset Type: %s\n", assets[i].assetType);
        printf("Purchase Value: %.2f\n", assets[i].purchaseValue);
        printf("Department: %s\n", assets[i].department);
        printf("Condition: %s\n", assets[i].condition);
        
    }
    printf("----------------------------------------\n");
}
/* Search for an asset by ID */
void searchAssetByID()
{
    int searchID;
    int i;
    int found = 0;
    if (assetCount == 0)
    {
        printf("\nNo assets have been registered.\n");
        return;
    }
    printf("\n========== Search Asset ==========\n");
    printf("Enter asset ID to search: ");
    scanf("%d", &searchID);
    for (i = 0; i < assetCount; i++)
    {
        if (assets[i].assetID == searchID)
        {
            printf("Asset found:\n");
            printf("Asset ID: %d\n", assets[i].assetID);
            printf("Asset Name: %s\n", assets[i].assetName);
            printf("Asset Type: %s\n", assets[i].assetType);
            printf("Purchase Value: %.2f\n", assets[i].purchaseValue);
            printf("Department: %s\n", assets[i].department);
            printf("Condition: %s\n", assets[i].condition);
            found = 1;
            break;
        }
    }
    if (!found)
    {
        printf("Asset not found.\n");
    }
}
