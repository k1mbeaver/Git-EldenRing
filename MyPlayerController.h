// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class ELDENRING_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
	
		AMyPlayerController();
public:
	virtual void OnPossess(APawn* aPawn) override;
	virtual void PostInitializeComponents() override; // 여기서 빙의되는지 알 수 있음
	virtual void SetupInputComponent() override;

private:
	UPROPERTY()
		class APlayerCharacter* myCharacter;

private:
	void UpDown(float NewAxisValue);

	void LeftRight(float NewAxisValue);

	void LookUp(float NewAxisValue);

	void Turn(float NewAxisValue);

	void Attack();

	void Run();

	void StopRun();

	void Jump();

	void StopJumping();

	void Skill();

	void StopSkillIntro();

	void TravelMode();

	void HpDrink();

	void MpDrink();

	void StaminaDrink();

	void CheckInventory();

	//void PlayerPause();
};
