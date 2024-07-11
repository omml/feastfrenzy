//
//  EnemyHandler.h
//  Feast Frenzy game
//
//  Created by Oscar Martinez on 1/Apr/2024.
//
#pragma once
#ifndef ENEMYHANDLER_H
#define ENEMYHANDLER_H

#include "CommonDefinitions.h"
#include "CharacterEnemy.h"
#include "DifficultyHandler.h"

class FoodHandler;

class EnemyHandler
{
private:
	DifficultyHandler* _difficultyHandler;
	CharacterEnemy _enemies[NUM_ENEMIES];
	ObjectDirection _originalDirection[NUM_ENEMIES];
	int _states[4];
	int _screenPosition;
	float _xPosIni;
	float _yPosIni;
	float _posXMin;
	float _posXMax;
	float _posYMin;
	float _posYMax;
	FoodHandler* _foodHandler;

public:
	EnemyHandler();
	
	void SetFoodHandler(FoodHandler* foodHandler);
	void SetDifficultyHandler(DifficultyHandler* difficultyHandler);
	
	CharacterEnemy* GetEnemy(int index);
	
	void Create(int screenPosition);
	
	void Display();

	void ReStart();
	
};
#endif