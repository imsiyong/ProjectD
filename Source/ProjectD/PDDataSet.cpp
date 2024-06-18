// Fill out your copyright notice in the Description page of Project Settings.


#include "PDDataSet.h"

FStat::FStat()
{
	ActorCode = 0;
	MaxHp = 1000.f;
	CurHp = 1000.f;
	Atk = 500.f;
	Def = 5.f;
	Speed = 100.f;
	AtkRange = 100.f;
	AtkSpeed = 2.0f;
	SightRange = 600.f;
}

FStat::FStat(int32 actorcode)
{
	ActorCode = actorcode;
	MaxHp = 1000.f;
	CurHp = 1000.f;
	Atk = 500.f;
	Def = 5.f;
	Speed = 100.f;
	AtkRange = 100.f;
	AtkSpeed = 2.0f;
	SightRange = 600.f;
}

FItemStat::FItemStat()
{
	Atk = 0.0f;
	AtkRange = 0.0f;
	AtkSpeed = 0.0f;
}

FItemStat::FItemStat(float atk, float atkRange, float atkSpeed)
{
	Atk = atk;
	AtkRange = atkRange;
	AtkSpeed = atkSpeed;
}
