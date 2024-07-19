//
//  CharacterEnemy.h
//  Feast Frenzy game
//
//  Created by Oscar Martinez on 1/Apr/2024.
//
#pragma once
#ifndef CHARACTERENEMY_H
#define CHARACTERENEMY_H

#include "Character.h"
#include "Food.h"

class CharacterEnemy : public Character
{
protected:
	int _offset;
	EnemyState _enemyState;
	float _xLimit;
	float _yLimit;
	Food* _food;
	ObjectDirection _screenSide;

	int _counter;
	int _maxCounter;
	bool _restartFood;
public:
	CharacterEnemy();
	
	CharacterEnemy(GameObjectType go_type, int sprite, float posX, float posY, const char name[], int colRad, float scale, float animSpeed, ObjectDirection screenSide, int offset);

	void SetFood(Food* food);
	
	// Sets the limit so the enemy moves up to that limit
	void SetLimits(float x, float y);
	// Checks if the enemy has reached a position set as limit
	bool HasReachedLimit();

	void LaunchFood();

	void Animate();

	void ReStart(ObjectDirection dir);
	void ReSpawn(ObjectDirection dir, bool resFood);

	void ChangeInitPosition();

	EnemyState GetState();
	FoodState GetFoodState();

};
#endif