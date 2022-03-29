//@ilia054@

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()
public:
	ATank();
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent);
	//Called When Actor dies
	void HandleDestruction();
	APlayerController* GetTankPlayerController() const{return TankPlayerController;};

	bool IsAlive=true;
	


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;


private:
	
	UPROPERTY(VisibleAnywhere,Category="Components")
	class USpringArmComponent *SpringArm={nullptr};
	
	UPROPERTY(VisibleAnywhere,Category="Components")
	class UCameraComponent *Camera={nullptr};

	UPROPERTY(EditAnyWhere,Category="Movment");
	float Speed=200.f;
	
	UPROPERTY(EditAnyWhere,Category="Movment");
	float TurnRate=100.f;

	void Move(float Value);
	void Turn(float Value);

	APlayerController *TankPlayerController={nullptr};

};
