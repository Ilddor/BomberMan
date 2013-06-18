#pragma once
#include "GameObject.h"
class CExplosion :
	public CGameObject
	{
	private:
		int m_id;
		sf::Vector2f* m_fieldPos;
		int m_animationState;
		sf::Time m_lastTick;
		int m_lastAnimationTime;
		bool m_maxBlow;
	public:
		void animate();
		void explode();
		void draw(sf::RenderWindow* window);
		bool destroy();
		void ticker(const sf::Clock& clock);
		CExplosion(int id, sf::Vector2f* fieldPos, sf::Vector2f position, std::list<CGameObject*>* objects, CTextureBase* texturebase);
		~CExplosion(void);
	};

