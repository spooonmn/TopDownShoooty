// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/InteractionInterface.h"

#include "InterfaceTestActor.generated.h"



UCLASS()
class TOPDOWNSHOOTY_API AInterfaceTestActor : public AActor, public IInteractionInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInterfaceTestActor();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void BeginFocus() override;
	virtual void EndFocus() override;
	virtual void BeginInteration() override;
	virtual void EndInteration() override;
	virtual void Interact(AMyTopDownCharacter* PlayerCharacter) override;

	UPROPERTY(EditAnywhere, Category = "Test Actor")
		UStaticMeshComponent * Mesh;

	UPROPERTY(EditInstanceOnly,Category = "Test Actor")
		FInteractableData InstanceInteractableData;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	

};
