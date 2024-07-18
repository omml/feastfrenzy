//
//  Table.cpp
//  Feast Frenzy game
//
//  Created by Oscar Martinez on 13/Jul/2024.
//
#include "Table.h"
#include "SpritesDefinitions.h"
#include "FileNamesHolder.h"

Table::Table() : MainGameObject()
{
}

Table::Table(GameObjectType go_type, int sprite, float posX, float posY, const char name[], int colRad, float scale, float animSpeed) :
	MainGameObject(go_type, sprite, posX, posY, name, colRad, scale, animSpeed)
{
	_hasCake = false;
	_collider = MainGameObject(TYPE_TABLE_COLLIDER, playercollider, posX, posY, FileNamesHolder::fileNames[playercollider], 30.f, 1.0f, 0.0f);
	_cake = MainGameObject(TYPE_CAKE_ON_TABLE, f_bk_n, posX, posY + 40.f, FileNamesHolder::fileNames[f_bk_n], 0.f, .75f, 0.0f);
	_smoke = MainGameObject(TYPE_CAKE_ON_TABLE, smoke_appear_7, posX, posY + 20.0f, FileNamesHolder::fileNames[smoke_appear_7], 0.f, 0.15f, 0.1f);
	_smokeCake = MainGameObject(TYPE_CAKE_ON_TABLE, smoke_disappear_7, posX, posY + 40.0f, FileNamesHolder::fileNames[smoke_disappear_7], 0.f, 0.075f, 0.1f);
}

// Function to check if player is in range to place cake
bool Table::IsCollidingWithPlayer(int playerId)
{
	bool retVal = false;

	Play::GameObject& table = Play::GetGameObject(_collider.GetObjectId());
	Play::GameObject& player = Play::GetGameObject(playerId);

	//check if the food and the player are colliding
	retVal = Play::IsColliding(table, player);
	
	return retVal;
}

// Sets whether the table has a cake on top
void Table::SetCake(bool val)
{
	_hasCake = val;

	if (_hasCake == true)
	{
		std::thread timerThread(std::bind(&Table::TimerToResetCake, this, 5.0f));
		timerThread.detach(); // Detach the thread to run independently
	}
}

// Returns whether the table has a cake on top
bool Table::HasCake()
{
	return _hasCake;
}

// Displays table, also a cake if it has a cake
void Table::Display()
{
	MainGameObject::Display();
	if (_hasCake)
	{
		_cake.Display();
	}

	if (_playedAppearSound == false)
	{
		_playedAppearSound = true;
		Play::PlayAudio("appear");
	}

	if (_smoke.GetAnimationFinished() == false)
	{
		_smoke.DisplayAnimStop(7);
	}

	if (_displayDisappear == true)
	{
		if (_smokeCake.GetAnimationFinished() == false)
		{
			_smokeCake.DisplayAnimStop(7);
		}
		else
		{
			_displayDisappear = false;
		}
	}
}

// Restarts the table hiding the cake
void Table::ReStart(float x, float y)
{
	SetCake(false);

	SetPosition(x, y);
	_collider.SetPosition(x, y);
	_cake.SetPosition(x, y + 40.f);
	_smoke.SetPosition(x, y + 20.0f);
	_smokeCake.SetPosition(x, y + 40.f);
	_smoke.ResetAnimationFinished();
	_playedAppearSound = false;
}

// Hide the cake and produce a sound
void Table::TimerToResetCake(int durationInSeconds)
{
	std::this_thread::sleep_for(std::chrono::seconds(durationInSeconds));
	SetCake(false);
	Play::PlayAudio("cakedisappear");
	_smokeCake.ResetAnimationFinished();
	_displayDisappear = true;
}
