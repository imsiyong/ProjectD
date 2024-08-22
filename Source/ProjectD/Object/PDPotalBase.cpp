// Fill out your copyright notice in the Description page of Project Settings.


#include "PDPotalBase.h"
#include "Components/BoxComponent.h"
#include "particles/ParticleSystem.h"
#include "particles/ParticleSystemComponent.h"
#include <Kismet/GameplayStatics.h>
#include "Misc/outputdeviceNull.h"


// Sets default values
APDPotalBase::APDPotalBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	RootComponent = BoxCollision;
	BoxCollision->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));
	LevelName = "RestLevel";

	ConstructorHelpers::FObjectFinder<UParticleSystem> PS(TEXT("/Game/StarterContent/Particles/P_Sparks.P_Sparks"));
	if (PS.Succeeded())
	{
		Particle = PS.Object;
	}
}

// Called when the game starts or when spawned
void APDPotalBase::BeginPlay()
{
	Super::BeginPlay();
	ParticleComponent = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Particle, FTransform(GetTargetLocation()), false, EPSCPoolMethod::ManualRelease, true);
}

void APDPotalBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	ParticleComponent->ReleaseToPool();
}

// Called every frame
void APDPotalBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APDPotalBase::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	/*AP1Character* character = Cast<AP1Character>(OtherActor);
	if (character == nullptr)
		return;*/

	FTimerHandle myTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(myTimerHandle, FTimerDelegate::CreateLambda([&]()
		{
			// 내가 원하는 코드 구현

			UGameplayStatics::OpenLevel(GetWorld(), FName(LevelName));
			// 타이머 초기화
			GetWorld()->GetTimerManager().ClearTimer(myTimerHandle);
		}), 1.f, false);
}

