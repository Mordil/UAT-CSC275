/*
	Nathan Harris
	8-17-16
*/

#pragma once

#include <string>
#include <vector>
#include <mutex>

#include "GameState.h"

namespace RPG
{
	// Static utilitiy class for file I/O.
	class FileUtility
	{
	public:
		/*
			Saves the provided state to a binary file with the provided file name.
			fileName = Name of the file without an extension
			stateToSave = Game State object to serialize and save.
			Returns true if the save was successful.
		*/
		static bool SaveGame(const std::string& fileName, const GameState& stateToSave);

		// Loads the specified file and returns a populated RPG::GameState.
		static GameState LoadGame(const std::string& fileName);

		static const std::vector<std::string>& GetSaveFileNames()
		{
			_refreshSaveFolder();
			return _saveFileNames;
		}

	private:
		// Hide constructor so instances cannot be created.
		FileUtility() { }
		~FileUtility() { }

		static const std::string _fileExtension;
		static const std::string _saveFolderName;
		static const std::string _saveFolderSubpath;
		static std::mutex _lockObj;

		static std::vector<std::string> _saveFileNames;

		static void _refreshSaveFolder();

		// Creates the save folder directory if it doesn't exist.
		// Returns the true if successful / does exist.
		static bool _ensureSaveDirectoryExists();

		// Creates a standard string with the subpath folder and extension attached to the file name provided.
		static const std::string _createFullSaveFileNameString(const std::string& fileName);
	};
}
