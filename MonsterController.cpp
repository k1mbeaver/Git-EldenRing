// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterController.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MonsterCharacter.h"
#include "MonsterInstance.h"

const FName AMonsterController::HomePosKey(TEXT("HomePos"));
const FName AMonsterController::PatrolPosKey(TEXT("PatrolPos"));
const FName AMonsterController::TargetKey(TEXT("Target"));
const FName AMonsterController::SkillTime(TEXT("SkillTime"));
const FName AMonsterController::bUIPrint(TEXT("bUIPrint"));


AMonsterController::AMonsterController(FObjectInitializer const& object_initializer)
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("BehaviorTree'/Game/AI/BT_MonsterAI.BT_MonsterAI'"));
	if (BTObject.Succeeded())
	{
		BTAsset = BTObject.Object;
	}

	BTAsset_Component = object_initializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorComp"));
	BBAsset = object_initializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackboardComp"));
}

void AMonsterController::BeginPlay()
{
	Super::BeginPlay();

	//RunBehaviorTree(BTAsset);
	//BTAsset_Component->StartTree(*BTAsset);
}

void AMonsterController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	myCharacter = Cast<AMonsterCharacter>(InPawn);
}

UBlackboardComponent* AMonsterController::get_blackboard() const
{
	return BBAsset;
}

void AMonsterController::RunAI()
{
	if (BBAsset)
	{
		BBAsset->InitializeBlackboard(*BTAsset->BlackboardAsset);
	}
}

void AMonsterController::StopAI()
{
	if (this == nullptr) // 서버, 클라이언트 할때는 이거 해줘야하나?
	{
		return;
	}

	BTAsset_Component->StopTree(EBTStopMode::Safe);
}

void AMonsterController::EndIntro() // 여기서 BT를 실행시킨다.
{
	RunBehaviorTree(BTAsset);
	BTAsset_Component->StartTree(*BTAsset);
}
