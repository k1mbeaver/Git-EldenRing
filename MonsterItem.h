// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MonsterItem.generated.h"

UCLASS()
class ELDENRING_API AMonsterItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMonsterItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//class UUISurvivorState* SurvivorStateWidget;
	//class UInventory* Inventory;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//void ItemBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION(BlueprintCallable)
		void ItemBeginOverlap(AActor* OverlapActor);

	UPROPERTY(Category = Mesh, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* Mesh;

	UPROPERTY(Category = Collision, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* CollisionBox;

	FString ItemName;

};
