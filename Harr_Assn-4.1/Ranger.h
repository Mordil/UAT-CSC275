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
	// Object representing the RPG class "Ranger".
	class Ranger : public Character
	{
	public:
		// Creates a ranger character with the provided name.
		Ranger(const std::string name);
		// Creates a ranger character with the provided name and attributes.
		Ranger(const std::string name, const Attributes stats);
		~Ranger();

	private:
		Ranger();

		void _registerAbilities();
	};
}
