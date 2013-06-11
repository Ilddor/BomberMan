#pragma once
#include "GameObject.h"
class CUnbreakableBlock :
	public CGameObject
	{
	public:
		void draw(sf::RenderWindow* window);
		bool destroy();
		void ticker(const sf::Clock& clock);
		CUnbreakableBlock(int id, const sf::Vector2f& myPos, const sf::Vector2f& fieldPos);
		~CUnbreakableBlock(void);
	};

