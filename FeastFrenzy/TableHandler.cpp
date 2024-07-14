//
//  TableHandler.cpp
//  Feast Frenzy game
//
//  Created by Oscar Martinez on 13/Jul/2024.
//
#include "TableHandler.h"

#define PLAY_USING_GAMEOBJECT_MANAGER
#include "Play.h"
#include "EnemyHandler.h"
#include "SpritesDefinitions.h"
#include "Table.h"
#include "FoodHandler.h"
#include "DifficultyHandler.h"

TableHandler::TableHandler()
{
	_foodHandler = nullptr;
	_difficultyHandler = nullptr;
}

// Sets the food handler to pass references of food to the enemies
void TableHandler::SetFoodHandler(FoodHandler* foodHandler)
{
	_foodHandler = foodHandler;
	_difficultyHandler = nullptr;
}

// Sets the food handler to pass references of food to the enemies
void TableHandler::SetDifficultyHandler(DifficultyHandler* difficultyHandler)
{
	_difficultyHandler = difficultyHandler;
}

// Returns enemy depending on index
Table* TableHandler::GetTable(int index)
{
	return &_tables[index];
}

int TableHandler::GetNumTables()
{
	return _difficultyHandler->GetNumTables();
}

// Creates enemies depending on the side of the screen
void TableHandler::Create(float xMin, float xMax, float yMin, float yMax)
{
	_posXMin = xMin;
	_posXMax = xMax;
	_posYMin = yMin;
	_posYMax = yMax;
	
	//Create enemies
	for (int i = 0; i < NUM_TABLES; i++)
	{
		// Select girl or granma
		float posX = Play::RandomRollRange(_posXMin, _posXMax);
		float posY = Play::RandomRollRange(_posYMin, _posYMax);

		// Create the enemy
		_tables[i] = Table(TYPE_TABLE, table, posX, posY, "gm", 10, 1.f, 0.f);
			
		// Each enemy is associated with a food object, the food object changes sprite
		//_foodHandler->GetFood(i)->SetEnemy(&_enemies[i]);
		//_enemies[i].SetFood(_foodHandler->GetFood(i));
	}
}

// This functions displays and animates each enemy, also
// checks the state to restart enemies
void TableHandler::Display()
{
	int loopLimit = _difficultyHandler->GetNumTables();

	for (int i = 0; i < loopLimit; i++)
	{
		_tables[i].Display();
	}
}

void TableHandler::ReStart()
{
	for (int i = 0; i < NUM_ENEMIES; i++)
	{
		_tables[i].ReStart();
	}
}

