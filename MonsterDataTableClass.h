// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "MonsterDataTableClass.generated.h"

USTRUCT(BlueprintType)
struct FMonsterDataTable : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	// �÷��̾� ���̷�Ż �޽�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USkeletalMesh* MonsterMesh;

	// ���� HP
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MonsterHp;

	// ���� Power
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MonsterPower;

	// ���� Speed
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MonsterSpeed;

	// ���� Skill Power
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float SkillPower;

	// ���� Skill Radius
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float SkillRadius;

	// ���� Skill Range
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float SkillRange;
};

UCLASS()
class ELDENRING_API AMonsterDataTableClass : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMonsterDataTableClass();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
