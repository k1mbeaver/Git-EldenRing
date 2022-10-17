// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "PlayerDoor.generated.h"

/**
 * 
 */
UCLASS()
class ELDENRING_API APlayerDoor : public ATriggerBox
{
	GENERATED_BODY()

		UFUNCTION(BlueprintCallable)
		void CastToPlayer(AActor* OtherActor);
};
