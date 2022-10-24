// Fill out your copyright notice in the Description page of Project Settings.


#include "EldenRingGM.h"
#include "MyPlayerController.h"
#include "PlayerUI_HUD.h"
#include "PlayerCharacter.h"

AEldenRingGM::AEldenRingGM()
//: Super()
{
	// set default pawn class to our Blueprinted character
	//DefaultPawnClass = AMyCharacter::StaticClass();
	//DefaultPawnClass = APlayerCharacter::StaticClass();

	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("Blueprint'/Game/BluePrint/MyPlayerCharacter_BP.MyPlayerCharacter_BP_C'"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// PlayerController
	PlayerControllerClass = AMyPlayerController::StaticClass();

	// use our custom HUD class
	HUDClass = APlayerUI_HUD::StaticClass();
}

void AEldenRingGM::PostLogin(APlayerController* NewPlayer)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("PostLogin Begin"));
	Super::PostLogin(NewPlayer);
	//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("PostLogin End"));

}