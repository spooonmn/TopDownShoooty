// Fill out your copyright notice in the Description page of Project Settings.


#include "Interfaces/InteractionInterface.h"
#include "TopDownShooty/MyTopDownCharacter.h"


// Add default functionality here for any IInteractionInterface functions that are not pure virtual.


void IInteractionInterface::BeginFocus()
{

}

void IInteractionInterface::EndFocus()
{

}

void IInteractionInterface::BeginInteration()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("begin interation")));
	//message on screen saying begin interation gengine

}

void IInteractionInterface::EndInteration()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("End interation")));

}

void IInteractionInterface::Interact(AMyTopDownCharacter* PlayerCharacter)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("interact interation")));

}
