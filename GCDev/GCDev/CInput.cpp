#include "CInput.h"

CInput::CInput() : m_pKeyboard(nullptr)
{
}


CInput::~CInput()
{
	
}


//---------------------------------------------------------------------------
//
//	Initialise()
//
//	Params:
//	keyHeldTime		-	Time(ms) to pass to indicate a key is flagged as held
//
//	Descrition:
//	Initialises the input module
//
//---------------------------------------------------------------------------
bool CInput::Initialise(Uint16 keyHeldTime)
{
	m_pKeyboard.reset(new CKeyboard);

	m_pKeyboard->SetHeldTime(keyHeldTime);

	return true;
}


//---------------------------------------------------------------------------
//
//	Initialise()
//
//	Params:
//	delta		-	Time passed since last main loop (not update tick)
//
//	Descrition:
//	Updates keys
//
//---------------------------------------------------------------------------
void CInput::Update(Uint32 delta)
{
	if (m_pKeyboard)
		m_pKeyboard->Update(delta);
}


//---------------------------------------------------------------------------
//
//	GetKeyboard()
//
//	Descrition:
//	Returns handle to keyboard 
//
//---------------------------------------------------------------------------
std::shared_ptr<CKeyboard> CInput::GetKeyboard()
{
	return m_pKeyboard;
}