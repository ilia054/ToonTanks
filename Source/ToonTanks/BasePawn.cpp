//@ilia054@


#include "BasePawn.h"
#include "Projectile.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp=CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent=CapsuleComp;
	BaseMesh=CreateAbstractDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(CapsuleComp);

	TurretMesh=CreateAbstractDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint=CreateAbstractDefaultSubobject<USceneComponent>(TEXT("Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);
}
void ABasePawn::HandleDestruction()
{

	//TODO:Visual/Sound effects
	if(DeathParticles)
		UGameplayStatics::SpawnEmitterAtLocation(this,DeathParticles,GetActorLocation(),GetActorRotation());
	if(DeathSound)
		UGameplayStatics::PlaySoundAtLocation(this,DeathSound,GetActorLocation(),1.0f);
	if(DeathCameraShakeClass)
		GetWorld()->GetFirstPlayerController()->ClientPlayCameraShake(DeathCameraShakeClass);
	

}
//Rotate the tower head
void ABasePawn::RotateTurret(FVector LookAtTarget)
{
	FVector ToTarget=LookAtTarget-TurretMesh->GetComponentLocation();
	FRotator LookAtRotation=FRotator(0.f,ToTarget.Rotation().Yaw,0.f);
	TurretMesh->SetWorldRotation(LookAtRotation);
}

void ABasePawn::Fire()
{
	FVector Location=ProjectileSpawnPoint->GetComponentLocation();
	FRotator Rotaion=ProjectileSpawnPoint->GetComponentRotation();
	auto Projectile=GetWorld()->SpawnActor<AProjectile>(ProjectileClass,Location,Rotaion);
	Projectile->SetOwner(this);
}

