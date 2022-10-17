// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterCharacter.h"
#include "GameFrameWork/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "EldenRingGM.h"
#include "EldenRingGameInstance.h"
#include "MonsterController.h"
#include "MonsterInstance.h"
#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "PlayerUI_HUD.h"
#include "DrawDebugHelpers.h"
#include "MonsterProjectile.h"
#include "MonsterItem.h"

// Sets default values
AMonsterCharacter::AMonsterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	//static ConstructorHelpers::FClassFinder<UAnimInstance> PLAYER_ANIM(TEXT("/Game/BluePrint/GruxAnimation_BP.GruxAnimation_BP_C"));
	//if (PLAYER_ANIM.Succeeded())
	//{
		//GetMesh()->SetAnimInstanceClass(PLAYER_ANIM.Class);
	//}

	ParticleMuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	ParticleMuzzleLocation->SetupAttachment(GetCapsuleComponent());
	//ParticleMuzzleLocation->SetRelativeLocation(FVector(-80.f, 80.0f, 30.0f));

	IntroParticleMuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("IntroMuzzleLocation"));
	IntroParticleMuzzleLocation->SetupAttachment(GetCapsuleComponent());
	//IntroParticleMuzzleLocation->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));

	ProjectileMuzzle = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileMuzzle"));
	ProjectileMuzzle->SetupAttachment(GetCapsuleComponent());

	//AttackParticleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("AttackLocation"));
	//AttackParticleLocation->SetupAttachment(GetCapsuleComponent());

	GetCharacterMovement()->JumpZVelocity = 400.0f;
	GetCharacterMovement()->MaxWalkSpeed = 200.0f;

	// 캐릭터가 자연스럽게 회전하게 
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
	GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("ProjectMonster"));

	// bullet effect
	//static ConstructorHelpers::FObjectFinder<UParticleSystem> ATTACK(TEXT("ParticleSystem'/Game/ParagonSevarog/FX/Particles/Abilities/Primary/FX/P_Sevarog_Melee_SucessfulImpact.P_Sevarog_Melee_SucessfulImpact'"));
	//if (ATTACK.Succeeded())
	//{
		//AttackParticle = ATTACK.Object;
	//}

	bCanAttack = true;
	bAlive = true;
	bUIPrint = false;

	fMaxHp = 100.0f;
	fAIHp = 100.0f;
	AttackRange = 250.0f;
	AttackRadius = 50.0f;
}

void AMonsterCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

// Called when the game starts or when spawned
void AMonsterCharacter::BeginPlay()
{
	Super::BeginPlay();

	//UEldenRingGameInstance* MyGI = GetGameInstance<UEldenRingGameInstance>();
	//nMonsterType = MyGI->GetPlayerStage();
	
	if (strMonsterType == "Grux")
	{
		//strMonsterType = "Grux";
		//strMonsterItem = "GruxItem";
		IntroParticleMuzzleLocation->SetRelativeLocation(FVector(0.0f, 0.0f, -70.0f));
		ParticleMuzzleLocation->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));
	}

	else if (strMonsterType == "Narbash")
	{
		//strMonsterType = "Narbash";
		//strMonsterItem = "NarbashItem";
		IntroParticleMuzzleLocation->SetRelativeLocation(FVector(10.0f, 0.0f, 150.0f));
		ParticleMuzzleLocation->SetRelativeLocation(FVector(60.0f, 0.0f, 20.0f));
	}

	else if (strMonsterType == "Rampage")
	{
		//strMonsterType = "Rampage";
		//strMonsterItem = "RampageItem";
		IntroParticleMuzzleLocation->SetRelativeLocation(FVector(10.0f, 0.0f, 50.0f));
		ParticleMuzzleLocation->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));
	}

	else if (strMonsterType == "Sevarog")
	{
		//strMonsterType = "Sevarog";
		//strMonsterItem = "SevarogItem";
		IntroParticleMuzzleLocation->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
		ParticleMuzzleLocation->SetRelativeLocation(FVector(0.0, 0.0f, -90.0f));
	}

	InitializeAI(strMonsterType); // Narbash, Props, Rampage, Sevarog, Grux
}

// Called every frame
void AMonsterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bAlive)
	{
		MonsterAnim->SetDeadAnim();

		StopAIController(); //이거 대신에 Death 애니메이션 노티파이로 작동하게 해보자
		//bCanMove = false;

		//FInputModeUIOnly InputMode;
		//UGameplayStatics::GetPlayerController(this, 0)->SetInputMode(InputMode);
		//UGameplayStatics::GetPlayerController(this, 0)->SetShowMouseCursor(true);

		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECR_Ignore);
		GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);

		DropItem();

		bAlive = true;
	}
}

// Called to bind functionality to input
void AMonsterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMonsterCharacter::Attack()
{
	if (bCanAttack)
	{
		bCanAttack = false;

		auto AnimInstance = Cast<UMonsterInstance>(GetMesh()->GetAnimInstance());
		if (nullptr == AnimInstance) return;

		AnimInstance->PlayAttackMontage(AttackMontage);
	}
}

void AMonsterCharacter::AttackCheck()
{
	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, this);
	bool bResult = GetWorld()->SweepSingleByChannel(
		HitResult,
		GetActorLocation(),
		GetActorLocation() + GetActorForwardVector() * AttackRange,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2, // Attack 채널 player의 경우에만 충돌 한다
		FCollisionShape::MakeSphere(AttackRadius),
		Params);

#if ENABLE_DRAW_DEBUG
		FVector TraceVec = GetActorForwardVector() * AttackRange;
		FVector Center = GetActorLocation() + TraceVec * 0.5f;
		float HalfHeight = AttackRange * 0.5f + AttackRadius;
		FQuat CapsuleRot = FRotationMatrix::MakeFromZ(TraceVec).ToQuat();
		FColor DrawColor = bResult ? FColor::Green : FColor::Red;
		float DebugLifeTime = 5.0f;

		// 이거는 에디터에서만 사용하는거		
		DrawDebugCapsule(GetWorld(),
			Center,
			HalfHeight,
			AttackRadius,
			CapsuleRot,
			DrawColor,
			false,
			DebugLifeTime);
		
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("PlayerPunch!")); // 플레이어가 펀치하는지 확인용

#endif


	if (bResult)
	{
		if (HitResult.Actor.IsValid())
		{
			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("Hit!"));
			FDamageEvent DamageEvent;
			AttackParticleStart(HitResult.ImpactPoint); // 몬스터 공격 파티클 출력하기
			APlayerCharacter* HitCharacter = Cast<APlayerCharacter>(HitResult.Actor);
			HitCharacter->TakeDamage(AttackPower, DamageEvent, GetController(), this);
		}
	}
}

float AMonsterCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	fAIHp -= FinalDamage;
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("Attack!"));

	APlayerUI_HUD* HUD = Cast<APlayerUI_HUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());

	HUD->SetMonsterHP(fAIHp / fMaxHp);

	if (fAIHp <= 0) // 피가 다 까이면
	{
		bAlive = false;
		HUD->SetMonsterHidden();
		//HUD->SetGameOverUIVisible();
	}

	//MyTakeDamage.Broadcast();
	return FinalDamage;
}

void AMonsterCharacter::AttackEnd()
{
	bCanAttack = true;
}

void AMonsterCharacter::Skill()
{
	if (bCanAttack)
	{
		bCanAttack = false;

		auto AnimInstance = Cast<UMonsterInstance>(GetMesh()->GetAnimInstance());
		if (nullptr == AnimInstance) return;

		AnimInstance->PlaySkillMontage(SkillMontage);
	}
}

void AMonsterCharacter::SkillCheck()
{
	if (strMonsterType == "Rampage")
	{
		GetCharacterMovement()->MaxWalkSpeed += 20; // 점점 이동속도가 증가한다.
	}

	else if (strMonsterType == "Sevarog")
	{
		// 투사체를 던진다.
		// try and fire a projectile
		if (ProjectileClass != nullptr)
		{
			UWorld* const World = GetWorld();

			if (World != nullptr)
			{
				const FRotator SpawnRotation = GetControlRotation();
				// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
				const FVector SpawnLocation = ((ProjectileMuzzle != nullptr) ? ProjectileMuzzle->GetComponentLocation() : GetActorLocation());

				// + SpawnRotation.RotateVector(GunOffset)
				//Set Spawn Collision Handling Override
				FActorSpawnParameters ActorSpawnParams;
				ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

				// spawn the projectile at the muzzle
				World->SpawnActor<AMonsterProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
			}
		}
	}

	else if (strMonsterType == "Narbash")
	{
		// 광범위 공격을 시전한다.
		FHitResult HitResult;
		FCollisionQueryParams Params(NAME_None, false, this);
		bool bResult = GetWorld()->SweepSingleByChannel(
			HitResult,
			GetActorLocation() + GetActorForwardVector() * SkillRange * -1,
			GetActorLocation() + GetActorForwardVector() * SkillRange,
			FQuat::Identity,
			ECollisionChannel::ECC_GameTraceChannel2, // Attack 채널 player의 경우에만 충돌 한다
			FCollisionShape::MakeSphere(SkillRange),
			Params);

#if ENABLE_DRAW_DEBUG
		FVector TraceVec = GetActorForwardVector() * SkillRange;
		FVector Center = GetActorLocation() + TraceVec * 0.5f;
		float HalfHeight = SkillRange * 0.5f + SkillRadius;
		FQuat CapsuleRot = FRotationMatrix::MakeFromZ(TraceVec).ToQuat();
		FColor DrawColor = bResult ? FColor::Green : FColor::Red;
		float DebugLifeTime = 5.0f;

		// 이거는 에디터에서만 사용하는거		
		DrawDebugCapsule(GetWorld(),
			Center,
			HalfHeight,
			SkillRadius,
			CapsuleRot,
			DrawColor,
			false,
			DebugLifeTime);

		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("MonsterSkill!")); // 플레이어가 펀치하는지 확인용

#endif


		if (bResult)
		{
			if (HitResult.Actor.IsValid())
			{
				GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("Hit!"));
				FDamageEvent DamageEvent;
				APlayerCharacter* HitCharacter = Cast<APlayerCharacter>(HitResult.Actor);
				HitCharacter->TakeDamage(SkillPower, DamageEvent, GetController(), this);
			}
		}
	}

	else if (strMonsterType == "Grux")
	{
		// 광범위 공격을 시전한다.
		FHitResult HitResult;
		FCollisionQueryParams Params(NAME_None, false, this);
		bool bResult = GetWorld()->SweepSingleByChannel(
			HitResult,
			GetActorLocation() + GetActorForwardVector() * SkillRange * -1,
			GetActorLocation() + GetActorForwardVector() * SkillRange,
			FQuat::Identity,
			ECollisionChannel::ECC_GameTraceChannel2, // Attack 채널 player의 경우에만 충돌 한다
			FCollisionShape::MakeSphere(SkillRange),
			Params);

#if ENABLE_DRAW_DEBUG
		FVector TraceVec = GetActorForwardVector() * SkillRange;
		FVector Center = GetActorLocation() + TraceVec * 0.5f;
		float HalfHeight = SkillRange * 0.5f + SkillRadius;
		FQuat CapsuleRot = FRotationMatrix::MakeFromZ(TraceVec).ToQuat();
		FColor DrawColor = bResult ? FColor::Green : FColor::Red;
		float DebugLifeTime = 5.0f;

		// 이거는 에디터에서만 사용하는거		
		DrawDebugCapsule(GetWorld(),
			Center,
			HalfHeight,
			SkillRadius,
			CapsuleRot,
			DrawColor,
			false,
			DebugLifeTime);

		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("MonsterSkill!")); // 플레이어가 펀치하는지 확인용

#endif


		if (bResult)
		{
			if (HitResult.Actor.IsValid())
			{
				GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("Hit!"));
				FDamageEvent DamageEvent;
				APlayerCharacter* HitCharacter = Cast<APlayerCharacter>(HitResult.Actor);
				HitCharacter->TakeDamage(SkillPower, DamageEvent, GetController(), this);
			}
		}
	}
}

void AMonsterCharacter::SkillEnd()
{
	bCanAttack = true;
}


void AMonsterCharacter::StopAIController()
{
	AMonsterController* AIController = Cast<AMonsterController>(GetController());

	AIController->StopAI();
}

void AMonsterCharacter::InitializeAI(FString MonsterType)
{
	UEldenRingGameInstance* MyGI = GetGameInstance<UEldenRingGameInstance>();

	AttackMontage = MyGI->GetMontage(MonsterType);
	IntroMontage = MyGI->GetStartIntroMontage(MonsterType);
	SkillMontage = MyGI->GetSkillMontage(MonsterType);

	AttackParticle = MyGI->GetMonsterAttackParticle(MonsterType);
	SkillParticle = MyGI->GetMonsterSkillParticle(MonsterType);
	IntroParticle = MyGI->GetMonsterIntroParticle(MonsterType);

	GetMesh()->SetSkeletalMesh(MyGI->GetMonsterSkeletalMesh(MonsterType));
	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -88.0f));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	GetMesh()->SetAnimInstanceClass(MyGI->GetAnimation(MonsterType));

	fMaxHp = MyGI->GetMonsterHp(MonsterType);
	fAIHp = fMaxHp;
	GetCharacterMovement()->MaxWalkSpeed = MyGI->GetMonsterSpeed(MonsterType);
	AttackPower = MyGI->GetMonsterPower(MonsterType);

	SkillPower = MyGI->GetMonsterSkillPower(MonsterType);
	SkillRadius = MyGI->GetMonsterSkillRadius(MonsterType);
	SkillRange = MyGI->GetMonsterSkillRange(MonsterType);

	MonsterAnim = Cast<UMonsterInstance>(GetMesh()->GetAnimInstance());
	MonsterAnim->AttackCheck_Attack.AddUObject(this, &AMonsterCharacter::AttackCheck);
	MonsterAnim->EndAttack_Attack.AddUObject(this, &AMonsterCharacter::AttackEnd);
	MonsterAnim->EndSkill_Skill.AddUObject(this, &AMonsterCharacter::SkillEnd);
	MonsterAnim->StartIntroParticle_Particle.AddUObject(this, &AMonsterCharacter::IntroParticleStart);
	MonsterAnim->StartSkillParticle_Particle.AddUObject(this, &AMonsterCharacter::SkillParticleStart);
	MonsterAnim->StartGame_Intro.AddUObject(this, &AMonsterCharacter::MoveMonster);
	MonsterAnim->StopMonster_Death.AddUObject(this, &AMonsterCharacter::StopMonster);
	MonsterAnim->EndSkillParticle_Particle.AddUObject(this, &AMonsterCharacter::SkillParticleEnd);
	MonsterAnim->SkillCheck_Skill.AddUObject(this, &AMonsterCharacter::SkillCheck);
	MonsterAnim->DestroyMonster_Death.AddUObject(this, &AMonsterCharacter::MonsterDestory);

	// 인트로 모션 시작
	MonsterAnim->PlayIntroMontage(IntroMontage);
}

void AMonsterCharacter::AttackParticleStart(FVector StartParticle)
{
	GameStatic->SpawnEmitterAtLocation(GetWorld(), AttackParticle, StartParticle);
}

void AMonsterCharacter::IntroParticleStart()
{
	GameStatic->SpawnEmitterAttached(IntroParticle, IntroParticleMuzzleLocation, FName("IntroParticleMuzzleLocation"));
}

void AMonsterCharacter::SkillParticleStart()
{
	GameStatic->SpawnEmitterAttached(SkillParticle, ParticleMuzzleLocation, FName("ParticleMuzzleLocation"));
}

void AMonsterCharacter::SkillParticleEnd()
{
	UEldenRingGameInstance* MyGI = GetGameInstance<UEldenRingGameInstance>();

	GameStatic->SpawnEmitterAttached(MyGI->GetMonsterSkillSpareParticle(strMonsterType), ParticleMuzzleLocation, FName("ParticleMuzzleLocation"));
}

void AMonsterCharacter::MoveMonster()
{
	AMonsterController* AIController = Cast<AMonsterController>(GetController());

	AIController->EndIntro();

	//APlayerUI_HUD* HUD = Cast<APlayerUI_HUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());

	//HUD->SetMonsterName(strMonsterType);
	//HUD->SetMonsterVisible();

	MonsterAnim->IsIntro = false;
}

void AMonsterCharacter::StopMonster()
{
	StopAIController();
}

void AMonsterCharacter::DropItem()
{
	// 아이템 생성 위치
	FVector vPos = this->GetActorLocation() + FVector(100.0f, 100.0f, 0.0f);

	// 스폰 파라미터 설정
	FActorSpawnParameters params;
	params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	// 월드에 액터를 배치한다.
	AMonsterItem* Item = GetWorld()->SpawnActor<AMonsterItem>(MonsterItemClass, vPos, GetActorRotation(), params);

	if (IsValid(Item))
	{
		Item->ItemName = strMonsterItem;
	}
}

void AMonsterCharacter::MonsterDestory()
{
	Destroy();
}