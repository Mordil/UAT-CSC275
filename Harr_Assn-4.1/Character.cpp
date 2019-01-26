/*
	Nathan Harris
	7-12-15
	Class implementation of the Character object.
*/
#include <time.h>
#include <array>
#include <iostream>

#include "Character.h"
#include "Utility.h"

using namespace std;
using namespace RPG;

Character::Character()
{
	Class = CharacterClass::CHAR_UNDEFINED_MIN;
}

Character::Character(const string name) : Character()
{
	CharacterName = name;
}

Character::~Character() { }

const std::string& Character::_getRandomCatchPhrase() const
{
	int index = GetRandomValue(0, CatchPhrases.size());
	return CatchPhrases[index];
}

void Character::DisplayInfo() const
{
	cout << "Name: " << CharacterName << "\n";
	cout << "Class: " << CharacterClassMap.at(Class) << "\n\n";

	if (CatchPhrases.size() > 0)
	{
		cout << "\"" << _getRandomCatchPhrase() << "\"\n\n";
	}

	cout << "- Attributes -" << "\n\n";

	cout << "Health: " << CurrentHealth << " / " << Stats.Health << "\n\n";

	cout << "Strength:\t" << Stats.Strength << "\n";
	cout << "Charisma:\t" << Stats.Charisma << "\n";
	cout << "Intelligence:\t" << Stats.Intelligence << "\n";
	cout << "Dexterity:\t" << Stats.Dexterity << "\n";
	cout << "Wisdom:\t\t" << Stats.Wisdom << "\n";
}

void Character::IncrementHealth(const int byAmount) const
{
	int newValue = CurrentHealth + byAmount;

	if (newValue <= 0)
	{
		CurrentHealth = 0;
	}
	else if (newValue >= Stats.Health)
	{
		CurrentHealth = Stats.Health;
	}
	else
	{
		CurrentHealth = newValue;
	}
}

void Character::IncrementMaxHealth(const int byAmount) const
{
	Stats.Health++;
	CurrentHealth = Stats.Health;
}
