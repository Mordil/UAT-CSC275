/*
	Nathan Harris
	7-12-15
	Implementation file for displaying different menus/headers used in the game.
*/

#include "Menus.h"
#include "Character.h"
#include "Utility.h"
#include "FileUtility.h"
#include "GameNavigation.h"

using namespace std;
using namespace RPG;

const vector<string> Menus::chapelQuotes = {
	"The wound is the place where the Light enters you.",
	"It has been said, 'time heals all wounds.' I do not agree. The wounds remain. In time, the mind, protecting its sanity, covers them with scar tissue and the pain lessens. But it is never gone.",
	"The emotion that can break your heart is sometimes the very one that heals it...",
	"Scars have the strange power to remind us that our past is real."
};

void Menus::_displayApplicationHeader()
{
	system("cls");

	cout << "===================" << "\n";
	cout << "    CONSOLE RPG    " << "\n";
	cout << "===================" << "\n\n";
}

void Menus::_displayCharacterCreationHeader()
{
	_displayApplicationHeader();

	cout << "--- Character Creation ---" << "\n\n";
}

void Menus::DisplayMainMenu(const bool& hasSavedGames)
{
	_displayApplicationHeader();

	cout << "--- Main Menu ---" << "\n\n";

	cout << "[1] New Game" << "\n";

	if (hasSavedGames)
	{
		cout << "[2] Load Save" << "\n\n";

		cout << "[3] Quit Game" << "\n\n";
	}
	else
	{
		cout << "\n" << "[2] Quit Game" << "\n\n";
	}
}

void Menus::DisplayLoadMenu(const vector<string>& fileNames)
{
	_displayApplicationHeader();

	cout << "--- Saved Games ---" << "\n\n";

	for (int i = 0; i < fileNames.size(); ++i)
	{
		cout << "[" << i + 1 << "] " << fileNames[i] << "\n";
	}

	cout << "\n" << "[" << fileNames.size() + 1 << "] Back" << "\n\n";
}

void Menus::DisplayCharacterClassSelectionMenu()
{
	_displayCharacterCreationHeader();

	cout << "- Class Selection -" << "\n\n";

	for (int i = 1; i < CharacterClass::CHAR_UNDEFINED_MAX; ++i)
	{
		try
		{
			cout << "[" << i << "] " << CharacterClassMap.find(i)->second << "\n";
		}
		catch (...)
		{
			cout << "Missing CharacterClass Display String for value \"" << i << "\"\n";
		}
	}

	cout << "\n";
}

void Menus::DisplayCharacterAttributeAllocMenu(const int& pointsRemaining, const Attributes& stats)
{
	_displayCharacterCreationHeader();

	cout << "- Attribute Assignment -" << "\n\n";
	cout << "Select an attribute to increase by 1 point. (" << pointsRemaining << " remaining)\n\n";

	cout << "[1] Health: " << stats.Health << "\n\n";
	
	cout << "[2] Strength:\t\t" << stats.Strength << "\n";
	cout << "[3] Wisdom:\t\t" << stats.Wisdom << "\n";
	cout << "[4] Charisma:\t\t" << stats.Charisma << "\n";
	cout << "[5] Dexterity:\t\t" << stats.Dexterity << "\n";
	cout << "[6] Intelligence:\t" << stats.Intelligence << "\n\n";
}

void Menus::DisplayGameMenu(const string& playerName)
{
	_displayApplicationHeader();

	cout << "Welcome home, " << playerName << ".\n\n";

	cout << "--- Map ---" << "\n\n";

	for (int i = 1; i < GameNavigation::NAV_UNDEFINED_MAX; ++i)
	{
		try
		{
			cout << "[" << i << "] " << GameNavigationMap.find(i)->second << "\n";
		}
		catch (...)
		{
			cout << "Missing GameNavigation Display String for value \"" << i << "\"\n";
		}

		// if this is the 2nd to last or last navigation option, add some extra formatting
		if (i == GameNavigation::EXIT_GAME - 1 ||
			i == GameNavigation::EXIT_GAME)
		{
			cout << "\n";
		}
	}
}

void Menus::DisplayCharacterStatScreen(const Character& player)
{
	_displayApplicationHeader();

	cout << "--- Character Info ---" << "\n\n";

	player.DisplayInfo();

	cout << "\n\n";

	system("pause");
}

void Menus::DisplayChapelScreen()
{
	_displayApplicationHeader();

	cout << "--- Chapel ---" << "\n\n";

	cout << "Chaplan: \"" << chapelQuotes[GetRandomValue(0, chapelQuotes.size())] << "\"" << "\n\n";

	cout << "You have been healed to full health." << "\n\n\n";

	system("pause");
}

void Menus::DisplaySaveScreen(const SaveState& saveState)
{
	_displayApplicationHeader();

	cout << "Saving the game..." << "\n\n";

	while (true)
	{
		switch (saveState)
		{
			case SaveState::SUCCESS:
				cout << "Your progress has been saved!" << "\n\n\n";

				system("pause");
				return;

			case SaveState::FAILED:
				cout << "Something went wrong, and your file could not be saved." << "\n\n\n";

				system("pause");
				return;

			default:
				break;
		}
	}
}

void Menus::DisplayForestScreen()
{
	_displayApplicationHeader();

	cout << "- Redbark Forest -" << "\n\n";
}

void Menus::DisplayCombatMenu(const Character& monster, const Character& player)
{
	DisplayForestScreen();

	cout << monster.GetCharacterName() << ":\n";
	cout << monster.GetCurrentHealth() << " / " << monster.GetStats().Health << "\n\n";

	cout << player.GetCharacterName() << ":\n";
	cout << player.GetCurrentHealth() << " / " << player.GetStats().Health << "\n\n\n";

	for (int i = 0; i < player.GetAbilities().size(); ++i)
	{
		cout << "[" << i + 1 << "] " << player.GetAbilities()[i].GetName() << "\n";
	}

	cout << "\n";
}

void Menus::DisplayQuitScreen()
{
	_displayApplicationHeader();

	cout << "Thanks for playing!" << "\n\n\n";

	system("pause");
}

int Menus::GetNavigation(const string& instructionText)
{
	cout << instructionText << "  ";

	string userInput = "";	
	cin >> userInput;

	// attempts to convert from string to int and return the value
	try
	{
		return stoi(userInput, nullptr);
	}
	catch (...)
	{
		// if there were exceptions, just return 0
		return 0;
	}
}
