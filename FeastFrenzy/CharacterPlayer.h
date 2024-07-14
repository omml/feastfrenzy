//
//  CharacterPlayer.h
//  Feast Frenzy game
//
//  Created by Oscar Martinez on 1/Apr/2024.
//
#pragma once
#ifndef CHARACTERPLAYER_H
#define CHARACTERPLAYER_H

#include "Character.h"
#include "Food.h"
#include "TableHandler.h"

class CharacterPlayer : public Character
{
private:
	bool _catched;
	Food* _food;
	TableHandler* _tableHandler;
public:
	CharacterPlayer();

	CharacterPlayer(GameObjectType go_type, int sprite, float posX, float posY, const char name[], int colRad, float scale, float animSpeed);

	void CheckPlayingArea();

	void CheckObjectsInPlayingArea();

	int GetKeyDown();

	void HandlePlayerControls();

	PlayerAnimationState GetAnimationState();

	void SetCatch(bool val, Food* food);

	bool GetCatch();

	void LaunchFood();

	void SetTableHandler(TableHandler* tableHandler);
};
#endif