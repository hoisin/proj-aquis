/*
	$ CTimer.h, Revision 1.0 $

	Class which provides timer functionality
*/

#pragma once
#ifndef __CTIMER_H__
#define __CTIMER_H__

#include <Windows.h>

class CTimer
{
protected:
	double m_secondsPerCount;
	double m_deltaTime;

	__int64 m_currentTime;
	__int64 m_prevTime;
	__int64 m_stopTime;
	__int64 m_pauseTime;
	__int64 m_baseTime;
	
	bool m_bStopped;	

public:
	CTimer(void);

	float Time(void) const;
	float DeltaTime(void) const;

	void Reset(void);
	void Start(void);
	void Stop(void);
	void Tick(void);
};

#endif



