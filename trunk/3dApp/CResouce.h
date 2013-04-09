/*
	Base Resource class
*/

#ifndef __CRESOURCE_H__
#define __CRESOURCE_H__

#include <string>

class CResource
{
public:
	CResource(void);
	~CResource(void);

protected:
	std::string m_name;
};


#endif