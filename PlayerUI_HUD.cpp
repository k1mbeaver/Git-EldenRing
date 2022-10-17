// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerUI_HUD.h"
#include "PlayerUIMain_UW.h"
#include "Engine/Canvas.h"
#include "Engine/Texture2D.h"
#include "TextureResource.h"
#include "CanvasItem.h"
#include "ItemStruct.h"
#include "UObject/ConstructorHelpers.h"

APlayerUI_HUD::APlayerUI_HUD()
{
	static ConstructorHelpers::FClassFinder<UPlayerUIMain_UW> WB_Main(TEXT("WidgetBlueprint'/Game/UI/PlayerUIMain_WB'"));
	if (WB_Main.Succeeded())
	{
		MainUIClass = WB_Main.Class;
	}
}

void APlayerUI_HUD::BeginPlay()
{
	Super::BeginPlay();

	CheckUIObject(); // 시작하면 UI를 생성한다.
}

bool APlayerUI_HUD::CheckUIObject()
{
	if (MainUIObject == nullptr) // UI가 없다면 생성.
	{
		return CreateUIObject();
	}
	return true; // 있다면 True.
}

bool APlayerUI_HUD::CreateUIObject()
{
	if (MainUIClass)
	{
		MainUIObject = CreateWidget<UPlayerUIMain_UW>(GetOwningPlayerController(), MainUIClass);
		if (MainUIObject)
		{
			MainUIObject->AddToViewport();
			return true; // 만들었다면 true.
		}
	}
	return false; // 못 만들었다면 false.
}

void APlayerUI_HUD::SetPlayerHP(float fCurrent)
{
	MainUIObject->SetPlayerHP(fCurrent);
}

void APlayerUI_HUD::SetPlayerMP(float fCurrent)
{
	MainUIObject->SetPlayerMP(fCurrent);
}

void APlayerUI_HUD::SetPlayerStamina(float fCurrent)
{
	MainUIObject->SetPlayerStamina(fCurrent);
}

void APlayerUI_HUD::SetMonsterHP(float fCurrent)
{
	MainUIObject->SetMonsterHP(fCurrent);
}

void APlayerUI_HUD::SetMonsterName(FString strMonsterName)
{
	MainUIObject->SetMonsterName(strMonsterName);
}

void APlayerUI_HUD::SetMonsterVisible()
{
	MainUIObject->SetMonsterVisible();
}

void APlayerUI_HUD::SetMonsterHidden()
{
	MainUIObject->SetMonsterHidden();
}

void APlayerUI_HUD::SetPotionAmount(FString strPotionType, int nAmount)
{
	MainUIObject->SetPotionAmount(strPotionType, nAmount);
}

void APlayerUI_HUD::SetVisible()
{
	MainUIObject->SetVisible();
}

void APlayerUI_HUD::SetHidden()
{
	MainUIObject->SetHidden();
}

void APlayerUI_HUD::SetImage(UTexture2D* Image)
{
	MainUIObject->SetImage(Image);
}

void APlayerUI_HUD::SetName(FString strName)
{
	MainUIObject->SetName(strName);
}

void APlayerUI_HUD::SetDescript(FString strDescript)
{
	MainUIObject->SetDescript(strDescript);
}

void APlayerUI_HUD::SetListView(int nIndex, FString strName, int nCount, UTexture2D* setImage)
{
	MainUIObject->SetListView(nIndex, strName, nCount, setImage);
}

void APlayerUI_HUD::Init()
{
	MainUIObject->Init();
}

void APlayerUI_HUD::ListUpdate()
{
	MainUIObject->ListUpdate();
}

void APlayerUI_HUD::SetListCount(int nIndex, int nCount)
{
	MainUIObject->SetListCount(nIndex, nCount);
}

void APlayerUI_HUD::SetListInit(int nIndex, FString strName, int nCount, UTexture2D* setImage)
{
	MainUIObject->SetListInit(nIndex, strName, nCount, setImage);
}


/*
void APlayerUI_HUD::SetItemDescriptHidden()
{
	MainUIObject->SetItemDescriptHidden();
}

void APlayerUI_HUD::SetItemDescriptVisible()
{
	MainUIObject->SetItemDescriptVisible();
}

void APlayerUI_HUD::SetItemDescript(FString setItemName, FString setItemDescript, UTexture2D* setItemImage)
{
	MainUIObject->SetItemDescript(setItemName, setItemDescript, setItemImage);
}

void APlayerUI_HUD::SetSlot(int nSlot, TArray<FPlayerItem> arrInventory)
{
	MainUIObject->SetSlot(nSlot, arrInventory);
}
*/