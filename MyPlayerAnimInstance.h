// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MyPlayerAnimInstance.generated.h"

DECLARE_MULTICAST_DELEGATE(FSaveAttack_AttackDelegate); // 공격 시작
DECLARE_MULTICAST_DELEGATE(FResetCombo_AttackDelegate); // 공격 끝
DECLARE_MULTICAST_DELEGATE(FAttackCheck_AttackDelegate); // 공격 체크
DECLARE_MULTICAST_DELEGATE(FStopIntro_AttackDelegate); // 스킬인트로 끝
DECLARE_MULTICAST_DELEGATE(FSkillPartile_AttackDelegate); // 스킬 파티클
DECLARE_MULTICAST_DELEGATE(FSkillCheck_AttackDelegate); // 스킬 공격 체크
DECLARE_MULTICAST_DELEGATE(FEndSKill_AttackDelegate); // 스킬 끝
DECLARE_MULTICAST_DELEGATE(FTravelMode_StartDelegate); // TravelModeStart 끝
DECLARE_MULTICAST_DELEGATE(FTravelMode_EndDelegate); // TravelModeEnd 끝
DECLARE_MULTICAST_DELEGATE(FOnOnCollisonStart_AttackDelegate); // 공격 시작
DECLARE_MULTICAST_DELEGATE(FOnOnCollisonEnded_AttackDelegate); // 공격 끝
DECLARE_MULTICAST_DELEGATE(FCantMove_StunDelegate); // 기절 시작
DECLARE_MULTICAST_DELEGATE(FCanMove_StunDelegate); // 기절 끝
DECLARE_MULTICAST_DELEGATE(FIntroCantMove_IntroDelegate); // 인트로 시작
DECLARE_MULTICAST_DELEGATE(FIntroSwordParticle_IntroDelegate); // 인트로 Sword 파티클 시작
DECLARE_MULTICAST_DELEGATE(FIntroParticle_IntroDelegate); // 인트로 파티클 시작
DECLARE_MULTICAST_DELEGATE(FIntroCanMove_IntroDelegate); // 인트로 끝
/**
 * 
 */
UCLASS()
class ELDENRING_API UMyPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UMyPlayerAnimInstance();
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	void PlayAttackMontage(UAnimMontage* GetAttackMontage);
	void PlaySkillMontage(UAnimMontage* GetAttackMontage);
	void PlaySkillIntroMontage(UAnimMontage* GetAttackMontage);
	void PlayTravelStartMontage(UAnimMontage* GetAttackMontage);
	void PlayTravelEndMontage(UAnimMontage* GetAttackMontage);
	void PlayStunMontage(UAnimMontage* GetAttackMontage);

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		UAnimMontage* AttackMontageTypeA;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		UAnimMontage* AttackMontageTypeB;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		UAnimMontage* AttackMontageTypeC;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		UAnimMontage* AttackMontageTypeD;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		UAnimMontage* AttackMontageSkill;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		UAnimMontage* AttackMontageSkillIntro;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		UAnimMontage* StartTravelMode;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		UAnimMontage* EndTravelMode;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		UAnimMontage* StunAnimation;

	FName GetAttackMontageSectionName(int32 Section);
	void SetDeadAnim();

	FSaveAttack_AttackDelegate SaveAttack_Attack;
	FResetCombo_AttackDelegate ResetCombo_Attack;
	FAttackCheck_AttackDelegate AttackCheck_Attack;
	FEndSKill_AttackDelegate EndSkill_Attack;
	FSkillPartile_AttackDelegate SkillParticle_Attack;
	FStopIntro_AttackDelegate StopIntro_Attack;
	FTravelMode_StartDelegate Start_Travel;
	FTravelMode_EndDelegate End_Travel;
	FCantMove_StunDelegate CantMove_Stun;
	FCanMove_StunDelegate CanMove_Stun;
	FIntroCantMove_IntroDelegate IntroCantMove_Intro;
	FIntroCanMove_IntroDelegate IntroCanMove_Intro;
	FIntroParticle_IntroDelegate IntroParticle_Intro;
	FIntroSwordParticle_IntroDelegate IntroSwordParticle_Intro;
	FSkillCheck_AttackDelegate SkillCheck_Attack;


private:
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		float CurrentPawnSpeed; // AnimInstance를 사용해서 C++ 스크립팅 한 것을 블루프린트에서 사용이 가능하다.

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		bool IsInAir;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		bool IsDead;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		bool IsTravel;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		bool IsIntro;

	int nCombo;

	UFUNCTION()
		void AnimNotify_SaveAttack();
	UFUNCTION()
		void AnimNotify_ResetCombo();
	UFUNCTION()
		void AnimNotify_AttackCheck();
	UFUNCTION()
		void AnimNotify_EndSkill();
	UFUNCTION()
		void AnimNotify_StopIntro();
	UFUNCTION()
		void AnimNotify_Travel_Start();
	UFUNCTION()
		void AnimNotify_Travel_End();
	UFUNCTION()
		void AnimNotify_CantMove();
	UFUNCTION()
		void AnimNotify_CanMove();
	UFUNCTION()
		void AnimNotify_IntroCantMove();
	UFUNCTION()
		void AnimNotify_IntroCanMove();
	UFUNCTION()
		void AnimNotify_IntroParticle();
	UFUNCTION()
		void AnimNotify_IntroSwordParticle();
	UFUNCTION()
		void AnimNotify_SkillParticle();
	UFUNCTION()
		void AnimNotify_SkillCheck();

public:
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		bool IsAttacking;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		bool IsCanMove;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		float fDirection; // AnimInstance를 사용해서 C++ 스크립팅 한 것을 블루프린트에서 사용이 가능하다.
};
