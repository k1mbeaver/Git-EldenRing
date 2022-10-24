// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

AMyPlayerController::AMyPlayerController()
{

}

void AMyPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);
	if (aPawn)
	{
		myCharacter = Cast<APlayerCharacter>(aPawn);
		//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("Success!"));
		SetInputMode(FInputModeGameOnly());
	}
}

void AMyPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("Possess!"));
}

void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	//AABCharacter* myCharacter = Cast<AABCharacter>(myPawn);

	// ĳ���� �̵� �Լ�
	InputComponent->BindAxis(TEXT("MoveForward"), this, &AMyPlayerController::UpDown);
	InputComponent->BindAxis(TEXT("MoveRight"), this, &AMyPlayerController::LeftRight);
	InputComponent->BindAxis(TEXT("LookUp"), this, &AMyPlayerController::LookUp);
	InputComponent->BindAxis(TEXT("Turn"), this, &AMyPlayerController::Turn);

	// ĳ���� ���� �Լ�
	InputComponent->BindAction("Jump", IE_Pressed, this, &AMyPlayerController::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &AMyPlayerController::StopJumping);

	// ĳ���� ���� �Լ�
	InputComponent->BindAction("Attack", IE_Pressed, this, &AMyPlayerController::Attack);

	// ĳ���� �޸��� �Լ�
	InputComponent->BindAction("Run", IE_Pressed, this, &AMyPlayerController::Run);
	InputComponent->BindAction("Run", IE_Released, this, &AMyPlayerController::StopRun);


	// ĳ���� ��ų �Լ�
	InputComponent->BindAction("Skill", IE_Pressed, this, &AMyPlayerController::Skill);
	InputComponent->BindAction("Skill", IE_Released, this, &AMyPlayerController::StopSkillIntro);

	// ĳ���� �����̵� �Լ�
	InputComponent->BindAction("TravelMode", IE_Pressed, this, &AMyPlayerController::TravelMode);

	// ĳ���� ������ ��� �Լ�
	InputComponent->BindAction("HPDrink", IE_Pressed, this, &AMyPlayerController::HpDrink);
	InputComponent->BindAction("MPDrink", IE_Pressed, this, &AMyPlayerController::MpDrink);
	InputComponent->BindAction("StaminaDrink", IE_Pressed, this, &AMyPlayerController::StaminaDrink);

	// ĳ���� �κ��丮 Ȯ�� �Լ�
	InputComponent->BindAction("Inventory", IE_Pressed, this, &AMyPlayerController::CheckInventory);

	// �÷��̾� �Ͻ����� �Լ�
	//InputComponent->BindAction("Pause", IE_Pressed, this, &AMyPlayerController::PlayerPause);
}

void AMyPlayerController::UpDown(float NewAxisValue)
{
	if (myCharacter)
	{
		myCharacter->UpDown(NewAxisValue);
		//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("UpDown!"));
	}
}

void AMyPlayerController::LeftRight(float NewAxisValue)
{
	if (myCharacter)
	{
		myCharacter->LeftRight(NewAxisValue);
		//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("LeftRight!"));
	}
}

void AMyPlayerController::LookUp(float NewAxisValue)
{
	if (myCharacter)
	{
		myCharacter->LookUp(NewAxisValue);
		//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("LookUp!"));
	}
}

void AMyPlayerController::Turn(float NewAxisValue)
{
	if (myCharacter)
	{
		myCharacter->Turn(NewAxisValue);
		//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("Turn!"));
	}
}

void AMyPlayerController::Jump()
{
	if (myCharacter != nullptr)
	{
		myCharacter->Jump();
		//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("Jump!"));
	}
}

void AMyPlayerController::Skill()
{
	if (myCharacter != nullptr)
	{
		myCharacter->Skill();
		//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("Jump!"));
	}
}


void AMyPlayerController::StopSkillIntro()
{
	if (myCharacter != nullptr)
	{
		myCharacter->StopSkillIntro();
		//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("Jump!"));
	}
}

void AMyPlayerController::TravelMode()
{
	if (myCharacter != nullptr)
	{
		myCharacter->TravelMode();
		//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("Jump!"));
	}
}

void AMyPlayerController::StopJumping()
{
	if (myCharacter != nullptr)
	{
		myCharacter->StopJumping();
		//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("StopJumping!"));
	}
}

void AMyPlayerController::Attack()
{
	if (myCharacter != nullptr)
	{
		myCharacter->Attack();
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("Attack!"));
	}
}

void AMyPlayerController::Run()
{
	if (myCharacter != nullptr)
	{
		myCharacter->Run();
		//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("Run!"));
	}
}

void AMyPlayerController::StopRun()
{
	if (myCharacter != nullptr)
	{
		myCharacter->StopRun();
		//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("StopRun!"));
	}
}

void AMyPlayerController::HpDrink()
{
	if (myCharacter != nullptr)
	{
		myCharacter->HpDrink();
		//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("StopRun!"));
	}
}

void AMyPlayerController::MpDrink()
{
	if (myCharacter != nullptr)
	{
		myCharacter->MpDrink();
		//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("StopRun!"));
	}
}

void AMyPlayerController::StaminaDrink()
{
	if (myCharacter != nullptr)
	{
		myCharacter->StaminaDrink();
		//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("StopRun!"));
	}
}

void AMyPlayerController::CheckInventory()
{
	if (myCharacter != nullptr)
	{
		myCharacter->CheckInventory();
		//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("StopRun!"));
	}
}

/*
void AMyPlayerController::PlayerPause()
{
	if (myCharacter != nullptr)
	{
		myCharacter->PlayerPause();
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("PlayerPause!"));
	}
}
*/