//
//  MainGame.cpp
//  Feast Frenzy game
//
//  Created by Oscar Martinez on 1/Apr/2024.
//

#define PLAY_IMPLEMENTATION
#define PLAY_USING_GAMEOBJECT_MANAGER
#include "Play.h"

#include "SpritesDefinitions.h"
#include "CommonDefinitions.h"
#include "FileNamesHolder.h"
#include "MainGameObject.h"
#include "PlayerHandler.h"
#include "EnemyHandler.h"
#include "FoodHandler.h"
#include "ScoreHolder.h"
#include "HealthBar.h"
#include "DifficultyHandler.h"
#include "TableHandler.h"
#include "RenderHandler.h"

int DISPLAY_WIDTH = 1280;
int DISPLAY_HEIGHT = 720;
int DISPLAY_SCALE = 1;

// Not used at the moment
struct GameState
{
	float timer = 0;
};
GameState gameState;

// Background
MainGameObject background;
// Table rows at bottom
MainGameObject bottomTables;
// Player handler
PlayerHandler playerHandler;
// Enemy handler for left screen enemies
EnemyHandler enemyHandlerLeft;
// Food handler for left screen enemies
FoodHandler foodHandlerLeft;
// Enemy handler for right screen enemies
EnemyHandler enemyHandlerRight;
// Food handler for right screen enemies
FoodHandler foodHandlerRight;
// Render handler for table and player objects
RenderHandler renderHandler;
// Main song audio id;
int songId;

MenuState guiState = GUI_MAIN;
bool playingSong = false;

void DisplayMainScreen()
{
	// First background
	background.Display();

	if (Play::KeyPressed(KEY_ENTER))
	{
		// Change to second background
		background.SetSprite(main_gui2, 0.0f);
		Play::PlayAudio("hit");
		guiState = GUI_MAIN2;
	}
}

void DisplaySecondScreen()
{
	// Second background
	background.Display();

	if (Play::KeyPressed(KEY_ENTER))
	{
		// Change to third background
		background.SetSprite(main_gui3, 0.0f);
		Play::PlayAudio("hit");
		guiState = GUI_MAIN3;
	}
}

void DisplayThirdScreen()
{
	// Third background
	background.Display();

	if (Play::KeyPressed(KEY_ENTER))
	{
		// Change to fourth background
		background.SetSprite(main_gui4, 0.0f);
		Play::PlayAudio("hit");
		guiState = GUI_MAIN4;
	}
}

void DisplayFourthScreen()
{
	// Fourth background
	background.Display();

	if (Play::KeyPressed(KEY_TAB))
	{
		// For instructions
		guiState = GUI_INSTRUCTIONS;
		Play::PlayAudio("hit");
	}
	else if (Play::KeyPressed(KEY_SPACE))
	{
		Play::PlayAudio("hit");
		if (playingSong == false)
		{
			// To play
			songId = Play::StartAudioLoop("main");
			playingSong = true;
		}
		guiState = GUI_PLAY;
	}
}

void DisplayInstructions()
{
	string s = FileNamesHolder::foodNames[playerHandler.GetHealthFood()];
	// Displays instructions
	Play::DrawFontText("40px", "Press ARROW keys to MOVE UP, DOWN, LEFT, RIGHT", { DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2 + 100 }, Play::CENTRE);
	Play::DrawFontText("40px", "Press SPACE to CATCH and THROW", { DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2 + 20 }, Play::CENTRE);
	Play::DrawFontText("40px", "Press E to EAT " + s, { DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2 - 60 }, Play::CENTRE);
	Play::DrawFontText("40px", "Press SPACE to PLAY", { DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2 - 140 }, Play::CENTRE);
	Play::PresentDrawingBuffer();

	if (Play::KeyPressed(KEY_SPACE))
	{
		Play::PlayAudio("hit");
		if (playingSong == false)
		{
			songId = Play::StartAudioLoop("main");
			playingSong = true;
		}
		guiState = GUI_PLAY;
	}
}

// Displays GUI during game
void DisplayInGameGUI()
{
	if (HealthBar::GetInstance().IsAlive())
	{
		// Playing mode
		// Update every game object
		renderHandler.Render();
		enemyHandlerLeft.Display();
		foodHandlerLeft.Display();
		enemyHandlerRight.Display();
		foodHandlerRight.Display();
		HealthBar::GetInstance().Display();

		// Display bottom tables
		bottomTables.Display();
		
		// Display score, level and text on top of the screen
		Play::DrawFontText("40px", "TAB: Help", { 0, DISPLAY_HEIGHT - 40 }, Play::LEFT);
		Play::DrawFontText("40px", "Score: " + std::to_string(ScoreHolder::GetInstance().GetScore()), {DISPLAY_WIDTH / 2 - 150, DISPLAY_HEIGHT - 40}, Play::CENTRE);
		Play::DrawFontText("40px", "Level: " + std::to_string(DifficultyHandler::GetInstance().GetLevel()), {DISPLAY_WIDTH / 2 + 150, DISPLAY_HEIGHT - 40}, Play::CENTRE);
		
		Play::PresentDrawingBuffer();

		if (Play::KeyPressed(KEY_TAB))
		{
			guiState = GUI_INSTRUCTIONS;
		}
	}
	else
	{
		guiState = GUI_GAMEOVER;
	}
}

// Restart all objects
void ReStartGame()
{
	HealthBar::GetInstance().ReStart();
	ScoreHolder::GetInstance().ReStart();
	enemyHandlerLeft.ReStart();
	enemyHandlerRight.ReStart();
	playerHandler.ReStart();
	background.SetSprite(main_gui, 0.0f);
	DifficultyHandler::GetInstance().ReStart();
	TableHandler::GetInstance().ReStart();
}

// Displays game over
void DisplayGameOverGUI()
{
	// Displays instructions
	Play::DrawFontText("40px", "Game Over", { DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2 + 260 }, Play::CENTRE);
	Play::DrawFontText("40px", "Final Score: " + std::to_string(ScoreHolder::GetInstance().GetScore()), {DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2 + 130}, Play::CENTRE);
	Play::DrawFontText("40px", "Train your catching and throwing skills", { DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2 }, Play::CENTRE);
	Play::DrawFontText("40px", "Press SPACE to MAIN SCREEN", { DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2 - 140 }, Play::CENTRE);
	Play::PresentDrawingBuffer();

	if (Play::KeyPressed(KEY_SPACE))
	{
		Play::PlayAudio("hit");
		if (playingSong == true)
		{
			Play::StopAudioLoop(songId);
			playingSong = false;
		}

		ReStartGame();

		guiState = GUI_MAIN;
	}
}

// To change initial backgrounds
void DisplayGame()
{
	switch (guiState)
	{
	case GUI_MAIN:
		DisplayMainScreen();
		break;

	case GUI_MAIN2:
		DisplaySecondScreen();
		break;

	case GUI_MAIN3:
		DisplayThirdScreen();
		break;

	case GUI_MAIN4:
		DisplayFourthScreen();
		break;

	case GUI_INSTRUCTIONS:
		DisplayInstructions();
		break;

	case GUI_PLAY:
		DisplayInGameGUI();
		break;
	case GUI_GAMEOVER:
		DisplayGameOverGUI();
		break;
	}
}


// The entry point for a PlayBuffer program
void MainGameEntry( PLAY_IGNORE_COMMAND_LINE )
{
	Play::CreateManager( DISPLAY_WIDTH, DISPLAY_HEIGHT, DISPLAY_SCALE );

	Play::LoadBackground("Data\\Backgrounds\\background.png");

	Play::CentreAllSpriteOrigins();

	// Create background
	background = MainGameObject(TYPE_BACKGROUND, main_gui, 640.0f, 360.0f, "main", 0, 1.0f, 0.0f);

	bottomTables = MainGameObject(TYPE_EXTRA_SCENERY, extrascenery, 636.0f, 77.0f, "extrascenery", 0, 1.0f, 0.0f);

	// Creates healthbar
	HealthBar::GetInstance().Create();

	// Creates the player
	playerHandler.Create();

	// Pass a reference of the player handler so when food items are created
	// they have a reference of the player if the player catches food
	foodHandlerLeft.SetPlayerHandler(&playerHandler);
	// Food is created before so it can be assigned to an enemy
	foodHandlerLeft.Create(DIRECTION_LEFT);
	// Pass a reference of the food handler so when enemies are created 
	// they have a reference to the food they are carrying
	enemyHandlerLeft.SetFoodHandler(&foodHandlerLeft);
	// Create enemies that appear on the left of the screen
	enemyHandlerLeft.Create(DIRECTION_LEFT);

	// Pass a reference of the player handler so when food items are created
	// they have a reference of the player if the player catches food
	foodHandlerRight.SetPlayerHandler(&playerHandler);
	// Food is created before so it can be assigned to an enemy
	foodHandlerRight.Create(DIRECTION_RIGHT);
	// Pass a reference of the food handler so when enemies are created 
	// they have a reference to the food they are carrying
	enemyHandlerRight.SetFoodHandler(&foodHandlerRight);
	// Create enemies that appear on the left of the screen
	enemyHandlerRight.Create(DIRECTION_RIGHT);

	// Create tables
	TableHandler::GetInstance().Create(150.f, 1125.0f, 128.0f, 475.f);

	// Set render handler
	renderHandler.SetPlayerHandler(&playerHandler);
}


// Called by PlayBuffer every frame (60 times a second!)
bool MainGameUpdate( float elapsedTime )
{
	gameState.timer += elapsedTime;

	Play::ClearDrawingBuffer( Play::cOrange );
	Play::DrawBackground();

	// Display background and game accordingle to menu state
	DisplayGame();

	// Check if it needs to increase difficulty
	DifficultyHandler::GetInstance().CheckDifficulty();

	Play::PresentDrawingBuffer();
	return Play::KeyDown( (Play::KeyboardButton)KEY_ESCAPE );
}

// Gets called once when the player quits the game 
int MainGameExit( void )
{
	Play::DestroyManager();
	return PLAY_OK;
}

