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
	// ��Ÿ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UAnimMontage* AttackMontageTypeA;

	// ��Ÿ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UAnimMontage* AttackMontageTypeB;

	// ��Ÿ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UAnimMontage* AttackMontageTypeC;

	// ��Ÿ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UAnimMontage* AttackMontageTypeD;

	// ��Ÿ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UAnimMontage* SkillMontage;

	// ��Ÿ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UAnimMontage* SkillIntroMontage;

	// ��Ÿ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UAnimMontage* StartTravelMontage;

	// ��Ÿ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UAnimMontage* EndTravelMontage;

	// ��Ÿ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UAnimMontage* StunMontage;

	// �ִϸ��̼�
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
