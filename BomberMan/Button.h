#pragma once

#include "Control.h"
#include <functional>

class CButton :
	public CControl
{
protected:
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	std::function<void()> m_function; 
public:
	bool mousePressed(sf::Event::MouseButtonEvent& mouse);

	void draw(sf::RenderWindow* window);

	CButton(EGameStates state, std::string pathToImg, sf::Vector2f position = sf::Vector2f(0,0), std::function<void()> func = nullptr);
	~CButton(void);
};

