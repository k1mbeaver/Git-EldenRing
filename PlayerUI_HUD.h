// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PlayerUI_HUD.generated.h"

/**
 * 
 */
UCLASS()
class ELDENRING_API APlayerUI_HUD : public AHUD
{
	GENERATED_BODY()
	
public:
	APlayerUI_HUD();
	virtual void BeginPlay() override;

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

	/*
	void SetItemDescript(FString setItemName, FString setItemDescript, UTexture2D* setItemImage);
	void SetItemDescriptVisible();
	void SetItemDescriptHidden();
	void SetSlot(int nSlot, TArray<FPlayerItem> arrInventory);
	*/
private:
	TSubclassOf<class UPlayerUIMain_UW> MainUIClass;
	class UPlayerUIMain_UW* MainUIObject;

private:
	bool CheckUIObject();
	bool CreateUIObject();
};
