// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "EldenRingGameInstance.generated.h"


struct FPlayerFileDataTable;
struct FMonsterDataTable;
struct FMontageDataTable;
struct FPlayerDataTable;
struct FMonsterParticleDataTable;
struct FPlayerMontageDataTable;
struct FImageDataTable;
struct FSoundDataTable;
struct FItemDataTable;
struct FInventoryDataTable;
class UDataTable;

/**
 * 
 */
UCLASS()
class ELDENRING_API UEldenRingGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UEldenRingGameInstance();

	// �÷��̾� ������ �� ������
	USkeletalMesh* GetPlayerSkeletalMesh(FString PlayerType);
	float GetPlayerHP();
	float GetPlayerStamina();
	int GetPlayerStage();
	float GetPlayerMP();

	// ���� �����Ͱ� ������
	USkeletalMesh* GetMonsterSkeletalMesh(FString MonsterType);
	float GetMonsterHp(FString MonsterType);
	float GetMonsterPower(FString MonsterType);
	float GetMonsterSpeed(FString MonsterType);
	float GetMonsterSkillPower(FString MonsterType);
	float GetMonsterSkillRadius(FString MonsterType);
	float GetMonsterSkillRange(FString MonsterType);

	// �ִ� ��Ÿ�� �����Ͱ� ������
	UAnimMontage* GetMontage(FString MontageType);
	UAnimMontage* GetSkillMontage(FString MontageType);
	UAnimMontage* GetStartIntroMontage(FString MontageType);

	// �ִϸ��̼� �����Ͱ� ������
	TSubclassOf<class UAnimInstance> GetAnimation(FString AnimationType);

	// ���� ��ƼŬ ������
	UParticleSystem* GetMonsterAttackParticle(FString MonsterType);
	UParticleSystem* GetMonsterSkillParticle(FString MonsterType);
	UParticleSystem* GetMonsterIntroParticle(FString MonsterType);
	UParticleSystem* GetMonsterSkillSpareParticle(FString MonsterType);

	// �÷��̾� ��Ÿ��, �ִϸ��̼�, ��ƼŬ ������
	UAnimMontage* GetPlayerAttackAMontage();
	UAnimMontage* GetPlayerAttackBMontage();
	UAnimMontage* GetPlayerAttackCMontage();
	UAnimMontage* GetPlayerAttackDMontage();
	UAnimMontage* GetPlayerSkillMontage();
	UAnimMontage* GetPlayerSkillIntroMontage();
	UAnimMontage* GetPlayerStunMontage();
	UAnimMontage* GetPlayerStartTravelMontage();
	UAnimMontage* GetPlayerEndTravelMontage();
	TSubclassOf<class UAnimInstance> GetPlayerAnimation();
	UParticleSystem* GetPlayerIntroParticle();
	UParticleSystem* GetPlayerIntroSwordParticle();
	UParticleSystem* GetPlayerSkillParticle();

	// �̹��� ������
	UTexture2D* GetImage(FString ImageType);

	// ���� ������
	USoundWave* GetSound(FString TypeName);

	// ������ ���� ������
	FString GetItemName(FString ItemType);
	UTexture2D* GetItemImage(FString ItemType);
	FString GetItemDescript(FString ItemType);

	// �κ��丮 ���� ������, �����ϱ�
	FString GetInventoryItemName(int nSlot);
	int GetInventoryItemCount(int nSlot);
	void SetInventoryItemCount(int nSlot, int nCount);
	void SetInventoryItemName(int nSlot, FString setItemName);
	void SetInventorySlotInit(int nSlot);


	/*
	FString GetMonsterName(FString MonsterType);
	float GetMonsterHp(FString MonsterType);
	float GetMonsterSpeed(FString MonsterType);
	float GetMonsterAttackDamage(FString MonsterType);
	float GetMonsterAttackSpeed(FString MonsterType);
	USkeletalMesh* GetMonsterSkeletalMesh(FString MonsterType);
	*/
	// ��� ������ �� ������
	//USoundWave* GetSoundWaveBGM(FString Title);

	//UPROPERTY()
		//int nMonsterDeath;

	UPROPERTY()
		FString strSkeletalMesh;

	// Json ���� (����� �̻��)
	//void JsonSave();
	//void JsonLoad();

private:
	UPROPERTY()
		UDataTable* FPlayerFileTable;

	UPROPERTY()
		UDataTable* FMonsterTable;

	UPROPERTY()
		UDataTable* FMontageTable;

	UPROPERTY()
		UDataTable* FPlayerTable;

	UPROPERTY()
		UDataTable* FMonsterParticleTable;

	UPROPERTY()
		UDataTable* FPlayerMontageTable;

	UPROPERTY()
		UDataTable* FImageTable;

	UPROPERTY()
		UDataTable* FSoundTable;

	UPROPERTY()
		UDataTable* FItemTable;

	UPROPERTY()
		UDataTable* FInventoryTable;
};
