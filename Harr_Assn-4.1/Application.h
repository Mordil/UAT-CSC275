/*
	Nathan Harris
	7-10-15
	Class definition for the "application" object.
*/

#pragma once

#include <mutex>

#include "GameState.h"
#include "Warrior.h"
#include "Mage.h"
#include "Ranger.h"

using namespace std;

namespace RPG
{

	class Application
	{
	public:
		Application() { }
		~Application() { }

		// Runs the application.
		void Run();

		// Starts the "game".
		void PlayGame();

		// Takes the player into the forest.
		void GoToChapel();

		// Saves the player's game.
		void SaveGame();

		// Takes the player into the forest.
		void GoToForest();

		// Displays closing message to user and prepares to shutdown the app.
		void Shutdown();

		// Has the user allocate points to stats of their choice.
		void IncreaseStats(const Character& player, int attributePointsToSpend);

		// Starts the game from a save file.
		bool LoadSave();

		// Takes the player through character creation and returns the generated object.
		Character CharacterCreation();

	private:
		RPG::GameState _gameState = RPG::GameState();
		std::mutex _lockObj;
	};
}
