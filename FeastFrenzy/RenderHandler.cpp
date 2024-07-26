//
//  RenderHandler.cpp
//  Feast Frenzy game
//
//  Created by Oscar Martinez on 13/Jul/2024.
//

#include <algorithm>
#include "RenderHandler.h"
#include "PlayerHandler.h"
#include "TableHandler.h"

RenderHandler::RenderHandler()
{}

void RenderHandler::SetPlayerHandler(PlayerHandler* p)
{
	_playerHandler = p;
}

// Comparator to compare objects by y position in decreasing order
bool CompareY(MainGameObject* a, MainGameObject* b)
{
	Play::GameObject& aObj = Play::GetGameObject(a->GetObjectId());
	Play::GameObject& bObj = Play::GetGameObject(b->GetObjectId());

	return aObj.pos.y >= bObj.pos.y;
}

void RenderHandler::Render()
{
	std::vector<MainGameObject*> objs;

	Play::GameObject& player = Play::GetGameObject( _playerHandler->GetObjectId());

	int numTables = TableHandler::GetInstance().GetNumTables();

	for (int i = 0; i < numTables; i++)
	{
		Table* table = TableHandler::GetInstance().GetTable(i);

		if (objs.size() == 0)
		{
			objs.push_back(table);
		}
		else
		{
			auto it = std::lower_bound(objs.begin(), objs.end(), table, CompareY);

			// Insert the object at the correct position
			objs.insert(it, table);
		}

		bool wasPlayerRendered = false;
		for (int j = 0; j < objs.size(); j++)
		{
			Play::GameObject& ro = Play::GetGameObject(objs[j]->GetObjectId());

			if (player.pos.y > ro.pos.y)
			{
				_playerHandler->Display();
				wasPlayerRendered = true;
			}

			objs[j]->Display();
		}

		if (wasPlayerRendered == false)
		{
			_playerHandler->Display();
		}
	}
}