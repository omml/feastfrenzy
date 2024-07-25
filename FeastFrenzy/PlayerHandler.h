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
private:
	TableHandler* _tableHandler;

	CharacterPlayer _player;

public:

	PlayerHandler();

	CharacterPlayer* GetPlayer();

	void Create();

	void SetTableHandler(TableHandler* tableHandler);

	void Display();

	void ReStart();

	int GetObjectId();

	int GetHealthFood();
};
#endif