//
//  Table.h
//  Feast Frenzy game
//
//  Created by Oscar Martinez on 13/Jul/2024.
//
#pragma once
#include "MainGameObject.h"
class Table : public MainGameObject
{
private:
	MainGameObject _collider;
	MainGameObject _cake;
	MainGameObject _smoke;
	MainGameObject _smokeCake;
	bool _hasCake = false;
	bool _playedAppearSound = false;
	bool _displayDisappear = false;

public:
	Table();
	Table(GameObjectType go_type, int sprite, float posX, float posY, const char name[], int colRad, float scale, float animSpeed);
	bool IsCollidingWithPlayer(int playerId);

	void SetCake(bool val);
	bool HasCake();

	void Display() override;

	void ReStart(float x, float y);

	void TimerToResetCake(int durationInSeconds);
};

