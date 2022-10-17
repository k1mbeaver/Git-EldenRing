// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "MonsterParticleDataTableClass.generated.h"


USTRUCT(BlueprintType)
struct FMonsterParticleDataTable : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	// �÷��̾� ���̷�Ż �޽�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UParticleSystem* MonsterAttack;

	// �÷��̾� ���̷�Ż �޽�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UParticleSystem* MonsterIntro;

	// �÷��̾� ���̷�Ż �޽�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UParticleSystem* MonsterSkill;

	// �÷��̾� ���̷�Ż �޽�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UParticleSystem* MonsterSkillSpare;
};

UCLASS()
class ELDENRING_API AMonsterParticleDataTableClass : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMonsterParticleDataTableClass();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
