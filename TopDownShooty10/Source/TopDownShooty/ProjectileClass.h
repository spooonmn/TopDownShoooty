// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileClass.generated.h"

UCLASS()
class TOPDOWNSHOOTY_API AProjectileClass : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectileClass();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;



	UPROPERTY(VisibleDefaultsOnly, Category = Projectile) class USphereComponent* CollisionSphere; //detects collisions

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement) class UProjectileMovementComponent* ProjectileMovement; //mesh of the projectile

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit); //function called when the projectile hits something


	UPROPERTY(EditAnywhere)
		float Damage = 20.0f; //damage of the projectile

};
