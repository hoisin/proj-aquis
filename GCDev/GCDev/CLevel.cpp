#include <iostream>
#include <fstream>
#include <string>
#include "CLevel.h"


CLevel::CLevel()
{
}


CLevel::~CLevel()
{
}


//---------------------------------------------------------------------------
//
//	LoadLevelData()
//
//	Params:
//	fileDir		-	file location
//
//	Description:
//	Loads level data from level data file
//
//---------------------------------------------------------------------------
bool CLevel::LoadLevelData(const std::string& fileDir)
{
	std::ifstream fileStream;
	std::string value;

	fileStream.open(fileDir.c_str());

	// Fail if cannot open/find file
	if (!fileStream.is_open()) 
		return false;

	int totalLevels = 0;
	while (!fileStream.eof()) {
		std::getline(fileStream, value);

		// Find total levels in level data
		if (value.find("total") != std::string::npos)
			totalLevels = atoi(value.substr(6, 1).c_str());

		// Generate arrays
		for (int i = 0; i < totalLevels; i++)
			m_bricks.push_back(std::vector<gcmath::Vec2<int>>());
		
		// Load level data for total levels
		for (int levels = 0; levels < totalLevels; levels++) {
			bool bNextLevelData = false;

			// Until we have read all data for current level
			while (!bNextLevelData) {
				std::getline(fileStream, value);

				// Finished current level loading, exit loop to load next set of level data
				if (value.find("#levelend") != std::string::npos)
					bNextLevelData = true;

				if (value.find("level") != std::string::npos) {
					// Nothing to do, currently redundant
				}
				else {

					if (value.find("bricks") != std::string::npos) {
						// Nothing to do, currently redundant
					}
					else {
						// Read position data
						std::string posVal = value;
						int xPos = atoi(value.substr(3, 4).c_str());
						int yPos = atoi(value.substr(10, 4).c_str());

						m_bricks[levels].push_back(gcmath::Vec2<int>(xPos, yPos));
					}
				}
			}
		}
	}		

	fileStream.close();

	return true;
}
