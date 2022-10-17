// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Inventory_UW.generated.h"

/**
 * 
 */
UCLASS()
class ELDENRING_API UInventory_UW : public UUserWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY(Meta = (BindWidget))
		class UTextBlock* ItemName;

	UPROPERTY(Meta = (BindWidget))
		class UTextBlock* ItemDescript;

	UPROPERTY(Meta = (BindWidget))
		class UImage* ItemImage;

	UPROPERTY(Meta = (BindWidget))
		class UListView* ItemListView;

	UPROPERTY(Meta = (BindWidget))
		class UInventoryPopup_UW* InventoryPopup_WB;

	//UPROPERTY(Meta = (BindWidget))
		//class UListView* ItemListView;

	//UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
		//int nCount;

	//UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
		//int nSlotNum;

protected:
	virtual void NativeOnInitialized() override;

public:
	void SetImage(UTexture2D* Image);
	void SetName(FString strName);
	void SetDescript(FString strDescript);
	void SetListView(int nIndex, FString strName, int nCount, UTexture2D* setImage);
	void SetHidden();
	void SetVisible();
	void SetListCount(int nIndex, int nCount);
	void SetListInit(int nIndex, FString strName, int nCount, UTexture2D* setImage);
	void ListUpdate();
	void Init();

	UFUNCTION(BlueprintCallable)
		void SetInitDescript(UObject* ItemData);

	UFUNCTION(BlueprintCallable)
		void SetPopup(bool IsHovered);
};
