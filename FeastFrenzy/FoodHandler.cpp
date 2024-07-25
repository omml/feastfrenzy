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
#include "PlayerHandler.h"

FoodHandler::FoodHandler() {}

// Sets a reference to the player handler so later a reference to player can be set
void FoodHandler::SetPlayerHandler(PlayerHandler* playerHandle)
{
	_playerHandler = playerHandle;
}

// Returns a pointer to a food item to be associated with an enemy
Food* FoodHandler::GetFood(int index)
{
	return &_food[index];
}

// Sets a reference to the score object to decrease depending health
void FoodHandler::SetHealthBarObject(HealthBar* healthBar)
{
	_healthBar = healthBar;
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
		// Sets the player
		_food[i].SetPlayer(_playerHandler->GetPlayer());
		// Sets the healthbar object
		_food[i].SetHealthBarObject(_healthBar);
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
