// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "PlayerMontageDataTableClass.generated.h"

USTRUCT(BlueprintType)
struct FPlayerMontageDataTable : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	// 根鸥林
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UAnimMontage* AttackMontageTypeA;

	// 根鸥林
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UAnimMontage* AttackMontageTypeB;

	// 根鸥林
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UAnimMontage* AttackMontageTypeC;

	// 根鸥林
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UAnimMontage* AttackMontageTypeD;

	// 根鸥林
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UAnimMontage* SkillMontage;

	// 根鸥林
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UAnimMontage* SkillIntroMontage;

	// 根鸥林
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UAnimMontage* StartTravelMontage;

	// 根鸥林
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UAnimMontage* EndTravelMontage;

	// 根鸥林
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UAnimMontage* StunMontage;

	// 局聪皋捞记
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class UAnimInstance> MyAnimation;
};

UCLASS()
class ELDENRING_API APlayerMontageDataTableClass : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlayerMontageDataTableClass();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
