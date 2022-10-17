// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "Animation/AnimInstance.h"
#include "PlayerFileDataTableClass.generated.h"

USTRUCT(BlueprintType)
struct FPlayerFileDataTable : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	// 플레이어 스켈레탈 메시
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USkeletalMesh* PlayerMesh;

	// 플레이어 애니메이션 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UAnimMontage* PlayerAttackAnimation;

	// 플레이어 사운드
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USoundWave* PlayerWalkSound;

	// 플레이어 사운드
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USoundWave* PlayerRunSound;

	// 플레이어 사운드
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USoundWave* PlayerAttackSound;

	// 플레이어 사운드
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USoundWave* PlayerAttackedSound;

	// 플레이어 사운드
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USoundWave* PlayerDeathSound;

	// 플레이어 스킬 파티클
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UParticleSystem* PlayerSkillParticle;

	// 플레이어 인트로 파티클
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UParticleSystem* PlayerIntroParticle;

	// 플레이어 인트로 칼 파티클
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UParticleSystem* PlayerIntroSwordParticle;
};

UCLASS()
class ELDENRING_API APlayerFileDataTableClass : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlayerFileDataTableClass();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
