/*
	Nathan Harris
	7-12-15
	Class definition of the RPG class "Warrior".
*/

#pragma once

#include <string>

#include "Character.h"

namespace RPG
{
	// Object representing the RPG class "Warrior".
	class Warrior : public Character
	{
	public:
		// Creates a warrior character with the provided name.
		Warrior(const std::string name);
		// Creates a warrior character with the provided name and attributes.
		Warrior(const std::string name, const Attributes stats);
		~Warrior();
		
	private:
		Warrior();

		void _registerAbilities();
	};
}
