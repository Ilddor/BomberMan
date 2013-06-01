#pragma once
#include <SFML\Graphics.hpp>
#include <list>
#include <iostream>
class CGameObject
{
protected:
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	sf::Vector2f m_position;
	std::list<CGameObject*>* m_objects;
public:
	bool isObjectAtPos(const sf::Vector2f& pos)
	{
		for(std::list<CGameObject*>::iterator it = m_objects->begin(); it != m_objects->end(); it++)
		{
			if((*it)->getPos().x == pos.x && (*it)->getPos().y == pos.y)
				return true;	
		}
		return false;
	}
	sf::Vector2f calculatePositionOnGameField(int x, int y) { 
		sf::Vector2f tmp((((x - 20) - ((int)(x - 20) % 16))/16),(((y - 20) - ((int)(y - 20) % 16))/16));
		std::cout << "Clicked on (" << tmp.x << "," << tmp.y << ")\n";
		return tmp; }
	virtual void draw(sf::RenderWindow* window) = 0;
	virtual void destroy() = 0;
	sf::Vector2f getPos() { return m_position; }
};