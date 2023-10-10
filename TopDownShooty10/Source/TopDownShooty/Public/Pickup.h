// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/InteractionInterface.h"
//#include <Items/ItemBase.h>
#include "Pickup.generated.h"

class UDataTable;
class UItemBase;
UCLASS()
class TOPDOWNSHOOTY_API APickup : public AActor, public IInteractionInterface
{
	GENERATED_BODY()

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void BeginFocus() override;
	virtual void EndFocus() override;
	


	//functions

	APickup();

	void InitializePickup(const TSubclassOf<UItemBase> BaseClass, const int32 InQuantity);

	void InitializeDrop(UItemBase* ItemDrop, const int32 InQuantity);

	FORCEINLINE UItemBase* GetItemData() { return ItemReference; }


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere,Category = "Pickup | Components")
		UStaticMeshComponent* PickupMesh;

	UPROPERTY(EditInstanceOnly, Category = "Pickup | Item DataBase")
		UDataTable* ItemDataTable;

	UPROPERTY(EditInstanceOnly, Category = "Pickup | Item DataBase")
		FName DesiredItemID;

	UPROPERTY(VisibleAnywhere, Category = "Pickup | Item Reference")
		UItemBase* ItemReference;

	UPROPERTY(EditInstanceOnly, Category = "Pickup |  Item Reference")
		int32 ItemQuantity;

	UPROPERTY(VisibleInstanceOnly, Category = "Pickup | Interaction")
		FInteractableData InstanceInteractableData;
	

	virtual void Interact(AMyTopDownCharacter* PlayerCharacter) override;
	void TakePickup(const AMyTopDownCharacter* Taker);

	void UpdateInteractableData();

};
