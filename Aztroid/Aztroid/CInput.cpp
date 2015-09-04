#include "CInput.h"

CInput::CInput() : m_pKeyboard(nullptr)
{
}


CInput::~CInput()
{
	
}


bool CInput::Initialise(Uint16 keyHeldTime)
{
	m_pKeyboard.reset(new CKeyboard);

	m_pKeyboard->SetHeldTime(keyHeldTime);

	return true;
}


void CInput::Update(Uint32 delta)
{
	if (m_pKeyboard)
		m_pKeyboard->Update(delta);
}


std::shared_ptr<CKeyboard> CInput::GetKeyboard()
{
	return m_pKeyboard;
}