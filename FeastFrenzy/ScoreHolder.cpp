//
//  ScoreHolder.cpp
//  Feast Frenzy game
//
//  Created by Oscar Martinez on 1/Apr/2024.
//
#include "ScoreHolder.h"

// Constructor
ScoreHolder::ScoreHolder()
{
	_score = 0;
}

// To implement Singleton pattern
ScoreHolder& ScoreHolder::GetInstance() {
	static ScoreHolder instance;
	return instance;
}

// Resets score
void ScoreHolder::ReStart()
{
	_score = 0;
}

// Gets the current score
int ScoreHolder::GetScore()
{
	return _score;
}

// Increases the score
void ScoreHolder::IncScore()
{
	_score++;
}

// Increases the score by given ammount
void ScoreHolder::IncScore(int value)
{
	_score += value;
}

// Decreases the score
void ScoreHolder::DecScore()
{
	_score--;

	if (_score < 0)
	{
		_score = 0;
	}
}