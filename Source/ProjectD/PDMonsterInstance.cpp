// Fill out your copyright notice in the Description page of Project Settings.


#include "PDMonsterInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UPDMonsterInstance::UPDMonsterInstance()
{
	ConstructorHelpers::FObjectFinder<UAnimMontage> AM(TEXT("/Game/BluePrint/AnimInstance/Montage/MTAttack1.MTAttack1"));
	if (AM.Succeeded())
	{
		AttackMontage = AM.Object;
	}
	ConstructorHelpers::FObjectFinder<UAnimMontage> deathMT(TEXT("/Game/BluePrint/AnimInstance/Montage/MTDeath1.MTDeath1"));
	if (deathMT.Succeeded())
	{
		DeathMontage = deathMT.Object;
	}
}

void UPDMonsterInstance::NativeInitializeAnimation()
{
	Pawn = TryGetPawnOwner();
	if (Pawn == nullptr)
		return;
	Character = Cast<ACharacter>(Pawn);
	if (Character == nullptr)
		return;
}

void UPDMonsterInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (Pawn == nullptr)
		return;
	CharacterSpeed = Pawn->GetVelocity().Size();
	IsInAir = Character->GetCharacterMovement()->IsFalling();
}



void UPDMonsterInstance::PlayAttackMontage()
{
	if (AttackMontage&&!Montage_IsPlaying(AttackMontage))
	{
		Montage_Play(AttackMontage, 1.f);
	}
}

void UPDMonsterInstance::PlayDeathMontage()
{
	if (DeathMontage && !Montage_IsPlaying(DeathMontage))
	{
		Montage_Play(DeathMontage, 1.f);
	}
}

void UPDMonsterInstance::AnimNotify_AttackStart()
{
	OnAttackHit.Broadcast();
}

void UPDMonsterInstance::AnimNotify_AttackEnd()
{
	OnAttackEnd.Broadcast();
}
