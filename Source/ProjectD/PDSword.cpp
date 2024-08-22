// Fill out your copyright notice in the Description page of Project Settings.


#include "PDSword.h"
#include "Components/BoxComponent.h"
#include "ProjectDCharacter.h"
#include "PDDataSet.h"
#include "PDPlayerController.h"
#include "ProjectDCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "PDCharacterItemInventory.h"
#include "UserWidget/PDItemInventory.h"

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
	
	ItemCode = 1;
	Texture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, TEXT("/Game/DownloadAsset/MyTexture/Texture_Sword.Texture_Sword")));
}

void APDSword::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag(FName("Player")) && ItemBasicState == EItemBasicState::Drop)
	{
		AProjectDCharacter* PDCharacter = Cast<AProjectDCharacter>(OtherActor);
		//PDCharacter->WeaponMount(EWeaponType::Sword);
		PDCharacter->Inventory22->AddItem(FString(TEXT("Sword")), 1, Texture, EInventoryType::Weapon, EEquipType::Right);
		PDCharacter->PDPlayerController->ItemInventory->Refresh();
		Destroy();
	}
}

void APDSword::EquipmentMount()
{
	if (Player == nullptr)
	{
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		if (PlayerController)
		{
			Player = Cast<AProjectDCharacter>(PlayerController->GetPawn());
		}
	}
	FName WeaponSocket(TEXT("hand_r_socket"));
	if (Player->GetMesh()->DoesSocketExist(WeaponSocket))
	{
		AttachToComponent(Player->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, WeaponSocket);
	}
}
