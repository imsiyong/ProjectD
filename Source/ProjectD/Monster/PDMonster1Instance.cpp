// Fill out your copyright notice in the Description page of Project Settings.


#include "PDMonster1Instance.h"

UPDMonster1Instance::UPDMonster1Instance()
{
	ConstructorHelpers::FObjectFinder<UAnimMontage> BA(TEXT("/Game/BluePrint/AnimInstance/Monster1/MTBasicAttack.MTBasicAttack"));
	if (BA.Succeeded())
	{
		BasicAttackMontage = BA.Object;
	}
	ConstructorHelpers::FObjectFinder<UAnimMontage> JA(TEXT("/Game/BluePrint/AnimInstance/Monster1/MTJumpAttack.MTJumpAttack"));
	if (JA.Succeeded())
	{
		JumpAttackMontage = JA.Object;
	}
	ConstructorHelpers::FObjectFinder<UAnimMontage> DM(TEXT("/Game/BluePrint/AnimInstance/Monster1/MTDeath.MTDeath"));
	if (DM.Succeeded())
	{
		DeathMontage = DM.Object;
	}
	ConstructorHelpers::FObjectFinder<UAnimMontage> RM(TEXT("/Game/BluePrint/AnimInstance/Monster1/MTReact.MTReact"));
	if (RM.Succeeded())
	{
		ReactMontage = RM.Object;
	}
	ConstructorHelpers::FObjectFinder<UAnimMontage> FM(TEXT("/Game/BluePrint/AnimInstance/Monster1/MTFind.MTFind"));
	if (FM.Succeeded())
	{
		FindMontage = FM.Object;
	}
}

void UPDMonster1Instance::NativeInitializeAnimation()
{
	Init();
}

void UPDMonster1Instance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (Pawn == nullptr)
		return;
	Speed = Pawn->GetVelocity().Size();
}

void UPDMonster1Instance::Init()
{
	Pawn = TryGetPawnOwner();
	if (Pawn == nullptr)
		return;
	Character = Cast<ACharacter>(Pawn);
	if (Character == nullptr)
		return;
}

void UPDMonster1Instance::PlayBasicAttackMontage()
{
	if (BasicAttackMontage && !MontageIsPlaying())
	{
		Montage_Play(BasicAttackMontage, 1.0f);
	}
}

void UPDMonster1Instance::PlayJumpAttackMontage()
{
	if (JumpAttackMontage && !MontageIsPlaying())
	{
		Montage_Play(JumpAttackMontage, 1.0f);
	}
}

void UPDMonster1Instance::PlayDeathMontage()
{
	if (DeathMontage && !MontageIsPlaying())
	{
		Montage_Play(DeathMontage, 1.0f);
	}
}

void UPDMonster1Instance::PlayReactMontage()
{
	if (ReactMontage && !MontageIsPlaying())
	{
		Montage_Play(ReactMontage, 1.0f);
	}
}

void UPDMonster1Instance::PlayFindMontage()
{
	if (FindMontage && !MontageIsPlaying())
	{
		Montage_Play(FindMontage, 1.0f);
	}
}

bool UPDMonster1Instance::MontageIsPlaying()
{
	if (Montage_IsPlaying(BasicAttackMontage))
		return true;
	if (Montage_IsPlaying(JumpAttackMontage))
		return true;
	if (Montage_IsPlaying(DeathMontage))
		return true;
	if (Montage_IsPlaying(ReactMontage))
		return true;
	if (Montage_IsPlaying(FindMontage))
		return true;
	return false;
}

void UPDMonster1Instance::AnimNotify_M1AttackStart()
{
	OnAttackHit.Broadcast();
}

void UPDMonster1Instance::AnimNotify_M1AttackEnd()
{
	OnAttackEnd.Broadcast();
}