/*
	Nathan Harris
	7-12-15
	Prototypes of the functions used to display headers/menus in the game.
*/

#include <string>
#include <iostream>
#include <vector>

#include "SaveState.h"
#include "Character.h"

namespace RPG
{
	// Class object that provides a common interface for displaying menus and information to the user, as well as getting user input.
	class Menus
	{
	public:
		// Displays the game's main menu.
		static void DisplayMainMenu(const bool& hasSavedGames);

		/*
			Displays the loading menu.
			If the result equals the size + 1 of the passed vector, the user has selected to quit the application.
		*/
		static void DisplayLoadMenu(const std::vector<std::string>& fileNames);

		// Displays the character creation's class selection menu.
		static void DisplayCharacterClassSelectionMenu();

		// Displays the character creation's naming menu.
		static void DisplayCharacterNameSelectionMenu() { _displayApplicationHeader(); }

		// Displays the character creation's attribute allocation menu.
		static void DisplayCharacterAttributeAllocMenu(const int& pointsRemaining, const Attributes& stats);

		// Displays location navigation menu.
		static void DisplayGameMenu(const std::string& playerName);

		// Displays the character info screen.
		static void DisplayCharacterStatScreen(const Character& player);
		
		// Displays the chapel screen with a random quote for the chaplan.
		static void DisplayChapelScreen();

		// Displays the forest header and text.
		static void DisplayForestScreen();

		// Displays the combat menu.
		static void DisplayCombatMenu(const Character& monster, const Character& player);

		// Displays the save message screen.
		static void DisplaySaveScreen(const SaveState& saveState);

		// Displays a friendly application closing screen.
		static void DisplayQuitScreen();

		/*
			Handles user input for menu navigation.
			instructionText = optional string to set to display to the user.
			Returns 0 by default if user input fails to cast to an int.
		*/
		static int GetNavigation(const std::string& instructionText = "What would you like to do?");

	private:
		Menus() { }
		~Menus() { }

		static const std::vector<std::string> chapelQuotes;

		// Clears the last console screen and displays the formatted application header.
		static void _displayApplicationHeader();

		// Calls _displayApplicationHeader() and displays the formatted character creation header.
		static void _displayCharacterCreationHeader();
	};
}
