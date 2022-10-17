// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MonsterInstance.generated.h"

DECLARE_MULTICAST_DELEGATE(FAttackCheck_AttackDelegate); // ����
DECLARE_MULTICAST_DELEGATE(FEndAttack_AttackDelegate); // ���� ��
DECLARE_MULTICAST_DELEGATE(FGameStart_IntroDelegate); // ���� ��Ʈ�� ��
DECLARE_MULTICAST_DELEGATE(FEndSkill_SkillDelegate); // ��ų ��� ��
DECLARE_MULTICAST_DELEGATE(FSkillCheck_SkillDelegate); // ��ų ȿ�� ���
DECLARE_MULTICAST_DELEGATE(FStartParticle_ParticleDelegate); // Attack ��ƼŬ ����
DECLARE_MULTICAST_DELEGATE(FStartIntroParticle_ParticleDelegate); // Intro ��ƼŬ ����
DECLARE_MULTICAST_DELEGATE(FStartSkillParticle_ParticleDelegate); // Intro ��ƼŬ ����
DECLARE_MULTICAST_DELEGATE(FEndSkillParticle_ParticleDelegate); // Intro ��ƼŬ ������
DECLARE_MULTICAST_DELEGATE(FStopMonster_DeathDelegate); // Death StopMonster
DECLARE_MULTICAST_DELEGATE(FDestroyMonster_DeathDelegate); // Destroy Monster

/**
 * 
 */
UCLASS()
class ELDENRING_API UMonsterInstance : public UAnimInstance
{
	GENERATED_BODY()

		UMonsterInstance();
		virtual void NativeUpdateAnimation(float DeltaSeconds) override;
		virtual void NativeBeginPlay() override;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		UAnimMontage* AttackMontage;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Intro, Meta = (AllowPrivateAccess = true))
		UAnimMontage* IntroMontage;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Skill, Meta = (AllowPrivateAccess = true))
		UAnimMontage* SkillMontage;

private:
	UFUNCTION()
		void AnimNotify_AttackCheck();

	UFUNCTION()
		void AnimNotify_EndAttack();

	UFUNCTION()
		void AnimNotify_GameStart();

	UFUNCTION()
		void AnimNotify_EndSkill();

	UFUNCTION()
		void AnimNotify_StartParticle();

	UFUNCTION()
		void AnimNotify_StartIntroParticle();

	UFUNCTION()
		void AnimNotify_StartSkillParticle();

	UFUNCTION()
		void AnimNotify_StopMonster();

	UFUNCTION()
		void AnimNotify_EndSkillParticle();

	UFUNCTION()
		void AnimNotify_SkillCheck();

	UFUNCTION()
		void AnimNotify_DestroyMonster();

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		float CurrentPawnSpeed; // AnimInstance�� ����ؼ� C++ ��ũ���� �� ���� �������Ʈ���� ����� �����ϴ�.

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		bool IsInAir;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		bool IsDead;

	int nMonsterType;

public:
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		bool IsAttacking;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		bool IsIntro;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		bool IsSkill;

	FAttackCheck_AttackDelegate AttackCheck_Attack;
	FEndAttack_AttackDelegate EndAttack_Attack;
	FGameStart_IntroDelegate StartGame_Intro;
	FEndSkill_SkillDelegate EndSkill_Skill;
	FStartParticle_ParticleDelegate StartParticle_Particle;
	FStartIntroParticle_ParticleDelegate StartIntroParticle_Particle;
	FStartSkillParticle_ParticleDelegate StartSkillParticle_Particle;
	FStopMonster_DeathDelegate StopMonster_Death;
	FEndSkillParticle_ParticleDelegate EndSkillParticle_Particle;
	FSkillCheck_SkillDelegate SkillCheck_Skill;
	FDestroyMonster_DeathDelegate DestroyMonster_Death;

	void PlayAttackMontage(UAnimMontage* GetAttackMontage);
	void PlayIntroMontage(UAnimMontage* GetIntroMontage);
	void PlaySkillMontage(UAnimMontage* GetIntroMontage);

	FName GetAttackMontageSectionName(int32 Section);
	void SetDeadAnim();
};
