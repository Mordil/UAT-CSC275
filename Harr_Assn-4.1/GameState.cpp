/*
	Nathan Harris
	8-15-16
*/

#include <fstream>
#include <thread>

#include <boost/filesystem.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>

#include "GameState.h"

RPG::GameState::GameState(const Character player) : GameState::GameState()
{
	_player = player;
}
