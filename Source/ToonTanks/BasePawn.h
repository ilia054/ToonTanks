//@ilia054@

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"



UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{

	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();
	void HandleDestruction();

protected:
	void RotateTurret(FVector LookAtTarget);
	void Fire();


private:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Components", meta=(AllowPrivateAccess="true"))
	class UCapsuleComponent *CapsuleComp={nullptr};

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Components", meta=(AllowPrivateAccess="true"))
	UStaticMeshComponent *BaseMesh={nullptr};

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Components", meta=(AllowPrivateAccess="true"))
	UStaticMeshComponent *TurretMesh={nullptr};

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Components", meta=(AllowPrivateAccess="true"))
	USceneComponent *ProjectileSpawnPoint={nullptr};

	//Projectile spawning
	UPROPERTY(EditDefaultsOnly,Category= "Combat")
	TSubclassOf<class AProjectile> ProjectileClass;

	///Death Particle Spawn
	UPROPERTY(EditAnywhere,Category="Combat")
	class UParticleSystem* DeathParticles={nullptr};

	UPROPERTY(EditAnywhere,Category="Combat")
	class USoundBase* DeathSound={nullptr};

	UPROPERTY(EditAnywhere,Category="Combat")
	TSubclassOf<class UCameraShakeBase> DeathCameraShakeClass;

};
