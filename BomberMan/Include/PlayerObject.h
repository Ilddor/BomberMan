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
		sf::Vector2f m_goalPosition;
		sf::Texture m_textures[16];
		EDirections m_direction;
		int m_animationState;
		int m_animationMultiplier;
		int m_lastAnimationTime;
		void loadTextures(int id);
		sf::Time m_lastTick;
	public:
		void KeyPressed(sf::Event::KeyEvent& keyboard);
		void move(int x, int y);
		void move(sf::Vector2f moveVector);
		void animate();
		void draw(sf::RenderWindow* window);
		bool destroy();
		void ticker(const sf::Clock& clock);
		void setPos(sf::Vector2f pos);
		bool isMoving();
		CPlayerObject(int id, sf::Vector2f* fieldPos, sf::Vector2f* startPos, std::list<CGameObject*>* objects);
		~CPlayerObject(void);
	};

