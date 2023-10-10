// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/InteractionInterface.h"
#include "MyTopDownCharacter.generated.h"

class ATopDownHUD;
USTRUCT()
struct FInteractionData
{
	GENERATED_USTRUCT_BODY()

	FInteractionData() : CurrentInteractable(nullptr), LastInteractionCheckTime(0.0f)
	{

	};

	UPROPERTY()
		AActor* CurrentInteractable;

	UPROPERTY()
		float LastInteractionCheckTime;

};


UCLASS() 
class TOPDOWNSHOOTY_API AMyTopDownCharacter : public ACharacter
{
	GENERATED_BODY()


protected:
	//==================================================================================================================================================================================================
	//
	//	F U N C T I O N S       P R O T E C T E D
	//
	//==================================================================================================================================================================================================
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// movement functions
	void MoveForward(float Value);
	void MoveRight(float Value);

	void OnFire();

	void Zoom(float Value);

	void RotateToMouse();

	void Run();
	void Walk();


	// interacting functions

	void PerformInteractionCheck(); // checks for interactable objects
	void FoundInteractable(AActor* NewInteractable); // if an interactable object is found it is stored in the struct of the actor
	void NoInteractableFound(); // if no interactable object is found the struct is cleared

	// these are the main functions for interaction the action, in the interface the functions are called for interacting
	void BeginInteract(); // called when the player presses the interact button
	void EndInteract(); // called when the player releases the interact button
	void Interact(); // called when the player presses the interact button and there is an interactable object in range


	//==================================================================================================================================================================================================
	//
	//	 P R O P E R T I E S   &   V A R I A B L E S    P R O T E C T E D
	//
	//==================================================================================================================================================================================================

	// interaction Variables
	float InteractionCheckFrequency;

	float InteractionCheckDistance;

	FTimerHandle TimerHandle_Interaction; // timer for interaction

	FInteractionData InteractionData; // is the strut that holds the data for the interaction

	UPROPERTY()
		ATopDownHUD* HUD; // the hud class



public:

	//==================================================================================================================================================================================================
	//
	//	F U N C T I O N S		P U B L I C		
	//
	//==================================================================================================================================================================================================

	// Sets default values for this character's properties
	AMyTopDownCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FORCEINLINE bool IsInteracting() const { return GetWorldTimerManager().IsTimerActive(TimerHandle_Interaction); } // checks if the player is interacting




	//==================================================================================================================================================================================================
	// 
	// P R O P E R T I E S   &   V A R I A B L E S		P U B L I C		
	// 
	//==================================================================================================================================================================================================

	// PROPERTIES for the character

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class USkeletalMeshComponent* BodyMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = camera)
		class UCameraComponent* TopDownCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = camera)
		class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class UStaticMeshComponent* GunMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		FVector GunOffset;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh) //muzzle where bullets come out
		class USceneComponent* MuzzleLocation;

	UPROPERTY(EditDefaultsOnly,Category = Projectile) 	
		TSubclassOf<class AProjectileClass> ProjectileClass; //class of the projectile

	UPROPERTY(BluePrintReadWrite)
		AProjectileClass * SpawnedProjectile; //instance of the projectile

	class UWorld* World;

	FRotator SpawnRotation;

	FVector SpawnLocation;


	// Items properties
	UPROPERTY(VisibleAnywhere, Category = "Character | Interaction")
	TScriptInterface <IInteractionInterface> TargetInteractable; // getting the interface from the class i made





private:
	//camera boom settings
	UPROPERTY(EditAnywhere, Category = camera)
		float CameraArmLength = 800.0f;

	UPROPERTY(EditAnywhere, Category = camera)
		float CameraZoomSpeed = 100.0f;

	UPROPERTY(EditAnywhere,Category = Movement)
		float RunSpeed = 800.0f;

	UPROPERTY(EditAnywhere, Category = Movement)
		float WalkSpeed = 600.0f;



};
