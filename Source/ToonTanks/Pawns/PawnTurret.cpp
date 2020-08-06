// Copyright 2020. Marco Bassaletti.


#include "PawnTurret.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "PawnTank.h"

APawnTurret::APawnTurret()
{
	
}

void APawnTurret::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &APawnTurret::CheckFireCondition, FireRate, true);

	PlayerPawn = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
}

void APawnTurret::HandleDestruction()
{
	Super::HandleDestruction();
	Destroy();
}

// Called every frame
void APawnTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!PlayerPawn || ReturnDistanceToPlayer() > FireRange)
	{
		return;
	}
	RotateTurret(PlayerPawn->GetActorLocation());
}

void APawnTurret::CheckFireCondition()
{
	if (!PlayerPawn)
	{
		return;
	}
	if (ReturnDistanceToPlayer() < FireRange)
	{
		Fire();
	}
}

float APawnTurret::ReturnDistanceToPlayer()
{
	if (!PlayerPawn)
	{
		return FLT_MAX;
	}

	return FVector::Dist(PlayerPawn->GetActorLocation(), this->GetActorLocation());
}