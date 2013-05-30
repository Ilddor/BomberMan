#pragma once
#include <SFML\Graphics.hpp>
class CGameObject
{
protected:
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	sf::Vector2f m_position;
public:
	virtual void draw(sf::RenderWindow* window) = 0;
	virtual void destroy() = 0;
	sf::Vector2f getPos() { return m_position; }
};