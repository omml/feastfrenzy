//
//  DifficultyHandler.h
//  Feast Frenzy game
//
//  Created by Oscar Martinez on 11/Jul/2024.
//
#pragma once

#include "CommonDefinitions.h"
#include "ScoreHolder.h"

class DifficultyHandler
{
private:
	DifficultyLevel _level;
	ScoreHolder* _score;

public:
	//static DifficultyHandler& getInstance();

	DifficultyHandler();

	void SetScoreHolderObject(ScoreHolder* s);

	void ReStart();

	void CheckDifficulty();

	int GetNumEnemies();

	int GetLevel();
};

