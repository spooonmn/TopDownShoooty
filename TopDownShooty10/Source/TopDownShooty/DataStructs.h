// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "DataStructs.generated.h"


/**
 * 
 */
class TOPDOWNSHOOTY_API DataStructs
{
public:
	DataStructs();
	~DataStructs();
};
UENUM()
enum class EItemQuality : uint8 //enum is a list of options for the data table
{
	// the quality of the item 
	Shoddy UMETA(DisplayName = "Shoddy"),
	Common UMETA(DisplayName = "Common"),
	Quality UMETA(DisplayName = "Quality"),
	Masterwork UMETA(DisplayName = "Masterwork"),
	Grandmaster UMETA(DisplayName = "Grandmaster")
};

UENUM()
enum class EItemType : uint8 //enum is used to categorize the item
{
	//the type of the item
	Weapon UMETA(DisplayName = "Weapon"),
	Armor UMETA(DisplayName = "Armor"),
	Consumable UMETA(DisplayName = "Consumable"),
	shield UMETA(DisplayName = "Shield"),
	quest UMETA(DisplayName = "Quest"),
	spell UMETA(DisplayName = "Spell"),
	Other UMETA(DisplayName = "Other")
};

USTRUCT()
struct FItemStats // structs are used to store the data of the item
{
	//this is the stats of the item

	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
		float Damage;
	UPROPERTY(EditAnywhere)
		float ArmorRating;
	UPROPERTY(EditAnywhere)
		float DamageValue;
	UPROPERTY(EditAnywhere)
		float RestorationValue;
	UPROPERTY(EditAnywhere)
		float SellValue;
};


USTRUCT() //this is used to make the struct work it is for UE
struct FItemTextData
{
	//this is the text data of the item
	GENERATED_USTRUCT_BODY() //this is used to make the struct work 

		UPROPERTY(EditAnywhere)
		FText ItemName;
	UPROPERTY(EditAnywhere)
		FText ItemDescription;
	UPROPERTY(EditAnywhere)
		FText InteractionText;
	UPROPERTY(EditAnywhere)
		FText UsageText;
};

USTRUCT()
struct FItemNumericData
{
	//this is the numeric data of the item
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
		float Weight;
	UPROPERTY(EditAnywhere)
		int32 MaxStackSize;
	UPROPERTY(EditAnywhere)
		bool bIsStackable;
};

USTRUCT()
struct FItemAssetData
{
	//this is the asset data of the item
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere)
		UTexture2D* Icon;
	UPROPERTY(EditAnywhere)
		UStaticMesh* Mesh;


};

USTRUCT()
struct FItemStruct : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
		// a list of all the data of the item

	UPROPERTY(EditAnywhere, Category = "Item Data")
		FName ID;

	UPROPERTY(EditAnywhere, Category = "Item Data")
		EItemQuality ItemQuality;

	UPROPERTY(EditAnywhere, Category = "Item Data")
		EItemType ItemType;

	UPROPERTY(EditAnywhere, Category = "Item Data")
		FItemStats ItemStats;

	UPROPERTY(EditAnywhere, Category = "Item Data")
		FItemTextData TextData;

	UPROPERTY(EditAnywhere, Category = "Item Data")
		FItemNumericData NumericData;

	UPROPERTY(EditAnywhere, Category = "Item Data")
		FItemAssetData AssetData;

};