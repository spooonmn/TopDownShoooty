// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnInventoryUpdated); // delegate to send signal when inventory is updated

class UItemBase;

UENUM(BlueprintType)
enum class EItemAddResult : uint8
{
	IAR_NoItemAdded UMETA(DisplayName = "No Item Added"),
	IAR_PartialAmountItemAdded UMETA(DisplayName = "Partial Amount of item added"),
	IAR_AllItemAdded UMETA(DisplayName = "All Item Added")
};// how much of the item was added to the inventory

USTRUCT(BlueprintType)
struct FItemAddResult
{
	GENERATED_BODY()

	FItemAddResult() :
		ActualAmountAdded(0),
		OperationResult(EItemAddResult::IAR_NoItemAdded),
		ResultMessage(FText::GetEmpty())
		{};// constructer to set default values of EItemAddResult 

	UPROPERTY(BlueprintReadOnly,Category="Item Added Result")
		int32 ActualAmountAdded; // eg  tried to pick up 5 only picked up 2

	UPROPERTY(BlueprintReadOnly, Category = "Item Added Result")
		EItemAddResult OperationResult; // did we pick up any? none, some or all

	UPROPERTY(BlueprintReadOnly, Category = "Item Added Result")
		FText ResultMessage; // log information

	static FItemAddResult AddedNone(const FText& ErrorMessage) // helper function to create a FItemAddResult for case where no item was added
	{
		FItemAddResult AddedNoneResult;
		AddedNoneResult.ActualAmountAdded = 0;
		AddedNoneResult.OperationResult = EItemAddResult::IAR_NoItemAdded;
		AddedNoneResult.ResultMessage = ErrorMessage;
		return AddedNoneResult;

	};
	static FItemAddResult AddedPartial(const int32 PartialAmountAdded,const FText& ErrorMessage) // helper function to create a FItemAddResult for case where some item was added
	{
		FItemAddResult AddedPartialResult;
		AddedPartialResult.ActualAmountAdded = PartialAmountAdded;
		AddedPartialResult.OperationResult = EItemAddResult::IAR_PartialAmountItemAdded;
		AddedPartialResult.ResultMessage = ErrorMessage;
		return AddedPartialResult;
	};
	static FItemAddResult AddedAll(const int32 AmountAdded, const FText& Message) // helper function to create a FItemAddResult for case where all item was added
	{
		FItemAddResult AddedAllResult;
		AddedAllResult.ActualAmountAdded = AmountAdded;
		AddedAllResult.OperationResult = EItemAddResult::IAR_AllItemAdded;
		AddedAllResult.ResultMessage = Message;
		return AddedAllResult;
	};
};
	



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOPDOWNSHOOTY_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	//properties and variables

	
	// delegete sends signal when inventory is updated ad subscribers that receve the signal will update their UI

	FOnInventoryUpdated OnInventoryUpdated; // delegate to send signal when inventory is updated


	//functions

	UInventoryComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(Category = "Inventory")
		FItemAddResult HandleAddItem(UItemBase* InputItem); // add an item to the inventory
	UPROPERTY(Category = "Inventory")
		UItemBase* FindMatchingItem(UItemBase* Itemin) const; // find an item in the inventory that matches the item passed in
	UPROPERTY(Category = "Inventory")
		UItemBase* FindNextItemByID(UItemBase* ItemIn) const; // find the next item in the inventory that matches the item passed in
	UPROPERTY(Category = "Inventory")
		UItemBase* FindNextPartialStack(UItemBase* ItemIn) const; // find the next partial stack in the inventory that matches the item passed in
	
	UPROPERTY(Category = "Inventory")
		void RemoveSingleInstanceOfItem(UItemBase* ItemIn); // removes all of stack
	UPROPERTY(Category = "Inventory")
		int32 RemoveAmountOfItem(UItemBase* ItemIn, int32 DesiredAmountToRemove); // remove a certain amount of an item from the inventory
	UPROPERTY(Category = "Inventory")
		void SplitExistingStack(UItemBase* ItemIn, const int32 AmountToSplit); // split a stack of items

	// getters
	UPROPERTY(Category = "Inventory")
		FORCEINLINE float GetInventoryTotalWeight() const { return InventoryTotalWeight; }; // get the total weight of the inventory
	UPROPERTY(Category = "Inventory")
		FORCEINLINE float GetWeightCapacity() const { return InventoryWeightCapacity; }; // get the total capacity
	UPROPERTY(Category = "Inventory")
		FORCEINLINE int32 GetSlotCapacity() const { return InventorySlotsCapacity; }; // the macx number of slots in the inventory
	UPROPERTY(Category = "Inventory")
		FORCEINLINE TArray<UItemBase*> GetInventoryContents() const { return InventoryContents; }; // gets referance to inventory contents
	
	// setters
	UPROPERTY(Category = "Inventory")
		FORCEINLINE void SetSlotsCapacity(const int32 NewSlotsCapacity) { InventorySlotsCapacity = NewSlotsCapacity; }; // set the max number of slots in the inventory eg backback upgrade
	UPROPERTY(Category = "Inventory")
		FORCEINLINE void SetWeightCapacity(const float NewWeightCapacity) { InventoryWeightCapacity = NewWeightCapacity; }; // set the max weight of the inventory eg backpack upgrade

protected:

	//properties and variables
	UPROPERTY(EditInstanceOnly,Category = "Inventory")
		float InventoryTotalWeight; // the total weight of the inventory
	UPROPERTY(VisibleAnywhere, Category = "Inventory")
		int32 InventorySlotsCapacity; // the max number of slots in the inventory
	UPROPERTY(EditInstanceOnly, Category = "Inventory")
		float InventoryWeightCapacity; // the max weight of the inventory

	UPROPERTY(VisibleAnywhere, Category = "Inventory")
		TArray<TObjectPtr<UItemBase>> InventoryContents; // the contents of the inventory






	// functions

	virtual void BeginPlay() override;


	FItemAddResult HandleNonStackableItems(UItemBase* ,int32 RequestedAddAmount); // handle items that are not stackable
	int32 HandleStackableItems(UItemBase* , int32 RequestedAddAmount); // handle items that are stackable
	int32 CalculateWeightAddAmount(UItemBase* , int32 RequestedAddAmount); // calculate the weight of the item to be added
	int32 CalculateNumberForFullStack(UItemBase* ExistingItem , int32 InitialRequestedAddAmount); // calculate the number of items that can be added to a full stack
		
	void AddNewItem(UItemBase* Item, const int32 AmountToAdd); // add a new item to the inventory

};
