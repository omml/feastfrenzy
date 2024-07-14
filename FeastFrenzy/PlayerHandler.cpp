//
//  PlayerHandler.cpp
//  Feast Frenzy game
//
//  Created by Oscar Martinez on 1/Apr/2024.
//
#include "PlayerHandler.h"
#include "SpritesDefinitions.h"

PlayerHandler::PlayerHandler() {}

CharacterPlayer* PlayerHandler::GetPlayer()
{
	return &player;
}

// Sets the table handler
void PlayerHandler::SetTableHandler(TableHandler* tableHandler)
{
	_tableHandler = tableHandler;

	player.SetTableHandler(_tableHandler);
}

// Creates the player
void PlayerHandler::Create()
{
	// Create the main player
	player = CharacterPlayer(TYPE_BOY_P, boy1_wd_8, 300, 300, "boy", 10, 0.5f, 0.0f);
	// Set the sprites 
	player.SetWalkSprites(boy1_wu_8, boy1_wd_8, boy1_wl_8, boy1_wr_8, 3.5f, 0.5f);
	player.SetWalkHoldSprites(boy1_wuh_8, boy1_wdh_8, boy1_wlh_8, boy1_wrh_8, 3.5f, 0.5f);
	player.SetThrowSprites(boy1_pu_3, boy1_pd_3, boy1_pl_3, boy1_pr_3, 0.1f);
	player.SetCatchSprites(boy1_cu_3, boy1_cd_3, boy1_cl_3, boy1_cr_3, 0.1f);
}

// Displays the player and waits for input
void PlayerHandler::Display()
{
	// Move player depending on keyboard input
	player.HandlePlayerControls();
}

int PlayerHandler::GetObjectId()
{
	return player.GetObjectId();
}

// Restarts the player
void PlayerHandler::ReStart()
{
	player.ReStart();
}
