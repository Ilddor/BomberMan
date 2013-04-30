#pragma once

#include <SFML\Graphics.hpp>

#include "Misc.h"

class Game
{
private:
	GameStates m_state;
public:
	void handleEvent(sf::Event& ev);

	Game(void);
	~Game(void);
};

