// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerUI_UW.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Components/Image.h"
#include "EldenRingGameInstance.h"

void UPlayerUI_UW::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	MonsterName = Cast<UTextBlock>(GetWidgetFromName(TEXT("MonsterName")));
	HPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("HPBar")));
	MPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("MPBar")));
	StaminaBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("StaminaBar")));
	MonsterHPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("MonsterHPBar")));
	PlayerImage = Cast<UImage>(GetWidgetFromName(TEXT("PlayerImage")));
	MonsterHPBarImage = Cast<UImage>(GetWidgetFromName(TEXT("MonsterHPBarImage")));
	ImageFillOne = Cast<UImage>(GetWidgetFromName(TEXT("ImageFillOne")));
	ImageFillTwo = Cast<UImage>(GetWidgetFromName(TEXT("ImageFillTwo")));
	ImageFillThree = Cast<UImage>(GetWidgetFromName(TEXT("ImageFillThree")));
	TextFillOne = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextFillOne")));
	TextFillTwo = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextFillTwo")));
	TextFillThree = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextFillThree")));
}

void UPlayerUI_UW::SetPlayerHP(float fCurrent)
{
	HPBar->SetPercent(fCurrent);
}

void UPlayerUI_UW::SetPlayerMP(float fCurrent)
{
	MPBar->SetPercent(fCurrent);
}

void UPlayerUI_UW::SetPlayerStamina(float fCurrent)
{
	StaminaBar->SetPercent(fCurrent);
}

void UPlayerUI_UW::SetMonsterHP(float fCurrent)
{
	MonsterHPBar->SetPercent(fCurrent);
}

void UPlayerUI_UW::SetMonsterName(FString strMonsterName)
{
	FText ftMonsterName = FText::FromString(strMonsterName);
	MonsterName->SetText(ftMonsterName);
}

void UPlayerUI_UW::SetMonsterVisible()
{
	MonsterName->SetVisibility(ESlateVisibility::Visible);
	MonsterHPBar->SetVisibility(ESlateVisibility::Visible);
	MonsterHPBarImage->SetVisibility(ESlateVisibility::Visible);
}

void UPlayerUI_UW::SetMonsterHidden()
{
	MonsterName->SetVisibility(ESlateVisibility::Hidden);
	MonsterHPBar->SetVisibility(ESlateVisibility::Hidden);
	MonsterHPBarImage->SetVisibility(ESlateVisibility::Hidden);
}

void UPlayerUI_UW::SetPotionAmount(FString strPotionType, int nAmount)
{
	if (strPotionType == "HP")
	{
		FString nToString = FString::FromInt(nAmount);
		FText strToft = FText::FromString(nToString);
		TextFillOne->SetText(strToft);
	}

	else if (strPotionType == "MP")
	{
		FString nToString = FString::FromInt(nAmount);
		FText strToft = FText::FromString(nToString);
		TextFillTwo->SetText(strToft);
	}

	else if (strPotionType == "Stamina")
	{
		FString nToString = FString::FromInt(nAmount);
		FText strToft = FText::FromString(nToString);
		TextFillThree->SetText(strToft);
	}
}

