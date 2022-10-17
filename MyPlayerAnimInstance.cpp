// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/PawnMovementComponent.h"

UMyPlayerAnimInstance::UMyPlayerAnimInstance()
{
	CurrentPawnSpeed = 0.0f;
	IsInAir = false;
	IsDead = false;
	IsAttacking = true;
	IsCanMove = true;
	IsTravel = false;
	IsIntro = true;
	fDirection = 0.0f;

	nCombo = 0;
	static ConstructorHelpers::FObjectFinder<UAnimMontage> ATTACK_MONTAGE1(TEXT("AnimMontage'/Game/ParagonKwang/Characters/Heroes/Kwang/Animations/PrimaryAttack_A_Slow_Montage.PrimaryAttack_A_Slow_Montage'"));
	if (ATTACK_MONTAGE1.Succeeded())
	{
		AttackMontageTypeA = ATTACK_MONTAGE1.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> ATTACK_MONTAGE2(TEXT("AnimMontage'/Game/ParagonKwang/Characters/Heroes/Kwang/Animations/PrimaryAttack_B_Slow_Montage.PrimaryAttack_B_Slow_Montage'"));
	if (ATTACK_MONTAGE2.Succeeded())
	{
		AttackMontageTypeB = ATTACK_MONTAGE2.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> ATTACK_MONTAGE3(TEXT("AnimMontage'/Game/ParagonKwang/Characters/Heroes/Kwang/Animations/PrimaryAttack_C_Slow_Montage.PrimaryAttack_C_Slow_Montage'"));
	if (ATTACK_MONTAGE3.Succeeded())
	{
		AttackMontageTypeC = ATTACK_MONTAGE3.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> ATTACK_MONTAGE4(TEXT("AnimMontage'/Game/ParagonKwang/Characters/Heroes/Kwang/Animations/PrimaryAttack_D_Slow_Montage.PrimaryAttack_D_Slow_Montage'"));
	if (ATTACK_MONTAGE4.Succeeded())
	{
		AttackMontageTypeD = ATTACK_MONTAGE4.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> ATTACK_SKILLMONTAGE(TEXT("AnimMontage'/Game/ParagonKwang/Characters/Heroes/Kwang/Animations/Montage/Ability_R_Montage.Ability_R_Montage'"));
	if (ATTACK_SKILLMONTAGE.Succeeded())
	{
		AttackMontageSkill = ATTACK_SKILLMONTAGE.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> ATTACK_SKILLINTROMONTAGE(TEXT("AnimMontage'/Game/ParagonKwang/Characters/Heroes/Kwang/Animations/Montage/Ability_R_Intro_Montage.Ability_R_Intro_Montage'"));
	if (ATTACK_SKILLINTROMONTAGE.Succeeded())
	{
		AttackMontageSkillIntro = ATTACK_SKILLINTROMONTAGE.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> TRAVEL_START(TEXT("AnimMontage'/Game/ParagonKwang/Characters/Heroes/Kwang/Animations/Montage/TravelMode_Start_Montage.TravelMode_Start_Montage'"));
	if (TRAVEL_START.Succeeded())
	{
		StartTravelMode = TRAVEL_START.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> TRAVEL_END(TEXT("AnimMontage'/Game/ParagonKwang/Characters/Heroes/Kwang/Animations/Montage/TravelMode_End_Montage.TravelMode_End_Montage'"));
	if (TRAVEL_END.Succeeded())
	{
		EndTravelMode = TRAVEL_END.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> STUN_START(TEXT("AnimMontage'/Game/ParagonKwang/Characters/Heroes/Kwang/Animations/Montage/Stun_Montage.Stun_Montage'"));
	if (STUN_START.Succeeded())
	{
		StunAnimation = STUN_START.Object;
	}
}

void UMyPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Pawn = TryGetPawnOwner(); // 폰에 접근해서 폰의 속력 값을 얻어온다.
	if (!::IsValid(Pawn)) return;

	if (!IsDead)
	{
		CurrentPawnSpeed = Pawn->GetVelocity().Size();
		auto Character = Cast<ACharacter>(Pawn);
		if (Character)
		{
			IsInAir = Character->GetMovementComponent()->IsFalling();
		}
	}
}

void UMyPlayerAnimInstance::PlayAttackMontage(UAnimMontage* GetAttackMontage)
{
	if (IsAttacking == true)
	{
		Montage_Play(GetAttackMontage, 1.0f);
	}
}

void UMyPlayerAnimInstance::PlaySkillMontage(UAnimMontage* GetAttackMontage)
{
	Montage_Play(AttackMontageSkill, 1.0f);
}

void UMyPlayerAnimInstance::PlaySkillIntroMontage(UAnimMontage* GetAttackMontage)
{
	Montage_Play(AttackMontageSkillIntro, 1.0f);
}

void UMyPlayerAnimInstance::PlayTravelStartMontage(UAnimMontage* GetAttackMontage)
{
	Montage_Play(StartTravelMode, 1.0f);
	IsTravel = true;
}

void UMyPlayerAnimInstance::PlayTravelEndMontage(UAnimMontage* GetAttackMontage)
{
	Montage_Play(EndTravelMode, 1.0f);
	IsTravel = false;
}

void UMyPlayerAnimInstance::PlayStunMontage(UAnimMontage* GetAttackMontage)
{
	Montage_Play(StunAnimation, 1.0f);
}

void UMyPlayerAnimInstance::SetDeadAnim()
{
	IsDead = true;
}

FName UMyPlayerAnimInstance::GetAttackMontageSectionName(int32 Section)
{
	return FName(*FString::Printf(TEXT("Attack%d"), Section));
}

void UMyPlayerAnimInstance::AnimNotify_SaveAttack()
{
	SaveAttack_Attack.Broadcast();
	IsAttacking = true;
	nCombo++;
}

void UMyPlayerAnimInstance::AnimNotify_ResetCombo()
{
	ResetCombo_Attack.Broadcast();
	nCombo = 0;
	IsAttacking = true;
}

void UMyPlayerAnimInstance::AnimNotify_AttackCheck()
{
	AttackCheck_Attack.Broadcast();
}

void UMyPlayerAnimInstance::AnimNotify_EndSkill()
{
	EndSkill_Attack.Broadcast();
	IsCanMove = true;
}

void UMyPlayerAnimInstance::AnimNotify_StopIntro()
{
	StopIntro_Attack.Broadcast();
}

void UMyPlayerAnimInstance::AnimNotify_Travel_Start()
{
	Start_Travel.Broadcast();
}

void UMyPlayerAnimInstance::AnimNotify_Travel_End()
{
	End_Travel.Broadcast();
}

void UMyPlayerAnimInstance::AnimNotify_CantMove()
{
	CantMove_Stun.Broadcast();
}

void UMyPlayerAnimInstance::AnimNotify_CanMove()
{
	CanMove_Stun.Broadcast();
}

void UMyPlayerAnimInstance::AnimNotify_IntroCantMove()
{
	IntroCantMove_Intro.Broadcast();
}

void UMyPlayerAnimInstance::AnimNotify_IntroCanMove()
{
	IntroCanMove_Intro.Broadcast();
	IsIntro = false;
}

void UMyPlayerAnimInstance::AnimNotify_IntroParticle()
{
	IntroParticle_Intro.Broadcast();
}

void UMyPlayerAnimInstance::AnimNotify_IntroSwordParticle()
{
	IntroSwordParticle_Intro.Broadcast();
}

void UMyPlayerAnimInstance::AnimNotify_SkillParticle()
{
	SkillParticle_Attack.Broadcast();
}

void UMyPlayerAnimInstance::AnimNotify_SkillCheck()
{
	SkillCheck_Attack.Broadcast();
}