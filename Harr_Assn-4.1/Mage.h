/*
	Nathan Harris
	7-12-15
	Class definition of the RPG class "Ranger".
*/

#pragma once

#include <string>

#include "Character.h"

namespace RPG
{
	// Object representing the RPG class "Mage".
	class Mage : public Character
	{
	public:
		// Creates a mage character with the provided name.
		Mage(const std::string name);
		// Creates a mage character with the provided name and attributes.
		Mage(const std::string name, const Attributes stats);
		~Mage();

	private:
		Mage();

		void _registerAbilities();
	};
}
