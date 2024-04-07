//
//  Character.cpp
//  Feast Frenzy game
//
//  Created by Oscar Martinez on 1/Apr/2024.
//
#include "Character.h"


Character::Character() : MainGameObject()
{
	_animationState = PLAYER_STATE_IDLE;
	_oldAnimationState = PLAYER_STATE_IDLE;
}
Character::Character(GameObjectType go_type, int sprite, float posX, float posY, const char name[], int colRad, float scale, float animSpeed) :
	MainGameObject(go_type, sprite, posX, posY, name, colRad, scale, animSpeed)
{
	_animationState = PLAYER_STATE_IDLE;
	_oldAnimationState = PLAYER_STATE_IDLE;
}
void Character::SetAnimationState(PlayerAnimationState animState)
{
	_animationState = animState;
}
void Character::SetCurrentDirection(ObjectDirection cd)
{
	_currentDirection = cd;
	_oldDirection = cd;
}

void Character::SetWalkSprites(int upSprite, int downSprite, int leftSprite, int rightSprite, float moveSpeed, float animSpeed)
{
	_walkingSprites[DIRECTION_UP]._spriteName = upSprite;
	_walkingSprites[DIRECTION_DOWN]._spriteName = downSprite;
	_walkingSprites[DIRECTION_LEFT]._spriteName = leftSprite;
	_walkingSprites[DIRECTION_RIGHT]._spriteName = rightSprite;
	_walkingSprites[DIRECTION_UP]._animSpeed = animSpeed;
	_walkingSprites[DIRECTION_DOWN]._animSpeed = animSpeed;
	_walkingSprites[DIRECTION_LEFT]._animSpeed = animSpeed;
	_walkingSprites[DIRECTION_RIGHT]._animSpeed = animSpeed;
	_walkingSprites[DIRECTION_UP]._moveSpeed = moveSpeed;
	_walkingSprites[DIRECTION_DOWN]._moveSpeed = moveSpeed;
	_walkingSprites[DIRECTION_LEFT]._moveSpeed = moveSpeed;
	_walkingSprites[DIRECTION_RIGHT]._moveSpeed = moveSpeed;
}

void Character::SetWalkHoldSprites(int upSprite, int downSprite, int leftSprite, int rightSprite, float moveSpeed, float animSpeed)
{
	_walkingHoldingSprites[DIRECTION_UP]._spriteName = upSprite;
	_walkingHoldingSprites[DIRECTION_DOWN]._spriteName = downSprite;
	_walkingHoldingSprites[DIRECTION_LEFT]._spriteName = leftSprite;
	_walkingHoldingSprites[DIRECTION_RIGHT]._spriteName = rightSprite;
	_walkingHoldingSprites[DIRECTION_UP]._animSpeed = animSpeed;
	_walkingHoldingSprites[DIRECTION_DOWN]._animSpeed = animSpeed;
	_walkingHoldingSprites[DIRECTION_LEFT]._animSpeed = animSpeed;
	_walkingHoldingSprites[DIRECTION_RIGHT]._animSpeed = animSpeed;
	_walkingHoldingSprites[DIRECTION_UP]._moveSpeed = moveSpeed;
	_walkingHoldingSprites[DIRECTION_DOWN]._moveSpeed = moveSpeed;
	_walkingHoldingSprites[DIRECTION_LEFT]._moveSpeed = moveSpeed;
	_walkingHoldingSprites[DIRECTION_RIGHT]._moveSpeed = moveSpeed;
}

void Character::SetThrowSprites(int upSprite, int downSprite, int leftSprite, int rightSprite, float animSpeed)
{
	_throwSprites[DIRECTION_UP]._spriteName = upSprite;
	_throwSprites[DIRECTION_DOWN]._spriteName = downSprite;
	_throwSprites[DIRECTION_LEFT]._spriteName = leftSprite;
	_throwSprites[DIRECTION_RIGHT]._spriteName = rightSprite;
	_throwSprites[DIRECTION_UP]._animSpeed = animSpeed;
	_throwSprites[DIRECTION_DOWN]._animSpeed = animSpeed;
	_throwSprites[DIRECTION_LEFT]._animSpeed = animSpeed;
	_throwSprites[DIRECTION_RIGHT]._animSpeed = animSpeed;
	_throwSprites[DIRECTION_UP]._moveSpeed = 0;
	_throwSprites[DIRECTION_DOWN]._moveSpeed = 0;
	_throwSprites[DIRECTION_LEFT]._moveSpeed = 0;
	_throwSprites[DIRECTION_RIGHT]._moveSpeed = 0;
}

void Character::SetCatchSprites(int upSprite, int downSprite, int leftSprite, int rightSprite, float animSpeed)
{
	_catchSprites[DIRECTION_UP]._spriteName = upSprite;
	_catchSprites[DIRECTION_DOWN]._spriteName = downSprite;
	_catchSprites[DIRECTION_LEFT]._spriteName = leftSprite;
	_catchSprites[DIRECTION_RIGHT]._spriteName = rightSprite;
	_catchSprites[DIRECTION_UP]._animSpeed = animSpeed;
	_catchSprites[DIRECTION_DOWN]._animSpeed = animSpeed;
	_catchSprites[DIRECTION_LEFT]._animSpeed = animSpeed;
	_catchSprites[DIRECTION_RIGHT]._animSpeed = animSpeed;
	_catchSprites[DIRECTION_UP]._moveSpeed = 0;
	_catchSprites[DIRECTION_DOWN]._moveSpeed = 0;
	_catchSprites[DIRECTION_LEFT]._moveSpeed = 0;
	_catchSprites[DIRECTION_RIGHT]._moveSpeed = 0;
}
