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

	int _colliderId;
	int _colliderYOffset;

	int _foodHealth = -1;

	bool _ateFood = false;
public:
	CharacterPlayer();

	CharacterPlayer(GameObjectType go_type, int sprite, float posX, float posY, const char name[], int colRad, float scale, float animSpeed);

	void CheckPlayingArea();

	void CheckObjectsInPlayingArea();

	void DisplayCollider();

	int GetKeyDown();

	void HandlePlayerControls();

	PlayerAnimationState GetAnimationState();

	void SetCatch(bool val, Food* food);

	bool GetCatch();

	void LaunchFood();

	bool PutOnTable();

	void ReStart() override;

	void SetHelathFood();
	int GetHealthFood();
};
#endif