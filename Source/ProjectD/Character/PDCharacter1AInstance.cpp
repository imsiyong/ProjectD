// Fill out your copyright notice in the Description page of Project Settings.


#include "PDCharacter1AInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UPDCharacter1AInstance::UPDCharacter1AInstance()
{

}

void UPDCharacter1AInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	Pawn = TryGetPawnOwner();
	if (Pawn == nullptr)
		return;
	Character = Cast<ACharacter>(Pawn);
	if (Character == nullptr)
		return;
}

void UPDCharacter1AInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (Pawn == nullptr)
		return;
	CharacterSpeed = Pawn->GetVelocity().Size();
	IsInAir = Character->GetCharacterMovement()->IsFalling();
}
