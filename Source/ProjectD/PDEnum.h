// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

enum class EMonsterBasicState
{
	LIVE,
	DEATH
};

enum class EPlayerBasicState
{
	LIVE,
	DEATH
};

enum class EMonsterActionState
{
	PATROL,
	MoveToPlayer,
	Attack,
	RESET,
	SetDest,
	MoveToDest,
	CheckDist,
	CheckField,
	MoveToCenter
};

enum class EItemBasicState
{
	None,
	Drop,
	Obtain,
	Mount
};

enum class EWeaponType
{
	None,
	Sword,
	Mace
};

UENUM(BlueprintType)
enum class ECharacterStatType:uint8
{
	None		UMETA(DisplayName = "None"),
	Atk			UMETA(DisplayName = "Atk"),
	AtkSpeed	UMETA(DisplayName = "AtkSpeed"),
	Def			UMETA(DisplayName = "Def"),
	Hp			UMETA(DisplayName = "Hp")
};

UENUM(BlueprintType)
enum class ESlotType :uint8
{
	None		UMETA(DisplayName ="None"),
	Inventory	UMETA(DisplayName="Weapon"),
	Equip		UMETA(DisplayName="Equip")
};

UENUM(BlueprintType)
enum class EInventoryType : uint8
{
	None		UMETA(DisplayName = "None"),
	Weapon		UMETA(DisplayName = "Weapon")
};

UENUM(BlueprintType)
enum class EEquipType : uint8
{
	Head		UMETA(DisplayName = "Weapon"),
	Body		UMETA(DisplayName = "Body"),
	Foot		UMETA(DisplayName = "Foot"),
	Left		UMETA(DisplayName = "Left"),
	Right		UMETA(DisplayName = "Right"),
	None		UMETA(DisplayName = "None")
};