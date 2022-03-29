//@ilia054@


#include "HealthComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "TooTanksGameMode.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth=MaxHealth;
	//Get the owner of the component 
	GetOwner()->OnTakeAnyDamage.AddDynamic(this,&UHealthComponent::DamgeTaken);
	TooTanksGameMode=Cast<ATooTanksGameMode>(UGameplayStatics::GetGameMode(this));

	
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
void UHealthComponent::DamgeTaken(AActor* DamgedActor,float Damage, const UDamageType* DamgeType,class AController* Instigator,AActor* DamageCauser)
{
	if(Damage<=0.f){return;}

	if(CurrentHealth-Damage<0)
		CurrentHealth=0;
	else
		CurrentHealth-=Damage;
	if(CurrentHealth==0.f && TooTanksGameMode)
	{
		TooTanksGameMode->ActorDied(DamgedActor);
	}

}

