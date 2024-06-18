// Fill out your copyright notice in the Description page of Project Settings.


#include "PDSword.h"
#include "Components/BoxComponent.h"
#include "ProjectDCharacter.h"
#include "PDDataSet.h"

APDSword::APDSword()
{
	ConstructorHelpers::FObjectFinder<UStaticMesh> SwordMesh(TEXT("/Game/DownloadAsset/Weapon_Pack/Mesh/Weapons/Weapons_Kit/SM_Sword.SM_Sword"));
	
	if (SwordMesh.Succeeded())
	{
		ItemMeshComponent->SetStaticMesh(SwordMesh.Object);
		ItemMeshComponent->SetCollisionProfileName(TEXT("NoCollision"));
	}

	ItemStat->Atk = -200.0f;
	ItemStat->AtkRange = 0.0f;
	ItemStat->AtkSpeed = 1.0f;
}

void APDSword::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag(FName("Player")) && ItemBasicState == EItemBasicState::Drop)
	{
		AProjectDCharacter* PDCharacter = Cast<AProjectDCharacter>(OtherActor);
		PDCharacter->WeaponMount(EWeaponType::Sword);
		Destroy();
	}
}
