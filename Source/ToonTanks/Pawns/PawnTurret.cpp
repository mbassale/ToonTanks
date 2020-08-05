// Fill out your copyright notice in the Description page of Project Settings.


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

// Called every frame
void APawnTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APawnTurret::CheckFireCondition()
{
	if (!PlayerPawn)
	{
		return;
	}
	if (ReturnDistanceToPlayer() < FireRange)
	{
		UE_LOG(LogTemp, Warning, TEXT("Turret Firing!"));
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
