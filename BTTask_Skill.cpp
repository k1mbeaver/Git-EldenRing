// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Skill.h"
#include "MonsterCharacter.h"
#include "MonsterController.h"

UBTTask_Skill::UBTTask_Skill()
{
    bNotifyTick = true;
    IsSkill = false;
}

EBTNodeResult::Type UBTTask_Skill::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

    auto MyAICharacter = Cast<AMonsterCharacter>(OwnerComp.GetAIOwner()->GetPawn());
    if (MyAICharacter == nullptr)
        return EBTNodeResult::Failed;

    MyAICharacter->Skill();
    IsSkill = true;
    // MyAICharacter->OnAttackEnd.AddLambda([this]() -> void {
        //IsAttacking = false;
        //});

    return EBTNodeResult::InProgress;
}

void UBTTask_Skill::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
    if (!IsSkill)
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
    }
}
