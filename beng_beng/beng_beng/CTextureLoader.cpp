#include "CTextureLoader.h"

CTextureLoader::CTextureLoader()
{
}


CTextureLoader::~CTextureLoader()
{
}


bool CTextureLoader::LoadFile(const std::string &fileName, unsigned int &outWidth, unsigned int &outHeight,
		unsigned char* pOutData)
{

	return LoadBMP(fileName, outWidth, outHeight, pOutData);
}



bool CTextureLoader::LoadBMP(const std::string &fileName, unsigned int &outWidth, unsigned int &outHeight,
		unsigned char* pOutData)
{
	// Read header data from BMP
	unsigned char header[54];	// Each BMP has a 54-byte header
	unsigned int dataPos;		// Position in the file where the actual data begins
	unsigned int imageSize;

	// Open the file
	FILE *pFile = fopen(fileName.c_str(), "rb");

	// If cannot open the file
	if(!pFile) {
		return false;
	}

	// If the file opened not a BMP file
	if(fread(header, 1, 54, pFile) != 54) {
		return false;
	}

	// Header should always start with "BM", else not valid BMP
	if(header[0] != 'B' || header[1] != 'M') {
		return false;
	}

	// Read image info
	dataPos		= *(int*)&(header[0x0A]);
	imageSize	= *(int*)&(header[0x22]);
	outWidth	= *(int*)&(header[0x12]);
	outHeight	= *(int*)&(header[0x16]);

	// In some cases BMP missing info, make up for it
	if(imageSize == 0)	imageSize = outWidth * outHeight * 3;
	if(dataPos == 0)	dataPos = 54;	// size of the header

	unsigned char* pData = new unsigned char[imageSize];

	fread(pData, 1, imageSize, pFile);

	fclose(pFile);

	pOutData = pData;
}