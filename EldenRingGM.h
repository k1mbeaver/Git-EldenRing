// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EldenRingGM.generated.h"

/**
 * 
 */
UCLASS()
class ELDENRING_API AEldenRingGM : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AEldenRingGM();
	virtual void PostLogin(APlayerController* NewPlayer) override; // �� �������� �÷��̾� ������ ����ȴ�.
};
