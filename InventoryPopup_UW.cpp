// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryPopup_UW.h"

void UInventoryPopup_UW::SetHidden()
{
	SetVisibility(ESlateVisibility::Hidden);
}

void UInventoryPopup_UW::SetVisible()
{
	SetVisibility(ESlateVisibility::Visible);
}