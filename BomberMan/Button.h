#pragma once

#include "Control.h"

class CButton :
	public CControl
{
protected:
	sf::Sprite m_sprite;
public:
	CButton(EGameStates state);
	~CButton(void);
};

