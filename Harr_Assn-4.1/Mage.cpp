/*
	Nathan Harris
	7-12-15
	Class implementation for the "Mage" RPG class
*/

#include "Mage.h"

RPG::Mage::Mage()
{
	Character::Class = CharacterClass::MAGE;

	// assign default base stats
	{
		Character::Stats.Charisma = 6;
		Character::Stats.Strength = 6;
		Character::Stats.Health = 8;
		Character::Stats.Dexterity = 8;
		Character::Stats.Wisdom = 10;
		Character::Stats.Intelligence = 10;
	}

	Character::CurrentHealth = Stats.Health;

	// "register" catch phrases
	Character::CatchPhrases = {
		"The currents of magic are in upheaval.",
		"Things are starting to get a little weird.",
		"Shhh... I'm trying to think here."
	};

	_registerAbilities();
}

RPG::Mage::Mage(const std::string name) : Mage()
{
	Character::CharacterName = name;
}

RPG::Mage::Mage(const std::string name, const Attributes stats) : Mage(name)
{
	Character::Stats = stats;
	Character::CurrentHealth = stats.Health;
}

RPG::Mage::~Mage() { }

void RPG::Mage::_registerAbilities()
{
	Abilities.clear();

	Abilities = {
		Ability("Attack", [](const Character& target, const Character& player)
			{
				int damage = (player.GetStats().Intelligence + player.GetStats().Wisdom) / 4;
				target.IncrementHealth(-damage);
			})
	};
}
