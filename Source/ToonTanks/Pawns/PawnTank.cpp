// Fill out your copyright notice in the Description page of Project Settings.

#include "PawnTank.h"

APawnTank::APawnTank()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

void APawnTank::BeginPlay()
{
	Super::BeginPlay();
	PlayerController = Cast<APlayerController>(GetController());
}

void APawnTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Move();
	Turn();

	if (PlayerController != nullptr)
	{
		FHitResult HitResult;
		if (PlayerController->GetHitResultUnderCursor(ECC_Visibility, false, HitResult))
		{
			Rotate(HitResult.ImpactPoint);
		}
	}
}

void APawnTank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &APawnTank::ProcessMove);
	PlayerInputComponent->BindAxis("Turn", this, &APawnTank::ProcessTurn);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APawnTank::Fire);
}

void APawnTank::ProcessMove(float Value)
{
	float X = Value * MoveSpeed * GetWorld()->DeltaTimeSeconds;
	MoveDirection = FMath::Lerp(MoveDirection, FVector(X, 0.f, 0.f), Smoothing);

	// Update X Tilt
	FRotator TiltRotator;
	FRotator Rotator = BaseMeshComponent->GetRelativeRotation();

	if (Value > 0.1f)
	{
		TiltRotator = FRotator(MoveTiltAngle, 0.f, Rotator.Roll);
	}
	else if (Value < -0.1f)
	{
		TiltRotator = FRotator(-MoveTiltAngle, 0.f, Rotator.Roll);
	}
	else
	{
		TiltRotator = FRotator(0.f, 0.f, Rotator.Roll);
	}

	FQuat Rotation = FMath::Lerp(FQuat(Rotator), FQuat(TiltRotator), Smoothing);
	BaseMeshComponent->SetRelativeRotation(Rotation);
}

void APawnTank::ProcessTurn(float Value)
{
	// Flip value if moving backwards
	Value *= MoveDirection.X >= 0.f ? 1.f : -1.f;
	
	float Yaw = Value * RotateSpeed * GetWorld()->DeltaTimeSeconds;
	RotateDirection = FMath::Lerp(RotateDirection, FQuat(FRotator(0.f, Yaw, 0.f)), Smoothing);

	// Update Y Tilt
	FRotator TiltRotator;
	FRotator Rotator = BaseMeshComponent->GetRelativeRotation();

	if (Value > 0.1f)
	{
		TiltRotator = FRotator(Rotator.Pitch, RotateTiltAngle * 2.f, RotateTiltAngle);
	}
	else if (Value < -0.1f)
	{
		TiltRotator = FRotator(Rotator.Pitch, -RotateTiltAngle * 2.f, -RotateTiltAngle);
	}
	else
	{
		TiltRotator = FRotator(Rotator.Pitch, 0.f, 0.f);
	}

	FQuat Rotation = FMath::Lerp(FQuat(Rotator), FQuat(TiltRotator), Smoothing);
	BaseMeshComponent->SetRelativeRotation(Rotation);
}

void APawnTank::Move()
{
	AddActorLocalOffset(MoveDirection, true);
}

void APawnTank::Turn()
{
	AddActorLocalRotation(RotateDirection, true);
}

void APawnTank::Destruct()
{
	Super::Destruct();
	// Hide
}
