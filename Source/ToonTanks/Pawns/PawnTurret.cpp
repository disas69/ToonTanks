// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTurret.h"
#include "Kismet/GameplayStatics.h"

APawnTurret::APawnTurret()
{
}

void APawnTurret::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(FireRateTimer, this, &APawnTurret::CheckFireCondition, FireRate, true);
}

void APawnTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APawnTurret::CheckFireCondition()
{
	UE_LOG(LogTemp, Warning, TEXT("Fire!"));
}
