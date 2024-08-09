// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PDMonster1Instance.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnAttackHit);
DECLARE_MULTICAST_DELEGATE(FOnAttackEnd);

/**
 * 
 */
UCLASS()
class PROJECTD_API UPDMonster1Instance : public UAnimInstance
{
	GENERATED_BODY()
public:
	UPDMonster1Instance();

	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	void Init();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float Speed;
	UPROPERTY()
		class APawn* Pawn;
	UPROPERTY()
		class ACharacter* Character;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
		class UAnimMontage* BasicAttackMontage;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
		class UAnimMontage* JumpAttackMontage;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
		class UAnimMontage* DeathMontage;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
		class UAnimMontage* ReactMontage;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
		class UAnimMontage* FindMontage;
	
	void PlayBasicAttackMontage();
	void PlayJumpAttackMontage();
	void PlayDeathMontage();
	void PlayReactMontage();
	void PlayFindMontage();
	bool MontageIsPlaying();


	FOnAttackHit OnAttackHit;
	FOnAttackEnd OnAttackEnd;
	UFUNCTION()
		void AnimNotify_M1AttackStart();
	UFUNCTION()
		void AnimNotify_M1AttackEnd();
};
