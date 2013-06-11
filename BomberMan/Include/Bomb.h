#pragma once
#include "GameObject.h"
class CBomb :
	public CGameObject
	{
	private:
		sf::Vector2f* m_fieldPos;
		sf::Texture m_textures[3];
		int m_animationState;
		sf::Time m_lastTick;
		int m_lastAnimationTime;

	public:
		void animate();
		void explode();
		void draw(sf::RenderWindow* window);
		bool destroy();
		void ticker(const sf::Clock& clock);
		CBomb(sf::Vector2f* fieldPos, sf::Vector2f position, std::list<CGameObject*>* objects);
		~CBomb(void);
	};

