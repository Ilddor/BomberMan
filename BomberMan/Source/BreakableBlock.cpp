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

CBreakableBlock::CBreakableBlock(int id, const sf::Vector2f& myPos, const sf::Vector2f& fieldPos)
{
	std::string texturePath = "Resources/Game/Field/breakable";
	texturePath += id + '0';
	texturePath += ".png";
	m_texture.loadFromFile(texturePath);
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(fieldPos.x + 16*myPos.x, fieldPos.y + 16*myPos.y); 
	m_position = myPos;
	m_destroyed = false; 
}


CBreakableBlock::~CBreakableBlock(void)
	{
	}
