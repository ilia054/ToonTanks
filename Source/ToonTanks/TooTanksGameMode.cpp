// Fill out your copyright notice in the Description page of Project Settings.


#include "TooTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"
#include "ToonTanksPlayerController.h"
#include "TimerManager.h"

void ATooTanksGameMode::BeginPlay()
{
    Super::BeginPlay();
    HandleGameStart();

}
void ATooTanksGameMode::HandleGameStart()
{
    TargetTowerCnt=GetTargetTowerCnt();

    Tank=Cast<ATank>(UGameplayStatics::GetPlayerPawn(this,0));
    ToonTanksPlayerController=Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this,0));

    StartGame();
    //set up delay at start
    if(ToonTanksPlayerController)
    {
        ToonTanksPlayerController->SetPlayerEnableState(false);

        FTimerHandle PlayerEnableTimerHandle;

        FTimerDelegate TimerDelegate=FTimerDelegate::CreateUObject(
            ToonTanksPlayerController,
            &AToonTanksPlayerController::SetPlayerEnableState
            ,true);

        GetWorldTimerManager().SetTimer(
            PlayerEnableTimerHandle,
            TimerDelegate,
            StartDelay,
            false);   
    }
    

}
void ATooTanksGameMode::ActorDied(AActor *DeadActor)
{

    if(DeadActor==Tank)
    {
        Tank->HandleDestruction();
        if(ToonTanksPlayerController)
            ToonTanksPlayerController->SetPlayerEnableState(false);
        GameOver(false);
    }
    else if(ATower* DestroyedTower=Cast<ATower>(DeadActor))
    {
        UE_LOG(LogTemp,Error,TEXT("%s has died"),*DeadActor->GetName());
        DestroyedTower->HandleDestruction();
        //if Boss is dead
        if(BossSpawned)
        {
        GameOver(true); 
            return;
        }
        //all towers destroyed
        --TargetTowerCnt;
        if(TargetTowerCnt==0)
        {   
            //spawing boss
            if(SpawnBoss)
            {
            FVector vec={-50.f,50.f,210.f};
            FRotator rot=FRotator::ZeroRotator;
            GetWorld()->SpawnActor<AActor>(SpawnBoss,vec,rot);
            BossSpawned=true;
            }
            
        }
    }


}


int32 ATooTanksGameMode::GetTargetTowerCnt()
{
    TArray<AActor*> Towers;
    UGameplayStatics::GetAllActorsOfClass(
        this,
        ATower::StaticClass(),
        Towers
    );
    return Towers.Num();
}

