/*
	Nathan Harris
	8-15-16
*/

#pragma once

#include <string>

#include "Character.h"

namespace RPG
{
	// Object representing a game session's data that can be saved and loaded.
	class GameState
	{
	public:
		// Create a blank GameState to manage the game data.
		GameState() { }
		// Create a new GameState for the character provided.
		GameState(const Character player);
		~GameState() { }

		// Get a reference to the player's character.
		const Character& GetPlayer() const { return _player; }

	private:
		friend class boost::serialization::access;

		// The player's character.
		Character _player;

		template<class Archive>
		void serialize(Archive& arch, const unsigned int version)
		{
			arch & _player;
		}
	};
}
