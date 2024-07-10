// Fill out your copyright notice in the Description page of Project Settings.


#include "PDMonsterSample.h"
#include "PDMonsterInstance.h"
#include "PDGameInstance.h"
#include "Components/CapsuleComponent.h"
#include "PDMonsterAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PDItem.h"
#include "PDMace.h"
#include "PDSword.h"
#include "Components/BoxComponent.h"
#include "PDMonsterManager.h"

// Sets default values
APDMonsterSample::APDMonsterSample()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ConstructorHelpers::FObjectFinder<USkeletalMesh> SM(TEXT("/Game/Mannequin/Character/Mesh/SK_Mannequin_Female.SK_Mannequin_Female"));
	if (SM.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SM.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -88.f), FRotator(0.f, -90.f, 0.f));
	}
	ConstructorHelpers::FClassFinder<UPDMonsterInstance> MI(TEXT("AnimBlueprint'/Game/BluePrint/AnimInstance/BPMonsterAnim.BPMonsterAnim_C'"));
	if (MI.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(MI.Class);
	}

	BasicState = EMonsterBasicState::LIVE;
	IsAttack = false;

	SprintSpeedMuti = 2.0f;
	GetCharacterMovement()->MaxWalkSpeed = 200.f;
	Tags.Add(FName("Monster"));

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("PDCharacter"));

	AIControllerClass = APDMonsterAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	DeathEventDelayTime = 5.0f;
}

// Called when the game starts or when spawned
void APDMonsterSample::BeginPlay()
{
	Super::BeginPlay();
}

void APDMonsterSample::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	//stat initialize
	if (UGameInstance* GameInstace = GetGameInstance())
	{
		UPDGameInstance* PDGameInstance = Cast<UPDGameInstance>(GameInstace);
		if (PDGameInstance)
		{
			PDGameInstance->MonsterStatArrayAdd();
			Stat = PDGameInstance->GetMonsterStatArray().Top();
		}
	}

	UPDMonsterInstance* AnimInstance = Cast<UPDMonsterInstance>(GetMesh()->GetAnimInstance());
	if (AnimInstance)
	{
		AnimInstance->OnAttackHit.AddUObject(this, &APDMonsterSample::AttackCheck);
		AnimInstance->OnAttackEnd.AddUObject(this, &APDMonsterSample::AttackEnd);
	}
}

// Called every frame
void APDMonsterSample::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APDMonsterSample::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

float APDMonsterSample::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
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

void APDMonsterSample::AttackStart()
{
	if (IsAttack)return;
	IsAttack = true;
	UPDMonsterInstance* animinstance = Cast<UPDMonsterInstance>(GetMesh()->GetAnimInstance());
	if (animinstance)
	{
		animinstance->PlayAttackMontage();
	}
}

void APDMonsterSample::AttackEnd()
{
	IsAttack = false;
}

void APDMonsterSample::AttackCheck()
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

void APDMonsterSample::DeathStart()
{
	//Death Montage Play
	UPDMonsterInstance* MonsterInstance = Cast<UPDMonsterInstance>(GetMesh()->GetAnimInstance());
	if (MonsterInstance)
	{
		MonsterInstance->StopAllMontages(0.0f);
		MonsterInstance->PlayDeathMontage();
	}

	BasicState = EMonsterBasicState::DEATH;

	//SetActorEnableCollision(false);
	GetCapsuleComponent()->SetCollisionProfileName("NoCollision");
	FActorSpawnParameters SpawnParams;
	FRotator SpawnRotator;
	FVector SpawnLocation = GetActorLocation();
	WeaponDrop();

	UPDMonsterManager::Get()->RemoveMonster(MonsterCode);

	//after 5seconds Actor destroy
	FTimerHandle DeathTimeHandle;
	GetWorld()->GetTimerManager().SetTimer(DeathTimeHandle, FTimerDelegate::CreateLambda([&]()
		{
			Destroy();
			/*GetWorld()->GetTimerManager().ClearTimer()*/
		}
	), DeathEventDelayTime, false);
}

void APDMonsterSample::DeathEnd()
{
}

void APDMonsterSample::SprintStart()
{
	GetCharacterMovement()->MaxWalkSpeed *= SprintSpeedMuti;
}

void APDMonsterSample::SprintStop()
{
	GetCharacterMovement()->MaxWalkSpeed /= SprintSpeedMuti;
}

void APDMonsterSample::WeaponDrop()
{
	FActorSpawnParameters SpawnParams;
	FRotator SpawnRotator;
	FVector SpawnLocation = GetActorLocation();
	

	int32 WeaponTypeNum = FMath::RandRange(0, 2);
	switch (WeaponTypeNum)
	{
	case 0:
		break;
	case 1:
		GetWorld()->SpawnActor<APDSword>(APDSword::StaticClass(), SpawnLocation, SpawnRotator, SpawnParams);
		break;
	case 2:
		GetWorld()->SpawnActor<APDMace>(APDMace::StaticClass(), SpawnLocation, SpawnRotator, SpawnParams);
		break;
	default:
		break;
	}
}


