/*
	Nathan Harris
	7-12-15
	Class definition for the base character class, with a name and attributes data struct.
*/

#pragma once

#include <string>
#include <functional>
#include <vector>

#include <boost/serialization/vector.hpp>
#include <boost/archive/binary_oarchive.hpp>

#include "CharacterClass.h"

namespace RPG
{
	// Data structure for role-playing attributes.
	struct Attributes
	{
	public:
		mutable int Health;
		mutable int Strength;
		mutable int Wisdom;
		mutable int Charisma;
		mutable int Dexterity;
		mutable int Intelligence;

	private:
		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& arch, const unsigned int version)
		{
			arch & Charisma;
			arch & Dexterity;
			arch & Health;
			arch & Intelligence;
			arch & Strength;
			arch & Wisdom;
		}
	};

	class Ability;

	// Base class for all playable and non-playable characters.
	class Character
	{
	public:
		Character();
		Character(const std::string name);
		~Character();

		// Displays the character's attributes and name.
		void DisplayInfo() const;

		// Returns a string representation of the Class member enumeration value.
		const std::string& GetClassDisplayString() const { return CharacterClassMap.at(Class); }

		// Gets the character's current health.
		const int& GetCurrentHealth() const { return CurrentHealth; }

		void IncrementHealth(const int byAmount) const;

		void IncrementMaxHealth(const int byAmount) const;

		// Get the character's name.
		const std::string& GetCharacterName() const { return CharacterName; }

		// Returns a reference to the character's attributes struct
		const Attributes& GetStats() const { return Stats; }

		const std::vector<Ability>& GetAbilities() const { return Abilities; }

	protected:
		mutable int CurrentHealth;

		std::string CharacterName;

		Attributes Stats;
		CharacterClass Class;

		std::vector<std::string> CatchPhrases;
		std::vector<Ability> Abilities;

	private:
		friend class boost::serialization::access;

		virtual void _registerAbilities() { }

		template<class Archive>
		void serialize(Archive& arch, const unsigned int version)
		{
			arch & CharacterName;
			arch & Class;
			arch & Stats;
			arch & CatchPhrases;
			arch & CurrentHealth;

			_registerAbilities();
		}

		const std::string& _getRandomCatchPhrase() const;
	};

	class Ability
	{
	public:
		typedef std::function<void(const Character& target, const Character& player)> AbilityFunction;

		Ability() { }
		Ability(const std::string name, AbilityFunction function);
		~Ability() { }

		const std::string& GetName() const { return _abilityName; }

		const AbilityFunction& GetFunction() const { return _function; }

	private:
		std::string _abilityName;
		AbilityFunction _function;
	};
}
