// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_SkillTime.h"
#include "MonsterController.h"
#include "MonsterCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTDecorator_SkillTime::UBTDecorator_SkillTime()
{
    NodeName = TEXT("CanSkill");
}

bool UBTDecorator_SkillTime::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
    bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

    int SkillTime = OwnerComp.GetBlackboardComponent()->GetValueAsInt(AMonsterController::SkillTime);
    bResult = (SkillTime == 20);
    return bResult;
}
