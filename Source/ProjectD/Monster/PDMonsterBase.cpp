// Fill out your copyright notice in the Description page of Project Settings.


#include "PDMonsterBase.h"
#include "../PDDataSet.h"
#include "Components/CapsuleComponent.h"

// Sets default values
APDMonsterBase::APDMonsterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MonsterCode = -1;
	MonsterBasicState = EMonsterBasicState::LIVE;
	MonsterGrade = EMonsterGrade::None;
	IsAttack =false;
	DeathDuration = 5.0f;
	SprintMultiplier=2.0f;

	Tags.Add(FName("Monster"));
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("PDCharacter"));
}

// Called when the game starts or when spawned
void APDMonsterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APDMonsterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APDMonsterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APDMonsterBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

float APDMonsterBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Stat->CurHp -= DamageAmount;
	if (Stat->CurHp <= 0.0f)
	{
		UE_LOG(LogTemp, Log, TEXT("Monster is dead CurHp: %f"), Stat->CurHp);
		DeathStart();
		return 0.0f;
	}
	UE_LOG(LogTemp, Log, TEXT("Monster Sample code[%d] CurHp : %f"), Stat->ActorCode, Stat->CurHp);
	return 0.0f;
}

void APDMonsterBase::DeathStart()
{
}

void APDMonsterBase::DeathEnd()
{
}

