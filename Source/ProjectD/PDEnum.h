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