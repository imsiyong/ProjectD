// Fill out your copyright notice in the Description page of Project Settings.


#include "PDMonsterAIController.h"
#include <Kismet/GameplayStatics.h>
#include "PDMonsterSample.h"
#include "PDMonsterInstance.h"
#include "Monster/PDMonster1.h"
#include "Monster/PDMonster1Instance.h"

APDMonsterAIController::APDMonsterAIController()
{
}

void APDMonsterAIController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
}

void APDMonsterAIController::BeginPlay()
{
	Super::BeginPlay();
	Init();
}

void APDMonsterAIController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void APDMonsterAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (MonsterPawn && MonsterPawn->BasicState == EMonsterBasicState::LIVE)
	{
		FSMState();
	}
}

void APDMonsterAIController::Init()
{
	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	MonsterPawn = Cast<APDMonsterSample>(GetPawn());
	MonsterActionState = EMonsterActionState::SetDest;
	Destination = FVector(FMath::RandRange(-980.f, 870.f), FMath::RandRange(100.f, 1400.f), 0);
}
bool APDMonsterAIController::EqualFloatNearby(float actorDest, float dest)
{
	float error=50.0f;
	if (FMath::Abs(actorDest - dest) < error)
		return true;
	else
		return false;
}

bool APDMonsterAIController::EqualActorXYNearby(AActor* actor, FVector dest)
{
	float error = 50.0f;
	float Xgap = FMath::Abs(actor->GetActorLocation().X - dest.X);
	float Ygap = FMath::Abs(actor->GetActorLocation().Y - dest.Y);
	if (Xgap < error && Ygap < error)return true;
	else return false;
}

void APDMonsterAIController::FSMState()
{
	switch (MonsterActionState)
	{
	case EMonsterActionState::SetDest:
		SetDest();
		break;
	case EMonsterActionState::MoveToDest:
		MoveToDest();
		break;
	case EMonsterActionState::CheckDist:
		CheckDist();
		break;
	case EMonsterActionState::CheckField:
		CheckField();
		break;
	case EMonsterActionState::MoveToCenter:
		MoveToCenter();
		break;
	case EMonsterActionState::Attack:
		Attack();
		break;
	default:
		break;
	}
}

void APDMonsterAIController::SetDest()
{
	Destination = FVector(FMath::RandRange(-980.f, 870.f), FMath::RandRange(100.f, 1400.f), 0);
	MonsterActionState = EMonsterActionState::MoveToDest;
}

void APDMonsterAIController::MoveToDest()
{
	MoveToLocation(Destination);
	if (EqualActorXYNearby(MonsterPawn, Destination))
	{
		MonsterActionState = EMonsterActionState::SetDest;
	}
	else
	{
		MonsterPawn->SprintStart();
		MonsterActionState = EMonsterActionState::CheckDist;
	}
}

void APDMonsterAIController::CheckDist()
{
	float Distance = FVector::Distance(MonsterPawn->GetActorLocation(), PlayerPawn->GetActorLocation());
	if (Distance < MonsterPawn->Stat->SightRange)
	{
		if (Distance < MonsterPawn->Stat->AtkRange)
		{
			MonsterPawn->AttackStart();
			MonsterActionState = EMonsterActionState::Attack;
		}
		else
		{
			MoveToActor(PlayerPawn);
			MonsterActionState = EMonsterActionState::CheckField;
		}
	}
	else
	{
		MonsterPawn->SprintStop();
		MonsterActionState = EMonsterActionState::MoveToDest;
	}
}

void APDMonsterAIController::Attack()
{
	if(!MonsterPawn->IsAttack)
	{
		MonsterActionState = EMonsterActionState::CheckDist;
	}
}

void APDMonsterAIController::CheckField()
{
	if (MonsterPawn->GetActorLocation().X < -980.f || MonsterPawn->GetActorLocation().X > 870.f
		|| MonsterPawn->GetActorLocation().Y < 100.f || MonsterPawn->GetActorLocation().Y>1400.f)
	{
		MonsterActionState = EMonsterActionState::MoveToCenter;
	}
	else
	{
		MonsterActionState = EMonsterActionState::CheckDist;
	}
}

void APDMonsterAIController::MoveToCenter()
{
	Destination = FVector(-400.f, 1100.f, 0.f);
	MoveToLocation(Destination);
	if (EqualActorXYNearby(MonsterPawn, Destination))
	{
		MonsterPawn->SprintStop();
		MonsterActionState = EMonsterActionState::SetDest;
	}
}