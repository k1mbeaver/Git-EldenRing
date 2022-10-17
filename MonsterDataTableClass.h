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
	// 플레이어 스켈레탈 메시
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USkeletalMesh* MonsterMesh;

	// 몬스터 HP
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MonsterHp;

	// 몬스터 Power
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MonsterPower;

	// 몬스터 Speed
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MonsterSpeed;

	// 몬스터 Skill Power
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float SkillPower;

	// 몬스터 Skill Radius
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float SkillRadius;

	// 몬스터 Skill Range
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
