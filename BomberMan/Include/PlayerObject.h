#pragma once
#include "GameObject.h"
#include <list>
class CPlayerObject :
	public CGameObject
	{
	private:
		sf::Vector2f* m_fieldPos;
		sf::Vector2f* m_startPos;
		std::list<CGameObject*>* m_objects;
		bool isObjectAtPos(const sf::Vector2f& pos);
	public:
		sf::Vector2f calculatePositionOnGameField(int x, int y);
		void KeyPressed(sf::Event::KeyEvent& keyboard);
		void move(int x, int y);
		void draw(sf::RenderWindow* window);
		void destroy();
		CPlayerObject(int id, sf::Vector2f* fieldPos, sf::Vector2f* startPos, std::list<CGameObject*>* objects);
		~CPlayerObject(void);
	};

