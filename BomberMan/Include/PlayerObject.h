#pragma once
#include "GameObject.h"
#include "Misc.h"
#include <list>
class CPlayerObject :
	public CGameObject
	{
	private:
		sf::Vector2f* m_fieldPos;
		sf::Vector2f* m_startPos;
		sf::Texture m_textures[16];
		EDirections m_direction;
		int m_animationState;
		int m_animationMultiplier;
		void loadTextures(int id);
	public:
		void KeyPressed(sf::Event::KeyEvent& keyboard);
		void move(int x, int y);
		void animate();
		void draw(sf::RenderWindow* window);
		void destroy();
		CPlayerObject(int id, sf::Vector2f* fieldPos, sf::Vector2f* startPos, std::list<CGameObject*>* objects);
		~CPlayerObject(void);
	};

