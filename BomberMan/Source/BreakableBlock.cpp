#include "BreakableBlock.h"
#include <string>

void CBreakableBlock::draw(sf::RenderWindow* window)
{
	window->draw(m_sprite);
}

bool CBreakableBlock::destroy()
{
	m_destroyed = true;
	return true;
}

void CBreakableBlock::ticker(const sf::Clock& clock)
{

}

CBreakableBlock::CBreakableBlock(int id, const sf::Vector2f& myPos, const sf::Vector2f& fieldPos, CTextureBase* texturebase)
{
	m_textureBase = texturebase;
	m_isLethal = false;
	m_sprite.setTexture(m_textureBase->m_textures[1][0]);
	m_sprite.setPosition(fieldPos.x + 16*myPos.x, fieldPos.y + 16*myPos.y); 
	m_position = myPos;
	m_destroyed = false;
	m_isLethal = false; 
}


CBreakableBlock::~CBreakableBlock(void)
	{
	}
