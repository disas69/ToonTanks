// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TanksGameModeBase.generated.h"

UCLASS()
class TOONTANKS_API ATanksGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ATanksGameModeBase();

	void ActorDestroyed(AActor* Actor);

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void GameStart();

	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool IsVictory);

private:
	void HandleGameStart();
	void HandleGameOver(bool IsVictory);
};
