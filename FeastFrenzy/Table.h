//
//  Table.h
//  Feast Frenzy game
//
//  Created by Oscar Martinez on 13/Jul/2024.
//
#pragma once
#include "MainGameObject.h"
class Table : public MainGameObject
{
public:
	Table();
	Table(GameObjectType go_type, int sprite, float posX, float posY, const char name[], int colRad, float scale, float animSpeed);
};

