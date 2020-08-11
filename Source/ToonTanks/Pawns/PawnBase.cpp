// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/KismetMathLibrary.h"
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
	FVector TargetDirection = FVector(TargetLocation.X, TargetLocation.Y, GetActorLocation().Z) - GetActorLocation();
	FRotator CurrentRotation = FRotator(0.f, TurretMeshComponent->GetComponentRotation().Yaw, 0.f);
	FRotator TargetRotation = FRotator(0.f, TargetDirection.Rotation().Yaw, 0.f);

	TurretMeshComponent->SetWorldRotation(FMath::Lerp(CurrentRotation, TargetRotation, 0.1f));
	TurretMeshComponent->SetRelativeRotation(FRotator(0.f, TurretMeshComponent->GetRelativeRotation().Yaw, 0.f));
}

void APawnBase::Fire()
{
	if (ProjectileType != nullptr)
	{
		FVector SpawnLocation = ProjectileSpawnPoint->GetComponentLocation();
		FRotator SpawnRotator = ProjectileSpawnPoint->GetComponentRotation();
		
		AProjectileBase* Projectile = GetWorld()->SpawnActor<AProjectileBase>(ProjectileType, SpawnLocation, SpawnRotator);
		Projectile->SetOwner(this);
	}
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
