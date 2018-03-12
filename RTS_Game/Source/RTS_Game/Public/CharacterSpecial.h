// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class CharacterSpecial
{
public:
	CharacterSpecial(uint32 = 5, uint32 = 5, uint32 = 5, uint32 = 5, uint32 = 5, uint32 = 5, uint32 = 5);
	~CharacterSpecial();

	uint32 Strength : 4;		// ����
	uint32 Perception : 4;		// ����������
	uint32 Endurance : 4;		// ������������
	uint32 Charisma : 4;		// �������
	uint32 Intelligence : 4;	// ���������
	uint32 Agility : 4;			// ��������
	uint32 Luck : 4;			// �����
};
