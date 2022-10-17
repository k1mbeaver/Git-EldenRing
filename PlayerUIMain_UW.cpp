// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerUIMain_UW.h"
#include "PlayerUI_UW.h"
#include "PlayerInventory_UW.h"
#include "Inventory_UW.h"
#include "ItemStruct.h"

void UPlayerUIMain_UW::SetPlayerHP(float fCurrent)
{
	PlayerUI_WB->SetPlayerHP(fCurrent);
}

void UPlayerUIMain_UW::SetPlayerMP(float fCurrent)
{
	PlayerUI_WB->SetPlayerMP(fCurrent);
}

void UPlayerUIMain_UW::SetPlayerStamina(float fCurrent)
{
	PlayerUI_WB->SetPlayerStamina(fCurrent);
}

void UPlayerUIMain_UW::SetMonsterHP(float fCurrent)
{
	PlayerUI_WB->SetMonsterHP(fCurrent);
}

void UPlayerUIMain_UW::SetMonsterName(FString strMonsterName)
{
	PlayerUI_WB->SetMonsterName(strMonsterName);
}

void UPlayerUIMain_UW::SetMonsterVisible()
{
	PlayerUI_WB->SetMonsterVisible();
}

void UPlayerUIMain_UW::SetMonsterHidden()
{
	PlayerUI_WB->SetMonsterHidden();
}

void UPlayerUIMain_UW::SetPotionAmount(FString strPotionType, int nAmount)
{
	PlayerUI_WB->SetPotionAmount(strPotionType, nAmount);
}

void UPlayerUIMain_UW::SetVisible()
{
	Inventory_WB->SetVisible();
}

void UPlayerUIMain_UW::SetHidden()
{
	Inventory_WB->SetHidden();
}

void UPlayerUIMain_UW::SetImage(UTexture2D* Image)
{
	Inventory_WB->SetImage(Image);
}

void UPlayerUIMain_UW::SetName(FString strName)
{
	Inventory_WB->SetName(strName);
}

void UPlayerUIMain_UW::SetDescript(FString strDescript)
{
	Inventory_WB->SetDescript(strDescript);
}

void UPlayerUIMain_UW::SetListView(int nIndex, FString strName, int nCount, UTexture2D* setImage)
{
	Inventory_WB->SetListView(nIndex, strName, nCount, setImage);
}

void UPlayerUIMain_UW::Init()
{
	Inventory_WB->Init();
}

void UPlayerUIMain_UW::ListUpdate()
{
	Inventory_WB->ListUpdate();
}

void UPlayerUIMain_UW::SetListCount(int nIndex, int nCount)
{
	Inventory_WB->SetListCount(nIndex, nCount);
}

void UPlayerUIMain_UW::SetListInit(int nIndex, FString strName, int nCount, UTexture2D* setImage)
{
	Inventory_WB->SetListInit(nIndex, strName, nCount, setImage);
}