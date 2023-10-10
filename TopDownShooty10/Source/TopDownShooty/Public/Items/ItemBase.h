// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TopDownShooty\DataStructs.h" // if i wonna include my own Header file i need to include the path to it if it is not in the same folder as the class i am using it in
#include "TopDownShooty\MyTopDownCharacter.h"

#include "ItemBase.generated.h"


UCLASS()
class TOPDOWNSHOOTY_API UItemBase : public UObject
{
	GENERATED_BODY()

		// a list of all the data of the item

public:
	//==================================================================================================================================================================================================
	// 
	// P R O P E R T I E S   &   V A R I A B L E S
	// 
	//==================================================================================================================================================================================================
	//UPROPERTY()
		//UInventoryComponent * OwningInventory; // this is a pointer to the inventory that owns this item
	
	//create a static int variable



	UPROPERTY(VisibleAnywhere, Category = "Item", meta = (UIMin = 1,UIMAX = 100)) // sets the min and max value for the quantity
		int32 Quantity; // this is on top level since its always changed

	UPROPERTY(VisibleAnywhere, Category = "Item")
		FName ID;

	UPROPERTY(VisibleAnywhere, Category = "Item")
		EItemQuality ItemQuality;

	UPROPERTY(VisibleAnywhere, Category = "Item")
		EItemType ItemType;

	UPROPERTY(VisibleAnywhere, Category = "Item")
		FItemStats ItemStats;

	UPROPERTY(VisibleAnywhere, Category = "Item")
		FItemTextData TextData;

	UPROPERTY(VisibleAnywhere, Category = "Item")
		FItemNumericData NumericData;

	UPROPERTY(VisibleAnywhere, Category = "Item")
		FItemAssetData AssetData;

	
	//==================================================================================================================================================================================================
	//
	//	F U N C T I O N S
	//
	//==================================================================================================================================================================================================

	UItemBase();

	UItemBase * CreateItemCopy(); //pointer to the item that is created

	//FORCEINLINE means that the function will be inlined by the compiler, which means that the compiler will replace the function call with the actual code of the function, which will result in faster execution time. beacuse this would be used lot
	UFUNCTION(Category = "Item")
	FORCEINLINE float GetItemStackWeight() const { return Quantity * NumericData.Weight; }; // this is a function that returns the weight of the item stack this is a constant function so it can be used in other const functions

	UFUNCTION(Category = "Item")
	FORCEINLINE float GetItemSingleWeight() const { return NumericData.Weight; };

	UFUNCTION(Category = "Item")
	FORCEINLINE bool IsFullItemStack() const {return Quantity == NumericData.MaxStackSize; }; // this is a function that returns true if the item stack is full

	UFUNCTION(Category = "Item")
	void SetQuantity(const int32 NewQuanttity);

	UFUNCTION(Category = "Item")
	virtual void Use(AMyTopDownCharacter* Character); // this is a virtual function that can be overriden by the child classes




protected:
	//==================================================================================================================================================================================================
	//
	//	P R I V A T E
	//
	//==================================================================================================================================================================================================
	//protected means that the child classes can access this but not the other classes

	// when you overload  comparison operator by searching for an ID it will return true if the ID is the same
	// comparison using Tarray functions      // FName is a type of string short designator
	bool operator == (const FName& OtherID) const
	{
		return this->ID == OtherID;
	}
};
