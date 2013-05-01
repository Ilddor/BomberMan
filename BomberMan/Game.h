#pragma once

#include <SFML\Graphics.hpp>
#include <list>

#include "Misc.h"
#include "Control.h"

class CGame
{
private:
	EGameStates m_state;
	sf::RenderWindow* m_windowPtr;
	std::list<CControl> m_controls;
public:
	void setWindowPointer(sf::RenderWindow* ptr);

	void draw();
	void handleEvent(sf::Event& ev);

	void addControl(CControl control);

	CGame(void);
	~CGame(void);
};

