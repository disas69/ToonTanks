// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "TanksGameModeBase.h"
#include "ToonTanks/Pawns/PawnTurret.h"

ATanksGameModeBase::ATanksGameModeBase()
{
}

void ATanksGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	Player = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
	TargetTurrets = GetTargetsCount();

	HandleGameStart();
}

void ATanksGameModeBase::ActorDestroyed(AActor* Actor)
{
	if (Actor == Player)
	{
		Player->Destruct();
		HandleGameOver(false);
	}
	else
	{
		APawnTurret* Turret = Cast<APawnTurret>(Actor);
		if (Turret != nullptr)
		{
			Turret->Destruct();

			if (--TargetTurrets <= 0)
			{
				HandleGameOver(true);
			}
		}
	}
}

void ATanksGameModeBase::HandleGameStart()
{
	GameStart();
}

void ATanksGameModeBase::HandleGameOver(bool IsVictory)
{
	GameOver(IsVictory);
}

int32 ATanksGameModeBase::GetTargetsCount() const
{
	TArray<AActor*> Turrets;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APawnTurret::StaticClass(), Turrets);

	return Turrets.Num();
}
