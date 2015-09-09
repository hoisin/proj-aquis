/*
04/09/2015

Main game class

*/

#ifndef __CAZTROID_H__
#define __CAZTROID_H__

#include <map>
#include <memory>
#include <string>

#include "CObject.h"

class CAztroid
{
public:
	CAztroid();
	~CAztroid();

	void Update(float deltaT);
	void Draw(float deltaT);

private:
	std::map<std::string, std::shared_ptr<CObject>> m_mEntities;
};


#endif