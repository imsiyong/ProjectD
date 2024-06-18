// Fill out your copyright notice in the Description page of Project Settings.


#include "PDMace.h"
#include "Components/BoxComponent.h"
#include "ProjectDCharacter.h"
#include "PDDataSet.h"

APDMace::APDMace()
{
	ConstructorHelpers::FObjectFinder<UStaticMesh> MaceMesh(TEXT("/Game/DownloadAsset/Weapon_Pack/Mesh/Weapons/Weapons_Kit/SM_Mace.SM_Mace"));
	if (MaceMesh.Succeeded())
	{
		ItemMeshComponent->SetStaticMesh(MaceMesh.Object);
		ItemMeshComponent->SetCollisionProfileName(TEXT("NoCollision"));
	}
	ItemStat->Atk = 200.0f;
	ItemStat->AtkRange = 0.0f;
	ItemStat->AtkSpeed = -1.0f;

}

void APDMace::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag(FName("Player")) && ItemBasicState == EItemBasicState::Drop)
	{
		AProjectDCharacter* PDCharacter = Cast<AProjectDCharacter>(OtherActor);
		PDCharacter->WeaponMount(EWeaponType::Mace);
		Destroy();
	}
}
