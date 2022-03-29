// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOONTANKS_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();


protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	UPROPERTY(EditAnyWhere,BlueprintReadWrite)
	float MaxHealth=100.f;
	UPROPERTY(EditAnyWhere,BlueprintReadWrite)
	float CurrentHealth=0.f;

private:
	UFUNCTION()	
	void DamgeTaken(AActor* DamgedActor,float Damge, const UDamageType* DamgeType,class AController* Instigator,AActor* DamageCauser);

	class ATooTanksGameMode* TooTanksGameMode;


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
