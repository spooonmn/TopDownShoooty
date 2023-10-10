// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/ItemBase.h"

UItemBase::UItemBase()
{


}

UItemBase* UItemBase::CreateItemCopy()  // add const? 
{

	UItemBase * ItemCopy = NewObject<UItemBase>(StaticClass());

	ItemCopy->ID = this->ID;
	ItemCopy->Quantity = this->Quantity;
	ItemCopy->ItemQuality = this->ItemQuality;
	ItemCopy-> ItemType= this->ItemType;
	ItemCopy-> TextData = this ->TextData;
	ItemCopy-> NumericData = this->NumericData;
	ItemCopy-> AssetData = this->AssetData;
	ItemCopy-> ItemStats = this->ItemStats;

	return ItemCopy;
}

void UItemBase::SetQuantity(const int32 NewQuanttity)
{
	if (NewQuanttity != Quantity)
	{
		Quantity = FMath::Clamp(NewQuanttity, 0, NumericData.bIsStackable ? NumericData.MaxStackSize : 1); // tunerary operator

		//if (OwningInventory)
		//{
		//     if quantity <= 0 
		//		owning inventory remove item(this)
		//}
	}
}

void UItemBase::Use(AMyTopDownCharacter* Character)
{
}
