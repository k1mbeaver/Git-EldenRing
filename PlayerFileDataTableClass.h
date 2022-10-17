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
	// �÷��̾� ���̷�Ż �޽�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USkeletalMesh* PlayerMesh;

	// �÷��̾� �ִϸ��̼� 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UAnimMontage* PlayerAttackAnimation;

	// �÷��̾� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USoundWave* PlayerWalkSound;

	// �÷��̾� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USoundWave* PlayerRunSound;

	// �÷��̾� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USoundWave* PlayerAttackSound;

	// �÷��̾� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USoundWave* PlayerAttackedSound;

	// �÷��̾� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USoundWave* PlayerDeathSound;

	// �÷��̾� ��ų ��ƼŬ
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UParticleSystem* PlayerSkillParticle;

	// �÷��̾� ��Ʈ�� ��ƼŬ
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UParticleSystem* PlayerIntroParticle;

	// �÷��̾� ��Ʈ�� Į ��ƼŬ
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
