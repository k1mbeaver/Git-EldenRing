// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterSpawner.h"
#include "NavigationSystem.h"
#include "MonsterCharacter.h"
#include "EldenRingGameInstance.h"
#include <random>

// Sets default values
AMonsterSpawner::AMonsterSpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/*
	static ConstructorHelpers::FObjectFinder<AMyAICharacter> AI_CHARACTER(TEXT("Blueprint'/Game/BluePrints/BP_MyAICharacter.BP_MyAICharacter'"));
	if (AI_CHARACTER.Succeeded())
	{
		DefaultAI = AI_CHARACTER.Object;
	}
	*/
}

// Called when the game starts or when spawned
void AMonsterSpawner::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AMonsterSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

int AMonsterSpawner::GetPlayerStageAI()
{
	UEldenRingGameInstance* MyGI = GetGameInstance<UEldenRingGameInstance>();
	int nHowManyAI = 1;
		//MyGI->GetPlayerStage();

	return nHowManyAI;
}

int AMonsterSpawner::RandomTransform(int min, int max)
{
	std::random_device rd;
	std::mt19937_64 rEngine(rd());
	std::uniform_int_distribution<>dist(min, max);
	return static_cast<int>(dist(rEngine));
}

FVector AMonsterSpawner::GiveFVector()
{
	int nDestinationX, nDestinationY;
	nDestinationX = RandomTransform(-2400, 2400); // -2400 ~ 2400 (x) // 2400 ~ -2400 (y)
	nDestinationY = RandomTransform(-2400, 2400);

	return FVector(nDestinationX, nDestinationY, 0);
}

void AMonsterSpawner::SetMonsterOption(int nIndex)
{
	UEldenRingGameInstance* MyGI = GetGameInstance<UEldenRingGameInstance>();

	/*
	if (nIndex % 20 == 0)
	{
		MyGI->strSkeletalMesh = "Tank";
	}

	else if (nIndex % 10 == 0)
	{
		MyGI->strSkeletalMesh = "Speed";
	}

	else if (nIndex % 5 == 0)
	{
		MyGI->strSkeletalMesh = "Damage";
	}

	else
	{
		MyGI->strSkeletalMesh = "GeneralMonster";
	}
	*/
}

