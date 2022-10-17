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

	// 플레이어 데이터 값 얻어오기
	USkeletalMesh* GetPlayerSkeletalMesh(FString PlayerType);
	float GetPlayerHP();
	float GetPlayerStamina();
	int GetPlayerStage();
	float GetPlayerMP();

	// 몬스터 데이터값 얻어오기
	USkeletalMesh* GetMonsterSkeletalMesh(FString MonsterType);
	float GetMonsterHp(FString MonsterType);
	float GetMonsterPower(FString MonsterType);
	float GetMonsterSpeed(FString MonsterType);
	float GetMonsterSkillPower(FString MonsterType);
	float GetMonsterSkillRadius(FString MonsterType);
	float GetMonsterSkillRange(FString MonsterType);

	// 애님 몽타주 데이터값 얻어오기
	UAnimMontage* GetMontage(FString MontageType);
	UAnimMontage* GetSkillMontage(FString MontageType);
	UAnimMontage* GetStartIntroMontage(FString MontageType);

	// 애니메이션 데이터값 얻어오기
	TSubclassOf<class UAnimInstance> GetAnimation(FString AnimationType);

	// 몬스터 파티클 얻어오기
	UParticleSystem* GetMonsterAttackParticle(FString MonsterType);
	UParticleSystem* GetMonsterSkillParticle(FString MonsterType);
	UParticleSystem* GetMonsterIntroParticle(FString MonsterType);
	UParticleSystem* GetMonsterSkillSpareParticle(FString MonsterType);

	// 플레이어 몽타주, 애니메이션, 파티클 얻어오기
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

	// 이미지 얻어오기
	UTexture2D* GetImage(FString ImageType);

	// 사운드 얻어오기
	USoundWave* GetSound(FString TypeName);

	// 아이템 정보 얻어오기
	FString GetItemName(FString ItemType);
	UTexture2D* GetItemImage(FString ItemType);
	FString GetItemDescript(FString ItemType);

	// 인벤토리 정보 얻어오기, 설정하기
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
	// 브금 데이터 값 얻어오기
	//USoundWave* GetSoundWaveBGM(FString Title);

	//UPROPERTY()
		//int nMonsterDeath;

	UPROPERTY()
		FString strSkeletalMesh;

	// Json 관련 (현재는 미사용)
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
