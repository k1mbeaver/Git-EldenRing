// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "EldenringGameInstance.h"
#include "PlayerCharacter.h"

// Sets default values
AMonsterProjectile::AMonsterProjectile()
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(250.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &AMonsterProjectile::OnHit);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.0f;
	ProjectileMovement->MaxSpeed = 3000.0f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;

	// Die after 2 seconds by default
	InitialLifeSpan = 2.0f;

	AttackPower = 200.0f;
}

void AMonsterProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	//UEldenRingGameInstance* MyGI = GetGameInstance<UEldenRingGameInstance>();
	//FString GunName = MyGI->GetPlayerGun();

	//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("PlayerHitSkill!")); // 몬스터의 스킬을 플레이어가 맞았나 안맞았나?

	//if (Cast<APlayerCharacter>(Hit.Actor)) // 맞은 대상이 몬스터일 때
	if (Cast<APlayerCharacter>(OtherActor)) // 맞은 대상이 몬스터일 때
	{
		APlayerCharacter* HitCharacter = Cast<APlayerCharacter>(Hit.Actor);

		HitCharacter->AttackedProjectTile(AttackPower);
		//GameStatic->SpawnEmitterAtLocation(GetWorld(), BloodParticle, Hit.ImpactPoint);

		Destroy();
	}

	else
	{
		//GameStatic->SpawnEmitterAtLocation(GetWorld(), GroundParticle, Hit.ImpactPoint);
		Destroy();
	}
	/*
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && OtherComp->IsSimulatingPhysics())
	{
		//OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());

		Destroy();
	}
	*/
}


