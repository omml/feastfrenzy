//
//  PlayerHandler.h
//  Feast Frenzy game
//
//  Created by Oscar Martinez on 1/Apr/2024.
//
#pragma once
#ifndef PLAYERHANDLER_H
#define PLAYERHANDLER_H

#include "CharacterPlayer.h"

// Class to create the food
class PlayerHandler
{
public:
	CharacterPlayer player;

	PlayerHandler();

	CharacterPlayer* GetPlayer();

	void Create();

	void Display();
};
#endif