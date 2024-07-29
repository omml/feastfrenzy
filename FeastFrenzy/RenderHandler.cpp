//
//  RenderHandler.cpp
//  Feast Frenzy game
//
//  Created by Oscar Martinez on 13/Jul/2024.
//

#include <algorithm>
#include "RenderHandler.h"
#include "CharacterPlayer.h"
#include "TableHandler.h"

RenderHandler::RenderHandler()
{}

// To implement Singleton pattern
RenderHandler& RenderHandler::GetInstance() {
	static RenderHandler instance;
	return instance;
}

// Comparator to compare objects by y position in decreasing order
bool CompareY(MainGameObject* a, MainGameObject* b)
{
	Play::GameObject& aObj = Play::GetGameObject(a->GetObjectId());
	Play::GameObject& bObj = Play::GetGameObject(b->GetObjectId());

	return aObj.pos.y >= bObj.pos.y;
}

// Initialize the render handler
void RenderHandler::Initialise()
{
	_objs.clear();

	AddTableObject();
}

// Restart the render handler
void RenderHandler::ReStart()
{
	_objs.clear();

	AddTableObject();
}

// Update the render handler
void RenderHandler::Update()
{
	AddTableObject();
}

// Add a table to the render objects
void RenderHandler::AddTableObject()
{
	if (_objs.size() < NUM_TABLES)
	{
		Table* table = TableHandler::GetInstance().GetTable(_objs.size());

		auto it = std::lower_bound(_objs.begin(), _objs.end(), table, CompareY);

		// Insert the object at the correct position
		_objs.insert(it, table);
	}
}

// Render objects in order, first objects that have a larger y value
void RenderHandler::Render()
{
	bool wasPlayerRendered = false;
	Play::GameObject& player = Play::GetGameObject(CharacterPlayer::GetInstance().GetObjectId());

	int numTables = _objs.size();

	for (int i = 0; i < numTables; i++)
	{
		Play::GameObject& ro = Play::GetGameObject(_objs[i]->GetObjectId());

		if (wasPlayerRendered == false)
		{
			if (player.pos.y > ro.pos.y)
			{
				CharacterPlayer::GetInstance().HandlePlayerControls();
				wasPlayerRendered = true;
			}
		}

		_objs[i]->Display();
	}

	if (wasPlayerRendered == false)
	{
		CharacterPlayer::GetInstance().HandlePlayerControls();
	}
}