// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PDEnum.h"
#include "PDItem.generated.h"

UCLASS()
class PROJECTD_API APDItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APDItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	EItemBasicState ItemBasicState;

	UPROPERTY(VisibleAnywhere)
		class UStaticMeshComponent* ItemMeshComponent;

	UPROPERTY(VisibleAnywhere, Category = "Item Box")
		class UBoxComponent* ItemBox;
	UFUNCTION()
		virtual void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex);
	UFUNCTION()
		void Hit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse,
			const FHitResult& Hit);

	class FItemStat* ItemStat;
};
