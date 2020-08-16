// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileBase.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AProjectileBase::AProjectileBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	RootComponent = ProjectileMesh;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	ProjectileMovementComponent->InitialSpeed = MovementSpeed;
	ProjectileMovementComponent->MaxSpeed = MovementSpeed;

	TrailParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Trail Particle System"));
	TrailParticleSystem->SetupAttachment(RootComponent);

	InitialLifeSpan = LifeSpan;
}

// Called when the game starts or when spawned
void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();

	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectileBase::OnHit);
	SetLifeSpan(LifeSpan);

	if (LaunchSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, LaunchSound, GetActorLocation());
	}
}

void AProjectileBase::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	AActor* ActorOwner = GetOwner();
	
	if (ActorOwner == nullptr)
	{
		return;
	}

	if (OtherActor != nullptr && OtherActor != this && OtherActor != ActorOwner)
	{
		UGameplayStatics::ApplyDamage(OtherActor, Damage, ActorOwner->GetInstigatorController(), this, DamageType);
	}

	if (HitParticles != nullptr)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, HitParticles, GetActorLocation());
	}

	if (HitSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());
	}
	
	Destroy();
}
