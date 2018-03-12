// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterSpecial.h"

CharacterSpecial::CharacterSpecial(
	uint32 S, uint32 P, uint32 E, uint32 C, uint32 I, uint32 A, uint32 L) :
	Strength(FMath::Clamp<uint32>(S, 1, 10)),
	Perception(FMath::Clamp<uint32>(P, 1, 10)),
	Endurance(FMath::Clamp<uint32>(E, 1, 10)),
	Charisma(FMath::Clamp<uint32>(C, 1, 10)),
	Intelligence(FMath::Clamp<uint32>(I, 1, 10)),
	Agility(FMath::Clamp<uint32>(A, 1, 10)),
	Luck(FMath::Clamp<uint32>(L, 1, 10))
{
}

CharacterSpecial::~CharacterSpecial()
{
}
