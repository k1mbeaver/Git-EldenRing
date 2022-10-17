// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemStruct.h"
#include "Engine/DataTable.h"
#include "InventoryDataTableClass.generated.h"

USTRUCT(BlueprintType)
struct FInventoryDataTable : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	// 아이템 정보
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString ItemName;

	// 아이템 갯수
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int ItemCount;
};

UCLASS()
class ELDENRING_API AInventoryDataTableClass : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInventoryDataTableClass();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
