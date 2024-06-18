// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PDMonsterInstance.generated.h"


DECLARE_MULTICAST_DELEGATE(FOnAttackHit);
DECLARE_MULTICAST_DELEGATE(FOnAttackEnd);
/**
 * 
 */
UCLASS()
class PROJECTD_API UPDMonsterInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	UPDMonsterInstance();

	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float CharacterSpeed;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		bool IsInAir;

	UPROPERTY()
		class APawn* Pawn;
	UPROPERTY()
		class ACharacter* Character;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
		class UAnimMontage* AttackMontage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
		class UAnimMontage* DeathMontage;

	class FStat* Stat;

	void PlayAttackMontage();
	void PlayDeathMontage();

	FOnAttackHit OnAttackHit;
	FOnAttackEnd OnAttackEnd;

	UFUNCTION()
		void AnimNotify_AttackStart();
	UFUNCTION()
		void AnimNotify_AttackEnd();
};
