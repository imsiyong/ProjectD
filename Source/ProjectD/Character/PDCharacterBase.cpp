// Fill out your copyright notice in the Description page of Project Settings.


#include "PDCharacterBase.h"
#include <Kismet/GameplayStatics.h>
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "../PDGameInstance.h"
#include "../BattleLevel/PDBattlePlayerController.h"
#include "../UserWidget/PDUWBattleStatus.h"

// Sets default values
APDCharacterBase::APDCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	MouseInputValid = true;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
	//
	//
	Tags.Add(FName("Player"));
}

// Called when the game starts or when spawned
void APDCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	if (PDGameInstance)
	{
		Stat = PDGameInstance->GetPlayerStat();
		Inventory = PDGameInstance->GetPlayerInventory();
		Equip = PDGameInstance->GetPlayerEquip();
	}
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if(PlayerController)
		PDPlayerController = Cast<APDBattlePlayerController>(PlayerController);
}

// Called every frame
void APDCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APDCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &APDCharacterBase::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APDCharacterBase::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APDCharacterBase::MyTurnAtRate);
	PlayerInputComponent->BindAxis("TurnRate", this, &APDCharacterBase::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APDCharacterBase::MyLookUpAtRate);
	PlayerInputComponent->BindAxis("LookUpRate", this, &APDCharacterBase::LookUpAtRate);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
}

void APDCharacterBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	PDGameInstance = Cast<UPDGameInstance>(GetGameInstance());
}

void APDCharacterBase::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void APDCharacterBase::MoveRight(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void APDCharacterBase::TurnAtRate(float Rate)
{
	if (MouseInputValid)
		AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void APDCharacterBase::MyTurnAtRate(float Rate)
{
	if (MouseInputValid)
		AddControllerYawInput(Rate);
}

void APDCharacterBase::LookUpAtRate(float Rate)
{
	if (MouseInputValid)
		AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void APDCharacterBase::MyLookUpAtRate(float Rate)
{
	if (MouseInputValid)
		AddControllerPitchInput(Rate);
}

float APDCharacterBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	ChangeCurHp(Stat->CurHp - DamageAmount);
	UE_LOG(LogTemp, Log, TEXT("Player code[%d] CurHp : %f"), Stat->ActorCode, Stat->CurHp);
	return 0.0f;
}

void APDCharacterBase::ChangeCurHp(float curHp)
{
	if (curHp < 0)
	{
		Stat->CurHp = 0;
		PDPlayerController->BattleStatusWidget->SetHpBar(0.0f);
	}
	else if (curHp > Stat->MaxHp)
	{
		Stat->CurHp = Stat->MaxHp;
		PDPlayerController->BattleStatusWidget->SetHpBar(1.f);
	}
	else
	{
		Stat->CurHp = curHp;
		PDPlayerController->BattleStatusWidget->SetHpBar(Stat->CurHp / Stat->MaxHp);
	}
}

void APDCharacterBase::AttackCheck()
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
	if (bResult && HitResult.Actor.IsValid() && HitResult.Actor->ActorHasTag("Monster"))
	{
		FDamageEvent DamageEvent;
		HitResult.Actor->TakeDamage(Stat->Atk, DamageEvent, GetController(), this);
	}
}

