//
//  RenderHandler.h
//  Feast Frenzy game
//
//  Created by Oscar Martinez on 13/Jul/2024.
//
#pragma once
#include <vector>
#include "MainGameObject.h"
#include "PlayerHandler.h"

class RenderHandler
{
private:
	PlayerHandler* _playerHandler;

	//bool CompareY(MainGameObject* a, MainGameObject* b);

public:
	RenderHandler();
	void SetPlayerHandler(PlayerHandler* p);
	void Render();
};

