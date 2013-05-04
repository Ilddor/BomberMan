#pragma once

#include "Control.h"
#include <SFML\Graphics.hpp>

class CTextField :
	public CControl
{
protected:
	sf::RectangleShape m_background;
	sf::Text m_text;
	sf::Font m_font;
public:
	bool mousePressed(sf::Event::MouseButtonEvent& mouse);
	void KeyPressed(sf::Event::KeyEvent& keyboard);

	void draw(sf::RenderWindow* window);

	sf::String getString();

	CTextField(EGameStates state, sf::Vector2f position = sf::Vector2f(0,0), sf::Vector2f size = sf::Vector2f(200,35));
	~CTextField(void);
};

