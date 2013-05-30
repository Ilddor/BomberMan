#pragma once
#include "GameObject.h"
class CPlayerObject :
	public CGameObject
	{
	private:
		sf::Vector2f* m_fieldPos;
		sf::Vector2f* m_startPos;
	public:
		void KeyPressed(sf::Event::KeyEvent& keyboard);
		void draw(sf::RenderWindow* window);
		void destroy();
		CPlayerObject(int id, sf::Vector2f* fieldPos, sf::Vector2f* startPos);
		~CPlayerObject(void);
	};

