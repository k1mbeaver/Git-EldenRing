// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemStruct.h"
#include "PlayerInventory_UW.generated.h"

class UUISlot_UW;

/**
 * 
 */
UCLASS()
class ELDENRING_API UPlayerInventory_UW : public UUserWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY(Meta = (BindWidget))
		class UTextBlock* ItemName;

	UPROPERTY(Meta = (BindWidget))
		class UTextBlock* ItemDescript;

	UPROPERTY(Meta = (BindWidget))
		class UImage* ItemImage;

	TArray<UUISlot_UW*> Slots;

protected:
	virtual void NativeOnInitialized() override;
	//virtual void NativeConstruct() override;
public:

	void SetVisible();
	void SetHidden();
	void SetItemDescript(FString setItemName, FString setItemDescript, UTexture2D* setItemImage);
	void SetItemDescriptVisible();
	void SetItemDescriptHidden();
	void SetSlot(int nSlot, TArray<FPlayerItem> arrInventory);
};
