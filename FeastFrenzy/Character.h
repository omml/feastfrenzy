//
//  Character.h
//  Feast Frenzy game
//
//  Created by Oscar Martinez on 1/Apr/2024.
//

#pragma once
#ifndef CHARACTER_H
#define CHARACTER_H

#include "MainGameObject.h"

// Main class that holds some common functionality for characters
class Character : public MainGameObject
{
protected:
	SpriteNameHolder _walkingSprites[4];
	SpriteNameHolder _walkingHoldingSprites[4];
	SpriteNameHolder _throwSprites[4];
	SpriteNameHolder _catchSprites[4];

	PlayerAnimationState _animationState;
	PlayerAnimationState _oldAnimationState;


public:
	Character();
	Character(GameObjectType go_type, int sprite, float posX, float posY, const char name[], int colRad, float scale, float animSpeed);
	void SetAnimationState(PlayerAnimationState animState);
	void SetCurrentDirection(ObjectDirection cd);
	void SetWalkSprites(int upSprite, int downSprite, int leftSprite, int rightSprite, float moveSpeed, float animSpeed);
	void SetWalkHoldSprites(int upSprite, int downSprite, int leftSprite, int rightSprite, float moveSpeed, float animSpeed);
	void SetThrowSprites(int upSprite, int downSprite, int leftSprite, int rightSprite, float animSpeed);
	void SetCatchSprites(int upSprite, int downSprite, int leftSprite, int rightSprite, float animSpeed);
};
#endif