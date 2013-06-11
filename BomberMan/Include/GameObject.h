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
		sf::Vector2i inputPos;
		inputPos.x = (int)pos.x;
		inputPos.y = (int)pos.y;
		for(std::list<CGameObject*>::iterator it = m_objects->begin(); it != m_objects->end(); it++)
		{
			if((*it)->getPos().x == inputPos.x && (*it)->getPos().y == inputPos.y)
				return true;	
		}
		return false;
	}
	sf::Vector2f calculatePositionOnGameField(int x, int y) { return sf::Vector2f((float)(((x - 20) - ((int)(x - 20) % 16))/16),(float)(((y - 20) - ((int)(y - 20) % 16))/16)); }
	virtual void draw(sf::RenderWindow* window) = 0;
	virtual void destroy() = 0;
	virtual void ticker(const sf::Clock& clock) = 0;
	sf::Vector2f getPos() { return m_position; }
};