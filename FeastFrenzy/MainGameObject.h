//
//  MainGameObject.h
//  Feast Frenzy game
//
//  Created by Oscar Martinez on 1/Apr/2024.
//
#pragma once
#ifndef MAINGAMEOBJECT_H
#define MAINGAMEOBJECT_H
#define PLAY_USING_GAMEOBJECT_MANAGER
#include "Play.h"
#include "CommonDefinitions.h"

// Main class to create and display game objects
class MainGameObject
{
protected:
	int _gameObjectId;
	GameObjectType _gameObjectType;
	ObjectDirection _currentDirection;
	ObjectDirection _oldDirection;
	bool _animationFinished;
	SingleSpriteState _spriteState;
	float _iniPosX;
	float _iniPosY;

public:
	MainGameObject();
	
	// Creates a gameobject and sets its sprite reade to be displayed
	MainGameObject(GameObjectType go_type, int sprite, float posX, float posY, const char name[], int colRad, float scale, float animSpeed);
	
	// Creates a gameobject and sets its sprite reade to be displayed, sets velocity
	MainGameObject(GameObjectType go_type, int sprite, float posX, float posY, float velX, float velY, const char name[], int colRad, float scale, float animSpeed);
	
	void SetSprite(int sprite, float animSpeed);

	ObjectDirection GetCurrentDirection();

	int GetObjectId();
	
	// Gets the position in one axis given by dir parameter
	float GetPosition(ObjectDirection dir);
	
	// Used with DisplaySingleSpriteAnimation to know the sprite state
	SingleSpriteState GetSpriteState();
	
	// Displays a static sprite animation, sets animation speed in first call
	void DisplaySingleSpriteAnimation(float animSpeed, int numFrames);
	
	// Displays a static sprite animation, sets new sprite and animation speed in first call
	void DisplaySingleSpriteAnimation(int sprite, float animSpeed, int numFrames);
	
	// To use with DisplayAnimStop
	bool GetAnimationFinished();
	
	// Displays a sprite until its animation ends
	void DisplayAnimStop(int numFrames);
	
	// Displays a game object which had sprite already set but with new animation speed
	void Display(float animSpeed);
	
	// Changes the sprite of the game object, sets its animation speed and displays it
	void DisplayChangeSprite(int sprite, float animSpeed);
	
	// Displays a game object with the last assigned sprite and properties
	void Display();

	// Displays a game object horizontally scaled, used for healthbar
	
	void DisplayHorizontallyScaled(const Play::Matrix2D& transformMatrix);

	Play::Vector2f GetSpriteSize();
	
	// Displays a game object reseting frame, animSpeed and velosity to zero
	void DisplayStop();
	
	// Sets the velocity of a game object depeding on its direction, move speed and animation speed
	void SetVelDir(ObjectDirection dir, float moveSpeed, float animSpeed);
	
	// When game object is stopped but we want to move it in the direction it is pointing to 
	// so we don't change the sprite
	void DisplayMoveSameDir(ObjectDirection dir, float moveSpeed, float animSpeed);
	
	// When we change the direction of the game object	we need to change
	// the sprite
	void DisplayChangeDir(int sprite, ObjectDirection dir, float moveSpeed, float animSpeed);

	void ReStart();
};
#endif

