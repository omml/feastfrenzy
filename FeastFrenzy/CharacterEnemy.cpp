//
//  CharacerEnemy.cpp
//  Feast Frenzy game
//
//  Created by Oscar Martinez on 1/Apr/2024.
//
#define PLAY_USING_GAMEOBJECT_MANAGER
#include "Play.h"
#include "CharacterEnemy.h"


CharacterEnemy::CharacterEnemy()
{
	_offset = 0;
	_enemyState = ENEMY_INIT;
	_xLimit = 0.0f;
	_yLimit = 0.0f;
	_counter = 0;
	_maxCounter = 0;
	_restartFood = true;
}
CharacterEnemy::CharacterEnemy(GameObjectType go_type, int sprite, float posX, float posY, const char name[], int colRad, float scale, float animSpeed, ObjectDirection screenSide, int offset) :
	Character(go_type, sprite, posX, posY, name, colRad, scale, animSpeed)
{
	_screenSide = screenSide;
	_offset = offset;
	_enemyState = ENEMY_INIT;
	_xLimit = 0.0f;
	_yLimit = 0.0f;
	_counter = 0;
	_maxCounter = Play::RandomRoll(4);
	_restartFood = true;
}

FoodState CharacterEnemy::GetFoodState()
{
	return _food->GetState();
}

EnemyState CharacterEnemy::GetState()
{
	return _enemyState;
}

void CharacterEnemy::ReStart(ObjectDirection dir, bool resFood)
{
	_enemyState = ENEMY_INIT;
	_maxCounter = Play::RandomRoll(4);
	_restartFood = resFood;
	if (_restartFood == true)
	{
		// Next time it respawns set animation walking holding again the food
		SetSprite(_walkingHoldingSprites[dir]._spriteName, _walkingHoldingSprites[dir]._animSpeed);
		_food->ReStart();
	}
	else
	{
		// Next time it respawns set animation to walking as player is carrying the
		SetSprite(_walkingSprites[dir]._spriteName, _walkingSprites[dir]._animSpeed);
	}
}

void CharacterEnemy::SetFood(Food* food)
{
	_food = food;
}

// Sets the limit so the enemy moves up to that limit
void CharacterEnemy::SetLimits(float x, float y)
{
	_xLimit = x;
	_yLimit = y;
}

// Checks if the enemy has reached a position set as limit
bool CharacterEnemy::HasReachedLimit()
{
	bool retVal = false;

	// Gets the current position depending on the direction
	float pos = GetPosition(_currentDirection);

	// Checks depending on the enemy direction
	switch (_currentDirection)
	{
	case DIRECTION_RIGHT:
		if (pos >= _xLimit)
		{
			retVal = true;
		}
		break;
	case DIRECTION_LEFT:
		if (pos <= _xLimit)
		{
			retVal = true;
		}
		break;
	case DIRECTION_UP:
		if (pos >= _yLimit)
		{
			retVal = true;
		}
		break;
	case DIRECTION_DOWN:
		if (pos <= _yLimit)
		{
			retVal = true;
		}
		break;
	}

	return retVal;
}

void CharacterEnemy::LaunchFood()
{
	_food->Throw(_currentDirection, 7.5f, false);
}

// When enemy as thrown food and disapeared it comes back in a different position 
void CharacterEnemy::ChangeInitPosition()
{
	float xPosIni, yPosIni,posXMin,posXMax,posYMin,posYMax;

	switch (_screenSide)
	{
	case DIRECTION_UP:
		break;
	case DIRECTION_DOWN:
		break;
	case DIRECTION_LEFT:
		posXMin = -50;
		posXMax = 50;
		posYMin = 110;
		posYMax = 500;
		yPosIni = (float)Play::RandomRollRange((int)posYMin, (int)posYMax);
		xPosIni = -100.0f;
		break;
	case DIRECTION_RIGHT:
		posXMin = 1280 + 50;
		posXMax = 1280 - 50;
		posYMin = 110;
		posYMax = 500;
		yPosIni = (float)Play::RandomRollRange((int)posYMin, (int)posYMax);
		xPosIni = 1280 + 100.0f;
		break;
	}
	Play::GameObject& go = Play::GetGameObject(_gameObjectId);

	go.pos = { xPosIni, yPosIni };

}

// This is the main state machine to control the enemy
void CharacterEnemy::Animate()
{
	int r = 0;
	_oldAnimationState = _animationState;

	// Does something depending on the state
	switch (_enemyState)
	{
	case ENEMY_INIT:

		// Moves near the table
		if (HasReachedLimit())
		{
			// Stops moving and animation
			DisplayStop();
			// Changes to the next state
			// Player is not holding the food
			if (_restartFood == true)
			{
				_enemyState = ENEMY_PREPARE_ATTACK;
			}
			else
			{
				_enemyState = ENEMY_CHANGE_DIRECTION;
			}
		}
		else
		{
			Display();
		}
		break;
	case ENEMY_PREPARE_ATTACK:
		// Prepares to display the attack sprite
		_spriteState = SPRITE_STATE_INIT;
		// Changes the sprite for the one throwing
		DisplaySingleSpriteAnimation(_throwSprites[_currentDirection]._spriteName, _throwSprites[_currentDirection]._animSpeed, 3);
		// Changes the state to let do the throwing animation
		_enemyState = ENEMY_ATTACK;
		//Sets velocity to the food so it launches
		LaunchFood();
		Play::PlayAudio("throw");
		break;
	case ENEMY_ATTACK:
		// Display the throw animation and wait for it to finish
		DisplaySingleSpriteAnimation(0.0f, 3);
		if (_spriteState == SPRITE_STATE_FINISHED)
		{
			// When it finishes move
			_enemyState = ENEMY_CHANGE_DIRECTION;
		}
		break;
	case ENEMY_CHANGE_DIRECTION:
		
		// Decide randmly to go up or down
		r = Play::RandomRoll(100);

		if (r < 50)
		{
			// Changes sprite depending on direction
			DisplayChangeDir(_walkingSprites[DIRECTION_UP]._spriteName, DIRECTION_UP, _walkingSprites[DIRECTION_UP]._moveSpeed, _walkingSprites[DIRECTION_UP]._animSpeed);
			// Sets the limits so it changes state when reaches them
			SetLimits(100, 500);
			// Changes the state and direction
			_enemyState = ENEMY_MOVE_UP;
			_currentDirection = DIRECTION_UP;
		}
		else
		{
			// Changes sprite depending on direction
			DisplayChangeDir(_walkingSprites[DIRECTION_DOWN]._spriteName, DIRECTION_DOWN, _walkingSprites[DIRECTION_DOWN]._moveSpeed, _walkingSprites[DIRECTION_DOWN]._animSpeed);
			// Sets the limits so it changes state when reaches them
			SetLimits(100, 100);
			// Changes the state and direction
			_enemyState = ENEMY_MOVE_DOWN;
			_currentDirection = DIRECTION_DOWN;
		}
		break;
	case ENEMY_MOVE_DOWN:
	case ENEMY_MOVE_UP:
		// Check if has reached the limit
		if (HasReachedLimit())
		{
			// It reached the limit, so stop moving and animating
			DisplayStop();
			// Increase the counter of loops
			_counter++;
			// Check if the loops are more than the max, the max is set randomly
			if (_counter > _maxCounter)
			{
				// Set sprites to move out of the screen acoording to the side of the screen it appeared from 
				DisplayChangeDir(_walkingSprites[_screenSide]._spriteName, _screenSide, _walkingSprites[_screenSide]._moveSpeed, _walkingSprites[_screenSide]._animSpeed);
				// Set all to move out of the screen
				switch (_screenSide)
				{
				case DIRECTION_RIGHT:
					SetLimits(1280 + 50, 500);
					_currentDirection = DIRECTION_RIGHT;
					break;
				case DIRECTION_LEFT:
					SetLimits(-50, 500);
					_currentDirection = DIRECTION_LEFT;
					break;
				}
				_enemyState = ENEMY_END;
			}
			else
			{
				// Finished current loop, change direction
				_enemyState = ENEMY_CHANGE_DIRECTION;
			}
		}
		else
		{
			Display();
		}
		break;
	case ENEMY_END:
		if (HasReachedLimit())
		{
			// It is out of the screen stop animation
			DisplayStop();
			// Calculate new position to come back again
			ChangeInitPosition();

			// Wait for enemy handler to restart this enemy
			_enemyState = ENEMY_IDLE;
		}
		else
		{
			// Keep moving to get out of the screen
			Display();
		}
		break;
	}
}
