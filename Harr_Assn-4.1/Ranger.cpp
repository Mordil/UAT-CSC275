/*
	Nathan Harris
	7-12-15
	Class implementation of the RPG class "Ranger".
*/

#include "Ranger.h"

RPG::Ranger::Ranger()
{
	Character::Class = CharacterClass::RANGER;

	// assign default base stats
	{
		Character::Stats.Intelligence = 6;
		Character::Stats.Strength = 6;
		Character::Stats.Charisma = 8;
		Character::Stats.Wisdom = 8;
		Character::Stats.Dexterity = 10;
		Character::Stats.Health = 10;
	}

	Character::CurrentHealth = Stats.Health;

	// "register" catch phrases
	Character::CatchPhrases = {
		"I can hit a bird in the air, flying.",
		"Nowhere to hide!",
		"I should have been a farmer like my father wanted...",
		"Lousy pay, constant danger..."
	};

	_registerAbilities();
}

RPG::Ranger::Ranger(const std::string name) : Ranger()
{
	Character::CharacterName = name;
}

RPG::Ranger::Ranger(const std::string name, const Attributes stats) : Ranger(name)
{
	Character::Stats = stats;
	Character::CurrentHealth = stats.Health;
}

RPG::Ranger::~Ranger() { }

void RPG::Ranger::_registerAbilities()
{
	Abilities.clear();

	Abilities = {
		Ability("Attack", [](const Character& target, const Character& player)
			{
				int damage = (player.GetStats().Dexterity + player.GetStats().Charisma) / 4;
				target.IncrementHealth(-damage);
			})
	};
}
