// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ToonTanks/Pawns/PawnBase.h"
#include "PawnTurret.generated.h"

UCLASS()
class TOONTANKS_API APawnTurret : public APawnBase
{
	GENERATED_BODY()

public:
	APawnTurret();

	FTimerHandle FireRateTimer;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float FireRate = 2.f;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void CheckFireCondition();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
};
