#pragma once

#include <SFML\Graphics.hpp>

#include "Misc.h"

class CControl
{
private:
	CControl();
protected:
	EGameStates m_state;
public:
	void setState(EGameStates state) { m_state = state; };
	EGameStates getState() { return m_state; };

	virtual bool mousePressed(sf::Event::MouseButtonEvent& mouse) = 0;
	virtual void KeyPressed(sf::Event::KeyEvent& keyboard) = 0;

	virtual void draw(sf::RenderWindow* window) = 0;

	CControl(EGameStates state): m_state(state) {};
};