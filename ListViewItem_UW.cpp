// Fill out your copyright notice in the Description page of Project Settings.


#include "ListViewItem_UW.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "PlayerItemData.h"

void UListViewItem_UW::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	ItemName = Cast<UTextBlock>(GetWidgetFromName(TEXT("ItemName")));
	ItemCount = Cast<UTextBlock>(GetWidgetFromName(TEXT("ItemCount")));
	ItemImage = Cast<UImage>(GetWidgetFromName(TEXT("ItemImage")));
}

void UListViewItem_UW::SetData(class UPlayerItemData* Data)
{
	SetItemCount(Data->GetItemCount());
	SetItemName(Data->GetItemName());
	SetItemImage(Data->GetItemImage());
}

void UListViewItem_UW::SetItemCount(int nCount)
{
	FString strCount = FString::FromInt(nCount);
	ItemCount->SetText(FText::FromString(strCount));
}

void UListViewItem_UW::SetItemName(FString setName)
{
	ItemName->SetText(FText::FromString(setName));
}

void UListViewItem_UW::SetItemImage(UTexture2D* setImage)
{
	ItemImage->SetBrushFromTexture(setImage);
}

UPlayerItemData* UListViewItem_UW::CastToPlayerItemData(UObject* ListItemData)
{
	UPlayerItemData* PlayerItemData = Cast<UPlayerItemData>(ListItemData);
	return PlayerItemData;
}
