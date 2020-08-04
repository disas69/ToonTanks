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
}

void APawnTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Rotate();
	Move();
}

void APawnTank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &APawnTank::ProcessMove);
	PlayerInputComponent->BindAxis("Turn", this, &APawnTank::ProcessRotate);
}

void APawnTank::ProcessMove(float Value)
{
	float X = Value * MoveSpeed * GetWorld()->DeltaTimeSeconds;
	MoveDirection = FMath::Lerp(MoveDirection, FVector(X, 0.f, 0.f), Smoothing);
}

void APawnTank::ProcessRotate(float Value)
{
	float Yaw = Value * RotateSpeed * GetWorld()->DeltaTimeSeconds;
	RotateDirection = FMath::Lerp(RotateDirection, FQuat(FRotator(0.f, Yaw, 0.f)), Smoothing);
}

void APawnTank::Move()
{
	AddActorLocalOffset(MoveDirection, true);
}

void APawnTank::Rotate()
{
	AddActorLocalRotation(RotateDirection, true);
}
