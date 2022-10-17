// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "GameFrameWork/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFrameWork/CharacterMovementComponent.h"
#include "Animation/AnimInstance.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/KismetMathLibrary.h"
#include "EldenRingGameInstance.h"
#include "MyPlayerAnimInstance.h"
#include "MyPlayerController.h"
#include "MonsterCharacter.h"
#include "PlayerUI_HUD.h"
#include "EldenRingGM.h"
#include "DrawDebugHelpers.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{

	//AutoPossessPlayer = EAutoReceiveInput::Player0;

	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA")); 
	ParticleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("ParticleMuzzleLocation"));
	ParticleLocation->SetupAttachment(GetCapsuleComponent());
	
	SpringArm->SetupAttachment(GetCapsuleComponent());
	Camera->SetupAttachment(SpringArm);

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));

	//CameraOffset = FVector(-800.0f, 0.0f, 300.0f);
	//Camera->SetRelativeRotation(FRotator(0.0f, -40.0f, 0.0f));
	//SpringArm->TargetArmLength = 300.0f;
	//SpringArm->SetRelativeLocationAndRotation(FVector(-400.0f, 0.0f, 400.0f), FRotator(-0.0f, 0.0f, 0.0f));


	//SpringArm->bUsePawnControlRotation = true; // LookUp을 위함
	//Camera->bUsePawnControlRotation = false;


	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	/*
	static ConstructorHelpers::FClassFinder<UAnimInstance> PLAYER_ANIM(TEXT("/Game/BluePrint/MyPlayerAnimation_BP.MyPlayerAnimation_BP_C"));
	if (PLAYER_ANIM.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(PLAYER_ANIM.Class);
	}
	*/

	// bullet effect
	//static ConstructorHelpers::FObjectFinder<UParticleSystem> FIRE(TEXT("ParticleSystem'/Game/ParagonMurdock/FX/Particles/Abilities/SpreadShot/FX/P_SpreadShotImpact_Radial.P_SpreadShotImpact_Radial'"));
	//if (FIRE.Succeeded())
	//{
	//	FireParticle = FIRE.Object;
	//}

	GetCharacterMovement()->JumpZVelocity = 400.0f;
	GetCharacterMovement()->MaxWalkSpeed = 200.0f;

	// 캐릭터가 자연스럽게 회전하게 
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
	GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("ProjectPlayer"));

	fMaxHp = 500.0f;
	fPlayerHp = 500.0f;
	fMaxMp = 100.0f;
	fPlayerMp = 100.0f;
	fMaxStamina = 100.0f;
	fPlayerStamina = 100.0f;
	AttackRange = 250.0f;
	AttackRadius = 50.0f;
	AttackPower = 50.0f; // 나중에 파워 설정 ㄱ
	SkillRange = 500.0f;
	SkillRadius = 1000.0f;
	SkillPower = 200.0f;

	//nSpecialGunBullet = 30;

	bIsRun = false;
	bPlayerPause = false;
	bCanMove = true;
	bIsPlayerControlled = false;
	bAttack = true;
	bTravel = false;
	bCanSkill = true;
	bRunning = false;
	bAlive = true;
	bInventory = false; // false가 안열려있는 상태, true는 열려있는 상태
	nInventory = 16;
	nItemClear = 0;
	//myGun = EGunState::BASIC;
}

void APlayerCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}


// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	UEldenRingGameInstance* MyGI = GetGameInstance<UEldenRingGameInstance>();
	GetMesh()->SetSkeletalMesh(MyGI->GetPlayerSkeletalMesh("Default"));
	GetMesh()->SetAnimInstanceClass(MyGI->GetPlayerAnimation());

	AttackAMontage = MyGI->GetPlayerAttackAMontage();
	AttackBMontage = MyGI->GetPlayerAttackBMontage();
	AttackCMontage = MyGI->GetPlayerAttackCMontage();
	AttackDMontage = MyGI->GetPlayerAttackDMontage();
	SkillIntroMontage = MyGI->GetPlayerSkillIntroMontage();
	SkillMontage = MyGI->GetPlayerSkillMontage();
	StartTravelMontage = MyGI->GetPlayerStartTravelMontage();
	EndTravelMontage = MyGI->GetPlayerEndTravelMontage();
	StunMontage = MyGI->GetPlayerStunMontage();

	PlayerAnim = Cast<UMyPlayerAnimInstance>(GetMesh()->GetAnimInstance());

	PlayerAnim->AttackCheck_Attack.AddUObject(this, &APlayerCharacter::AttackCheck);
	PlayerAnim->EndSkill_Attack.AddUObject(this, &APlayerCharacter::StopSkill);
	PlayerAnim->StopIntro_Attack.AddUObject(this, &APlayerCharacter::StopIntro);
	PlayerAnim->Start_Travel.AddUObject(this, &APlayerCharacter::IsTravelMode);
	PlayerAnim->End_Travel.AddUObject(this, &APlayerCharacter::IsTravelMode);
	PlayerAnim->CantMove_Stun.AddUObject(this, &APlayerCharacter::IsStunStart);
	PlayerAnim->CanMove_Stun.AddUObject(this, &APlayerCharacter::IsStunEnd);
	PlayerAnim->IntroCantMove_Intro.AddUObject(this, &APlayerCharacter::IntroCantMove);
	PlayerAnim->IntroCanMove_Intro.AddUObject(this, &APlayerCharacter::IntroCanMove);
	PlayerAnim->SaveAttack_Attack.AddUObject(this, &APlayerCharacter::SaveCombo);
	PlayerAnim->ResetCombo_Attack.AddUObject(this, &APlayerCharacter::ResetCombo);
	PlayerAnim->IntroParticle_Intro.AddUObject(this, &APlayerCharacter::IntroParticle);
	PlayerAnim->IntroSwordParticle_Intro.AddUObject(this, &APlayerCharacter::IntroSwordParticle);
	PlayerAnim->SkillParticle_Attack.AddUObject(this, &APlayerCharacter::SkillParticle);
	PlayerAnim->SkillCheck_Attack.AddUObject(this, &APlayerCharacter::SkillCheck);

	TestHUD = Cast<APlayerUI_HUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());

	TestHUD->SetPotionAmount(HpPotion.PotionType, MyGI->GetInventoryItemCount(0));
	TestHUD->SetPotionAmount(MpPotion.PotionType, MyGI->GetInventoryItemCount(1));
	TestHUD->SetPotionAmount(StaminaPotion.PotionType, MyGI->GetInventoryItemCount(2));
	bIsRun = false;// 시작할 때 달리기 느려지는 오류 대처

	Inventory.Init(DefaultInventory, nInventory);
	InitInventory();
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bAlive)
	{
		UEldenRingGameInstance* MyGI = GetGameInstance<UEldenRingGameInstance>();
		UGameplayStatics::PlaySoundAtLocation(this, MyGI->GetSound("PlayerDead"), GetActorLocation());

		PlayerAnim->SetDeadAnim();

		bCanMove = false;

		FInputModeUIOnly InputMode;
		UGameplayStatics::GetPlayerController(this, 0)->SetInputMode(InputMode);
		UGameplayStatics::GetPlayerController(this, 0)->SetShowMouseCursor(true);

		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECR_Ignore);
		GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);

		bAlive = true; // 다시 실행되지 않게하기 위함

		//HUD->SetGameOverUIVisible();
	}

	if (bRunning)
	{
		fPlayerStamina -= 0.1f;
		TestHUD->SetPlayerStamina(fPlayerStamina / fMaxStamina);
	}

	if (fPlayerStamina <= 0.0f)
	{
		bRunning = false;
		bIsRun = false;
	}

	if (fPlayerMp <= 0.0f)
	{
		bCanSkill = false;
	}

	//Camera->SetRelativeLocation(CameraOffset);
}


void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// 캐릭터 이동 함수
	//PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &APlayerCharacter::UpDown);
	//PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &APlayerCharacter::LeftRight);
	//PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APlayerCharacter::LookUp);
	//PlayerInputComponent->BindAxis(TEXT("Turn"), this, &APlayerCharacter::Turn);
	
	// 캐릭터 점프 함수
	//PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	//PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	// 캐릭터 공격 함수
	//PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AMyCharacter::OnFire);

	// 캐릭터 달리기 함수
	//PlayerInputComponent->BindAction("Run", IE_Pressed, this, &AMyCharacter::Run);
	//PlayerInputComponent->BindAction("Run", IE_Released, this, &AMyCharacter::StopRun);

	// 캐릭터 견착 함수
	//PlayerInputComponent->BindAction("ReadyFire", IE_Pressed, this, &AMyCharacter::ReadyFire);
	//PlayerInputComponent->BindAction("ReadyFire", IE_Released, this, &AMyCharacter::ResetReadyFire);

	// 플레이어 일시정지 함수
	//PlayerInputComponent->BindAction("Pause", IE_Pressed, this, &AMyCharacter::PlayerPause);
	
}


void APlayerCharacter::UpDown(float NewAxisValue)
{
	if (bCanMove)
	{
		FVector Direction = FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::X);
		Direction.Z = 0.0f;
		Direction.Normalize();

		AddMovementInput(Direction, NewAxisValue);
	}
}

void APlayerCharacter::LeftRight(float NewAxisValue)
{
	if (bCanMove)
	{
		FVector Direction = FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::Y);
		Direction.Z = 0.0f;
		Direction.Normalize();

		AddMovementInput(Direction, NewAxisValue);
	}
}

void APlayerCharacter::LookUp(float NewAxisValue)
{
	if (bCanMove)
	{
		AddControllerPitchInput(NewAxisValue);
	}
}

void APlayerCharacter::Turn(float NewAxisValue)
{
	if (bCanMove)
	{
		AddControllerYawInput(NewAxisValue);
	}
}


void APlayerCharacter::Jump()
{
	if (bCanMove)
	{
		Super::Jump();
		UEldenRingGameInstance* MyGI = GetGameInstance<UEldenRingGameInstance>();
		UGameplayStatics::PlaySoundAtLocation(this, MyGI->GetSound("PlayerJump"), GetActorLocation());
	}
}

void APlayerCharacter::StopJumping()
{
	if (bCanMove)
	{
		Super::StopJumping();
	}
}

void APlayerCharacter::Attack()
{
	// 공격 애니메이션 실행
	//CharacterAnim->PlayAttackMontage();
	if (bAttack)
	{
		auto AnimInstance = Cast<UMyPlayerAnimInstance>(GetMesh()->GetAnimInstance());
		UEldenRingGameInstance* MyGI = GetGameInstance<UEldenRingGameInstance>();
		if (nullptr == AnimInstance) return;

		if (nCombo == 0)
		{
			AnimInstance->PlayAttackMontage(AttackAMontage);
			UGameplayStatics::PlaySoundAtLocation(this, MyGI->GetSound("PlayerAttack1"), GetActorLocation());
		}

		else if (nCombo == 1)
		{
			AnimInstance->PlayAttackMontage(AttackBMontage);
			UGameplayStatics::PlaySoundAtLocation(this, MyGI->GetSound("PlayerAttack2"), GetActorLocation());
		}

		else if (nCombo == 2)
		{
			AnimInstance->PlayAttackMontage(AttackCMontage);
			UGameplayStatics::PlaySoundAtLocation(this, MyGI->GetSound("PlayerAttack3"), GetActorLocation());
		}

		else if (nCombo == 3)
		{
			AnimInstance->PlayAttackMontage(AttackDMontage);
			UGameplayStatics::PlaySoundAtLocation(this, MyGI->GetSound("PlayerAttack4"), GetActorLocation());
		}
		bAttack = false;
	}
}

void APlayerCharacter::AttackCheck()
{
	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, this);
	bool bResult = GetWorld()->SweepSingleByChannel(
		HitResult,
		GetActorLocation(),
		GetActorLocation() + GetActorForwardVector() * AttackRange,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel3, // Attack 채널 player의 경우에만 충돌 한다
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
			AMonsterCharacter* HitCharacter = Cast<AMonsterCharacter>(HitResult.Actor);
			HitCharacter->TakeDamage(AttackPower, DamageEvent, GetController(), this);
		}
	}
}

void APlayerCharacter::Skill()
{
	// 공격 애니메이션 실행
	//CharacterAnim->PlayAttackMontage();

	if (bCanMove && bCanSkill)
	{
		bCanMove = false;
		bAttack = false;
		bIsRun = false;
		
		fPlayerMp -= 10.0f;

		APlayerUI_HUD* HUD = Cast<APlayerUI_HUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());

		HUD->SetPlayerMP(fPlayerMp / fMaxMp);

		auto AnimInstance = Cast<UMyPlayerAnimInstance>(GetMesh()->GetAnimInstance());
		if (nullptr == AnimInstance) return;

		AnimInstance->PlaySkillIntroMontage(SkillIntroMontage);

		UEldenRingGameInstance* MyGI = GetGameInstance<UEldenRingGameInstance>();
		UGameplayStatics::PlaySoundAtLocation(this, MyGI->GetSound("PlayerSkillIntro"), GetActorLocation());

		bSkill = true;
	}
}

void APlayerCharacter::SkillCheck()
{
	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, this);
	bool bResult = GetWorld()->SweepSingleByChannel(
		HitResult,
		GetActorLocation() + GetActorForwardVector() * SkillRange * -1,
		GetActorLocation() + GetActorForwardVector() * SkillRange,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel3, // Attack 채널 player의 경우에만 충돌 한다
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

	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("PlayerSkill!")); // 플레이어가 펀치하는지 확인용

#endif


	if (bResult)
	{
		if (HitResult.Actor.IsValid())
		{
			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("Hit!"));
			FDamageEvent DamageEvent;
			AMonsterCharacter* HitCharacter = Cast<AMonsterCharacter>(HitResult.Actor);
			HitCharacter->TakeDamage(SkillPower, DamageEvent, GetController(), this);
		}
	}
}

void APlayerCharacter::SaveCombo()
{
	nCombo++;
	bAttack = true;
}

void APlayerCharacter::ResetCombo()
{
	nCombo = 0;
	bAttack = true;
}

void APlayerCharacter::StopSkillIntro()
{
	if (bSkill)
	{
		auto AnimInstance = Cast<UMyPlayerAnimInstance>(GetMesh()->GetAnimInstance());
		if (nullptr == AnimInstance) return;

		AnimInstance->PlaySkillMontage(SkillMontage);

		UEldenRingGameInstance* MyGI = GetGameInstance<UEldenRingGameInstance>();
		UGameplayStatics::PlaySoundAtLocation(this, MyGI->GetSound("PlayerSkill"), GetActorLocation());
	}
}

void APlayerCharacter::StopSkill()
{
	bCanMove = true;
	bSkill = false;
	bIsRun = true;

	//GetCharacterMovement()->MaxWalkSpeed = 200.0f;
}

void APlayerCharacter::StopIntro()
{
	bCanMove = true;
	bSkill = false;

	// MP 일정 돌려주기
	fPlayerMp += 5.0f;

	APlayerUI_HUD* HUD = Cast<APlayerUI_HUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());

	HUD->SetPlayerMP(fPlayerMp / fMaxMp);

	//GetCharacterMovement()->MaxWalkSpeed = 200.0f;
}

void APlayerCharacter::TravelMode()
{
	if (bCanMove && bTravel)
	{
		bCanMove = false; // 일단 못움직이게하고

		auto AnimInstance = Cast<UMyPlayerAnimInstance>(GetMesh()->GetAnimInstance());
		if (nullptr == AnimInstance) return;

		AnimInstance->PlayTravelEndMontage(EndTravelMontage);
	}

	else if(bCanMove && !bTravel)
	{
		bCanMove = false; // 일단 못움직이게하고

		auto AnimInstance = Cast<UMyPlayerAnimInstance>(GetMesh()->GetAnimInstance());
		if (nullptr == AnimInstance) return;

		AnimInstance->PlayTravelStartMontage(StartTravelMontage);
	}
}

void APlayerCharacter::IsTravelMode()
{
	if (bTravel)
	{
		bTravel = false;
		bCanMove = true;
		bAttack = true;
		GetCharacterMovement()->MaxWalkSpeed = 200.0f;
	}

	else
	{
		bTravel = true;
		bCanMove = true;
		bAttack = false;
		GetCharacterMovement()->MaxWalkSpeed = 5000.0f;
	}
}

void APlayerCharacter::Run()
{
	if (bIsRun)
	{
		GetCharacterMovement()->MaxWalkSpeed *= 2;
		bRunning = true;
	}

	else
	{
		GetCharacterMovement()->MaxWalkSpeed = 200.0f;
		
		if (bTravel)
		{
			GetCharacterMovement()->MaxWalkSpeed = 300.0f;
		}
	}
}

void APlayerCharacter::StopRun()
{
	if (bIsRun)
	{
		GetCharacterMovement()->MaxWalkSpeed /= 2;
		bRunning = false;
	}

	else
	{
		GetCharacterMovement()->MaxWalkSpeed = 200.0f;

		if (bTravel)
		{
			GetCharacterMovement()->MaxWalkSpeed = 300.0f;
		}
	}
}

void APlayerCharacter::HpDrink()
{
	UEldenRingGameInstance* MyGI = GetGameInstance<UEldenRingGameInstance>();

	if (MyGI->GetInventoryItemCount(0) == 0)
	{
		return;
	}

	if (fPlayerHp >= 500.0f)
	{
		fPlayerHp = 500.0f;
		return;
	}

	fPlayerHp += 30.0f;

	// 이거는 사용안함
	HpPotion.PotionAmount -= 1;

	APlayerUI_HUD* HUD = Cast<APlayerUI_HUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());

	int nCount = MyGI->GetInventoryItemCount(0) - 1;
	MyGI->SetInventoryItemCount(0, nCount);

	HUD->SetPlayerHP(fPlayerHp / fMaxHp);
	HUD->SetPotionAmount("HP", MyGI->GetInventoryItemCount(0));

	HUD->SetListCount(0, nCount);
	HUD->ListUpdate();
}

void APlayerCharacter::MpDrink()
{
	UEldenRingGameInstance* MyGI = GetGameInstance<UEldenRingGameInstance>();

	if (MyGI->GetInventoryItemCount(1) == 0)
	{
		return;
	}

	if (fPlayerMp >= 100.0f)
	{
		fPlayerMp = 100.0f;
		return;
	}

	if (fPlayerMp <= 0.0f)
	{
		bCanSkill = true;
	}

	fPlayerMp += 30.0f;

	// 이거는 사용안함
	MpPotion.PotionAmount -= 1;

	APlayerUI_HUD* HUD = Cast<APlayerUI_HUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());

	int nCount = MyGI->GetInventoryItemCount(1) - 1;
	MyGI->SetInventoryItemCount(1, nCount);

	HUD->SetPlayerMP(fPlayerMp / fMaxMp);
	HUD->SetPotionAmount("MP", MyGI->GetInventoryItemCount(1));

	HUD->SetListCount(1, nCount);
	HUD->ListUpdate();
}

void APlayerCharacter::StaminaDrink()
{
	UEldenRingGameInstance* MyGI = GetGameInstance<UEldenRingGameInstance>();

	if (MyGI->GetInventoryItemCount(2) == 0)
	{
		return;
	}

	if (fPlayerStamina >= 100.0f)
	{
		fPlayerStamina = 100.0f;
		return;
	}

	if (fPlayerStamina <= 0.0f)
	{
		bIsRun = true;
	}

	fPlayerStamina += 30.0f;

	// 이거는 사용안함
	StaminaPotion.PotionAmount -= 1;

	APlayerUI_HUD* HUD = Cast<APlayerUI_HUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());

	int nCount = MyGI->GetInventoryItemCount(2) - 1;
	MyGI->SetInventoryItemCount(2, nCount);

	HUD->SetPlayerStamina(fPlayerStamina / fMaxStamina);
	HUD->SetPotionAmount("Stamina", MyGI->GetInventoryItemCount(2));

	HUD->SetListCount(2, nCount);
	HUD->ListUpdate();
}

void APlayerCharacter::IsStunStart()
{
	bAttack = false;
	UEldenRingGameInstance* MyGI = GetGameInstance<UEldenRingGameInstance>();
	UGameplayStatics::PlaySoundAtLocation(this, MyGI->GetSound("PlayerAttacked"), GetActorLocation());
}

void APlayerCharacter::IsStunEnd()
{
	bAttack = true;
}

void APlayerCharacter::IntroParticle()
{
	UEldenRingGameInstance* MyGI = GetGameInstance<UEldenRingGameInstance>();

	//ParticleLocation->SetRelativeLocation(FVector(0.0f, 0.0f, -20.0f));

	GameStatic->SpawnEmitterAttached(MyGI->GetPlayerIntroParticle(), ParticleLocation, FName("ParticleLocation"));
}

void APlayerCharacter::IntroSwordParticle()
{
	UEldenRingGameInstance* MyGI = GetGameInstance<UEldenRingGameInstance>();

	GameStatic->SpawnEmitterAttached(MyGI->GetPlayerIntroSwordParticle(), ParticleLocation, FName("ParticleLocation"));
}

void APlayerCharacter::SkillParticle()
{
	UEldenRingGameInstance* MyGI = GetGameInstance<UEldenRingGameInstance>();

	GameStatic->SpawnEmitterAttached(MyGI->GetPlayerSkillParticle(), ParticleLocation, FName("ParticleLocation"));
}

/*
void APlayerCharacter::PlayerPause()
{
	//APlayerInterface_HUD* HUD = Cast<APlayerInterface_HUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());

	GameStatic->SetGamePaused(GetWorld(), true);

	FInputModeUIOnly InputMode;
	UGameplayStatics::GetPlayerController(this, 0)->SetInputMode(InputMode);
	UGameplayStatics::GetPlayerController(this, 0)->SetShowMouseCursor(true);
	//HUD->SetGamePauseUIVisible();
}
*/
float APlayerCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	PlayerAnim->PlayStunMontage(StunMontage); // 기절 애니메이션 출력

	fPlayerHp -= FinalDamage;
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("Attack!"));

	APlayerUI_HUD* HUD = Cast<APlayerUI_HUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());

	HUD->SetPlayerHP(fPlayerHp / fMaxHp);

	if (fPlayerHp <= 0.0f) // 피가 다 까이면
	{
		bAlive = false;
	}

	//MyTakeDamage.Broadcast();
	return FinalDamage;

}

void APlayerCharacter::AttackedProjectTile(float fDamage)
{
	fPlayerHp -= fDamage;

	APlayerUI_HUD* HUD = Cast<APlayerUI_HUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());

	HUD->SetPlayerHP(fPlayerHp / fMaxHp);

	if (fPlayerHp <= 0.0f)
	{
		bAlive = false;
	}
}

void APlayerCharacter::IntroCantMove()
{
	bCanMove = false;
	bAttack = false;
	bSkill = false;
	bIsRun = false;

	UEldenRingGameInstance* MyGI = GetGameInstance<UEldenRingGameInstance>();
	UGameplayStatics::PlaySoundAtLocation(this, MyGI->GetSound("PlayerIntro"), GetActorLocation());
}

void APlayerCharacter::IntroCanMove()
{
	bCanMove = true;
	bAttack = true;
	bSkill = true;
	bIsRun = true;
}

void APlayerCharacter::CheckInventory()
{
	if (!bInventory)
	{
		APlayerUI_HUD* HUD = Cast<APlayerUI_HUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());

		//GameStatic->SetGamePaused(GetWorld(), true);
		
		// 인벤토리 초기화
		//InitInventory();

		FInputModeUIOnly InputMode;
		//UGameplayStatics::GetPlayerController(this, 0)->SetInputMode(InputMode);
		UGameplayStatics::GetPlayerController(this, 0)->SetShowMouseCursor(true);

		HUD->SetVisible();
		UEldenRingGameInstance* MyGI = GetGameInstance<UEldenRingGameInstance>();

		//HUD->SetItemDescriptVisible();
		//HUD->SetItemDescript(MyGI->GetItemName("HP"), MyGI->GetItemDescript("HP"), MyGI->GetItemImage("HP"));

		bInventory = true;
	}

	else
	{
		APlayerUI_HUD* HUD = Cast<APlayerUI_HUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());

		//GameStatic->SetGamePaused(GetWorld(), false);

		UGameplayStatics::GetPlayerController(this, 0)->SetShowMouseCursor(false);

		HUD->SetHidden();
		HUD->Init();

		bInventory = false;
	}
}

void APlayerCharacter::InitInventory()
{
	UEldenRingGameInstance* MyGI = GetGameInstance<UEldenRingGameInstance>();
	APlayerUI_HUD* HUD = Cast<APlayerUI_HUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());

	for (int Index = 0; Index < 10; Index++)
	{
		FString strName = MyGI->GetInventoryItemName(Index);
		int nCount = MyGI->GetInventoryItemCount(Index);
		UTexture2D* setImage;
		if (strName == "")
		{
			setImage = MyGI->GetItemImage("Default");
		}

		else
		{
			setImage = MyGI->GetItemImage(strName);
		}

		HUD->SetListView(Index, strName, nCount, setImage);
	}
}

void APlayerCharacter::GetItem(FString ItemName)
{
	UEldenRingGameInstance* MyGI = GetGameInstance<UEldenRingGameInstance>();
	APlayerUI_HUD* HUD = Cast<APlayerUI_HUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());

	for (int Index = 0; Index < nInventory; Index++)
	{
		if (MyGI->GetInventoryItemName(Index) != "")
		{
			continue;
		}

		else
		{
			MyGI->SetInventoryItemName(Index, ItemName);
			MyGI->SetInventoryItemCount(Index, 1);

			int nCount = MyGI->GetInventoryItemCount(Index);
			UTexture2D* setImage = MyGI->GetItemImage(ItemName);

			nItemClear++;

			HUD->SetListInit(Index, ItemName, nCount, setImage);

			break;
		}
	}

	HUD->ListUpdate();
}

void APlayerCharacter::GameClear()
{
	if (nItemClear >= 4)
	{
		UWorld* World = GetWorld();

		APlayerController* PlayerController = World->GetFirstPlayerController();

		PlayerController->ConsoleCommand("quit");
	}
}

