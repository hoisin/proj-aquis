/*
	30/07/2015

	Application code
*/

#ifndef __CAPP_H__
#define __CAPP_H__

#include <memory>

class CGfx;
class CInput;
class CBreakOut;

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

	void InputProcess(unsigned int deltaT);

private:
	bool m_bRun;

	CGfx* m_pGfx;
	std::shared_ptr<CInput> m_pInput;
	std::shared_ptr<CBreakOut> m_pGame;

	unsigned int m_lastLoopTick;
	unsigned int m_lastUpdateTick;
	unsigned int m_tick;
};


#endif