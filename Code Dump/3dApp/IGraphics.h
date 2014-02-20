/*
	Date: 30/01/2013
	Interface for graphics component
*/

#pragma once
#ifndef __IGRAPHICS_H__
#define __IGRAPHICS_H__

#include <Windows.h>

class IGraphics
{
public:
	IGraphics(void) {}
	virtual ~IGraphics(void) {}

	virtual bool VInitialise(HWND hwnd, int screenHeight, int screenWidth, bool bVSync, bool bFullScreen, 
		float screenDepth, float screenNear) = 0;

	virtual void VShutDown(void) = 0;

	virtual bool VRenderScene(void) = 0;

	// Prototyping, loads scene from xml or some other file
	// Herp derp.... doing too much for prototyping. (Been trying to load full models etc....)
	// Too much effort. Going to procedurally generating simple shapes instead (i.e. cubes, spheres)
	virtual bool VLoadScene(void) = 0;
};

#endif