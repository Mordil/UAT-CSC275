/*
	Nathan Harris
	8-17-16
*/

#include <thread>
#include <fstream>

#include <boost/filesystem.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/algorithm/string.hpp>

#include "FileUtility.h"

const std::string RPG::FileUtility::_fileExtension = ".sav";
const std::string RPG::FileUtility::_saveFolderName = "saves";
const std::string RPG::FileUtility::_saveFolderSubpath = "./" + RPG::FileUtility::_saveFolderName;

std::mutex RPG::FileUtility::_lockObj;
std::vector<std::string> RPG::FileUtility::_saveFileNames;

bool RPG::FileUtility::SaveGame(const std::string& fileName, const GameState& stateToSave)
{
	auto successResult = true;

	std::string filePathString = _createFullSaveFileNameString(fileName);

	auto saveTask = [&filePathString, &stateToSave, &successResult]()
	{
		if (_ensureSaveDirectoryExists())
		{
			try
			{
				std::lock_guard<std::mutex> lock(_lockObj);

				std::ofstream outStream(filePathString);
				boost::archive::binary_oarchive archive(outStream);

				archive << stateToSave;

				_refreshSaveFolder();
			}
			catch (...)
			{
				successResult = false;
			}
		}
	};

	std::thread(saveTask).join();

	return successResult;
}

RPG::GameState RPG::FileUtility::LoadGame(const std::string& fileName)
{
	GameState returnObj;

	std::string filePathString = _createFullSaveFileNameString(fileName);

	if (_ensureSaveDirectoryExists())
	{
		std::lock_guard<std::mutex> lock(_lockObj);

		std::ifstream inStream(filePathString);
		boost::archive::binary_iarchive archive(inStream);

		archive >> returnObj;
	}

	return returnObj;
}

void RPG::FileUtility::_refreshSaveFolder()
{
	if (_ensureSaveDirectoryExists())
	{
		using namespace boost::filesystem;

		path fullPath(system_complete(_saveFolderSubpath));
		directory_iterator emptyIterator;

		_saveFileNames.clear();

		for (directory_iterator i(fullPath); i != emptyIterator; ++i)
		{
			path filePath = i->path();

			if (filePath.extension().string() == _fileExtension)
			{
				std::string fileName = filePath.filename().string();
				boost::trim_if(fileName, boost::is_any_of(_fileExtension));
				_saveFileNames.push_back(fileName);
			}
		}
	}
}

bool RPG::FileUtility::_ensureSaveDirectoryExists()
{
	try
	{
		namespace fs = boost::filesystem;

		fs::path path = fs::system_complete(_saveFolderSubpath);
		fs::create_directory(path);

		return true;
	}
	catch (...)
	{
		return false;
	}
}

const std::string RPG::FileUtility::_createFullSaveFileNameString(const std::string& fileName)
{
	return _saveFolderName + "/" + fileName + _fileExtension;
}
