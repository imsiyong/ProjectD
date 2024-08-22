// Fill out your copyright notice in the Description page of Project Settings.


#include "PDMonster1.h"
#include "PDMonster1Instance.h"
#include "PDMonster1AIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "../PDDataSet.h"
#include "../Manager/PDNormalMonsterManager.h"

APDMonster1::APDMonster1()
{
	MonsterGrade = EMonsterGrade::Normal;
	GetCharacterMovement()->MaxWalkSpeed = 200.f;

	ConstructorHelpers::FObjectFinder<USkeletalMesh> SM(TEXT("/Game/DownloadAsset/ImportAsset/Character/Monster1/Warrok_W_Kurniawan.Warrok_W_Kurniawan"));
	if (SM.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SM.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -88.f), FRotator(0.f, -90.f, 0.f));
	}
	ConstructorHelpers::FClassFinder<UPDMonster1Instance> MI(TEXT("AnimBlueprint'/Game/BluePrint/AnimInstance/Monster1/BPMonster1Instance.BPMonster1Instance_C'"));
	if (MI.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(MI.Class);
	}
	AIControllerClass = APDMonster1AIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void APDMonster1::Init()
{
	if(Monster1Instance==nullptr)
		Monster1Instance = Cast<UPDMonster1Instance>(GetMesh()->GetAnimInstance());
}

void APDMonster1::BeginPlay()
{
	Super::BeginPlay();
}

void APDMonster1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APDMonster1::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APDMonster1::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	Init();

	//Stat Initialize
	
	if (Monster1Instance)
	{
		Monster1Instance->OnAttackHit.AddUObject(this, &APDMonster1::AttackCheck);
		Monster1Instance->OnAttackEnd.AddUObject(this, &APDMonster1::AttackEnd);
	}
}

void APDMonster1::DeathStart()
{
	if (Monster1Instance)
	{
		Monster1Instance->StopAllMontages(0.0f);
		Monster1Instance->PlayDeathMontage();
	}
	MonsterBasicState = EMonsterBasicState::DEATH;
	GetCapsuleComponent()->SetCollisionProfileName("NoCollision");
	
	//Drop a Item
	WeaponDrop();

	//Monster Remove on MonsterManager
	UPDNormalMonsterManager::Get()->RemoveMonster(MonsterCode);

	//after 5seconds Actor destory
	FTimerHandle DeathTimeHandle;
	GetWorld()->GetTimerManager().SetTimer(DeathTimeHandle, FTimerDelegate::CreateLambda([&]()
		{
			Destroy();
			/*GetWorld()->GetTimerManager().ClearTimer()*/
		}
	), DeathDuration, false);

}

void APDMonster1::DeathEnd()
{
}

void APDMonster1::BasicAttackStart()
{
	if (IsAttack)
		return;
	else
		IsAttack = true;
	if (Monster1Instance)
	{
		Monster1Instance->PlayBasicAttackMontage();
	}
}

void APDMonster1::JumpAttackStart()
{
	if (IsAttack)
		return;
	else
		IsAttack = true;

	if (Monster1Instance)
	{
		Monster1Instance->PlayJumpAttackMontage();
	}
}

void APDMonster1::AttackEnd()
{
	IsAttack = false;
}

void APDMonster1::AttackCheck()
{
	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, this);

	float AttackRange = Stat->AtkRange;
	float AttackRadius = 50.f;

	bool bResult = GetWorld()->SweepSingleByChannel(
		OUT HitResult,
		GetActorLocation(),
		GetActorLocation() + GetActorForwardVector() * AttackRange,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(AttackRadius),
		Params);
	if (bResult && HitResult.Actor.IsValid() && HitResult.Actor->ActorHasTag("Player"))
	{
		FDamageEvent DamageEvent;
		HitResult.Actor->TakeDamage(Stat->Atk, DamageEvent, GetController(), this);
	}
}

void APDMonster1::ReactStart()
{
	if (Monster1Instance)
	{
		Monster1Instance->PlayReactMontage();
	}
}

void APDMonster1::FindStart()
{
	if (Monster1Instance)
	{
		Monster1Instance->PlayFindMontage();
	}
}

void APDMonster1::SprintStart()
{
	GetCharacterMovement()->MaxWalkSpeed *= SprintMultiplier;
}

void APDMonster1::SprintStop()
{
	GetCharacterMovement()->MaxWalkSpeed /= SprintMultiplier;
}

void APDMonster1::WeaponDrop()
{
}
