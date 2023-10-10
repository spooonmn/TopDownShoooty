// Fill out your copyright notice in the Description page of Project Settings.


#include "TopDownCharacterController.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Animation/AnimInstance.h"



// Sets default values
ATopDownCharacterController::ATopDownCharacterController()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	TopDownCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCamera->SetupAttachment(RootComponent);
	TopDownCamera->SetRelativeLocation(FVector(-300.0f, 0.0f, 300.0f));
	TopDownCamera->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));
	TopDownCamera->bUsePawnControlRotation = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 400.0f;
	SpringArm->bUsePawnControlRotation = true;

}

// Called when the game starts or when spawned
void ATopDownCharacterController::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATopDownCharacterController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATopDownCharacterController::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveRight", this, &ATopDownCharacterController::MoveRight);
	PlayerInputComponent->BindAxis("MoveForward", this, &ATopDownCharacterController::MoveForward);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ATopDownCharacterController::OnFire);
	PlayerInputComponent->BindAxis("Zoom", this, &ATopDownCharacterController::Zoom);


}

void ATopDownCharacterController::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void ATopDownCharacterController::MoveRight(float Value)
{
if (Value != 0.0f)
	{
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void ATopDownCharacterController::OnFire()
{
}

void ATopDownCharacterController::Zoom(float Value)
{
	CameraArmLength += Value;
	SpringArm->TargetArmLength = FMath::Max(CameraArmLength,0.0f);

}





