// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ToonTanks/Pawns/PawnTank.h"
#include "ToonTanks/Pawns/PawnBase.h"
#include "PawnTurret.generated.h"

UCLASS()
class TOONTANKS_API APawnTurret : public APawnBase
{
	GENERATED_BODY()

public:
	APawnTurret();

	FTimerHandle FireRateTimer;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void CheckFireCondition();
	virtual void Destruct() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	APawnTank* Tank;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float FireRate = 2.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float FireRadius = 500.f;

	bool IsTargetInRange(AActor* Target);
};
