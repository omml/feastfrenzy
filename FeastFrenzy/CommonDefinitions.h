//
//  CommonDefinitions.h
//  Feast Frenzy game
//
//  Created by Oscar Martinez on 1/Apr/2024.
//
#pragma once
#ifndef COMMONDEFINITIONS_H
#define COMMONDEFINITIONS_H

//Common definitions

#define NUM_ENEMIES 3

// To indicate the direction game objects are pointing to
enum ObjectDirection
{
	DIRECTION_UP = 0,
	DIRECTION_DOWN,
	DIRECTION_LEFT,
	DIRECTION_RIGHT,
};

// To indicate the state of the food
enum FoodState
{
	FOOD_CARRIED_ENEMY = 0,
	FOOD_CARRIED_PLAYER,
	FOOD_FLYING,
	FOOD_PREPARE_HIT,
	FOOD_HIT,
	FOOD_IDLE,
};


// State of animation for a single sprite
enum SingleSpriteState
{
	SPRITE_STATE_INIT = 0,
	SPRITE_STATE_ANIM,
	SPRITE_STATE_FINISHED,
};

// State of character
enum PlayerAnimationState
{
	
	PLAYER_STATE_IDLE = -2,
	PLAYER_STATE_IDLE_HOLD,
	PLAYER_STATE_WALK = 0,
	PLAYER_STATE_WALK_HOLD,
	PLAYER_STATE_PREPARE_CATCH,
	PLAYER_STATE_CATCH,
	PLAYER_STATE_PREPARE_DOWN,
	PLAYER_STATE_DOWN,
	PLAYER_STATE_PREPARE_ATTACK,
	PLAYER_STATE_ATTACK,
};

// To check which keys have been pressed
enum PlayerKey
{
	PLAYER_PRESSED_NONE = -1,
	PLAYER_PRESSED_UP,
	PLAYER_PRESSED_DOWN,
	PLAYER_PRESSED_LEFT,
	PLAYER_PRESSED_RIGHT,
	PLAYER_PRESSED_SPACE,
};

// State of the enemy
enum EnemyState
{
	ENEMY_INIT,
	ENEMY_PREPARE_ATTACK,
	ENEMY_ATTACK,
	ENEMY_CHANGE_DIRECTION,
	ENEMY_MOVE_UP,
	ENEMY_MOVE_DOWN,
	ENEMY_HIT,
	ENEMY_END,
	ENEMY_IDLE,
};

// Object types
enum GameObjectType
{
	TYPE_NULL = 0,
	TYPE_BOY_P,
	TYPE_GIRL_E,
	TYPE_GM_F,
	TYPE_MOU_E,
	TYPE_EXP1_N,
	TYPE_EXP1_B,
	TYPE_ENEMY_START = 100,
	TYPE_ENEMY_END = 116,
	TYPE_FOOD_START = 200,
	TYPE_FOOD_END = 216,
	TYPE_BACKGROUND,
	TYPE_HEALTHBAR,
};

enum MenuState
{
	GUI_MAIN = 0,
	GUI_MAIN2,
	GUI_MAIN3,
	GUI_MAIN4,
	GUI_INSTRUCTIONS,
	GUI_PLAY,
	GUI_GAMEOVER,
};

// To hold names of sprites, animation and moving speed
struct SpriteNameHolder
{
	int _spriteName;
	float _animSpeed;
	float _moveSpeed;
};

#endif