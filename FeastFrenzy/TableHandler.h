//
//  TableHandler.h
//  Feast Frenzy game
//
//  Created by Oscar Martinez on 13/Jul/2024.
//
#pragma once

#include "Table.h"
#include "DifficultyHandler.h"
#include "FoodHandler.h"

class TableHandler
{
private:
	DifficultyHandler* _difficultyHandler;
	Table _tables[NUM_ENEMIES];
	FoodHandler* _foodHandler;
	float _posXMin;
	float _posXMax;
	float _posYMin;
	float _posYMax;

public:
	TableHandler();

	void SetFoodHandler(FoodHandler* foodHandler);
	void SetDifficultyHandler(DifficultyHandler* difficultyHandler);

	Table* GetTable(int index);

	void Create(float xMin, float xMax, float yMin, float yMax);

	void Display();

	void ReStart();

	int GetNumTables();
};

