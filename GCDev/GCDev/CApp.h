/*
	30/07/2015

	Application code
*/

#ifndef __CAPP_H__
#define __CAPP_H__

class CGfx;

class CApp
{
public:
	CApp();
	~CApp();

	bool Intitialise(unsigned int updateTick);

	void Run();

private:
	void Update(unsigned int deltaT);

	void Draw(unsigned int deltaT);

private:
	bool m_bRun;

	CGfx* m_pGfx;

	unsigned int m_lastTick;
	unsigned int m_tick;
};


#endif