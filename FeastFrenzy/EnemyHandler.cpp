//
//  EnemyHandler.cpp
//  Feast Frenzy game
//
//  Created by Oscar Martinez on 1/Apr/2024.
//
#define PLAY_USING_GAMEOBJECT_MANAGER
#include "Play.h"
#include "EnemyHandler.h"
#include "SpritesDefinitions.h"
#include "CharacterEnemy.h"
#include "FoodHandler.h"
#include "DifficultyHandler.h"

EnemyHandler::EnemyHandler()
{
	_foodHandler = nullptr;
	_difficultyHandler = nullptr;
}

// Sets the food handler to pass references of food to the enemies
void EnemyHandler::SetFoodHandler(FoodHandler* foodHandler)
{
	_foodHandler = foodHandler;
	_difficultyHandler = nullptr;
}

// Sets the food handler to pass references of food to the enemies
void EnemyHandler::SetDifficultyHandler(DifficultyHandler* difficultyHandler)
{
	_difficultyHandler = difficultyHandler;
}

// Returns enemy depending on index
CharacterEnemy* EnemyHandler::GetEnemy(int index)
{
	return &_enemies[index];
}

// Creates enemies depending on the side of the screen
void EnemyHandler::Create(int screenPosition)
{
	_screenPosition = screenPosition;
	int initSprite = 0;
	ObjectDirection direction = DIRECTION_DOWN;

	switch (_screenPosition)
	{
	case DIRECTION_UP:
		break;
	case DIRECTION_DOWN:
		break;
	case DIRECTION_LEFT:
		// Sets initial movement limits, direction and sprite for the left side of the screen
		_posXMin = -50;
		_posXMax = 50;
		_posYMin = 110;
		_posYMax = 500;
		// Enemy will move from out of the screen to appear
		direction = DIRECTION_RIGHT;
		//initSprite = girl1_wrh_8;
		break;
	case DIRECTION_RIGHT:
		// Sets initial movement limits, direction and sprite for the right side of the screen
		_posXMin = 1280+50;
		_posXMax = 1280-50;
		_posYMin = 110;
		_posYMax = 500;
		// Enemy will move from out of the screen to appear
		direction = DIRECTION_LEFT;
		//initSprite = girl1_wlh_8;
		break;
	}
	//Create enemies
	for (int i = 0; i < NUM_ENEMIES; i++)
	{
		// Select girl or granma
		int enemyType = Play::RandomRollRange(0, 100);

		// Set initial sprite depending on start screen position
		switch (_screenPosition)
		{
		case DIRECTION_UP:
			break;
		case DIRECTION_DOWN:
			break;
		case DIRECTION_LEFT:
			if (enemyType < 50)
			{
				initSprite = girl1_wrh_8;
			}
			else
			{
				initSprite = gm1_wrh_8;
			}
			break;
		case DIRECTION_RIGHT:
			if (enemyType < 50)
			{
				initSprite = girl1_wlh_8;
			}
			else
			{
				initSprite = gm1_wlh_8;
			}
			break;
		}

		switch (_screenPosition)
		{
		case DIRECTION_UP:
			break;
		case DIRECTION_DOWN:
			break;
		case DIRECTION_LEFT:
			// Sets initial position, position in Y axis is set randomly
			_yPosIni = (float)Play::RandomRollRange((int)_posYMin,(int)_posYMax);
			_xPosIni = -100.0f;
			break;
		case DIRECTION_RIGHT:
			// Sets initial position, position in Y axis is set randomly
			_yPosIni = (float)Play::RandomRollRange((int)_posYMin, (int)_posYMax);
			_xPosIni = 1280+100.0f;
			break;
		}

		_originalDirection[i] = direction;

		// The type is selected between TYPE_ENEMY_START and TYPE_ENEMY_END, each screen side
		// has a range alocated
		GameObjectType goType = (GameObjectType)((screenPosition * 4) + TYPE_ENEMY_START + i);

		if ( enemyType < 50)
		{
			// Create the enemy
			_enemies[i] = CharacterEnemy(goType, initSprite, _xPosIni, _yPosIni, "girl", 45, 0.5f, 2.5f, (ObjectDirection)screenPosition, i);
			// Sets walking sprites
			_enemies[i].SetWalkSprites(girl1_wu_8, girl1_wd_8, girl1_wl_8, girl1_wr_8, 3.5f, 0.5f);
			// Sets walking while holding sprites
			_enemies[i].SetWalkHoldSprites(girl1_wuh_8, girl1_wdh_8, girl1_wlh_8, girl1_wrh_8, 3.5f, 0.5f);
			// Sets throw sprites
			_enemies[i].SetThrowSprites(girl1_pu_3, girl1_pd_3, girl1_pl_3, girl1_pr_3, 0.3f);
		}
		else
		{
			// Create the enemy
			_enemies[i] = CharacterEnemy(goType, initSprite, _xPosIni, _yPosIni, "gm", 45, 0.5f, 2.5f, (ObjectDirection)screenPosition, i);
			// Sets walking sprites
			_enemies[i].SetWalkSprites(gm1_wu_8, gm1_wd_8, gm1_wl_8, gm1_wr_8, 3.5f, 0.5f);
			// Sets walking while holding sprites
			_enemies[i].SetWalkHoldSprites(gm1_wuh_8, gm1_wdh_8, gm1_wlh_8, gm1_wrh_8, 3.5f, 0.5f);
			// Sets throw sprites
			_enemies[i].SetThrowSprites(gm1_pu_3, gm1_pd_3, gm1_pl_3, gm1_pr_3, 0.3f);
		}
		// Sets initial velocity and direction
		_enemies[i].SetVelDir(direction, 3.5f, 0.5f);
		// Sets intial animation state
		_enemies[i].SetAnimationState(PLAYER_STATE_WALK_HOLD);
		// Sets initial movement limits
		_enemies[i].SetLimits(_posXMax, 0.0f);
		// Sets initial direction
		_enemies[i].SetCurrentDirection(direction);
		// Each enemy is associated with a food object, the food object changes sprite
		_foodHandler->GetFood(i)->SetEnemy(&_enemies[i]);
		_enemies[i].SetFood(_foodHandler->GetFood(i));
	}
}

// This functions displays and animates each enemy, also
// checks the state to restart enemies
void EnemyHandler::Display()
{
	int loopLimit = _difficultyHandler->GetNumEnemies();

	for (int i = 0; i < loopLimit; i++)
	{
		// If enemy is out of the screen and food as well
		// of if enemy is out of screen and food was catched
		// restart the enemy, if the food went out of the screen enemy will
		// throw it again, if not enemy will just wander to be hit
		if (_enemies[i].GetState() == ENEMY_IDLE && (_enemies[i].GetFoodState() == FOOD_IDLE || _enemies[i].GetFoodState() == FOOD_CARRIED_PLAYER))
		{
			// Set initial position
			_enemies[i].SetVelDir(_originalDirection[i], 3.5f, 0.5f);
			// Set initial state
			_enemies[i].SetAnimationState(PLAYER_STATE_WALK_HOLD);
			// Set initial limits
			_enemies[i].SetLimits(_posXMax, 0.0f);
			// Set original direction
			_enemies[i].SetCurrentDirection(_originalDirection[i]);
			// Restart, set a flag if enemy's food was catched
			_enemies[i].ReStart(_originalDirection[i], _enemies[i].GetFoodState() != FOOD_CARRIED_PLAYER);
		}
		else
		{
			_enemies[i].Animate();
		}
	}
}

void EnemyHandler::ReStart()
{
	for (int i = 0; i < NUM_ENEMIES; i++)
	{
		// Set initial position
		_enemies[i].SetVelDir(_originalDirection[i], 3.5f, 0.5f);
		// Set initial state
		_enemies[i].SetAnimationState(PLAYER_STATE_WALK_HOLD);
		// Set initial limits
		_enemies[i].SetLimits(_posXMax, 0.0f);
		// Set original direction
		_enemies[i].SetCurrentDirection(_originalDirection[i]);
		// Restart, set a flag if enemy's food was catched
		_enemies[i].ReStart(_originalDirection[i], true);
	}
}

