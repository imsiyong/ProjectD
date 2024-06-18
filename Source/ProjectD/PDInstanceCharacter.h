// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PDInstanceCharacter.generated.h"


DECLARE_MULTICAST_DELEGATE(FOnAttackHit);
/**
 * 
 */
UCLASS()
class PROJECTD_API UPDInstanceCharacter : public UAnimInstance
{
	GENERATED_BODY()
public:
	UPDInstanceCharacter();

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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Component")
		class UAnimMontage* AttackMontage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
		class UAnimMontage* DeathMontage;

	void PlayAttackMontage(float AtkSpeed);
	void PlayDeathMontage();

	UFUNCTION()
	void AnimNotify_AttackStart();

	FOnAttackHit OnAttackHit;
};
