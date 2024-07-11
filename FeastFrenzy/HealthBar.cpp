
//
//  HealthBar.cpp
//  Feast Frenzy game
//
//  Created by Oscar Martinez on 11/Jul/2024.
//
#include "HealthBar.h"
#include "SpritesDefinitions.h"
#include "FileNamesHolder.h"

HealthBar::HealthBar(float maxHealth, float decreasePrecentage)
{
	_maxHealth = maxHealth;

	if (_maxHealth <= 0.f)
	{
		_maxHealth = 100.f;
	}

	_currentHealth = maxHealth;
	_decreasePercentage = decreasePrecentage;

	if (_decreasePercentage > 1.0f)
	{
		_decreasePercentage = 1.f;
	}

	_decreaseStep = _maxHealth * _decreasePercentage;
}

void HealthBar::Create()
{
	_posX = 1135+29;
	_posY = 656;
	_mainScale = 0.125f;
	_healthScale = 1.f;
	_background = MainGameObject(TYPE_HEALTHBAR, healthbar_bg, _posX - 29, _posY + 4, FileNamesHolder::fileNames[healthbar_bg], 0, 0.125f, 0.f);
	_main = MainGameObject(TYPE_HEALTHBAR, healthbar_main, _posX, _posY, FileNamesHolder::fileNames[healthbar_main], 0, _mainScale, 0.f);
	_guide = MainGameObject(TYPE_HEALTHBAR, healthbar_guide, _posX - 29, _posY + 4, FileNamesHolder::fileNames[healthbar_guide], 0, 0.125f, 0.f);

	_spriteSize = _main.GetSpriteSize() * _mainScale;

	CalculateTransformMatrix();
}

// Checks if the player still has health
bool HealthBar::IsAlive()
{
	return _currentHealth > 0.f;
}

// Decreases the health
void HealthBar::DecreaseHealth()
{
	_currentHealth -= _decreaseStep;

	if (_currentHealth < 0)
	{
		_currentHealth = 0.f;
	}

	// Set new scale for the health bar
	_healthScale = _currentHealth / _maxHealth;

	// Recalculate health bar 
	CalculateTransformMatrix();
}

// Calculates the health bar transformation matrix to take in count changes on scale
void HealthBar::CalculateTransformMatrix()
{
	_scaledSize = _spriteSize.x * _healthScale;

	Play::Matrix2D scaleMatrix = Play::MatrixScale(_mainScale * _healthScale, _mainScale);

	// Create a translation matrix
	Play::Matrix2D translationMatrix = Play::MatrixTranslation(_posX + (_scaledSize - _spriteSize.x) / 2.f, _posY);

	_matrix = scaleMatrix * translationMatrix;
}

void HealthBar::Display()
{
	_main.DisplayHorizontallyScaled(_matrix);

	_background.Display();
	//guide.Display();
}