// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerUI_UW.generated.h"

/**
 * 
 */
UCLASS()
class ELDENRING_API UPlayerUI_UW : public UUserWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY(Meta = (BindWidget))
		class UTextBlock* MonsterName;

	UPROPERTY(Meta = (BindWidget))
		class UProgressBar* HPBar;

	UPROPERTY(Meta = (BindWidget))
		class UProgressBar* MPBar;

	UPROPERTY(Meta = (BindWidget))
		class UProgressBar* StaminaBar;

	UPROPERTY(Meta = (BindWidget))
		class UProgressBar* MonsterHPBar;

	UPROPERTY(Meta = (BindWidget))
		class UImage* PlayerImage;

	UPROPERTY(Meta = (BindWidget))
		class UImage* MonsterHPBarImage;

	UPROPERTY(Meta = (BindWidget))
		class UImage* ImageFillOne;

	UPROPERTY(Meta = (BindWidget))
		class UImage* ImageFillTwo;

	UPROPERTY(Meta = (BindWidget))
		class UImage* ImageFillThree;

	UPROPERTY(Meta = (BindWidget))
		class UTextBlock* TextFillOne;

	UPROPERTY(Meta = (BindWidget))
		class UTextBlock* TextFillTwo;

	UPROPERTY(Meta = (BindWidget))
		class UTextBlock* TextFillThree;

protected:
	virtual void NativeOnInitialized() override;
	//virtual void NativeConstruct() override;
public:

	void SetPlayerHP(float fCurrent);
	void SetPlayerMP(float fCurrent);
	void SetPlayerStamina(float fCurrent);
	void SetMonsterHP(float fCurrent);
	void SetMonsterName(FString strMonsterName);
	void SetMonsterVisible();
	void SetMonsterHidden();
	void SetPotionAmount(FString strPotionType, int nAmount);
};
