// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/TopDownHUD.h"
#include "UserInterface/MainMenu.h"
#include "UserInterface/Interaction/InteractionWidget.h"




ATopDownHUD::ATopDownHUD()
{
	//bIsMenuVisible = false;
}
void ATopDownHUD::BeginPlay()
{
	Super::BeginPlay();

	if (MainMenuClass)
	{
		MainMenuWidget = CreateWidget<UMainMenu>(GetWorld(), MainMenuClass); // how to create a widget
		MainMenuWidget->AddToViewport(5); // how to add a widget to the viewport
		MainMenuWidget->SetVisibility(ESlateVisibility::Collapsed); // how to hide a widget

	}
	if (InteractionWidgetClass)
	{
		InteractionWidget = CreateWidget<UInteractionWidget>(GetWorld(), InteractionWidgetClass); // how to create a widget
		InteractionWidget->AddToViewport(-1); // how to add a widget to the viewport
		InteractionWidget->SetVisibility(ESlateVisibility::Collapsed); // how to hide a widget

	}


	
}

void ATopDownHUD::DisplayMenu()
{
	if (MainMenuClass)
	{
		bIsMenuVisible = true;
		MainMenuWidget->SetVisibility(ESlateVisibility::Visible); // how to show a widget
	}
}
void ATopDownHUD::HideMenu()
{
	if (MainMenuClass)
	{
		bIsMenuVisible = false;
		MainMenuWidget->SetVisibility(ESlateVisibility::Collapsed); // how to show a widget
	}
}

void ATopDownHUD::ShowInteractionWidget()
{
	if (InteractionWidget)
	{
		InteractionWidget->SetVisibility(ESlateVisibility::Visible); // how to show a widget
	}
}

void ATopDownHUD::HideInteractionWidget()
{
	if (InteractionWidget)
	{
		InteractionWidget->SetVisibility(ESlateVisibility::Collapsed); // how to show a widget
	}
}

void ATopDownHUD::UpdateInteractionWidget(const FInteractableData* InteractableData)
{
	if (InteractionWidget)
	{
		if (InteractionWidget->GetVisibility() == ESlateVisibility::Collapsed)
		{
			InteractionWidget->SetVisibility(ESlateVisibility::Visible); // how to show a widget

		}
		InteractionWidget->UpdateWidget(InteractableData);
	}
}
