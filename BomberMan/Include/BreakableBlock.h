#pragma once
#include "GameObject.h"
class CBreakableBlock :
	public CGameObject
	{
	public:
		void draw(sf::RenderWindow* window);
		bool destroy();
		void ticker(const sf::Clock& clock);
		CBreakableBlock(int id, const sf::Vector2f& myPos, const sf::Vector2f& fieldPos, CTextureBase* texturebase);
		~CBreakableBlock(void);
	};

