//
//  DifficultyHandler.cpp
//  Feast Frenzy game
//
//  Created by Oscar Martinez on 11/Jul/2024.
//
#include "DifficultyHandler.h"
#include "RenderHandler.h"

DifficultyHandler::DifficultyHandler()
{
	_level = LEVEL01;
}

// To implement Singleton pattern
DifficultyHandler& DifficultyHandler::GetInstance() {
	static DifficultyHandler instance;
	return instance;
}

int DifficultyHandler::GetLevel()
{
	return (int)_level;
}

void DifficultyHandler::ReStart()
{
	_level = LEVEL01;
}

void DifficultyHandler::CheckDifficulty()
{
	int threshold = 0;

	switch (_level)
	{
	case LEVEL01:
		threshold = 2;
		break;
	case LEVEL02:
		threshold = 10;
		break;
	case LEVEL03:
		threshold = 30;
		break;
	case LEVEL04:
		threshold = 40;
		break;
	case LEVEL05:
		threshold = 50;
		break;
	case LEVEL06:
		threshold = 60;
		break;
	}

	if (ScoreHolder::GetInstance().GetScore() >= threshold)
	{
		_level = (DifficultyLevel)((int)_level + 1);

		RenderHandler::GetInstance().Update();
	}
}

int DifficultyHandler::GetNumEnemies()
{
	int retVal = 0;

	switch (_level)
	{
	case LEVEL01:
		retVal = 1;
		break;
	case LEVEL02:
		retVal = 2;
		break;
	case LEVEL03:
		retVal = 3;
		break;
	case LEVEL04:
		retVal = 3;
		break;
	case LEVEL05:
		retVal = 3;
		break;
	case LEVEL06:
		retVal = 3;
		break;
	}

	return retVal;
}

int DifficultyHandler::GetNumTables()
{
	int retVal = 0;

	switch (_level)
	{
	case LEVEL01:
		retVal = 1;
		break;
	case LEVEL02:
		retVal = 2;
		break;
	case LEVEL03:
		retVal = 3;
		break;
	case LEVEL04:
		retVal = 3;
		break;
	case LEVEL05:
		retVal = 3;
		break;
	case LEVEL06:
		retVal = 3;
		break;
	}

	return retVal;
}