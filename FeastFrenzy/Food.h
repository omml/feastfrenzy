//
//  Food.h
//  Feast Frenzy game
//
//  Created by Oscar Martinez on 1/Apr/2024.
//
#pragma once
#ifndef FOOD_H
#define FOOD_H

#include "MainGameObject.h"
#include "ScoreHolder.h"
#include "HealthBar.h"

class CharacterEnemy;
class CharacterPlayer;

// Main class that holds some common functionality for characters
class Food : public MainGameObject
{
protected:
	// It acts like an index to enemy objects
	int _offset;
	// Index offset to differenciate from enemies spawn from left,right,up,down
	int _directionOffset;
	FoodState _state;
	bool _fromPlayer;

	CharacterEnemy* _enemy;
	CharacterPlayer* _player;

	ScoreHolder* _score;
	HealthBar* _healthBar;

	bool _isCake;

public:
	Food();

	Food(GameObjectType go_type, int sprite, float posX, float posY, const char name[], int colRad, float scale, float animSpeed, int offset, int dirOffset);
	
	// Sets reference to the enemy is carrying the food
	void SetEnemy(CharacterEnemy* enemy);
	// Sets refence to the player in case player catches the food
	void SetPlayer(CharacterPlayer* player);
	// Displays the food on top of the character depending on character's direction
	void DisplayCarriedPosition();
	// Throws the food, changes the food state, this function
	// will be hanged by enemy or player
	void Throw(ObjectDirection dir, float moveSpeed, bool fromPlayer);
	// Handle food animation depending on state
	void Animate();
	// Check if is outside screen
	bool IsOutsideScreen();
	// Restarts to initial state
	void ReStart();

	void SetScoreObject(ScoreHolder* score);
	void SetHealthBarObject(HealthBar* healthBar);

	FoodState GetState();

	bool IsCollidingWithPlayer();

	bool IsCollidingWithEnemies();

	bool IsCake();
	void SetIdle();
};
#endif