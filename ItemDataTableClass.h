// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "ItemDataTableClass.generated.h"

USTRUCT(BlueprintType)
struct FItemDataTable : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	// 아이템 이름
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString ItemName;

	// 아이템 이미지
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* ItemImage;

	// 아이템 설명
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString ItemDescript;


	//TSubclassOf<class USoundWave> MySound;
};

UCLASS()
class ELDENRING_API AItemDataTableClass : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemDataTableClass();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
