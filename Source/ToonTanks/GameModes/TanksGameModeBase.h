// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTanks/Pawns/PawnTank.h"
#include "TanksGameModeBase.generated.h"

UCLASS()
class TOONTANKS_API ATanksGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ATanksGameModeBase();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game Loop")
	int32 StartDelay = 3;

	void ActorDestroyed(AActor* Actor);

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void GameStart();

	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool IsVictory);

private:
	APawnTank* Player;
	int32 TargetTurrets = 0;

	void HandleGameStart();
	void HandleGameOver(bool IsVictory);
	int32 GetTargetsCount() const;
};
