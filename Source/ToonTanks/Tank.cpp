//@ilia054@



#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"
//set deafult values
ATank::ATank()
{
    SpringArm=CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    SpringArm->SetupAttachment(RootComponent);
    Camera=CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm);
    
}
void ATank::SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    PlayerInputComponent->BindAxis(TEXT("MoveForward"),this,&ATank::Move);
    PlayerInputComponent->BindAxis(TEXT("Turn"),this,&ATank::Turn);
    
    //Bind Fire action to tank
    PlayerInputComponent->BindAction(TEXT("Fire"),IE_Pressed,this,&ATank::Fire);
    
}

void ATank::BeginPlay()
{
    Super::BeginPlay();
    //APlayerController is a subclass of AController
    TankPlayerController=Cast<APlayerController>(GetController());
}
// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    if(TankPlayerController)
    {
    FHitResult HitResult;
    TankPlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility,false,HitResult);
    RotateTurret(HitResult.ImpactPoint);
    }

}
void ATank::HandleDestruction()
{
    Super::HandleDestruction();
    //Hiding tank insted of destroying
    SetActorHiddenInGame(true);
    SetActorTickEnabled(false);
    IsAlive=false;
    
}
void ATank::Move(float Value)
{
    FVector DeltaLocation=FVector::ZeroVector;
    // X= Valu *DeltaTime *Speed 
    DeltaLocation.X=Value*Speed*UGameplayStatics::GetWorldDeltaSeconds(this);

    AddActorLocalOffset(DeltaLocation,true);
}
void ATank::Turn(float Value)
{
    FRotator DeltaRotation=FRotator::ZeroRotator;
    //Yaw=Value*DeltaTime*TurnRate
    DeltaRotation.Yaw=Value*TurnRate*UGameplayStatics::GetWorldDeltaSeconds(this);

    AddActorLocalRotation(DeltaRotation,true);

}



