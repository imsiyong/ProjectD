// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PDPotalBase.generated.h"

UCLASS()
class PROJECTD_API APDPotalBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APDPotalBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
		FString LevelName;
	UPROPERTY()
		class UBoxComponent* BoxCollision;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	UPROPERTY()
		class UParticleSystem* Particle;

	class UParticleSystemComponent* ParticleComponent;
};
