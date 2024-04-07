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

// Decreases the score
void ScoreHolder::DecScore()
{
	_score--;

	if (_score < 0)
	{
		_score = 0;
	}
}