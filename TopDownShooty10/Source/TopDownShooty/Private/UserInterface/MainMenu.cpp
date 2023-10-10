// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/MainMenu.h"
#include "TopDownShooty/MyTopDownCharacter.h"



void UMainMenu::NativeOnInitialized()
{
}

void UMainMenu::NativeConstruct()
{
    Super::NativeConstruct();

    PlayerCharacter = Cast<AMyTopDownCharacter>(GetOwningPlayerPawn());


}

bool UMainMenu::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

    // cast operation to item drag drop, ensure player is valid call dop item on play
}
