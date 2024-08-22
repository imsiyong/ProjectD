// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PDCharacterBase.h"
#include "PDManCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTD_API APDManCharacter : public APDCharacterBase
{
	GENERATED_BODY()
public:
	APDManCharacter();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void PostInitializeComponents() override;

public:
	class UPDCharacter1AInstance* PDCharacter1AInstance;
};
