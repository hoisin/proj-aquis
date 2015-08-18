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


bool CLevel::LoadLevelData(int totalLevels)
{
	// Generate arrays
	for (int i = 0; i < totalLevels; i++) {
		m_bricks.push_back(std::vector<gcmath::Vec2<int>>());
	}

	std::ifstream fileStream;

	

	std::string value;

	int level = -1;

	for (level = 0; level < totalLevels; level++) {

		std::string fileDir = "..\\Assets\\level_" + std::to_string(level + 1) + ".dat";
		fileStream.open(fileDir.c_str());

		while (!fileStream.eof()) {
			std::getline(fileStream, value);

			if (value.find("level") != std::string::npos) {
				// Nothing to do
			}
			else {

				if (value.find("bricks") != std::string::npos) {
					// Nothing to do
				} 
				else {
					// Read position data
					std::string posVal = value;
					int xPos = atoi(value.substr(3, 4).c_str());
					int yPos = atoi(value.substr(10, 4).c_str());

					m_bricks[level].push_back(gcmath::Vec2<int>(xPos, yPos));
				}
			}


		}

		fileStream.close();
	}

	return true;
}


void CLevel::AddBrick(const gcmath::Vec2<int>& newBrickPos)
{
	auto newBrick = newBrickPos;

	m_brickPositions.push_back(newBrick);
}


