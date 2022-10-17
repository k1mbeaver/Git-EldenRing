// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryItemData.h"

// Sets default values
AInventoryItemData::AInventoryItemData()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AInventoryItemData::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInventoryItemData::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

