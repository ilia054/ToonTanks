// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TooTanksGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATooTanksGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	void ActorDied(AActor *DeadActor);

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();

	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool bWonGame);

private:
	class ATank* Tank={nullptr};
	class AToonTanksPlayerController *ToonTanksPlayerController={nullptr};
	float StartDelay=4.f;
	int32 TargetTowerCnt=0.f;
	void HandleGameStart();
	int32 GetTargetTowerCnt();
	UPROPERTY(EditAnywhere,meta=(AlowPrivateAccess="true"))
	TSubclassOf<AActor> SpawnBoss;
	bool BossSpawned=false;

	
};
