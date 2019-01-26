/*
	Nathan Harris
	8-8-16
*/

#include "CharacterFactory.h"
#include "Warrior.h"
#include "Mage.h"
#include "Ranger.h"

using namespace RPG;

Character RPG::CharacterFactory::CreateCharacter(const CharacterClass classId, const std::string name)
{
	Character result;

	switch (classId)
	{
		case CharacterClass::WARRIOR:
			result = Warrior(name);
			break;

		case CharacterClass::RANGER:
			result = Ranger(name);
			break;

		case CharacterClass::MAGE:
			result = Mage(name);
			break;
	}

	return result;
}
