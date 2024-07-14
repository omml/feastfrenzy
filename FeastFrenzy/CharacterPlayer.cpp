//
//  CharacterPlayer.cpp
//  Feast Frenzy game
//
//  Created by Oscar Martinez on 1/Apr/2024.
//
#define PLAY_USING_GAMEOBJECT_MANAGER
#include "Play.h"
#include "CharacterPlayer.h"
#include "CommonDefinitions.h"


CharacterPlayer::CharacterPlayer()
{
	_catched = false;
}

CharacterPlayer::CharacterPlayer(GameObjectType go_type, int sprite, float posX, float posY, const char name[], int colRad, float scale, float animSpeed) :
	Character(go_type, sprite, posX, posY, name, colRad, scale, animSpeed)
{
	_catched = false;
}

void CharacterPlayer::SetTableHandler(TableHandler* tableHandler)
{
	_tableHandler = tableHandler;
}

// Function to get user input
int CharacterPlayer::GetKeyDown()
{
	int retVal = -1;
	if (Play::KeyDown(Play::KEY_SPACE))
	{
		retVal = PLAYER_PRESSED_SPACE;
	}
	else if (Play::KeyDown(Play::KEY_UP))
	{
		retVal = PLAYER_PRESSED_UP;
	}
	else if (Play::KeyDown(Play::KEY_LEFT))
	{
		retVal = PLAYER_PRESSED_LEFT;
	}
	else if (Play::KeyDown(Play::KEY_RIGHT))
	{
		retVal = PLAYER_PRESSED_RIGHT;
	}
	else if (Play::KeyDown(Play::KEY_DOWN))
	{
		retVal = PLAYER_PRESSED_DOWN;
	}
	else
	{
		retVal = PLAYER_PRESSED_NONE;
	}
	return retVal;
	
}

// Function to check that the player keeps in the rectangle in the middle
void CharacterPlayer::CheckPlayingArea()
{
	Play::GameObject& obj = Play::GetGameObject(_gameObjectId);

	if (obj.pos.x > 1130.0f)
	{
		obj.pos = { 1130.0f, obj.pos.y };
	}
	if (obj.pos.x < 150.0f)
	{
		obj.pos = { 150.0f, obj.pos.y };
	}
	if (obj.pos.y > 510.0f)
	{
		obj.pos = { obj.pos.x, 510.0f };
	}
	if (obj.pos.y < 140.0f)
	{
		obj.pos = { obj.pos.x, 140.0f };
	}
}

// Function to check that the player keeps in the rectangle in the middle
void CharacterPlayer::CheckObjectsInPlayingArea()
{
	Play::GameObject& player = Play::GetGameObject(_gameObjectId);

	Play::Vector2f playerSize = GetSpriteSize();

	int numTables = _tableHandler->GetNumTables();

	for (int i = 0; i < numTables; i++)
	{
		Table* t = _tableHandler->GetTable(i);

		Play::GameObject& table = Play::GetGameObject(t->GetObjectId());

		//check if the food and the player are colliding
		if (Play::IsColliding(table, player))
		{
			Play::Vector2f tableSize = t->GetSpriteSize();

			switch (_currentDirection)
			{
			case DIRECTION_RIGHT:
				player.pos = { table.pos.x - 30.f, player.pos.y };
				break;
			case DIRECTION_LEFT:
				player.pos = { table.pos.x + 30.f, player.pos.y };
				break;
			case DIRECTION_UP:
				player.pos = { player.pos.x,  table.pos.y - 30.f };
				break;
			case DIRECTION_DOWN:
				player.pos = { player.pos.x,  table.pos.y + 30.f };
				break;
			}

			break;
		}
	}
}

// Returns the current animation state
PlayerAnimationState CharacterPlayer::GetAnimationState()
{
	return _animationState;
}

// If the player catches a food item keep a reference to 
// Food object so it can be thrown later
void CharacterPlayer::SetCatch(bool val, Food* food)
{
	_catched = val;
	_food = food;
}

// Return if the player has catched a food item
bool CharacterPlayer::GetCatch()
{
	return _catched;
}

void CharacterPlayer::LaunchFood()
{
	// It is no longer catghing so reset
	_catched = false;
	// Throw food but tell it was from the player
	_food->Throw(_currentDirection, 7.5f, true);
}

// This function has the state machine for the player
void CharacterPlayer::HandlePlayerControls()
{
	int input;
	_oldDirection = _currentDirection;

	CheckPlayingArea();

	CheckObjectsInPlayingArea();

	switch (_animationState)
	{
	case PLAYER_STATE_IDLE:
		// The character is waiting for player input
		input = GetKeyDown();
		switch (input)
		{
		case PLAYER_PRESSED_NONE:
			Display();
			break;
		case PLAYER_PRESSED_UP:
		case PLAYER_PRESSED_DOWN:
		case PLAYER_PRESSED_LEFT:
		case PLAYER_PRESSED_RIGHT:
			// Change sprite depending on direction and change state
			_currentDirection = (ObjectDirection)input;
			DisplayChangeDir(_walkingSprites[_currentDirection]._spriteName, _currentDirection, _walkingSprites[_currentDirection]._moveSpeed, _walkingSprites[_currentDirection]._animSpeed);
			_animationState = PLAYER_STATE_WALK;
			break;
		case PLAYER_PRESSED_SPACE:
			// Start preparation to display catch animation
			DisplayStop();
			// Changes to the next state
			_animationState = PLAYER_STATE_PREPARE_CATCH;
			break;
		}
		break;
	case PLAYER_STATE_WALK:
		// Character is wakling, check player input
		input = GetKeyDown();
		switch (input)
		{
		case PLAYER_PRESSED_NONE:
			// Player stopped pressing an arrow then stop moving and the animation
			DisplayStop();
			// Change to idle state
			_animationState = PLAYER_STATE_IDLE;
			break;
		case PLAYER_PRESSED_UP:
		case PLAYER_PRESSED_DOWN:
		case PLAYER_PRESSED_LEFT:
		case PLAYER_PRESSED_RIGHT:
			if (_oldDirection == _currentDirection)
			{
				// Player kept pressing arrow key on the same direction
				Display();
			}
			else
			{
				// Player pressed a different arrow key
				// Change sprite and direction
				_currentDirection = (ObjectDirection)input;
				DisplayChangeDir(_walkingSprites[_currentDirection]._spriteName, _currentDirection, _walkingSprites[_currentDirection]._moveSpeed, _walkingSprites[_currentDirection]._animSpeed);
			}
			break;
		case PLAYER_PRESSED_SPACE:
			// Stop current animation to prepare for catch animation
			DisplayStop();
			// Changes to the next state
			_animationState = PLAYER_STATE_PREPARE_CATCH;
			break;
		}
		break;
	case PLAYER_STATE_PREPARE_CATCH:
		// Prepares to display the attack sprite
		_spriteState = SPRITE_STATE_INIT;
		// Changes the sprite for the one throwing
		DisplaySingleSpriteAnimation(_catchSprites[_currentDirection]._spriteName, _catchSprites[_currentDirection]._animSpeed, 3);
		// Changes the state to let do the throwing animation
		_animationState = PLAYER_STATE_CATCH;
		break;
	case PLAYER_STATE_CATCH:
		// Display the throw animation and wait for it to finish
		DisplaySingleSpriteAnimation(0.0f, 3);
		if (_spriteState == SPRITE_STATE_FINISHED)
		{
			if (_catched == false)
			{
				// Player did not catch food, animate the hands down
				// _catched is set by the food class collision detection
				DisplayStop();
				// Changes to the next state
				_animationState = PLAYER_STATE_PREPARE_DOWN;
			}
			else
			{
				// Player catched food, change the sprites to holding
				// and reset catched variable
				_catched = false;
				DisplaySingleSpriteAnimation(_walkingHoldingSprites[_currentDirection]._spriteName, _walkingHoldingSprites[_currentDirection]._animSpeed, 0);
				_animationState = PLAYER_STATE_IDLE_HOLD;
			}
		}
		break;
	case PLAYER_STATE_PREPARE_DOWN:
		// Prepares to display the attack sprite
		_spriteState = SPRITE_STATE_INIT;
		// Changes the sprite for the one throwing
		DisplaySingleSpriteAnimation(_throwSprites[_currentDirection]._spriteName, _throwSprites[_currentDirection]._animSpeed, 3);
		// Changes the state to let do the throwing animation
		_animationState = PLAYER_STATE_DOWN;
		break;
	case PLAYER_STATE_DOWN:
		// Display the throw animation and wait for it to finish
		DisplaySingleSpriteAnimation(0.0f, 3);
		if (_spriteState == SPRITE_STATE_FINISHED)
		{
			// Sets idle animation
			DisplaySingleSpriteAnimation(_walkingSprites[_currentDirection]._spriteName, _walkingSprites[_currentDirection]._animSpeed, 3);
			// Changes to the next state
			_animationState = PLAYER_STATE_IDLE;
		}
		break;
	case PLAYER_STATE_IDLE_HOLD:
		// Character is holding food, but not moving
		// Wait for user input
		input = GetKeyDown();
		switch (input)
		{
		case PLAYER_PRESSED_NONE:
			// Keep drawing the character holding
			Display();
			break;
		case PLAYER_PRESSED_UP:
		case PLAYER_PRESSED_DOWN:
		case PLAYER_PRESSED_LEFT:
		case PLAYER_PRESSED_RIGHT:
			// Change sprite for walking holding
			_currentDirection = (ObjectDirection)input;
			DisplayChangeDir(_walkingHoldingSprites[_currentDirection]._spriteName, _currentDirection, _walkingHoldingSprites[_currentDirection]._moveSpeed, _walkingHoldingSprites[_currentDirection]._animSpeed);
			_animationState = PLAYER_STATE_WALK_HOLD;
			break;
		case PLAYER_PRESSED_SPACE:
			// Stop current animation and movement to prepare for throwing food animation
			DisplayStop();

			// Changes to the next state
			_animationState = PLAYER_STATE_PREPARE_ATTACK;
			break;
		}
		break;
	case PLAYER_STATE_WALK_HOLD:
		// The character is walking holding food
		// Check the player input
		input = GetKeyDown();
		switch (input)
		{
		case PLAYER_PRESSED_NONE:
			// Player stopped pressing arrows
			// Stop movement and animation
			DisplayStop();
			_animationState = PLAYER_STATE_IDLE_HOLD;
			break;
		case PLAYER_PRESSED_UP:
		case PLAYER_PRESSED_DOWN:
		case PLAYER_PRESSED_LEFT:
		case PLAYER_PRESSED_RIGHT:
			if (_oldDirection == _currentDirection)
			{
				// Player still going in same direction
				Display();
			}
			else
			{
				// Player changed direction, then change sprite
				_currentDirection = (ObjectDirection)input;
				DisplayChangeDir(_walkingHoldingSprites[_currentDirection]._spriteName, _currentDirection, _walkingHoldingSprites[_currentDirection]._moveSpeed, _walkingHoldingSprites[_currentDirection]._animSpeed);
			}
			break;
		case PLAYER_PRESSED_SPACE:
			// Player wants to throw the food, stop animation and movement
			DisplayStop();

			// Changes to the next state to prepare for throwing animation
			_animationState = PLAYER_STATE_PREPARE_ATTACK;
			break;
		}
		break;
	case PLAYER_STATE_PREPARE_ATTACK:
		// Prepares to display the attack sprite
		_spriteState = SPRITE_STATE_INIT;
		// Changes the sprite for the one throwing
		DisplaySingleSpriteAnimation(_throwSprites[_currentDirection]._spriteName, _throwSprites[_currentDirection]._animSpeed, 3);
		// Changes the state to let do the throwing animation
		_animationState = PLAYER_STATE_ATTACK;
		//Sets velocity to the food so it launches
		LaunchFood();
		// Play throw sound
		Play::PlayAudio("throw");
		break;
	case PLAYER_STATE_ATTACK:
		// Display the throw animation and wait for it to finish
		DisplaySingleSpriteAnimation(0.0f, 3);
		if (_spriteState == SPRITE_STATE_FINISHED)
		{
			// When it finishes move
			_animationState = PLAYER_STATE_IDLE;
		}
		break;
	}
}
