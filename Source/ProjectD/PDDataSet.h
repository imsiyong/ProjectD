#pragma once

#include "CoreMinimal.h"

class FStat
{
public:
	int32 ActorCode;
	float MaxHp;
	float CurHp;
	float Atk;
	float Def;
	float Speed;
	float AtkRange;
	float AtkSpeed;
	float SightRange;

public:
	FStat();
	FStat(int32 actorcode);

	FStat& operator=(const FStat& ref)
	{
		return *this;
	}

	int32 GetActorCode() { return ActorCode; }
	void SetActorCode(int32 actorcode) { ActorCode = actorcode; }

	float GetMaxHp() { return MaxHp; }
	void SetMaxHp(float hp) { MaxHp = hp; }

	float GetCurHp() { return CurHp; }
	void SetCurHp(float hp) { CurHp = hp; }

	float GetAtk() { return Atk; }
	void SetAtk(float atk) { Atk = atk; }

	float GetDef() { return Def; }
	void SetDef(float def) { Def = def; }

	float GetSpeed() { return Speed; }
	void SetSpeed(float speed) { MaxHp = Speed; }

	float GetAtkRange() { return AtkRange; }
	float SetAtkRange(float atkrange) { AtkRange = atkrange; }

	float GetAtkSpeed() { return AtkSpeed; }
	float SetAtkSpeed(float atkSpeed) { AtkSpeed = atkSpeed; }

	float GetSightRange() { return SightRange; }
	float SetSightRange(float sightrange) { SightRange = sightrange; }
};

class FItemStat
{
public:
	float Atk;
	float AtkRange;
	float AtkSpeed;

public:
	FItemStat();
	FItemStat(float atk = 0, float atkRange = 0, float atkSpeed = 0);

	float GetAtk() { return Atk; }
	void SetAtk(float atk) { Atk = atk; }

	float GetAtkRange() { return AtkRange; }
	void SetAtkRange(float atkRange) { AtkRange = atkRange; }

	float GetAtkSpeed() { return AtkSpeed; }
	void SetAtkSpeed(float atkSpeed) { AtkSpeed = atkSpeed; }
};