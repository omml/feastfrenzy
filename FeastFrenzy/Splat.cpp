//
//  Splat.cpp
//  Feast Frenzy game
//
//  Created by Oscar Martinez on 1/Apr/2024.
//
#include "CommonDefinitions.h"
#include "Splat.h"

// THIS CLASS WAS ORIGINALLY CREATED FOR SPLATS BUT WITH AT THE END WAS NOT NEEDED
Splat::Splat()
{
	_spriteState = SPRITE_STATE_INIT;
}

Splat::Splat(GameObjectType go_type, int sprite, float posX, float posY, const char name[], int colRad, float scale, float animSpeed) :
	MainGameObject(go_type, sprite, posX, posY, name, colRad, scale, animSpeed)
{
	_spriteState = SPRITE_STATE_INIT;
}

void Splat::Animate(int numFrames)
{
	switch (_spriteState)
	{
	case SPRITE_STATE_INIT:
		Display(0.1f);
		_spriteState = SPRITE_STATE_ANIM;
		break;
	case SPRITE_STATE_ANIM:
		if (GetAnimationFinished() == true)
		{
			_spriteState = SPRITE_STATE_FINISHED;
		}
		else
		{
			DisplayAnimStop(numFrames);
		}
		break;
	case SPRITE_STATE_FINISHED:
		break;
	}
}
