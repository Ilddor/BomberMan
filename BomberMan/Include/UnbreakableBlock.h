#pragma once
#include "GameObject.h"
class CUnbreakableBlock :
	public CGameObject
	{
	public:
		void draw(sf::RenderWindow* window);
		void destroy();
		CUnbreakableBlock(int id, const sf::Vector2f& myPos, const sf::Vector2f& fieldPos);
		~CUnbreakableBlock(void);
	};

