// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerDoor.h"
#include "PlayerCharacter.h"

void APlayerDoor::CastToPlayer(AActor* OtherActor)
{
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(OtherActor);

	PlayerCharacter->GameClear();
}