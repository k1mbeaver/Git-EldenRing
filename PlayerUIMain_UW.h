// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerUIMain_UW.generated.h"

/**
 * 
 */
UCLASS()
class ELDENRING_API UPlayerUIMain_UW : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY(Meta = (BindWidget))
		class UPlayerUI_UW* PlayerUI_WB;

	UPROPERTY(Meta = (BindWidget))
		class UInventory_UW* Inventory_WB;
		//class UPlayerInventory_UW* PlayerInventory_WB;


public:
	void SetPlayerHP(float fCurrent);
	void SetPlayerMP(float fCurrent);
	void SetPlayerStamina(float fCurrent);
	void SetMonsterHP(float fCurrent);
	void SetMonsterName(FString strMonsterName);
	void SetMonsterVisible();
	void SetMonsterHidden();
	void SetPotionAmount(FString strPotionType, int nAmount);

	// 인벤토리
	void SetVisible();
	void SetHidden();
	void SetImage(UTexture2D* Image);
	void SetName(FString strName);
	void SetDescript(FString strDescript);
	void SetListView(int nIndex, FString strName, int nCount, UTexture2D* setImage);
	void Init();
	void ListUpdate();
	void SetListCount(int nIndex, int nCount);
	void SetListInit(int nIndex, FString strName, int nCount, UTexture2D* setImage);
};
