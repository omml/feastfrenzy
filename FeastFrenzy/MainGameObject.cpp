//
//  MainGameObject.cpp
//  Feast Frenzy game
//
//  Created by Oscar Martinez on 1/Apr/2024.
//
#define PLAY_USING_GAMEOBJECT_MANAGER
#include "Play.h"
#include "MainGameObject.h"
#include "SpritesDefinitions.h"
#include "FileNamesHolder.h"


MainGameObject::MainGameObject()
{
	_gameObjectId = -1;
	_gameObjectType = TYPE_NULL;
	_currentDirection = DIRECTION_DOWN;
	_oldDirection = DIRECTION_DOWN;
	_animationFinished = false;
	_spriteState = SPRITE_STATE_FINISHED;
}

// Creates a gameobject and sets its sprite reade to be displayed
MainGameObject::MainGameObject(GameObjectType go_type, int sprite, float posX, float posY, const char name[], int colRad, float scale, float animSpeed)
{
	// Stores initial position for when game is restarted
	_iniPosX = posX;
	_iniPosY = posY;
	// Sets the gameobject type
	_gameObjectType = go_type;
	// Creates the Play Buffer object
	_gameObjectId = Play::CreateGameObject(_gameObjectType, { posX, posY }, colRad, name);
	// Sets intial values
	_currentDirection = DIRECTION_DOWN;
	_oldDirection = DIRECTION_DOWN;
	_animationFinished = false;
	_spriteState = SPRITE_STATE_FINISHED;
	_iniAnimSpeed = animSpeed;

	// Sets scale and sprite
	Play::GameObject& obj = Play::GetGameObject(_gameObjectId);
	obj.scale = scale;
	Play::SetSprite(obj, FileNamesHolder::fileNames[sprite], animSpeed);
}

// Creates a gameobject and sets its sprite reade to be displayed, sets velocity
MainGameObject::MainGameObject(GameObjectType go_type, int sprite, float posX, float posY, float velX, float velY, const char name[], int colRad, float scale, float animSpeed)
{
	// Stores initial position for when game is restarted
	_iniPosX = posX;
	_iniPosY = posY;
	// Sets the gameobject type
	_gameObjectType = go_type;
	// Creates the Play Buffer object
	_gameObjectId = Play::CreateGameObject(_gameObjectType, { posX, posY }, colRad, name);
	// Sets intial values
	_currentDirection = DIRECTION_DOWN;
	_oldDirection = DIRECTION_DOWN;

	Play::GameObject& obj = Play::GetGameObject(_gameObjectId);

	// Sets scale, velocity and sprite
	obj.scale = scale;
	obj.velocity = { velX, velY };
	Play::SetSprite(obj, FileNamesHolder::fileNames[sprite], animSpeed);
}

// Returns Frame Buffer game object ID
int MainGameObject::GetObjectId()
{
	return _gameObjectId;
}

// Returns game object type
GameObjectType MainGameObject::GetGameObjectType()
{
	return _gameObjectType;
}

// Sets game object position
void MainGameObject::SetPosition(float x, float y)
{
	Play::GameObject& obj = Play::GetGameObject(_gameObjectId);

	obj.pos = { x, y };

	_iniPosX = x;
	_iniPosY = y;
}

// Reset object
void MainGameObject::ReStart()
{
	// Sets intial values
	_currentDirection = DIRECTION_DOWN;
	_oldDirection = DIRECTION_DOWN;
	_animationFinished = false;
	_spriteState = SPRITE_STATE_FINISHED;

	Play::GameObject& obj = Play::GetGameObject(_gameObjectId);
	obj.pos = { _iniPosX, _iniPosY };
	obj.velocity = { 0.f, 0.f };
}

// Reset animation finished
void MainGameObject::ResetAnimationFinished()
{
	Play::GameObject& obj = Play::GetGameObject(_gameObjectId);
	
	obj.framePos = 0.0f;
	obj.frame = 0;
	obj.animSpeed = _iniAnimSpeed;

	Play::UpdateGameObject(obj);
	
	_animationFinished = false;
}

// Returns the animation frame position
float MainGameObject::GetFramePosition()
{
	Play::GameObject& obj = Play::GetGameObject(_gameObjectId);

	return obj.framePos;
}

// Gets object's current direction
ObjectDirection MainGameObject::GetCurrentDirection()
{
	return _currentDirection;
}

// Sets object sprite with the given animation speed
void MainGameObject::SetSprite(int sprite, float animSpeed)
{
	Play::GameObject& obj = Play::GetGameObject(_gameObjectId);
	Play::SetSprite(obj, FileNamesHolder::fileNames[sprite], animSpeed);
}

// Gets the position in one axis given by dir parameter
float MainGameObject::GetPosition(ObjectDirection dir)
{
	float retVal = 0.0f;

	Play::GameObject& obj = Play::GetGameObject(_gameObjectId);

	_currentDirection = dir;

	switch (_currentDirection)
	{
	case DIRECTION_LEFT:
	case DIRECTION_RIGHT:
		retVal = obj.pos.x;
		break;
	case DIRECTION_UP:
	case DIRECTION_DOWN:
		retVal = obj.pos.y;
		break;
	}
	return retVal;
}

// Used with DisplaySingleSpriteAnimation to know the sprite state
SingleSpriteState MainGameObject::GetSpriteState()
{
	return _spriteState;
}

// Displays a static sprite animation, sets animation speed in first call
// Used to display an animation
void MainGameObject::DisplaySingleSpriteAnimation(float animSpeed, int numFrames)
{
	switch (_spriteState)
	{
	case SPRITE_STATE_INIT:
		Display(animSpeed);
		_spriteState = SPRITE_STATE_ANIM;
		break;
	case SPRITE_STATE_ANIM:
		if (GetAnimationFinished() == true)
		{
			_spriteState = SPRITE_STATE_FINISHED;
		}
		DisplayAnimStop(numFrames);
		break;
	case SPRITE_STATE_FINISHED:
		DisplayAnimStop(numFrames);
		break;
	}
}

// Displays a static sprite animation, sets new sprite and animation speed in first call
// Used to display an animation until it is finished and then disappears
void MainGameObject::DisplaySingleSpriteAnimation(int sprite, float animSpeed, int numFrames)
{
	switch (_spriteState)
	{
	case SPRITE_STATE_INIT:
		_animationFinished = false;
		DisplayChangeSprite(sprite, animSpeed);
		_spriteState = SPRITE_STATE_ANIM;
		break;
	case SPRITE_STATE_ANIM:
		if (GetAnimationFinished() == true)
		{
			_spriteState = SPRITE_STATE_FINISHED;
		}
		else
		{
			DisplayAnimStop(numFrames);
		}
		break;
	case SPRITE_STATE_FINISHED:
		break;
	}
}

// To use with DisplayAnimStop
bool MainGameObject::GetAnimationFinished()
{
	return _animationFinished;
}

// Displays a sprite until its animation ends
// Then it stops the animation and movement
// Resets animation
void MainGameObject::DisplayAnimStop(int numFrames)
{
	Play::GameObject& obj = Play::GetGameObject(_gameObjectId);

	if (_animationFinished == false)
	{
		if (obj.frame == numFrames - 1)
		{
			_animationFinished = true;
			// Stop animation
			obj.animSpeed = 0.0f;
			// Reset frame to initial
			obj.frame = numFrames - 1;
		}
	}

	Play::UpdateGameObject(obj);
	Play::DrawObjectRotated(obj);
}

// Displays a game object which had sprite already set but with new animation speed
void MainGameObject::Display(float animSpeed)
{
	Play::GameObject& obj = Play::GetGameObject(_gameObjectId);

	// Sets new animation speed
	obj.animSpeed = animSpeed;
	// Resets flag to indicate animation has finished
	_animationFinished = false;

	Play::UpdateGameObject(obj);
	Play::DrawObjectRotated(obj);
}

void MainGameObject::DisplayHorizontallyScaled(const Play::Matrix2D& transformMatrix)
{
	Play::GameObject& obj = Play::GetGameObject(_gameObjectId);

	Play::DrawSpriteTransformed(obj.spriteId, transformMatrix, 0);
}

// Changes the sprite of the game object, sets its animation speed and displays it
void MainGameObject::DisplayChangeSprite(int sprite, float animSpeed)
{
	Play::GameObject& obj = Play::GetGameObject(_gameObjectId);

	obj.animSpeed = animSpeed;
	obj.frame = 0;
	obj.framePos = 0.0f;

	Play::SetSprite(obj, FileNamesHolder::fileNames[sprite], animSpeed);

	Play::UpdateGameObject(obj);
	Play::DrawObjectRotated(obj);
}

//Get the size of the sprite
Play::Vector2f MainGameObject::GetSpriteSize()
{
	Play::GameObject& obj = Play::GetGameObject(_gameObjectId);

	return Play::Graphics::GetSpriteSize(obj.spriteId);
}

// Displays a game object with the last assigned sprite and properties
void MainGameObject::Display()
{
	Play::GameObject& obj = Play::GetGameObject(_gameObjectId);

	Play::UpdateGameObject(obj);
	Play::DrawObjectRotated(obj);
}

// Displays a game object reseting frame, animSpeed and velocity to zero
void MainGameObject::DisplayStop()
{
	Play::GameObject& obj = Play::GetGameObject(_gameObjectId);

	obj.frame = 0;
	obj.animSpeed = 0.0f;
	obj.velocity = { 0.0f, 0.0f };

	Play::UpdateGameObject(obj);
	Play::DrawObjectRotated(obj);
}

// Sets the velocity of a game object depeding on its direction, move speed and animation speed
void MainGameObject::SetVelDir(ObjectDirection dir, float moveSpeed, float animSpeed)
{
	Play::GameObject& obj = Play::GetGameObject(_gameObjectId);

	_currentDirection = dir;

	switch (_currentDirection)
	{
	case DIRECTION_UP:
		obj.velocity = { 0.0f, moveSpeed };
		break;
	case DIRECTION_DOWN:
		obj.velocity = { 0.0f, -moveSpeed };
		break;
	case DIRECTION_LEFT:
		obj.velocity = { -moveSpeed, 0.0f };
		break;
	case DIRECTION_RIGHT:
		obj.velocity = { moveSpeed, 0.0f };
		break;
	}
	obj.animSpeed = animSpeed;
}

// When game object is stopped but we want to move it in the direction it is pointing to 
// so we don't change the sprite
void MainGameObject::DisplayMoveSameDir(ObjectDirection dir, float moveSpeed, float animSpeed)
{
	Play::GameObject& obj = Play::GetGameObject(_gameObjectId);

	_currentDirection = dir;

	switch (_currentDirection)
	{
	case DIRECTION_UP:
		obj.velocity = { 0.0f, moveSpeed };
		break;
	case DIRECTION_DOWN:
		obj.velocity = { 0.0f, -moveSpeed };
		break;
	case DIRECTION_LEFT:
		obj.velocity = { -moveSpeed, 0.0f };
		break;
	case DIRECTION_RIGHT:
		obj.velocity = { moveSpeed, 0.0f };
		break;
	}
	obj.animSpeed = animSpeed;

	Play::UpdateGameObject(obj);
	Play::DrawObjectRotated(obj);
}
// When we change the direction of the game object	we need to change
// the sprite
void MainGameObject::DisplayChangeDir(int sprite, ObjectDirection dir, float moveSpeed, float animSpeed)
{
	Play::GameObject& obj = Play::GetGameObject(_gameObjectId);

	Play::SetSprite(obj, FileNamesHolder::fileNames[sprite], animSpeed);

	switch (dir)
	{
	case DIRECTION_UP:
		obj.velocity = { 0.0f, moveSpeed };
		break;
	case DIRECTION_DOWN:
		obj.velocity = { 0.0f, -moveSpeed };
		break;
	case DIRECTION_LEFT:
		obj.velocity = { -moveSpeed, 0.0f };
		break;
	case DIRECTION_RIGHT:
		obj.velocity = { moveSpeed, 0.0f };
		break;
	}

	Play::UpdateGameObject(obj);
	Play::DrawObjectRotated(obj);
}


