// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/PawnMovementComponent.h"
#include "EldenRingGameInstance.h"
#include "Kismet/GameplayStatics.h"

UMonsterInstance::UMonsterInstance()
{
	CurrentPawnSpeed = 0.0f;
	IsInAir = false;
	IsDead = false;
	IsAttacking = false;
	IsIntro = true;
	IsSkill = false;

	//static ConstructorHelpers::FObjectFinder<UAnimMontage> ATTACK_MONTAGE(TEXT("AnimMontage'/Game/ParagonGrux/Characters/Heroes/Grux/Animations/PrimaryAttack_FourStrikes_Montage.PrimaryAttack_FourStrikes_Montage'"));
	//if (ATTACK_MONTAGE.Succeeded())
	//{
		//AttackMontage = ATTACK_MONTAGE.Object;
	//}
}

void UMonsterInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
}

void UMonsterInstance::NativeUpdateAnimation(float DeltaSeconds)
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

void UMonsterInstance::PlayAttackMontage(UAnimMontage* GetAttackMontage)
{
	Montage_Play(GetAttackMontage, 1.0f);
}

void UMonsterInstance::PlaySkillMontage(UAnimMontage* GetAttackMontage)
{
	Montage_Play(GetAttackMontage, 1.0f);
}

void UMonsterInstance::PlayIntroMontage(UAnimMontage* GetIntroMontage)
{
	Montage_Play(GetIntroMontage, 1.0f);
}

void UMonsterInstance::SetDeadAnim()
{
	IsDead = true;
}

FName UMonsterInstance::GetAttackMontageSectionName(int32 Section)
{
	return FName(*FString::Printf(TEXT("Attack%d"), Section));
}

void UMonsterInstance::AnimNotify_AttackCheck()
{
	AttackCheck_Attack.Broadcast();
}

void UMonsterInstance::AnimNotify_EndAttack()
{
	EndAttack_Attack.Broadcast();
}

void UMonsterInstance::AnimNotify_GameStart()
{
	StartGame_Intro.Broadcast();
}

void UMonsterInstance::AnimNotify_EndSkill()
{
	EndSkill_Skill.Broadcast();
}

void UMonsterInstance::AnimNotify_StartParticle()
{
	StartParticle_Particle.Broadcast();
}

void UMonsterInstance::AnimNotify_StartIntroParticle()
{
	StartIntroParticle_Particle.Broadcast();
}

void UMonsterInstance::AnimNotify_StartSkillParticle()
{
	StartSkillParticle_Particle.Broadcast();
}

void UMonsterInstance::AnimNotify_StopMonster()
{
	StopMonster_Death.Broadcast();
}

void UMonsterInstance::AnimNotify_EndSkillParticle()
{
	EndSkillParticle_Particle.Broadcast();
}

void UMonsterInstance::AnimNotify_SkillCheck()
{
	SkillCheck_Skill.Broadcast();
}

void UMonsterInstance::AnimNotify_DestroyMonster()
{
	DestroyMonster_Death.Broadcast();
}