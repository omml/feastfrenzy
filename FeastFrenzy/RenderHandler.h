//
//  RenderHandler.h
//  Feast Frenzy game
//
//  Created by Oscar Martinez on 13/Jul/2024.
//
#pragma once
#include <vector>
#include "MainGameObject.h"

class RenderHandler
{
private:
	std::vector<MainGameObject*> _objs;
	void AddTableObject();

public:
	static RenderHandler& GetInstance();
	RenderHandler();
	void Initialise();
	void ReStart();
	void Render();
	void Update();
private:
	RenderHandler(const RenderHandler&) = delete;
	void operator=(const RenderHandler&) = delete;
};

