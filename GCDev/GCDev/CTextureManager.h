/*
	30/07/2015

	SDL texture manager
*/

#ifndef __CTEXTUREMANAGER_H__
#define __CTEXTUREMANAGER_H__

#include <vector>
#include <string>
#include "SDL.h"


class CTexture 
{
public:
	CTexture(SDL_Surface* pTexSurface, Uint16 texWidth, Uint16 texHeight);
	CTexture();
	~CTexture();

	Uint16 GetTotalRowAnimations(Uint16 row);
	Uint16 GetTotalTypesAnimations();

public:
	SDL_Surface*			pSurface;		// Handle to loaded texture
	Uint16					width;			// Width of whole texture
	Uint16					height;			// Height of whole texture

	// Animation/frame data.
	SDL_Rect				animFrame;		// Size of each animation frame

	// Store number of frames info in vector.
	// Value stored in an element represents the frames in X
	// The total elements in the vector represents the number of animations in Y
	std::vector<Uint16>		rowTotalFrames;


};



class CTextureManager
{
public:
	CTextureManager();
	~CTextureManager();

	int LoadTexture(const std::string& textureFile, CTexture* pOutTexture = nullptr);

	void SetTextureAnimationFrame(Uint16 texIdx, Uint16 width, Uint16 height);
	void AddTotalFrames(Uint16 texIdx, Uint16 totalFrames);

	Uint16 GetTotalFramesRow(Uint16 texIdx, Uint16 animRow);
	CTexture* GetTexture(Uint16 texIdx);

private:
	std::vector<CTexture*> m_pTextures;
};



#endif