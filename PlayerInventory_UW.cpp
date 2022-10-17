// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerInventory_UW.h"
#include "UISlot_UW.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "PlayerCharacter.h"
#include "Blueprint/WidgetTree.h"

void UPlayerInventory_UW::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	ItemName = Cast<UTextBlock>(GetWidgetFromName(TEXT("ItemName")));
	ItemDescript = Cast<UTextBlock>(GetWidgetFromName(TEXT("ItemDescript")));
	ItemImage = Cast<UImage>(GetWidgetFromName(TEXT("ItemImage")));
	//MonsterName = Cast<UTextBlock>(GetWidgetFromName(TEXT("MonsterName")));
}

void UPlayerInventory_UW::SetVisible()
{
	SetVisibility(ESlateVisibility::Visible);
}

void UPlayerInventory_UW::SetHidden()
{
	SetVisibility(ESlateVisibility::Hidden);
}

void UPlayerInventory_UW::SetItemDescriptVisible()
{
	ItemName->SetVisibility(ESlateVisibility::Visible);
	ItemDescript->SetVisibility(ESlateVisibility::Visible);
	ItemImage->SetVisibility(ESlateVisibility::Visible);
}

void UPlayerInventory_UW::SetItemDescriptHidden()
{
	ItemName->SetVisibility(ESlateVisibility::Hidden);
	ItemDescript->SetVisibility(ESlateVisibility::Hidden);
	ItemImage->SetVisibility(ESlateVisibility::Hidden);
}

void UPlayerInventory_UW::SetItemDescript(FString setItemName, FString setItemDescript, UTexture2D* setItemImage)
{
	ItemName->SetText(FText::FromString(setItemName));
	ItemDescript->SetText(FText::FromString(setItemDescript));
	ItemImage->SetBrushFromTexture(setItemImage);
}

void UPlayerInventory_UW::SetSlot(int nSlot, TArray<FPlayerItem> arrInventory)
{
	Slots.Init(nullptr, nSlot);
	TArray<UWidget*> widgets;

	WidgetTree->GetAllWidgets(widgets);

	UUISlot_UW* slot = nullptr;

	for (int Index = 0; Index < nSlot; Index++) // 위젯의 갯수 만큼 진행한다. auto widget : widgets
	{
		UWidget* widget = nullptr;
		slot = Cast<UUISlot_UW>(widget);

		if (!slot) continue;
		
		slot->SetSlot(arrInventory[Index], Index);

		Slots[Index] = slot;
	}
}