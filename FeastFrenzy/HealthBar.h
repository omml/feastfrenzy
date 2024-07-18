//
//  HealthBar.h
//  Feast Frenzy game
//
//  Created by Oscar Martinez on 11/Jul/2024.
//
#pragma once
#define PLAY_USING_GAMEOBJECT_MANAGER
#include "Play.h"
#include "MainGameObject.h"
class HealthBar
{
public:
	HealthBar(float maxHealth, float decreasePrecentage);
	void Create();
	void Display();
	void DecreaseHealth();
	void IncreaseHealth();
	bool IsAlive();
	void ReStart();
private:
	MainGameObject _background;
	MainGameObject _main;
	//MainGameObject _guide;

	float _maxHealth;
	float _currentHealth;
	float _decreasePercentage;
	float _decreaseStep;

	float _posX;
	float _posY;
	Play::Matrix2D _matrix;
	float _mainScale;
	float _healthScale;
	float _scaledSize;
	Play::Vector2f _spriteSize;

	void CalculateTransformMatrix();
};

