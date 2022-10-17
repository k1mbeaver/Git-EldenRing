// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterItem.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "EldenRingGameInstance.h"
#include "PlayerCharacter.h"

// Sets default values
AMonsterItem::AMonsterItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	Mesh->SetupAttachment(CollisionBox);
}

// Called when the game starts or when spawned
void AMonsterItem::BeginPlay()
{
	Super::BeginPlay();

	//CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AMonsterItem::ItemBeginOverlap);
}

/*
void AMonsterItem::ItemBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerCharacter* myPlayer = Cast<APlayerCharacter>(OverlappedComponent);

	myPlayer->GetItem(ItemName);

	this->Destroy();
}
*/

void AMonsterItem::ItemBeginOverlap(AActor* OverlapActor)
{
	APlayerCharacter* myPlayer = Cast<APlayerCharacter>(OverlapActor);

	myPlayer->GetItem(ItemName);

	this->Destroy();
}

// Called every frame
void AMonsterItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

