// Fill out your copyright notice in the Description page of Project Settings.

#include "TanksGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanks/Pawns/PawnTurret.h"

ATanksGameModeBase::ATanksGameModeBase()
{
}

void ATanksGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	Player = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
	PlayerController = Cast<APlayerControllerBase>(UGameplayStatics::GetPlayerController(this, 0));
	TargetTurrets = GetTargetsCount();

	HandleGameStart();
}

void ATanksGameModeBase::ActorDestroyed(AActor* Actor)
{
	if (Actor == Player)
	{
		Player->Destruct();

		if (PlayerController != nullptr)
		{
			PlayerController->SetEnabled(false);
		}
		
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

	if (PlayerController != nullptr)
	{
		PlayerController->SetEnabled(false);

		FTimerHandle PlayerEnableHandle;
		FTimerDelegate PlayerEnableDelegate = FTimerDelegate::CreateUObject(PlayerController, &APlayerControllerBase::SetEnabled, true);

		GetWorld()->GetTimerManager().SetTimer(PlayerEnableHandle, PlayerEnableDelegate, StartDelay, false);
	}
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
