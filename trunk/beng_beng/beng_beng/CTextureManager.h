//--------------------------------------------------------------------------
//
//	26/02/2015
//
//	Texture Manager. Handles texture loading from file (only BMP currently).
//	May extend support for render-to-texture.
//
//	Author: SeaFooD © 2015
//
//--------------------------------------------------------------------------

#ifndef __CTEXTUREMANGER_H__
#define __CTEXTUREMANGER_H__

class CTexture2D;
class CTextureLoader;

#include <map>

class CTextureManager
{
public:
	CTextureManager(void);
	~CTextureManager(void);

	// Loads BMP only at the moment
	bool LoadTexture(const std::string& textureID, const std::string& texureFile);
	CTexture2D* GetTexture(const std::string &textureID);
	
private:
	std::map<std::string, CTexture2D*> m_mpTexture;
	CTextureLoader* m_pTextureLoader;
};

#endif