// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PlayerItemData.generated.h"

/**
 * 
 */
UCLASS()
class ELDENRING_API UPlayerItemData : public UObject
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
		int ItemIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
		int ItemCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
		FString ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
		UTexture2D* ItemImage;

public:
	void SetItemIndex(int nIndex);
	void SetItemName(FString strName);
	void SetItemImage(UTexture2D* setImage);
	void SetItemCount(int nCount);
	void SetItemDescript(FString strDescript);

	int GetItemIndex();
	int GetItemCount();
	FString GetItemName();
	UTexture2D* GetItemImage();
	FString GetItemDescript();

	FString ItemDescript;
};
