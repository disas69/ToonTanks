// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTurret.h"
#include "Kismet/GameplayStatics.h"

APawnTurret::APawnTurret()
{
}

void APawnTurret::BeginPlay()
{
	Super::BeginPlay();

	Tank = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
	GetWorld()->GetTimerManager().SetTimer(FireRateTimer, this, &APawnTurret::CheckFireCondition, FireRate, true);
}

bool APawnTurret::IsTargetInRange(AActor* Target)
{
	FVector TargetLocation = Target->GetActorLocation();
	if (FVector::Dist(TargetLocation, GetActorLocation()) <= FireRadius)
	{
		return true;
	}

	return false;
}

void APawnTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Tank != nullptr && IsTargetInRange(Tank))
	{
		Rotate(Tank->GetActorLocation());
	}
}

void APawnTurret::CheckFireCondition()
{
	if (Tank != nullptr)
	{
		FVector TankLocation = Tank->GetActorLocation();
		if (FVector::Dist(TankLocation, GetActorLocation()) <= FireRadius)
		{
			Fire();
		}
	}
}

void APawnTurret::Destruct()
{
	Super::Destruct();
	Destroy();
}
