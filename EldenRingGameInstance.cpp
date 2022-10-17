// Fill out your copyright notice in the Description page of Project Settings.


#include "EldenRingGameInstance.h"
#include "PlayerFileDataTableClass.h"
#include "MonsterDataTableClass.h"
#include "MontageDataTableClass.h"
#include "PlayerDataTableClass.h"
#include "MonsterParticleDataTableClass.h"
#include "PlayerMontageDataTableClass.h"
#include "ImageDataTableClass.h"
#include "SoundDataTableClass.h"
#include "ItemDataTableClass.h"
#include "InventoryDataTableClass.h"

UEldenRingGameInstance::UEldenRingGameInstance()
{
	FString PlayerFileDataPath = TEXT("DataTable'/Game/DataTable/PlayerFileData.PlayerFileData'");
	FString MonsterDataPath = TEXT("DataTable'/Game/DataTable/MonsterData.MonsterData'");
	FString MontageDataPath = TEXT("DataTable'/Game/DataTable/MontageData.MontageData'");
	FString PlayerDataPath = TEXT("DataTable'/Game/DataTable/PlayerData.PlayerData'");
	FString MonsterParticleDataPath = TEXT("DataTable'/Game/DataTable/MonsterParticleData.MonsterParticleData'");
	FString PlayerMontageDataPath = TEXT("DataTable'/Game/DataTable/PlayerMontageData.PlayerMontageData'");
	FString ImageDataPath = TEXT("DataTable'/Game/DataTable/ImageData.ImageData'");
	FString SoundDataPath = TEXT("DataTable'/Game/DataTable/SoundData.SoundData'");
	FString ItemDataPath = TEXT("DataTable'/Game/DataTable/ItemData.ItemData'");
	FString InventoryDataPath = TEXT("DataTable'/Game/DataTable/InventoryData.InventoryData'");

	//E:/Unreal/ZombieShooting/Content/File/Json/PlayerData.uasset
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_ABPLAYERFILE(*PlayerFileDataPath);

	if (DT_ABPLAYERFILE.Succeeded())
	{
		FPlayerFileTable = DT_ABPLAYERFILE.Object;
	}

	static ConstructorHelpers::FObjectFinder<UDataTable> DT_ABMONSTER(*MonsterDataPath);

	if (DT_ABMONSTER.Succeeded())
	{
		FMonsterTable = DT_ABMONSTER.Object;
	}

	static ConstructorHelpers::FObjectFinder<UDataTable> DT_ABMONTAGE(*MontageDataPath);

	if (DT_ABMONTAGE.Succeeded())
	{
		FMontageTable = DT_ABMONTAGE.Object;
	}

	static ConstructorHelpers::FObjectFinder<UDataTable> DT_ABPLAYER(*PlayerDataPath);

	if (DT_ABPLAYER.Succeeded())
	{
		FPlayerTable = DT_ABPLAYER.Object;
	}

	static ConstructorHelpers::FObjectFinder<UDataTable> DT_ABMONSERPARTICLE(*MonsterParticleDataPath);

	if (DT_ABMONSERPARTICLE.Succeeded())
	{
		FMonsterParticleTable = DT_ABMONSERPARTICLE.Object;
	}

	static ConstructorHelpers::FObjectFinder<UDataTable> DT_ABPLAYERMONTAGE(*PlayerMontageDataPath);

	if (DT_ABPLAYERMONTAGE.Succeeded())
	{
		FPlayerMontageTable = DT_ABPLAYERMONTAGE.Object;
	}

	static ConstructorHelpers::FObjectFinder<UDataTable> DT_IMAGE(*ImageDataPath);

	if (DT_IMAGE.Succeeded())
	{
		FImageTable = DT_IMAGE.Object;
	}

	static ConstructorHelpers::FObjectFinder<UDataTable> DT_SOUND(*SoundDataPath);

	if (DT_SOUND.Succeeded())
	{
		FSoundTable = DT_SOUND.Object;
	}

	static ConstructorHelpers::FObjectFinder<UDataTable> DT_ITEM(*ItemDataPath);

	if (DT_ITEM.Succeeded())
	{
		FItemTable = DT_ITEM.Object;
	}

	static ConstructorHelpers::FObjectFinder<UDataTable> DT_INVENTORY(*InventoryDataPath);

	if (DT_INVENTORY.Succeeded())
	{
		FInventoryTable = DT_INVENTORY.Object;
	}
}

USkeletalMesh* UEldenRingGameInstance::GetPlayerSkeletalMesh(FString PlayerType)
{
	FPlayerFileDataTable* SkeletalMeshData = FPlayerFileTable->FindRow<FPlayerFileDataTable>(*PlayerType, TEXT(""));
	USkeletalMesh* PlayerSkeletalMesh = SkeletalMeshData->PlayerMesh;
	return PlayerSkeletalMesh;
}

USkeletalMesh* UEldenRingGameInstance::GetMonsterSkeletalMesh(FString MonsterType)
{
	FMonsterDataTable* SkeletalMeshData = FMonsterTable->FindRow<FMonsterDataTable>(*MonsterType, TEXT(""));
	USkeletalMesh* MonsterSkeletalMesh = SkeletalMeshData->MonsterMesh;
	return MonsterSkeletalMesh;
}

float UEldenRingGameInstance::GetMonsterHp(FString MonsterType)
{
	FMonsterDataTable* MonsterData = FMonsterTable->FindRow<FMonsterDataTable>(*MonsterType, TEXT(""));
	float MonsterHp = MonsterData->MonsterHp;
	return MonsterHp;
}

float UEldenRingGameInstance::GetMonsterSpeed(FString MonsterType)
{
	FMonsterDataTable* MonsterData = FMonsterTable->FindRow<FMonsterDataTable>(*MonsterType, TEXT(""));
	float MonsterSpeed = MonsterData->MonsterSpeed;
	return MonsterSpeed;
}

float UEldenRingGameInstance::GetMonsterPower(FString MonsterType)
{
	FMonsterDataTable* MonsterData = FMonsterTable->FindRow<FMonsterDataTable>(*MonsterType, TEXT(""));
	float MonsterPower = MonsterData->MonsterPower;
	return MonsterPower;
}

float UEldenRingGameInstance::GetMonsterSkillPower(FString MonsterType)
{
	FMonsterDataTable* MonsterData = FMonsterTable->FindRow<FMonsterDataTable>(*MonsterType, TEXT(""));
	float MonsterPower = MonsterData->SkillPower;
	return MonsterPower;
}

float UEldenRingGameInstance::GetMonsterSkillRadius(FString MonsterType)
{
	FMonsterDataTable* MonsterData = FMonsterTable->FindRow<FMonsterDataTable>(*MonsterType, TEXT(""));
	float MonsterPower = MonsterData->SkillRadius;
	return MonsterPower;
}

float UEldenRingGameInstance::GetMonsterSkillRange(FString MonsterType)
{
	FMonsterDataTable* MonsterData = FMonsterTable->FindRow<FMonsterDataTable>(*MonsterType, TEXT(""));
	float MonsterPower = MonsterData->SkillRange;
	return MonsterPower;
}

UAnimMontage* UEldenRingGameInstance::GetMontage(FString MontageType)
{
	FMontageDataTable* MontageData = FMontageTable->FindRow<FMontageDataTable>(*MontageType, TEXT(""));
	UAnimMontage* myMontage = MontageData->MyMontage;
	return myMontage;
}

TSubclassOf<class UAnimInstance> UEldenRingGameInstance::GetAnimation(FString AnimationType)
{
	FMontageDataTable* AnimationData = FMontageTable->FindRow<FMontageDataTable>(*AnimationType, TEXT(""));
	TSubclassOf<class UAnimInstance> myAnimation = AnimationData->MyAnimation;
	return myAnimation;
}

float UEldenRingGameInstance::GetPlayerHP()
{
	FPlayerDataTable* PlayerData = FPlayerTable->FindRow<FPlayerDataTable>("Player", TEXT(""));
	float PlayerHP = PlayerData->PlayerHP;
	return PlayerHP;
}

float UEldenRingGameInstance::GetPlayerStamina()
{
	FPlayerDataTable* PlayerData = FPlayerTable->FindRow<FPlayerDataTable>("Player", TEXT(""));
	float PlayerStamina = PlayerData->PlayerStamina;
	return PlayerStamina;
}

int UEldenRingGameInstance::GetPlayerStage()
{
	FPlayerDataTable* PlayerData = FPlayerTable->FindRow<FPlayerDataTable>("Player", TEXT(""));
	int PlayerStage = PlayerData->Stage;
	return PlayerStage;
}

float UEldenRingGameInstance::GetPlayerMP()
{
	FPlayerDataTable* PlayerData = FPlayerTable->FindRow<FPlayerDataTable>("Player", TEXT(""));
	float PlayerMP = PlayerData->PlayerMP;
	return PlayerMP;
}

UAnimMontage* UEldenRingGameInstance::GetStartIntroMontage(FString MontageType)
{
	FMontageDataTable* MontageData = FMontageTable->FindRow<FMontageDataTable>(*MontageType, TEXT(""));
	UAnimMontage* myMontage = MontageData->StartIntroMontage;
	return myMontage;
}

UAnimMontage* UEldenRingGameInstance::GetSkillMontage(FString MontageType)
{
	FMontageDataTable* MontageData = FMontageTable->FindRow<FMontageDataTable>(*MontageType, TEXT(""));
	UAnimMontage* myMontage = MontageData->SkillMontage;
	return myMontage;
}

UParticleSystem* UEldenRingGameInstance::GetMonsterAttackParticle(FString MonsterType)
{
	FMonsterParticleDataTable* ParticleData = FMonsterParticleTable->FindRow<FMonsterParticleDataTable>(*MonsterType, TEXT(""));
	UParticleSystem* myParticle = ParticleData->MonsterAttack;
	return myParticle;
}

UParticleSystem* UEldenRingGameInstance::GetMonsterSkillParticle(FString MonsterType)
{
	FMonsterParticleDataTable* ParticleData = FMonsterParticleTable->FindRow<FMonsterParticleDataTable>(*MonsterType, TEXT(""));
	UParticleSystem* myParticle = ParticleData->MonsterSkill;
	return myParticle;
}

UParticleSystem* UEldenRingGameInstance::GetMonsterSkillSpareParticle(FString MonsterType)
{
	FMonsterParticleDataTable* ParticleData = FMonsterParticleTable->FindRow<FMonsterParticleDataTable>(*MonsterType, TEXT(""));
	UParticleSystem* myParticle = ParticleData->MonsterSkillSpare;
	return myParticle;
}

UParticleSystem* UEldenRingGameInstance::GetMonsterIntroParticle(FString MonsterType)
{
	FMonsterParticleDataTable* ParticleData = FMonsterParticleTable->FindRow<FMonsterParticleDataTable>(*MonsterType, TEXT(""));
	UParticleSystem* myParticle = ParticleData->MonsterIntro;
	return myParticle;
}

UAnimMontage* UEldenRingGameInstance::GetPlayerAttackAMontage()
{
	FPlayerMontageDataTable* MontageData = FPlayerMontageTable->FindRow<FPlayerMontageDataTable>("Player", TEXT(""));
	UAnimMontage* myMontage = MontageData->AttackMontageTypeA;
	return myMontage;
}

UAnimMontage* UEldenRingGameInstance::GetPlayerAttackBMontage()
{
	FPlayerMontageDataTable* MontageData = FPlayerMontageTable->FindRow<FPlayerMontageDataTable>("Player", TEXT(""));
	UAnimMontage* myMontage = MontageData->AttackMontageTypeB;
	return myMontage;
}

UAnimMontage* UEldenRingGameInstance::GetPlayerAttackCMontage()
{
	FPlayerMontageDataTable* MontageData = FPlayerMontageTable->FindRow<FPlayerMontageDataTable>("Player", TEXT(""));
	UAnimMontage* myMontage = MontageData->AttackMontageTypeC;
	return myMontage;
}

UAnimMontage* UEldenRingGameInstance::GetPlayerAttackDMontage()
{
	FPlayerMontageDataTable* MontageData = FPlayerMontageTable->FindRow<FPlayerMontageDataTable>("Player", TEXT(""));
	UAnimMontage* myMontage = MontageData->AttackMontageTypeD;
	return myMontage;
}

UAnimMontage* UEldenRingGameInstance::GetPlayerSkillMontage()
{
	FPlayerMontageDataTable* MontageData = FPlayerMontageTable->FindRow<FPlayerMontageDataTable>("Player", TEXT(""));
	UAnimMontage* myMontage = MontageData->SkillMontage;
	return myMontage;
}

UAnimMontage* UEldenRingGameInstance::GetPlayerSkillIntroMontage()
{
	FPlayerMontageDataTable* MontageData = FPlayerMontageTable->FindRow<FPlayerMontageDataTable>("Player", TEXT(""));
	UAnimMontage* myMontage = MontageData->SkillIntroMontage;
	return myMontage;
}

UAnimMontage* UEldenRingGameInstance::GetPlayerEndTravelMontage()
{
	FPlayerMontageDataTable* MontageData = FPlayerMontageTable->FindRow<FPlayerMontageDataTable>("Player", TEXT(""));
	UAnimMontage* myMontage = MontageData->EndTravelMontage;
	return myMontage;
}

UAnimMontage* UEldenRingGameInstance::GetPlayerStartTravelMontage()
{
	FPlayerMontageDataTable* MontageData = FPlayerMontageTable->FindRow<FPlayerMontageDataTable>("Player", TEXT(""));
	UAnimMontage* myMontage = MontageData->StartTravelMontage;
	return myMontage;
}

UAnimMontage* UEldenRingGameInstance::GetPlayerStunMontage()
{
	FPlayerMontageDataTable* MontageData = FPlayerMontageTable->FindRow<FPlayerMontageDataTable>("Player", TEXT(""));
	UAnimMontage* myMontage = MontageData->StunMontage;
	return myMontage;
}

TSubclassOf<class UAnimInstance> UEldenRingGameInstance::GetPlayerAnimation()
{
	FPlayerMontageDataTable* AnimationData = FPlayerMontageTable->FindRow<FPlayerMontageDataTable>("Player", TEXT(""));
	TSubclassOf<class UAnimInstance> myAnimation = AnimationData->MyAnimation;
	return myAnimation;
}

UTexture2D* UEldenRingGameInstance::GetImage(FString ImageType)
{
	FImageDataTable* ImageData = FImageTable->FindRow<FImageDataTable>(*ImageType, TEXT(""));
	UTexture2D* myImage = ImageData->MyImage;
	return myImage;
}

UParticleSystem* UEldenRingGameInstance::GetPlayerIntroParticle()
{
	FPlayerFileDataTable* ParticleData = FPlayerFileTable->FindRow<FPlayerFileDataTable>("Default", TEXT(""));
	UParticleSystem* PlayerParticle = ParticleData->PlayerIntroParticle;
	return PlayerParticle;
}

UParticleSystem* UEldenRingGameInstance::GetPlayerIntroSwordParticle()
{
	FPlayerFileDataTable* ParticleData = FPlayerFileTable->FindRow<FPlayerFileDataTable>("Default", TEXT(""));
	UParticleSystem* PlayerParticle = ParticleData->PlayerIntroSwordParticle;
	return PlayerParticle;
}

UParticleSystem* UEldenRingGameInstance::GetPlayerSkillParticle()
{
	FPlayerFileDataTable* ParticleData = FPlayerFileTable->FindRow<FPlayerFileDataTable>("Default", TEXT(""));
	UParticleSystem* PlayerParticle = ParticleData->PlayerSkillParticle;
	return PlayerParticle;
}

USoundWave* UEldenRingGameInstance::GetSound(FString TypeName)
{
	FSoundDataTable* SoundData = FSoundTable->FindRow<FSoundDataTable>(*TypeName, TEXT(""));
	USoundWave* MySound = SoundData->MySound;
	return MySound;
}

UTexture2D* UEldenRingGameInstance::GetItemImage(FString ItemType)
{
	FItemDataTable* ImageData = FItemTable->FindRow<FItemDataTable>(*ItemType, TEXT(""));
	UTexture2D* myImage = ImageData->ItemImage;
	return myImage;
}

FString UEldenRingGameInstance::GetItemName(FString ItemType)
{
	FItemDataTable* ItemData = FItemTable->FindRow<FItemDataTable>(*ItemType, TEXT(""));
	FString ItemName = ItemData->ItemName;
	return ItemName;
}

FString UEldenRingGameInstance::GetItemDescript(FString ItemType)
{
	FItemDataTable* ItemData = FItemTable->FindRow<FItemDataTable>(*ItemType, TEXT(""));
	FString ItemDesript = ItemData->ItemDescript;
	return ItemDesript;
}

FString UEldenRingGameInstance::GetInventoryItemName(int nSlot)
{
	FString strSlot = FString::FromInt(nSlot);
	FInventoryDataTable* InventoryData = FInventoryTable->FindRow<FInventoryDataTable>(*strSlot, TEXT(""));
	FString ItemName = InventoryData->ItemName;
	return ItemName;
}

int UEldenRingGameInstance::GetInventoryItemCount(int nSlot)
{
	FString strSlot = FString::FromInt(nSlot);
	FInventoryDataTable* InventoryData = FInventoryTable->FindRow<FInventoryDataTable>(*strSlot, TEXT(""));
	int ItemCount = InventoryData->ItemCount;
	return ItemCount;
}

void UEldenRingGameInstance::SetInventoryItemCount(int nSlot, int nCount)
{
	FString strSlot = FString::FromInt(nSlot);
	FInventoryDataTable* InventoryData = FInventoryTable->FindRow<FInventoryDataTable>(*strSlot, TEXT(""));
	InventoryData->ItemCount = nCount;
}

void UEldenRingGameInstance::SetInventoryItemName(int nSlot, FString setItemName)
{
	FString strSlot = FString::FromInt(nSlot);
	FInventoryDataTable* InventoryData = FInventoryTable->FindRow<FInventoryDataTable>(*strSlot, TEXT(""));
	InventoryData->ItemName = setItemName;
}

void UEldenRingGameInstance::SetInventorySlotInit(int nSlot)
{
	FString strSlot = FString::FromInt(nSlot);
	FInventoryDataTable* InventoryData = FInventoryTable->FindRow<FInventoryDataTable>(*strSlot, TEXT(""));
	InventoryData->ItemCount = 0;
	InventoryData->ItemName = "";
}