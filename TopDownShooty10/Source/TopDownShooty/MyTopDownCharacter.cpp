


#include "MyTopDownCharacter.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Animation/AnimInstance.h"
#include "ProjectileClass.h"
#include "DrawDebugHelpers.h"
#include "UserInterface/TopDownHUD.h"

#include "Engine/World.h"
#include "GameFramework/PlayerController.h"


// Sets default values
AMyTopDownCharacter::AMyTopDownCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);



	// CHARACTER MOVEMENT
	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;

	// BOOM ARM CAMERA
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = CameraArmLength;
	CameraBoom->bUsePawnControlRotation = false;
	CameraBoom->bDoCollisionTest = false;
	CameraBoom->bInheritPitch = false;
	CameraBoom->bInheritYaw = false;
	CameraBoom->bInheritRoll = false;


	// set the camera booms rotation on t axis to -70
	CameraBoom->SetRelativeRotation(FRotator(-70.0f, 0.0f, 0.0f));

	// Creating the Camera and it settings
	TopDownCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCamera->SetupAttachment(CameraBoom);
	// Enable Camera Lag
	CameraBoom->bEnableCameraLag = true;
	CameraBoom->CameraLagSpeed = 3.0f;
	// Enable Camera Smoothing for the Camera Lag
	CameraBoom->bEnableCameraRotationLag = true;
	CameraBoom->CameraRotationLagSpeed = 10.0f;

	// BaseCamera settings
	CameraArmLength = 1500.0f;
	CameraZoomSpeed = 100.0f;

	//set up gun 
	GunMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GunMesh"));
	GunMesh->SetOnlyOwnerSee(true);

	// set up muzzle location
	MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	MuzzleLocation->SetupAttachment(GunMesh);
	MuzzleLocation->SetRelativeLocation(FVector(0.2f, 48.4f, -10.6f));

	GunOffset= FVector(100.0f, 0.0f, 10.0f);
	
	// Interaction params

	InteractionCheckFrequency = 0.1f;   
	InteractionCheckDistance = 400.0f;

}

// Called when the game starts or when spawned
void AMyTopDownCharacter::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController) // camera settings
	{
		PlayerController->bShowMouseCursor = true;
		PlayerController->bEnableClickEvents = true;
		PlayerController->bEnableMouseOverEvents = true;
	}
	GunMesh->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
	//GunMesh->SetRelativeLocation(FVector(-90.0f, 0.0f, 0.0f));
	World = GetWorld();

	HUD = Cast<ATopDownHUD>(GetWorld()->GetFirstPlayerController()->GetHUD()); // cast the HUD to the ATopDownHUD class
	
	

}

// Called every frame
void AMyTopDownCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	RotateToMouse();

	if (GetWorld()->TimeSince(InteractionData.LastInteractionCheckTime) > InteractionCheckFrequency)
	{
			PerformInteractionCheck();
	}


}


// Called to bind functionality to input
void AMyTopDownCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMyTopDownCharacter::MoveRight);
	PlayerInputComponent->BindAxis("MoveForward", this, &AMyTopDownCharacter::MoveForward);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AMyTopDownCharacter::OnFire);
	PlayerInputComponent->BindAxis("Zoom", this, &AMyTopDownCharacter::Zoom);
	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &AMyTopDownCharacter::Run);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &AMyTopDownCharacter::Walk);
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AMyTopDownCharacter::BeginInteract);
	PlayerInputComponent->BindAction("Interact", IE_Released, this, &AMyTopDownCharacter::EndInteract);



}

void AMyTopDownCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		AddMovementInput(FVector(1,0,0), Value);
	}
}

void AMyTopDownCharacter::MoveRight(float Value)
{

	if (Value != 0.0f)
	{
		AddMovementInput(FVector(0,1,0), Value);
	}
}

void AMyTopDownCharacter::OnFire()
{
	//message on screen
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("FIRE"));
	if (World != NULL) {
		
		SpawnRotation = GetActorRotation();
		SpawnLocation = ((MuzzleLocation != nullptr) ? MuzzleLocation->GetComponentLocation() : GetActorLocation()) + SpawnRotation.RotateVector(GunOffset);

		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

		

		SpawnedProjectile = World->SpawnActor<AProjectileClass>(ProjectileClass, SpawnLocation, SpawnRotation, SpawnParams);
		if (SpawnedProjectile != NULL) {
			// message on screen
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Projectile Spawned"));
		}
		//message on screen of SpawnedProjectiles location
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("SpawnedProjectile Location: %s"), *SpawnLocation.ToString()));


	}

}

void AMyTopDownCharacter::Zoom(float Value)
{
	CameraArmLength += Value * CameraZoomSpeed;
	CameraBoom->TargetArmLength = FMath::Max(CameraArmLength, 0.0f);
	// message to the screen


}

void AMyTopDownCharacter::RotateToMouse()
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController)
	{
		// Get the mouse cursor position in screen space
		float MouseX, MouseY;
		PlayerController->GetMousePosition(MouseX, MouseY);

		// Calculate the offset from the center of the screen
		float CenterX = 0.5f * GEngine->GameViewport->Viewport->GetSizeXY().X;
		float CenterY = 0.5f * GEngine->GameViewport->Viewport->GetSizeXY().Y;

		float OffsetX = MouseX - CenterX;
		float OffsetY = MouseY - CenterY;

		// Calculate the angle in radians
		float AngleRadians = FMath::Atan2(OffsetY, OffsetX);

		// Convert radians to degrees
		float AngleDegrees = FMath::RadiansToDegrees(AngleRadians);
		AngleDegrees += 90.0f;

		// Now, AngleDegrees contains the angle between the mouse and the center of the screen (your character's position).
		//display AngleDegrees
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("AngleDegrees: %f"), AngleDegrees));

		// Set the character's rotation on the Z-axis to AngleDegrees
		FRotator NewRotation = GetActorRotation();
		NewRotation.Yaw = AngleDegrees;
		SetActorRotation(NewRotation);
	}
	
}

void AMyTopDownCharacter::Run()
{
	//sets the character movement speed to run speed
	GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
}

void AMyTopDownCharacter::Walk()
{
	//sets the character movement speed to walk speed
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;

}

// INTERACTION FUNCTIONS

void AMyTopDownCharacter::PerformInteractionCheck() // line check to see if there is an interactable in front of the player
{
	InteractionData.LastInteractionCheckTime = GetWorld() ->GetTimeSeconds(); // set the last interaction check time to the current time since its being executed

	FVector TraceStart{GetPawnViewLocation()}; // the start of the line trace is the pawn view location
	
	FVector TraceEnd{TraceStart + (GetActorRotation().Vector() * InteractionCheckDistance)}; // the end of the line trace is the start plus the view rotation vector times the interaction check distance
	TraceEnd.Z -= 200.0f;
	// ray cast from camera to mouseposition	

	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	FVector MouseLocation;
	FVector MouseDirection;
	PlayerController->DeprojectMousePositionToWorld(MouseLocation, MouseDirection);
	float RayLength = 1000000.f; // Set a large value for ray length
	FVector RayEnd = MouseLocation + RayLength * MouseDirection;

	FHitResult HitResult;
	FCollisionQueryParams TraceParams;
	TraceParams.AddIgnoredActor(this); // Ignore this actor
	
	//DrawDebugLine(GetWorld(), MouseLocation, RayEnd, FColor::Red, false, 1.0f, 0, 2.0f); // draw the line trace



	
	//DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Red, false, 1.0f, 0, 2.0f); // draw the line trace
	
	FCollisionQueryParams QueryParams; // create a collision query params for LineTraceSingleByChannel
	QueryParams.AddIgnoredActor(this); // ignore the player character
	FHitResult TraceHit; // create a hit result for the line trace  including the actor

	if (GetWorld()->LineTraceSingleByChannel(HitResult, MouseLocation, RayEnd, ECollisionChannel::ECC_Visibility, TraceParams)) // the line trace
	{
		if (HitResult.GetActor()->GetClass()->ImplementsInterface(UInteractionInterface::StaticClass())) // if the actor can be interacted with
		{
			const float Distance = (TraceStart - HitResult.ImpactPoint).Size(); // the distance between the start of the line trace and the impact point

			if (HitResult.GetActor() != InteractionData.CurrentInteractable && Distance <= InteractionCheckDistance)
			{
				FoundInteractable(HitResult.GetActor()); // if the actor is not the current interactable and the distance is less than the interaction check distance then the actor is the new interactable
			}
			if (HitResult.GetActor() == InteractionData.CurrentInteractable)
			{
				return; // still looking at same interactable no logic needed, maintain current status
			}
		}
	}

	NoInteractableFound(); // if no interactable is found then clear the struct

}

void AMyTopDownCharacter::FoundInteractable(AActor* NewInteractable)
{
	if (IsInteracting())
	{
		EndInteract();
	}

	if (InteractionData.CurrentInteractable)
	{
		TargetInteractable = InteractionData.CurrentInteractable;
		TargetInteractable->EndFocus();

	}

	InteractionData.CurrentInteractable = NewInteractable;
	TargetInteractable = NewInteractable;

	HUD->UpdateInteractionWidget(&TargetInteractable->InteractableData); // update the interaction widget 

	TargetInteractable->BeginFocus();
}

void AMyTopDownCharacter::NoInteractableFound()
{
	if (IsInteracting())
	{
		GetWorldTimerManager().ClearTimer(TimerHandle_Interaction);
	}
	if (InteractionData.CurrentInteractable)
	{
		if (IsValid(TargetInteractable.GetObject())) // if the target interactable is valid then end focus sometimes it crashes otherwise
		{
			TargetInteractable->EndFocus();
		}
		// hide interaction widget on the HUD
		HUD->HideInteractionWidget();

		InteractionData.CurrentInteractable = nullptr;
		TargetInteractable = nullptr;
	}

}

void AMyTopDownCharacter::BeginInteract()
{
	//message on screen saying begin interation gengine
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("begin interation")));

	// verify nothing has changed with the interactable state since begining interaction
	PerformInteractionCheck();

	if (InteractionData.CurrentInteractable)
	{
		if (IsValid(TargetInteractable.GetObject()))
		{
			TargetInteractable->BeginInteration();

			if (FMath::IsNearlyZero(TargetInteractable->InteractableData.InteractionDuration, 0.1f)) // if the interaction duration is nearly zero then interact
			{
				Interact();
			}
			else
			{
				GetWorldTimerManager().SetTimer(TimerHandle_Interaction,
					this,
					&AMyTopDownCharacter::Interact,
					TargetInteractable->InteractableData.InteractionDuration,
					false);
				// start the interaction timer, lots of overloads for this function
			}
			
		}
	}

}

void AMyTopDownCharacter::EndInteract()
{

	GetWorldTimerManager().ClearTimer(TimerHandle_Interaction);
	if (IsValid(TargetInteractable.GetObject()))
	{
		TargetInteractable->EndInteration();
	}

}

void AMyTopDownCharacter::Interact()
{
	GetWorldTimerManager().ClearTimer(TimerHandle_Interaction);
	if (IsValid(TargetInteractable.GetObject()))
	{
		TargetInteractable->Interact(this);
	}
}

