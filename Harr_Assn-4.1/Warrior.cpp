/*
	Nathan Harris
	7-12-15
	Class implementation of the RPG class "Warrior".
*/

#include "Warrior.h"

RPG::Warrior::Warrior()
{
	Character::Class = CharacterClass::WARRIOR;

	// assign default base stats
	{
		Character::Stats.Charisma = 6;
		Character::Stats.Wisdom = 6;
		Character::Stats.Intelligence = 6;
		Character::Stats.Dexterity = 8;
		Character::Stats.Strength = 10;
		Character::Stats.Health = 12;
	}

	Character::CurrentHealth = Stats.Health;

	// "register" catch phrases
	Character::CatchPhrases = {
		"I don't use my lance a lot...",
		"What's the hold up?"
	};

	_registerAbilities();
}

RPG::Warrior::Warrior(const std::string name) : Warrior()
{
	Character::CharacterName = name;
}

RPG::Warrior::Warrior(const std::string name, const  Attributes stats) : Warrior(name)
{
	Character::Stats = stats;
	Character::CurrentHealth = stats.Health;
}

RPG::Warrior::~Warrior() { }

void RPG::Warrior::_registerAbilities()
{
	Abilities.clear();

	Abilities = {
		Ability("Attack", [](const Character& target, const Character& player)
			{
				int damage = (player.GetStats().Strength) / 4;
				target.IncrementHealth(-damage);
			})
	};
}
