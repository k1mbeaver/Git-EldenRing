// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemStruct.h"
#include "UISlot_UW.generated.h"

/**
 * 
 */
UCLASS()
class ELDENRING_API UUISlot_UW : public UUserWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY(Meta = (BindWidget))
		class UTextBlock* ItemCount;

	UPROPERTY(Meta = (BindWidget))
		class UImage* ItemImage;

	//UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
		//int nCount;

	//UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
		//int nSlotNum;

protected:
	virtual void NativeOnInitialized() override;

public:
	void SetImage(UTexture2D* Image);
	void SetCount(int nCount);
	void SetSlot(FPlayerItem arrInventory, int nSlotNum);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (UIMax = 15, UIMin = -1))
		int Slotnum;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int Count;
};
