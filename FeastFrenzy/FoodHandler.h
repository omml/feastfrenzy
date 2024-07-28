//
//  FoodHandler.h
//  Feast Frenzy game
//
//  Created by Oscar Martinez on 1/Apr/2024.
//
#pragma once
#ifndef FOODHANDLER_H
#define FOODHANDLER_H

#include "Food.h"
#include "EnemyHandler.h"

class PlayerHandler;
class Food;

// Class to create the food
class FoodHandler
{

public:
	Food _food[NUM_ENEMIES];

	FoodHandler();

	Food* GetFood(int index);
	
	void Create(ObjectDirection dir);
	
	void Display();

	void SetOppositeCollisionObjs(EnemyHandler* enemyHandler);
};
#endif
