//
//  FoodHandler.cpp
//  Feast Frenzy game
//
//  Created by Oscar Martinez on 1/Apr/2024.
//
#define PLAY_USING_GAMEOBJECT_MANAGER
#include "Play.h"
#include "FoodHandler.h"
#include "SpritesDefinitions.h"

FoodHandler::FoodHandler() {}

// Returns a pointer to a food item to be associated with an enemy
Food* FoodHandler::GetFood(int index)
{
	return &_food[index];
}

// Creates all food items, one for each enemy
void FoodHandler::Create(ObjectDirection dir)
{
	int r = 0;

	for (int i = 0; i < NUM_ENEMIES; i++)
	{
		GameObjectType goType = (GameObjectType)((dir * 4) + TYPE_FOOD_START + i);
		// Selects a random sprite
		r = Play::RandomRollRange(f_bk_n, f_tm_n);
		// Creates the game object
		_food[i] = Food(goType, r, -100.0f, -100.0f, "f", 25, 0.75f, 0.0f, i, dir*4 );
	}
}

// Displays all food objects
void FoodHandler::Display()
{
	for (int i = 0; i < NUM_ENEMIES; i++)
	{
		_food[i].Animate();
	}
}

// Sets Enemies that are on the oposite side of the screen so collision testing can be done just
// against them
void FoodHandler::SetOppositeCollisionObjs(EnemyHandler* enemyHandler)
{
	CharacterEnemy* enemy;
	int enemyId;

	for (int i = 0; i < NUM_ENEMIES; i++)
	{
		enemy = enemyHandler->GetEnemy(i);

		enemyId = enemy->GetObjectId();

		for (int j = 0; j < NUM_ENEMIES; j++)
		{
			_food[j].SetOppositeCollisionObj(enemyId);
		}
	}
}
