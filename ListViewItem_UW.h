// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ListViewItem_UW.generated.h"

/**
 * 
 */
UCLASS()
class ELDENRING_API UListViewItem_UW : public UUserWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY(Meta = (BindWidget))
		class UTextBlock* ItemName;

	UPROPERTY(Meta = (BindWidget))
		class UTextBlock* ItemCount;

	UPROPERTY(Meta = (BindWidget))
		class UImage* ItemImage;

	void SetItemCount(int nCount);
	void SetItemName(FString setName);
	void SetItemImage(UTexture2D* setImage);
	void SetItemDescript(FString setDescript);

	//UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
		//int nCount;

	//UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
		//int nSlotNum;

protected:
	virtual void NativeOnInitialized() override;
	
public:
	UFUNCTION(BlueprintCallable)
		void SetData(class UPlayerItemData* Data);

	UFUNCTION(BlueprintCallable)
		UPlayerItemData* CastToPlayerItemData(UObject* ListItemObject);
};
