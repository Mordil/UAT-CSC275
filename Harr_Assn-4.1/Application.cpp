/*
	Nathan Harris
	7-12-15
	Class implementation of the application class - functions for maintaining the game loop
		and game logic, as well as creating new characters.
*/

#include <vector>
#include <thread>
#include <iostream>

#include <boost/regex.h>
#include <boost/filesystem.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/algorithm/string.hpp>

#include "Application.h"
#include "CharacterFactory.h"
#include "FileUtility.h"
#include "Utility.h"
#include "Menus.h"
#include "SaveState.h"
#include "GameNavigation.h"

using namespace std;
using namespace RPG;

void Application::Run()
{
	bool canPlay = false;

	while (true)
	{
		bool hasSavedGames = FileUtility::GetSaveFileNames().size() > 0;

		RPG::Menus::DisplayMainMenu(hasSavedGames);

		int userSelection = Menus::GetNavigation();

		// New Game
		if (userSelection == 1)
		{
			_gameState = GameState(CharacterCreation());
			FileUtility::SaveGame(_gameState.GetPlayer().GetCharacterName(), _gameState);
			canPlay = true;
		}
		else if (userSelection == 2)
		{
			if (hasSavedGames)
			{
				canPlay = LoadSave();
			}
			else
			{
				// User has selected to quit the application.
				break;
			}
		}
		else if (userSelection == 3 && hasSavedGames)
		{
			// User has selected to quit the application.
			break;
		}

		if (canPlay)
		{
			PlayGame();
			canPlay = false;
			// autosave for good measure
			FileUtility::SaveGame(_gameState.GetPlayer().GetCharacterName(), _gameState);
		}
	}

	Shutdown();
}

void Application::PlayGame()
{
	// Game state.
	bool gameIsRunning = true;

	// loop until the user navigates to EXIT_GAME
	while (gameIsRunning)
	{
		Menus::DisplayGameMenu(_gameState.GetPlayer().GetCharacterName());

		int navResult = Menus::GetNavigation();

		// check if out of our range - if so, start loop over
		if (navResult >= GameNavigation::NAV_UNDEFINED_MAX || navResult <= GameNavigation::NAV_UNDEFINED_MIN)
		{
			continue;
		}
		else
		{
			// determine what the location is and call its logic function.
			switch (static_cast<GameNavigation>(navResult))
			{
				case GameNavigation::CHAPEL:
					GoToChapel();
					break;

				case GameNavigation::FOREST:
					GoToForest();
					break;

				case GameNavigation::INFO_PAGE:
					Menus::DisplayCharacterStatScreen(_gameState.GetPlayer());
					break;

				case GameNavigation::SAVE_GAME:
					SaveGame();
					break;

				case GameNavigation::EXIT_GAME:
					gameIsRunning = false;
					break;
			}
		}
	}
}

void Application::Shutdown()
{
	Menus::DisplayQuitScreen();
}

bool Application::LoadSave()
{
	const vector<string>* const fileNames = &FileUtility::GetSaveFileNames();
	
	int quitIndex = fileNames->size() + 1;

	while (true)
	{
		Menus::DisplayLoadMenu(*fileNames);

		int input = Menus::GetNavigation("Which game would you like to load?");

		if (input == quitIndex)
		{
			// user has selected to return to main menu
			return false;
		}
		else if (input > 0 && input < quitIndex)
		{
			_gameState = FileUtility::LoadGame((*fileNames)[input - 1]);
			return true;
		}
	}
}

Character Application::CharacterCreation()
{
	bool shouldLoop = true;
	CharacterClass selectedClass;
	string playerName;

	// Class selection
	while (shouldLoop)
	{
		Menus::DisplayCharacterClassSelectionMenu();

		int input = Menus::GetNavigation("Which class would you like to play?");

		selectedClass = static_cast<CharacterClass>(input);

		shouldLoop = (selectedClass <= CharacterClass::CHAR_UNDEFINED_MIN || selectedClass >= CharacterClass::CHAR_UNDEFINED_MAX);
	}

	// reset flag for the next loop
	shouldLoop = true;

	// player name
	while (shouldLoop)
	{
		Menus::DisplayCharacterNameSelectionMenu();

		cout << "What would you like to name your character? (6-18 characters only)  ";

		cin >> playerName;

		// regular expression to see if the user's input has any invalid characters or is too short/long
		boost::RegEx expression("^[A-z]{6,18}+$");

		// shouldLoop = true if no match
		shouldLoop = !expression.Match(playerName);
	}

	Character player = CharacterFactory::CreateCharacter(selectedClass, playerName);

	// Allow the user to allocate attribute points
	IncreaseStats(player, 5);

	return player;
}

void Application::IncreaseStats(const Character& player, int attributePointsToSpend)
{
	bool invalidInput = true;
	// Create a pointer to the player's stats to make it shorter to access
	const Attributes* playerStats = &player.GetStats();

	/*
	lambda for shorthand use during input handling
	increment the value passed, decrement the pointsToAdd, and set invalidInput to false
	*/
	auto assignAttributePoint = [&attributePointsToSpend, &invalidInput](int& valueToIncrement)
	{
		valueToIncrement++;
		attributePointsToSpend--;
		invalidInput = false;
	};

	// loop until no more.
	while (attributePointsToSpend > 0)
	{
		while (invalidInput)
		{
			Menus::DisplayCharacterAttributeAllocMenu(attributePointsToSpend, *playerStats);
			
			// switch based on input to add a point to the attribute
			// reduces points remaining by 1 after doing so
			switch (Menus::GetNavigation("Which attribute would you like to increase by 1 point?"))
			{
				case 1:
					player.IncrementMaxHealth(1);
					attributePointsToSpend--;
					invalidInput = false;
					break;

				case 2:
					assignAttributePoint(playerStats->Strength);
					break;

				case 3:
					assignAttributePoint(playerStats->Wisdom);
					break;

				case 4:
					assignAttributePoint(playerStats->Charisma);
					break;

				case 5:
					assignAttributePoint(playerStats->Dexterity);
					break;

				case 6:
					assignAttributePoint(playerStats->Intelligence);
					break;

				default:
					break;
			}
		}

		// reset the flag so the next loop can loop through input handling
		invalidInput = true;
	}
}

void Application::GoToChapel()
{
	auto goToFullHealth = [this](const Character* const player)
	{
		lock_guard<mutex> lock(this->_lockObj);

		int value = player->GetStats().Health - player->GetCurrentHealth();
		player->IncrementHealth(value);
	};

	// let this happen on a background thread so it's asynchronous
	thread(goToFullHealth, &_gameState.GetPlayer()).detach();

	Menus::DisplayChapelScreen();
}

void Application::SaveGame()
{
	SaveState state;

	auto saveFunc = [&state, this]()
	{
		state = FileUtility::SaveGame(_gameState.GetPlayer().GetCharacterName(), _gameState) ? SaveState::SUCCESS : SaveState::FAILED;
	};

	thread(saveFunc).detach();

	Menus::DisplaySaveScreen(state);
}

void Application::GoToForest()
{
	Menus::DisplayForestScreen();

	int monsterClassIndex = GetRandomValue(CharacterClass::CHAR_UNDEFINED_MIN + 1, CharacterClass::CHAR_UNDEFINED_MAX - 1);
	CharacterClass monsterClass = static_cast<CharacterClass>(monsterClassIndex);

	Character monster = CharacterFactory::CreateCharacter(monsterClass, "A Scary Monster");

	cout << "A random mob has appeared!" << "\n\n";

	system("pause");

	const Character* const player = &_gameState.GetPlayer();
	const int numOfAbilities = player->GetAbilities().size();

	while (monster.GetCurrentHealth() > 0 &&
		   player->GetCurrentHealth() > 0)
	{
		Menus::DisplayCombatMenu(monster, *player);

		int navSelection = Menus::GetNavigation();

		if (navSelection > 0 && navSelection <= numOfAbilities)
		{
			player->GetAbilities()[navSelection - 1].GetFunction()(monster, *player);

			if (monster.GetCurrentHealth() > 0)
			{
				int monsterAbility = GetRandomValue(0, monster.GetAbilities().size() - 1);
				monster.GetAbilities()[monsterAbility].GetFunction()(*player, monster);
			}
		}
	}

	Menus::DisplayForestScreen();

	if (monster.GetCurrentHealth() <= 0)
	{
		cout << "Congratulations, you have slayed " << monster.GetCharacterName() << "!\n\n";
	}
	else if (player->GetCurrentHealth() <= 0)
	{
		cout << "RIP. You have died in glorious combat." << "\n\n";
		int value = player->GetStats().Health - player->GetCurrentHealth();
		player->IncrementHealth(value);
	}

	system("pause");
}
