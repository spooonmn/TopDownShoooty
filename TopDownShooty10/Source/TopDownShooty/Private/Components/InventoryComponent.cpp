// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InventoryComponent.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	
}


void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	
	
}
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


}

FItemAddResult UInventoryComponent::HandleNonStackableItems(UItemBase*, int32 RequestedAddAmount)
{
	return FItemAddResult();
}

int32 UInventoryComponent::HandleStackableItems(UItemBase*, int32 RequestedAddAmount)
{
	return int32();
}

int32 UInventoryComponent::CalculateWeightAddAmount(UItemBase*, int32 RequestedAddAmount)
{
	return int32();
}

int32 UInventoryComponent::CalculateNumberForFullStack(UItemBase* ExistingItem, int32 InitialRequestedAddAmount)
{
	return int32();
}

void UInventoryComponent::AddNewItem(UItemBase* Item, const int32 AmountToAdd)
{
}

FItemAddResult UInventoryComponent::HandleAddItem(UItemBase* InputItem)
{
	return FItemAddResult();
}

UItemBase* UInventoryComponent::FindMatchingItem(UItemBase* Itemin) const
{
	if (ItemIn)
	{
		if(InventoryContents.Contains(ItemIn))
		{
			return ItemIn;
		}
	}
	return nullptr;
}

UItemBase* UInventoryComponent::FindNextItemByID(UItemBase* ItemIn) const
{
	if (ItemIn)
	{
		if (const TArray <TObjectPtr<UItemBase>>::ElementType* Result = InventoryContents.FindByKey(ItemIn)) // getting pointer to ellemt type then dereference pointer idk ;/
		{
			return *Result;
		}
	}
	return nullptr;
}

UItemBase* UInventoryComponent::FindNextPartialStack(UItemBase* ItemIn) const
{
	if (const TArray <TObjectPtr<UItemBase>>::ElementType* Result
		= InventoryContents.FindLastByPredicate([&ItemIn](const UItemBase* InventoryItem)
			{
				return InventoryItem->ID == ItemIn->ID && InventoryItem->IsFullItemStack();
			}
		))
	{
		return *Result;
	}
	return nullptr;
	
}

void UInventoryComponent::RemoveSingleInstanceOfItem(UItemBase* ItemIn)
{
}

int32 UInventoryComponent::RemoveAmountOfItem(UItemBase* ItemIn, int32 DesiredAmountToRemove)
{
	return int32();
}

void UInventoryComponent::SplitExistingStack(UItemBase* ItemIn, const int32 AmountToSplit)
{
}

