//
//  Table.cpp
//  Feast Frenzy game
//
//  Created by Oscar Martinez on 13/Jul/2024.
//
#include "Table.h"

Table::Table() : MainGameObject()
{
}

Table::Table(GameObjectType go_type, int sprite, float posX, float posY, const char name[], int colRad, float scale, float animSpeed) :
	MainGameObject(go_type, sprite, posX, posY, name, colRad, scale, animSpeed)
{
}
