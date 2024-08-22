// Fill out your copyright notice in the Description page of Project Settings.


#include "PDManCharacter.h"
#include "PDCharacter1AInstance.h"

APDManCharacter::APDManCharacter()
{

	ConstructorHelpers::FObjectFinder<USkeletalMesh> SM(TEXT("/Game/Man/Mesh/Full/SK_Man_Full_03.SK_Man_Full_03"));
	if (SM.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SM.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -88.f), FRotator(0.f, -90.f, 0.f));
	}
	ConstructorHelpers::FClassFinder<UPDCharacter1AInstance> AM(TEXT("AnimBlueprint'/Game/BluePrint/AnimInstance/Man/BPManInstnace.BPManInstnace_C'"));
	if (AM.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(AM.Class);
	}
}

void APDManCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void APDManCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APDManCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APDManCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	PDCharacter1AInstance = Cast<UPDCharacter1AInstance>(GetMesh()->GetAnimInstance());
}
