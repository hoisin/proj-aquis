//--------------------------------------------------------------------------
//
//	16/04/2014
//
//	Class handling texture loading
//
//	Note: This has been tested for the BMP loading and is working correctly.
//		Simply read data retrieved and wrote it back to another file for test.
//
//	Using FreeImage library for loading images
//
//	Author: SeaFooD © 2014
//
//--------------------------------------------------------------------------

#ifndef __CTEXTURELOADER_H__
#define __CTEXTURELOADER_H__

#include <string>

class CTextureLoader
{
public:
	CTextureLoader();
	~CTextureLoader();

	bool LoadFile(const std::string &fileName, unsigned int &outWidth, unsigned int &outHeight,
		unsigned char** pOutData);

	bool LoadBMP(const std::string &fileName, unsigned int &outWidth, unsigned int &outHeight,
		unsigned char** pOutData);

private:
};

#endif