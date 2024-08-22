// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PDCharacter1AInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTD_API UPDCharacter1AInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	UPDCharacter1AInstance();

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
};
