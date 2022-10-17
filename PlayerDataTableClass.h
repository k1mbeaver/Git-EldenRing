// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "PlayerDataTableClass.generated.h"

USTRUCT(BlueprintType)
struct FPlayerDataTable : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	// HP
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float PlayerHP;

	// 스태미너
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float PlayerStamina;

	// Stage
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int Stage;

	// MP
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float PlayerMP;

};

UCLASS()
class ELDENRING_API APlayerDataTableClass : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlayerDataTableClass();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
