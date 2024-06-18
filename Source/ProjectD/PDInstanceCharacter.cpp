// Fill out your copyright notice in the Description page of Project Settings.


#include "PDInstanceCharacter.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UPDInstanceCharacter::UPDInstanceCharacter()
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

void UPDInstanceCharacter::NativeInitializeAnimation()
{
	Pawn = TryGetPawnOwner();
	if (Pawn == nullptr)
		return;
	Character = Cast<ACharacter>(Pawn);
	if (Character==nullptr)
		return;
}

void UPDInstanceCharacter::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	
	if (Pawn == nullptr)
		return;
	CharacterSpeed = Pawn->GetVelocity().Size();
	IsInAir = Character->GetCharacterMovement()->IsFalling();
}



void UPDInstanceCharacter::PlayAttackMontage(float AtkSpeed)
{
	if (AttackMontage&&!Montage_IsPlaying(AttackMontage))
	{
		Montage_Play(AttackMontage, AtkSpeed);
	}
}

void UPDInstanceCharacter::PlayDeathMontage()
{
	if (DeathMontage && !Montage_IsPlaying(DeathMontage))
	{
		Montage_Play(DeathMontage, 1.f);
	}
}

void UPDInstanceCharacter::AnimNotify_AttackStart()
{
	OnAttackHit.Broadcast();
}
