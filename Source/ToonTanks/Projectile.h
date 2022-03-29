// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"
class USoundBase;


UCLASS()
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()

	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	
	UPROPERTY(EditDefaultsOnly,Category="Components")
	UStaticMeshComponent *ProjectileMesh={nullptr};
	
	UPROPERTY(VisibleAnywhere,Category="Movment")
	class UProjectileMovementComponent *ProjectileMovment={nullptr};
	
	UFUNCTION()
	void OnHit(UPrimitiveComponent *HitComp,AActor*OtherActor,UPrimitiveComponent* OtherComp,FVector NormalImpulse,const FHitResult&Hit);

	UPROPERTY(EditAnywhere)
	float Damage=30.f;

	UPROPERTY(EditAnywhere,Category="Combat")
	class UParticleSystem* HitParticles={nullptr};

	UPROPERTY(EditAnywhere,Category="Combat")
	class UParticleSystemComponent *SmokeTrailParticle={nullptr};

	UPROPERTY(EditAnywhere,Category="Combat")
	USoundBase *LaunchSound={nullptr};

	UPROPERTY(EditAnywhere,Category="Combat")
	 USoundBase *HitSound={nullptr};

	UPROPERTY(EditAnywhere,Category="Combat")
	TSubclassOf<class UCameraShakeBase> HitCameraShakeClass;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
