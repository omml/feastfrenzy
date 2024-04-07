//
//  Food.cpp
//  Feast Frenzy game
//
//  Created by Oscar Martinez on 1/Apr/2024.
//
#define PLAY_USING_GAMEOBJECT_MANAGER
#include "Play.h"
#include "Food.h"
#include "CharacterEnemy.h"
#include "CharacterPlayer.h"
#include "SpritesDefinitions.h"

// Main class for Food items
Food::Food() : MainGameObject()
{
	_offset = 0;
	_state = FOOD_CARRIED_ENEMY;
	_enemy = nullptr;
	_player = nullptr;
	_score = nullptr;
}

Food::Food(GameObjectType go_type, int sprite, float posX, float posY, const char name[], int colRad, float scale, float animSpeed, int offset, int dirOffset) :
		MainGameObject(go_type, sprite, posX, posY, name, colRad, scale, animSpeed)
{
	_offset = offset;
	_directionOffset = dirOffset;
	_state = FOOD_CARRIED_ENEMY;
	_enemy = nullptr;
	_player = nullptr;
	_score = nullptr;
}

// Returns food's state
FoodState Food::GetState()
{
	return _state;
}

// Sets reference to the score object
void Food::SetScoreObject(ScoreHolder* score)
{
	_score = score;
}

// Restart the food, 
void Food::ReStart()
{
	// Selects a random sprite
	int r = Play::RandomRollRange(f_bk_n, f_tm_n);

	// Sets the sprite
	SetSprite(r, 0.0f);

	// Resets flag to indicate who throw the food for collision detection
	_fromPlayer = false;

	// Sets initial food state
	_state = FOOD_CARRIED_ENEMY;

	// Sprite state for when displaying splat
	_spriteState = SPRITE_STATE_INIT;
}

// Sets reference to the enemy is carrying the food
void Food::SetEnemy(CharacterEnemy* enemy)
{
	_enemy = enemy;
}

// Sets refence to the player in case player catches the food
void Food::SetPlayer(CharacterPlayer* player)
{
	_player = player;
}

// Displays the food on top of the character depending on character's direction
void Food::DisplayCarriedPosition()
{
	bool isPlayer = false;
	float posX = 0.0f;
	float posY = 0.0f;
	ObjectDirection dir = DIRECTION_RIGHT;

	// Gets the food object
	Play::GameObject& food = Play::GetGameObjectByType(TYPE_FOOD_START + _offset + _directionOffset);
	// Gets the enemy object
	Play::GameObject& enemy = Play::GetGameObjectByType(TYPE_ENEMY_START + _offset + _directionOffset);
	// Gets the player object
	Play::GameObject& player = Play::GetGameObjectByType(TYPE_BOY_P);


	if (_state == FOOD_CARRIED_ENEMY)
	{
		// If food is carried by an enemy get its position and direction

		posX = enemy.pos.x;
		posY = enemy.pos.y;

		dir = _enemy->GetCurrentDirection();
	}
	else
	{
		// If food is carried by the player get its position and direction

		isPlayer = true;
		posX = player.pos.x;
		posY = player.pos.y;

		dir = _player->GetCurrentDirection();
	}

	// Depending on holders direction, position the food over the head
	switch (dir)
	{
	case DIRECTION_UP:
		if (isPlayer == false)
		{
			food.pos = { posX, posY + 40.0f };
		}
		else
		{
			food.pos = { posX, posY + 40.0f };
		}
		break;
	case DIRECTION_DOWN:
		if (isPlayer == false)
		{
			food.pos = { posX, posY + 35.0f };
		}
		else
		{
			food.pos = { posX, posY + 30.0f };
		}
		break;
	case DIRECTION_RIGHT:
		if (isPlayer == false)
		{
			food.pos = { posX + 10.0f, posY + 40.0f };
		}
		else
		{
			food.pos = { posX + 12.5f, posY + 35.0f };
		}
		break;
	case DIRECTION_LEFT:
		if (isPlayer == false)
		{
			food.pos = { posX - 10.0f, posY + 40.0f };
		}
		else
		{
			food.pos = { posX - 12.5f, posY + 35.0f };
		}
		break;
	}

	// Updates and displays the food object
	Play::UpdateGameObject(food);
	Play::DrawObjectRotated(food);
}

// Throws the food, changes the food state, this function
// will be hanged by enemy or player
void Food::Throw(ObjectDirection dir, float moveSpeed, bool fromPlayer)
{
	// Sets direction and speed
	SetVelDir(dir, moveSpeed, 0.0f);
	_state = FOOD_FLYING;
	_fromPlayer = fromPlayer;
}

// Checks wheather food is out of screen
bool Food::IsOutsideScreen()
{
	bool retVal = false;

	Play::GameObject& obj = Play::GetGameObject(_gameObjectId);

	if (obj.pos.x > 1280.0f || obj.pos.x < 0.0f || obj.pos.y > 720.0f || obj.pos.y < 0.0f)
	{
		retVal = true;
	}
	
	return retVal;
}

// Checks if food collided with player and the food was thrown by an enemy
bool Food::IsCollidingWithPlayer()
{
	bool retVal = false;

	if (_fromPlayer == false)
	{
		Play::GameObject& food = Play::GetGameObject(_gameObjectId);
		Play::GameObject& player = Play::GetGameObjectByType(TYPE_BOY_P);

		//check if the food and the player are colliding
		if (Play::IsColliding(food, player))
		{
			retVal = true;
		}
	}
	
	return retVal;
}

// Checks if food collided with an enemy and the food was thrown by the player
bool Food::IsCollidingWithEnemies()
{
	bool retVal = false;

	if (_fromPlayer == true)
	{
		Play::GameObject& food = Play::GetGameObject(_gameObjectId);

		// Loop trough all players 
		for (int i = TYPE_ENEMY_START; i < TYPE_ENEMY_END; i++)
		{
			Play::GameObject& enemy = Play::GetGameObjectByType(i);

			//check if the food and the enemy are colliding
			if (Play::IsColliding(food, enemy))
			{
				retVal = true;
				break;
			}
		}
	}

	return retVal;
}

// Handle food animation depending on state
void Food::Animate()
{
	switch (_state)
	{
	case FOOD_CARRIED_PLAYER:
	case FOOD_CARRIED_ENEMY:
		// Food is being carried, display it on top of character
		DisplayCarriedPosition();
		break;
	case FOOD_FLYING:
		// Food was thrown display and move it
		Display();
		
		if (IsCollidingWithPlayer())
		{
			// Food collided with player, check if player pressed space bar to catch
			PlayerAnimationState playerAnimState = _player->GetAnimationState();
			if (_player->GetCatch() == false && (playerAnimState == PLAYER_STATE_PREPARE_CATCH || playerAnimState == PLAYER_STATE_CATCH))
			{
				// Food was catched, stop movement
				DisplayStop();
				// Change food state to display it on top of character
				_state = FOOD_CARRIED_PLAYER;

				// Tell the player it catched food and set a reference to it
				// so later player can throw it
				_player->SetCatch(true, this);
			}
			else
			{
				// Decreases the score as player was hit
				_score->DecScore();

				Display();
				// Prepare to display the splat animation
				_state = FOOD_PREPARE_HIT;
			}
		}
		else if (IsCollidingWithEnemies())
		{
			// Increases the score as player hit an enemy
			_score->IncScore();

			Display();
			// Prepare to display the splat animation
			_state = FOOD_PREPARE_HIT;
		}
		else if (IsOutsideScreen())
		{
			//Checked if outside of the screen

			// Stop moving and set to idle so it can be restarted
			DisplayStop();
			_state = FOOD_IDLE;
		}
		break;
	case FOOD_PREPARE_HIT:
		// Prepares to display the attack sprite
		_spriteState = SPRITE_STATE_INIT;
		// Changes the sprite for one of the splats randomly
		DisplaySingleSpriteAnimation(Play::RandomRollRange(exp26_b_16,exp32_b_16), 64.0f,8);
		_state = FOOD_HIT;
		Play::PlayAudio("hit");
		break;
	case FOOD_HIT:
		// Display the splat animation and wait for it to finish
		DisplaySingleSpriteAnimation(64.0f, 8);
		if (_spriteState == SPRITE_STATE_FINISHED)
		{
			// When it finishes sets food to idle so it can be restarted
			_state = FOOD_IDLE;
		}
		break;
	case FOOD_IDLE:
		break;
	}
}
