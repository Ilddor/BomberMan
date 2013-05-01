#pragma once

#include <SFML\Graphics.hpp>

#include "Misc.h"

class CControl
{
protected:
	EGameStates m_state;
public:
	void setState(EGameStates state) { m_state = state; };
	EGameStates getState() { return m_state; };

	virtual bool mousePressed(sf::Event::MouseButtonEvent& mouse);

	virtual void draw(sf::RenderWindow* window);

	CControl() = delete;
	CControl(EGameStates state): m_state(state) {};
};