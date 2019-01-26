/*
	Nathan Harris
	8-20-16
*/

#pragma once

#include <map>
#include <string>

namespace RPG
{
	// Enumeration of all "locations" a player can exist in. Used for switches.
	enum GameNavigation { NAV_UNDEFINED_MIN, CHAPEL, FOREST, INFO_PAGE, SAVE_GAME, EXIT_GAME, NAV_UNDEFINED_MAX };

	const std::map<int, std::string> GameNavigationMap = {
		{ GameNavigation::CHAPEL, "Visit Chapel (Heal to Full Health)" },
		{ GameNavigation::FOREST, "Adventure in the forest (Fight Monsters)" },
		{ GameNavigation::INFO_PAGE, "See Character Stats" },
		{ GameNavigation::EXIT_GAME, "Exit Game" },
		{ GameNavigation::SAVE_GAME, "Save Progress" }
	};
}
