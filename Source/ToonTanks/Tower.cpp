//@ilia054@


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

void ATower::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if(IsTankInRange())
        RotateTurret(Tank->GetActorLocation());

}
void ATower::HandleDestruction()
{
    Super::HandleDestruction();
    Destroy();
}

bool ATower::IsTankInRange()
{
    if(Tank)
    {
    float DistanceToTank=FVector::Dist(GetActorLocation(),Tank->GetActorLocation());
    return DistanceToTank<=FireRange;
    }
    return false;
}
void ATower::BeginPlay()
{
    Super::BeginPlay();
    //Getting tank
    Tank=Cast<ATank>(UGameplayStatics::GetPlayerPawn(this,0));

    //Setup Fire timer when tower spawns
    GetWorldTimerManager().SetTimer(FireRateTimerHandle,this,&ATower::CheckFireCondition,FireRate,true);
}
void ATower::CheckFireCondition()
{
    if(Tank==nullptr)
        return;
    if(IsTankInRange() && Tank->IsAlive)
        Fire();

}
