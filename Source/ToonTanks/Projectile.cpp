//@ilia054@


#include "Projectile.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/DamageType.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	ProjectileMesh=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	RootComponent=ProjectileMesh;

	//Projectile speed
	ProjectileMovment=CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movment Component"));
	ProjectileMovment->InitialSpeed=1300.f;
	ProjectileMovment->MaxSpeed=1300.f;
	
	SmokeTrailParticle=CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Smoke Trail"));
	SmokeTrailParticle->SetupAttachment(RootComponent);


}
// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	ProjectileMesh->OnComponentHit.AddDynamic(this,&AProjectile::OnHit);
	if(LaunchSound)
		UGameplayStatics::PlaySoundAtLocation(this,LaunchSound,GetActorLocation(),0.5f);
	
}
// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
//Called when actor is hit by projectile
void AProjectile::OnHit(UPrimitiveComponent *HitComp,AActor*OtherActor,UPrimitiveComponent* OtherComp,FVector NormalImpulse,const FHitResult&Hit)
{
	auto MyOwner=GetOwner();
	if(MyOwner==nullptr)
	{	Destroy();
		return;
	}

	auto MyOwnerInstigator=MyOwner->GetInstigatorController();
	auto DamgeTypeClass=UDamageType::StaticClass();
	if(OtherActor && OtherActor!=this && OtherActor!=MyOwner)
	{
		UGameplayStatics::ApplyDamage(OtherActor,Damage,MyOwnerInstigator,this,DamgeTypeClass);
		//Add projectile on hit
		if(HitParticles)
		UGameplayStatics::SpawnEmitterAtLocation(this,HitParticles,GetActorLocation(),GetActorRotation());
		//Play sound if hit
		if(HitSound)
			UGameplayStatics::PlaySoundAtLocation(this,HitSound,GetActorLocation(),0.5f);
		if(HitCameraShakeClass)
			GetWorld()->GetFirstPlayerController()->ClientPlayCameraShake(HitCameraShakeClass);
	}
	Destroy();

}

