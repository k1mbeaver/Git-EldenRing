// Fill out your copyright notice in the Description page of Project Settings.


#include "UISlot_UW.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void UUISlot_UW::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	ItemCount = Cast<UTextBlock>(GetWidgetFromName(TEXT("ItemCount")));
	ItemImage = Cast<UImage>(GetWidgetFromName(TEXT("ItemImage")));
}

void UUISlot_UW::SetImage(UTexture2D* Image)
{
	ItemImage->SetBrushFromTexture(Image);
}

void UUISlot_UW::SetCount(int nCount)
{
	if (nCount <= 1)
	{
		ItemCount->SetVisibility(ESlateVisibility::Hidden);
	}

	else
	{
		ItemCount->SetVisibility(ESlateVisibility::Visible);
	}

	ItemCount->SetText(FText::FromString(FString::FromInt(nCount)));
}

void UUISlot_UW::SetSlot(FPlayerItem arrInventory, int nSlotNum)
{
	Slotnum = nSlotNum;
	SetImage(arrInventory.ItemImage);
	SetCount(arrInventory.ItemCount);
}