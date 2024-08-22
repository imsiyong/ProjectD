// Fill out your copyright notice in the Description page of Project Settings.


#include "PDMonster1AIController.h"
#include <Kismet/GameplayStatics.h>
#include "PDMonster1.h"
#include "PDMonster1Instance.h"

#define ERROR 50.f
#define BOUNDARY 1000.f

APDMonster1AIController::APDMonster1AIController()
{
	Init();
}

void APDMonster1AIController::Init()
{
	if (PlayerPawn == nullptr)
	{
		PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	}
	if (MonsterPawn == nullptr)
	{
		MonsterPawn = Cast<APDMonster1>(GetPawn());
	}
	MonsterActionState = ENormalMonsterActionState::Spawn;
	DestIndex = 0;
}

void APDMonster1AIController::SetPoint(FVector spawnPoint, TArray<FVector> destination)
{
	SpawnPoint = spawnPoint;
	Destination = destination;
}


void APDMonster1AIController::BeginPlay()
{
	Super::BeginPlay();
	Init();
}

void APDMonster1AIController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void APDMonster1AIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (PlayerPawn && MonsterPawn && MonsterPawn->MonsterBasicState == EMonsterBasicState::LIVE)
	{
		FSMState();
	}
	
}

bool APDMonster1AIController::EqualFloatNearby(float actorDest, float dest)
{
	float error = ERROR;
	if (FMath::Abs(actorDest - dest) < error)
		return true;
	else
		return false;
}

bool APDMonster1AIController::EqualActorXYNearby(AActor* actor, FVector dest)
{
	float error = ERROR;
	float Xgap = FMath::Abs(actor->GetActorLocation().X - dest.X);
	float Ygap = FMath::Abs(actor->GetActorLocation().Y - dest.Y);
	if (Xgap < error && Ygap < error)return true;
	else return false;
}

bool APDMonster1AIController::IsOutOfBound()
{
	float Distance = FVector::Dist(PlayerPawn->GetActorLocation(), SpawnPoint);
	if (Distance < BOUNDARY)
		return false;
	else
		return true;
}

void APDMonster1AIController::FSMState()
{
	switch (MonsterActionState)
	{
	case ENormalMonsterActionState::Spawn:
		ActorSpawn();
		break;
	case ENormalMonsterActionState::Patrol:
		Patrol();
		break;
	case ENormalMonsterActionState::Tracking:
		Tracking();
		break;
	case ENormalMonsterActionState::Attack:
		Attack();
		break;
	default:
		break;
	}
}

void APDMonster1AIController::ActorSpawn()
{
	UE_LOG(LogTemp, Log, TEXT("ActorSpawn~"));
	MoveToLocation(SpawnPoint);
	if (EqualActorXYNearby(MonsterPawn, SpawnPoint))
	{
		MonsterActionState = ENormalMonsterActionState::Patrol;
		return;
	}
}

void APDMonster1AIController::Patrol()
{
	UE_LOG(LogTemp, Log, TEXT("Patrol~: Num : %d"), Destination.Num());
	float Distance = FVector::Dist(MonsterPawn->GetActorLocation(), PlayerPawn->GetActorLocation());
	if (Distance < MonsterPawn->Stat->SightRange)
	{
		MonsterActionState = ENormalMonsterActionState::Tracking;
		return;
	}
	MoveToLocation(Destination[DestIndex]);
	
	if (EqualActorXYNearby(MonsterPawn, Destination[DestIndex]))
	{
		UE_LOG(LogTemp, Log, TEXT("Patrol~: Num : %d"), DestIndex);
		DestIndex = (DestIndex + 1) % Destination.Num();
	}
}

void APDMonster1AIController::Tracking()
{
	UE_LOG(LogTemp, Log, TEXT("Tracking~"));
	MoveToActor(PlayerPawn);
	float Distance = FVector::Dist(MonsterPawn->GetActorLocation(), PlayerPawn->GetActorLocation());
	if (Distance > MonsterPawn->Stat->SightRange || IsOutOfBound())
	{
		MonsterActionState = ENormalMonsterActionState::Spawn;
		return;
	}
	if (Distance < MonsterPawn->Stat->AtkRange)
	{
		MonsterActionState = ENormalMonsterActionState::Attack;
		MonsterPawn->BasicAttackStart();
		return;
	}
}

void APDMonster1AIController::Attack()
{
	UE_LOG(LogTemp, Log, TEXT("Attack~"));
	if (!MonsterPawn->IsAttack)
	{
		MonsterActionState = ENormalMonsterActionState::Tracking;
	}
}
