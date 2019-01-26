/*
	Nathan Harris
	8-8-16
	Factory pattern for easily creating characters.

	An id, which can be retrieved from using the CharacterClass enum's backing int value, with a character name are passed, and a Character type object is returned with randomized stats.

	This will allow me to create characters with a single line, rather than a bunch of other logic. This can also be extended and accessible from the class.
*/
#pragma once

#include <string>

#include "Character.h"

namespace RPG
{
	class CharacterFactory
	{
	public:
		static Character CreateCharacter(const CharacterClass classId, const std::string name);

	private:
		CharacterFactory() { }
		~CharacterFactory() { }
	};
}
