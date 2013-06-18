#include "UnbreakableBlock.h"
#include <string>

void CUnbreakableBlock::draw(sf::RenderWindow* window)
{
	window->draw(m_sprite);
}

bool CUnbreakableBlock::destroy()
{
	return false;
}

void CUnbreakableBlock::ticker(const sf::Clock& clock)
{

}

CUnbreakableBlock::CUnbreakableBlock(int id, const sf::Vector2f& myPos, const sf::Vector2f& fieldPos, CTextureBase* texturebase)
{
	m_textureBase = texturebase;
	m_sprite.setTexture(m_textureBase->m_textures[2][0]);
	m_sprite.setPosition(fieldPos.x + 16*myPos.x, fieldPos.y + 16*myPos.y); 
	m_position = myPos;
	m_destroyed = false; 
}


CUnbreakableBlock::~CUnbreakableBlock(void)
	{
	}
