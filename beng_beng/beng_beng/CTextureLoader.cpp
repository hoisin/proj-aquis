#include "CTextureLoader.h"
#include "FreeImage.h"

CTextureLoader::CTextureLoader()
{
	FreeImage_Initialise();
}


CTextureLoader::~CTextureLoader()
{
	FreeImage_DeInitialise();
}


bool CTextureLoader::LoadFile(const std::string &fileName, unsigned int &outWidth, unsigned int &outHeight,
		unsigned char** pOutData)
{
	FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;

	// Pointer to the image, once loaded
	FIBITMAP *dib(0);

	// pointer to the image data
	BYTE* bits(0);
	
	unsigned int width(0), height(0);

	fif = FreeImage_GetFileType(fileName.c_str(), 0);

	// If still unknown, try to get the file format from the file extension
	if(fif == FIF_UNKNOWN)
		fif = FreeImage_GetFIFFromFilename(fileName.c_str());

	if(fif == FIF_UNKNOWN)
		return false;

	// check that the pluging has reading capabilities and load the file
	if(FreeImage_FIFSupportsReading(fif))
		dib = FreeImage_Load(fif, fileName.c_str());

	// If the image failed to load, return fail
	if(!dib) 
		return false;

	// Retrieve the image data
	bits = FreeImage_GetBits(dib);

	// Get the image height and width
	width = FreeImage_GetWidth(dib);
	height = FreeImage_GetHeight(dib);

	// If thie somehow one of these fail, return fail
	if(bits == 0 || width == 0 || height == 0)
		return false;

	unsigned int bpp = FreeImage_GetBPP(dib) / 8;

	// Create copy of image data
	*pOutData = new unsigned char[bpp * width * height];
	outWidth = width;
	outHeight = height;

	memcpy(*pOutData, bits, bpp * width * height);

	FreeImage_Unload(dib);

	return true;
}



bool CTextureLoader::LoadBMP(const std::string &fileName, unsigned int &outWidth, unsigned int &outHeight,
		unsigned char** pOutData)
{
	// Read header data from BMP
	unsigned char header[54];	// Each BMP has a 54-byte header
	unsigned int dataPos;		// Position in the file where the actual data begins
	unsigned int imageSize;

	// Open the file
	FILE *pFile = NULL;// = fopen(fileName.c_str(), "rb");
	fopen_s(&pFile, fileName.c_str(), "rb");

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

	*pOutData = pData;

	return true;
}