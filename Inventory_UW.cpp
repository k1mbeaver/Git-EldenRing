// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory_UW.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/ListView.h"
#include "PlayerItemData.h"
#include "EldenRingGameInstance.h"
#include "InventoryPopup_UW.h"

void UInventory_UW::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	ItemName = Cast<UTextBlock>(GetWidgetFromName(TEXT("ItemName")));
	ItemDescript = Cast<UTextBlock>(GetWidgetFromName(TEXT("ItemDescript")));
	ItemImage = Cast<UImage>(GetWidgetFromName(TEXT("ItemImage")));
	ItemListView = Cast<UListView>(GetWidgetFromName(TEXT("ItemListView")));
	InventoryPopup_WB = Cast<UInventoryPopup_UW>(GetWidgetFromName(TEXT("InventoryPopup_WB")));
}

void UInventory_UW::SetImage(UTexture2D* Image)
{
	ItemImage->SetBrushFromTexture(Image);
}

void UInventory_UW::SetName(FString strName)
{
	ItemName->SetText(FText::FromString(strName));
}

void UInventory_UW::SetDescript(FString strDescript)
{
	ItemDescript->SetText(FText::FromString(strDescript));
}

void UInventory_UW::SetListView(int nIndex, FString strName, int nCount, UTexture2D* setImage)
{
	UPlayerItemData* ItemData = NewObject<UPlayerItemData>(this, UPlayerItemData::StaticClass());
	ItemData->SetItemIndex(nIndex);
	ItemData->SetItemCount(nCount);
	ItemData->SetItemName(strName);
	ItemData->SetItemImage(setImage);
	ItemListView->AddItem(ItemData);
}

void UInventory_UW::SetListInit(int nIndex, FString strName, int nCount, UTexture2D* setImage)
{
	UPlayerItemData* ItemData = Cast<UPlayerItemData>(ItemListView->GetItemAt(nIndex));

	ItemData->SetItemName(strName);
	ItemData->SetItemCount(nCount);
	ItemData->SetItemImage(setImage);
}

void UInventory_UW::Init()
{
	UEldenRingGameInstance* MyGI = GetGameInstance<UEldenRingGameInstance>();

	ItemImage->SetBrushFromTexture(MyGI->GetImage("Null"));
	ItemName->SetText(FText::FromString(""));
	ItemDescript->SetText(FText::FromString(""));
}

void UInventory_UW::SetHidden()
{
	Init();
	SetVisibility(ESlateVisibility::Hidden);
}

void UInventory_UW::SetVisible()
{
	SetVisibility(ESlateVisibility::Visible);
}

void UInventory_UW::ListUpdate()
{
	ItemListView->RegenerateAllEntries();
}

void UInventory_UW::SetListCount(int nIndex, int nCount)
{
	UPlayerItemData* ItemData = Cast<UPlayerItemData>(ItemListView->GetItemAt(nIndex));

	ItemData->SetItemCount(nCount);
}

void UInventory_UW::SetInitDescript(UObject* ItemData)
{
	UEldenRingGameInstance* MyGI = GetGameInstance<UEldenRingGameInstance>();

	UPlayerItemData* myItemData = Cast<UPlayerItemData>(ItemData);

	SetImage(myItemData->GetItemImage());
	SetName(myItemData->GetItemName());

	SetDescript(MyGI->GetItemDescript(myItemData->GetItemName()));

	//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("ItemClick!"));
}

void UInventory_UW::SetPopup(bool IsHovered)
{
	if (!IsHovered)
	{
		InventoryPopup_WB->SetHidden();
	}

	else
	{
		InventoryPopup_WB->SetVisible();
	}
}