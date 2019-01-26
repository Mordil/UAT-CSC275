/*
	Nathan Harris
	8-20-16
*/

#include "Character.h"

using namespace std;
using namespace RPG;

Ability::Ability(const std::string name, const Ability::AbilityFunction function)
{
	_abilityName = name;
	_function = function;
}
