// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MonsterCharacter.h"
#include "MonsterProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS(config = Game)
class ELDENRING_API AMonsterProjectile : public AActor
{
	GENERATED_BODY()

	/** Square collision component */
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
		USphereComponent* CollisionComp;

	/** Projectile movement component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
		UProjectileMovementComponent* ProjectileMovement;
	
public:	
	// Sets default values for this actor's properties
	AMonsterProjectile();

	/** called when projectile hits something */
	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	/** Returns CollisionComp subobject **/
	USphereComponent* GetCollisionComp() const { return CollisionComp; }
	/** Returns ProjectileMovement subobject **/
	UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		float AttackPower;

	UPROPERTY()
		class UGameplayStatics* GameStatic;
};
