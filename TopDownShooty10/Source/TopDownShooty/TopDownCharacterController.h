// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TopDownCharacterController.generated.h"

UCLASS()
class TOPDOWNSHOOTY_API ATopDownCharacterController : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATopDownCharacterController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


protected:
	void MoveForward(float Value);
	void MoveRight(float Value);

	void OnFire();	

	void Zoom(float Value);



public:
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class USkeletalMeshComponent* BodyMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = camera)
		class UCameraComponent* TopDownCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = camera)
	class USpringArmComponent* SpringArm;



private:

	//camera boom settings
	UPROPERTY(EditAnywhere, Category = camera)
		float CameraArmLength = 800.0f;
	UPROPERTY(EditAnywhere, Category = camera)
		float CameraZoomSpeed = 400.0f;


};
