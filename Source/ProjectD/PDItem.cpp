// Fill out your copyright notice in the Description page of Project Settings.


#include "PDItem.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "ProjectDCharacter.h"
#include "PDDataSet.h"

// Sets default values
APDItem::APDItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ItemMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WEAPON"));
	RootComponent = ItemMeshComponent;
	ConstructorHelpers::FObjectFinder<UStaticMesh> ItemMesh(TEXT("/Game/DownloadAsset/Weapon_Pack/Mesh/Weapons/Weapons_Kit/SM_Sword.SM_Sword"));

	ItemBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	ItemBox->SetCollisionProfileName("Item");
	ItemBox->SetBoxExtent(FVector(10.f, 10.f, 10.f));
	ItemBox->SetupAttachment(RootComponent);

	Tags.Add(FName("Item"));

	ItemBasicState = EItemBasicState::Drop;

	ItemStat = new FItemStat(10.f, 10.f);
	ItemCode = -1;//상속시 다 변경
}

// Called when the game starts or when spawned
void APDItem::BeginPlay()
{
	Super::BeginPlay();
	ItemBox->OnComponentBeginOverlap.AddDynamic(this, &APDItem::BeginOverlap);
	ItemBox->OnComponentEndOverlap.AddDynamic(this, &APDItem::EndOverlap);
	ItemBox->OnComponentHit.AddDynamic(this, &APDItem::Hit);
}

// Called every frame
void APDItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APDItem::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag(FName("Player"))&&ItemBasicState == EItemBasicState::Drop)
	{
		ItemBasicState = EItemBasicState::Obtain;
		AProjectDCharacter* PDCharacter = Cast<AProjectDCharacter>(OtherActor);
		PDCharacter->ItemInfo = GetWorld()->SpawnActor < APDItem>();
		PDCharacter->ItemInfo->ItemBox->SetCollisionProfileName("NoCollision");
		PDCharacter->ItemInfo->ItemBasicState = EItemBasicState::Mount;

		FName WeaponSocket(TEXT("hand_r_socket"));
		if (PDCharacter->GetMesh()->DoesSocketExist(WeaponSocket))
		{
			PDCharacter->ItemInfo->AttachToComponent(PDCharacter->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, WeaponSocket);
		}
		Destroy();
	}
}

void APDItem::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

void APDItem::Hit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
}

void APDItem::EquipmentMount()
{
}
