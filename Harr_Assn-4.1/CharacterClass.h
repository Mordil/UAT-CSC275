/*
	Nathan Harris
	8-18-16
*/

#pragma once

#include <map>
#include <string>

namespace RPG
{
	// Enumeration of available RPG classes.
	enum CharacterClass { CHAR_UNDEFINED_MIN, WARRIOR, MAGE, RANGER, CHAR_UNDEFINED_MAX };

	// Static lookup of the friendly display string of the RPG class enum.
	const std::map<int, std::string> CharacterClassMap = {
		{ CharacterClass::CHAR_UNDEFINED_MIN, "Undefined" },
		{ CharacterClass::WARRIOR, "Warrior" },
		{ CharacterClass::MAGE, "Mage" },
		{ CharacterClass::RANGER, "Ranger" }
	};
}
