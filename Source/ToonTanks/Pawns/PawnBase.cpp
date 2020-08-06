// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnBase.h"

// Sets default values
APawnBase::APawnBase()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComponent;

	BaseMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMeshComponent->SetupAttachment(RootComponent);

	TurretMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMeshComponent->SetupAttachment(BaseMeshComponent);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurretMeshComponent);
}

// Called when the game starts or when spawned
void APawnBase::BeginPlay()
{
	Super::BeginPlay();
}

void APawnBase::Rotate(FVector TargetLocation)
{
	FQuat CurrentRotation = FQuat(TurretMeshComponent->GetComponentRotation());
	FVector TargetDirection = FVector(TargetLocation.X, TargetLocation.Y, TurretMeshComponent->GetComponentLocation().Z) - TurretMeshComponent->GetComponentLocation();
	FQuat TargetRotation = FQuat(TargetDirection.Rotation());

	TurretMeshComponent->SetWorldRotation(FMath::Lerp(CurrentRotation, TargetRotation, 0.1f));
}

void APawnBase::Fire()
{
}

void APawnBase::Destruct()
{
}

// Called every frame
void APawnBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APawnBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
