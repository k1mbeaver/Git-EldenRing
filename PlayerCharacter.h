// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ItemStruct.h"
#include "PlayerCharacter.generated.h"

struct Potion
{
	FString PotionType = "Null";
	int PotionAmount = 0;
};

UCLASS()
class ELDENRING_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void PostInitializeComponents() override;
	float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamasgeCauser) override;
	virtual void Jump() override;
	virtual void StopJumping() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, Category = Camera)
		class USpringArmComponent* SpringArm;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, Category = Camera)
		class UCameraComponent* Camera;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		USceneComponent* ParticleLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
		TArray<FPlayerItem> Inventory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
		FPlayerItem DefaultInventory = {"", "", nullptr, 0};

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
		int nInventory; // 인벤토리 슬롯 수

	//UPROPERTY(VisibleInstanceOnly, Replicated, Category = Animation)
	//UPROPERTY(VisibleInstanceOnly, Category = Animation)
		//class UMyPlayerAnimInstance* MyAnim;

	//UPROPERTY(VisibleAnywhere, Category = PlayerStart)
		//class AActor* PlayerSpawn;

	/** Projectile class to spawn */
	//UPROPERTY(EditDefaultsOnly, Category = Projectile)
		//TSubclassOf<class AZombieShootingProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HP)
		float fPlayerHp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HP)
		float fMaxHp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MP)
		float fPlayerMp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MP)
		float fMaxMp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stamina)
		float fPlayerStamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stamina)
		float fMaxStamina;

	/** AnimMontage to play each time we fire */
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	//UAnimMontage* FireAnimation;

	//UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		//USceneComponent* MuzzleLocation;

	/** Gun muzzle's offset from the characters location */
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		//FVector GunOffset;

	UPROPERTY(VisibleInstanceOnly, Category = Animation)
		class UMyPlayerAnimInstance* CharacterAnim;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		bool bAttack;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		float AttackRange;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		float AttackRadius;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		float AttackPower;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Skill, Meta = (AllowPrivateAccess = true))
		float SkillRange;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Skill, Meta = (AllowPrivateAccess = true))
		float SkillRadius;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Skill, Meta = (AllowPrivateAccess = true))
		float SkillPower;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
		bool bIsRun;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
		bool bRunning;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
		bool bPlayerPause;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
		bool bCanMove;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
		bool bIsPlayerControlled;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
		bool bSkill;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
		bool bCanSkill;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
		bool bTravel;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
		bool bAlive;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
		bool bInventory;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
		int nCombo;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
		int nItemClear;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
		FVector CameraOffset;

	UPROPERTY()
		class UGameplayStatics* GameStatic;

	Potion HpPotion = { "HP", 5 };
	Potion MpPotion = { "MP", 5 };
	Potion StaminaPotion = { "Stamina", 5 };

	//UPROPERTY()
		//class UParticleSystem* AttackParticle;

	//UPROPERTY()
		//class UGameplayStatics* GameStatic;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		//USoundBase* AttackSound;

	//void StartSettingGun(); // 시작할 때 총 초기화

	//void PlaySettingGun(FString yourGun); // 플레이 중 총 초기화
	/*
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		float AttackRange;

	UPROPERTY(VisibleInstanceOnly, Replicated, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		float AttackPower;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		float AttackRadius;

	UPROPERTY(VisibleInstanceOnly, Replicated, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		bool IsAttacking;

	UPROPERTY(VisibleInstanceOnly, Replicated, Category = Speed)
		float fSprintSpeedMultiPlayer; // 달리기
	*/
	UPROPERTY(VisibleInstanceOnly, Category = Animation)
		class UMyPlayerAnimInstance* PlayerAnim;

	UPROPERTY(VisibleInstanceOnly, Category = HUD)
		class APlayerUI_HUD* TestHUD;
private:

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		UAnimMontage* AttackAMontage;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		UAnimMontage* AttackBMontage;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		UAnimMontage* AttackCMontage;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		UAnimMontage* AttackDMontage;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Skill, Meta = (AllowPrivateAccess = true))
		UAnimMontage* SkillMontage;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Skill, Meta = (AllowPrivateAccess = true))
		UAnimMontage* SkillIntroMontage;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Travel, Meta = (AllowPrivateAccess = true))
		UAnimMontage* StartTravelMontage;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Travel, Meta = (AllowPrivateAccess = true))
		UAnimMontage* EndTravelMontage;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Stun, Meta = (AllowPrivateAccess = true))
		UAnimMontage* StunMontage;

public:
	void UpDown(float NewAxisValue);

	void LeftRight(float NewAxisValue);

	void LookUp(float NewAxisValue);

	void Turn(float NewAxisValue);

	void Attack();

	void AttackCheck();

	void Run();

	void StopRun();

	void Skill();

	void SkillCheck();

	void StopSkillIntro();

	void TravelMode();

	void HpDrink();

	void MpDrink();

	void StaminaDrink();

	void CheckInventory();

	void InitInventory();

	void GetItem(FString ItemName);

	void GameClear();

	UFUNCTION()
		void SaveCombo();

	UFUNCTION()
		void ResetCombo();
	
	UFUNCTION()
		void IsStunStart();

	UFUNCTION()
		void IsStunEnd();

	UFUNCTION()
		void IsTravelMode();

	UFUNCTION()
		void StopSkill();

	UFUNCTION()
		void StopIntro();

	UFUNCTION()
		void IntroCantMove();

	UFUNCTION()
		void IntroCanMove();

	UFUNCTION()
		void IntroParticle();

	UFUNCTION()
		void IntroSwordParticle();

	UFUNCTION()
		void SkillParticle();

	UFUNCTION()
		void AttackedProjectTile(float fDamage);

	//void PlayerPause();
};
