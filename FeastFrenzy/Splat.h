//
//  Splat.h
//  Feast Frenzy game
//
//  Created by Oscar Martinez on 1/Apr/2024.
//
#pragma once
#ifndef SPLAT_H
#define SPLAT_H

#include "MainGameObject.h"

// THIS CLASS WAS ORIGINALLY CREATED FOR SPLATS BUT WITH AT THE END WAS NOT NEEDED
// Class to create splats for when food collides with characters
class Splat : public MainGameObject
{

public:
	Splat();
	
	Splat(GameObjectType go_type, int sprite, float posX, float posY, const char name[], int colRad, float scale, float animSpeed);

	void Animate(int numFrames);
};
#endif