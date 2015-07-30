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

	void Run();

private:
	bool Intitialise();

	void Update();

	void Draw();

private:
	bool m_bRun;

	CGfx* m_pGfx;
};


#endif