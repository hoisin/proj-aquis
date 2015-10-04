/*
04/09/2015

Main game class

*/

#ifndef __CAZTROID_H__
#define __CAZTROID_H__

#include <map>
#include <memory>
#include <vector>
#include <string>

#include "CObject.h"

class CGfx;

class CAztroid
{
public:
	CAztroid();
	~CAztroid();

	void LoadLevel(int level);

	void Update(float deltaT);
	void Draw(float deltaT, CGfx* pGfx);

	CObject* GetObject(const std::string& objGroup, int objIndex);

private:
	std::map<std::string, std::vector<std::shared_ptr<CObject>>> m_mEntities;
};


#endif