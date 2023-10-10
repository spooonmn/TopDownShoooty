// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "TopDownHUD.generated.h"

struct FInteractableData;
class UInteractionWidget;
class UMainMenu;

UCLASS()
class TOPDOWNSHOOTY_API ATopDownHUD : public AHUD
{
	GENERATED_BODY()
	

	public:
		UPROPERTY(EditDefaultsOnly, Category ="Widget")
			TSubclassOf<class UMainMenu> MainMenuClass;
		UPROPERTY(EditDefaultsOnly, Category = "Widget")
			TSubclassOf<class UInteractionWidget> InteractionWidgetClass;

		bool bIsMenuVisible;

		ATopDownHUD();

		void DisplayMenu();
		void HideMenu();

		void ShowInteractionWidget();
		void HideInteractionWidget();
		void UpdateInteractionWidget(const FInteractableData* InteractableData);

protected:
	

	UPROPERTY()
		UMainMenu* MainMenuWidget;

	UPROPERTY()
		UInteractionWidget* InteractionWidget;



	virtual void BeginPlay() override;


};
