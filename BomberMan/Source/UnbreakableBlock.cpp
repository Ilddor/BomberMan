#include "UnbreakableBlock.h"
#include <string>

void CUnbreakableBlock::draw(sf::RenderWindow* window)
{
	window->draw(m_sprite);
}

void CUnbreakableBlock::destroy()
{

}

CUnbreakableBlock::CUnbreakableBlock(int id, const sf::Vector2f& myPos, const sf::Vector2f& fieldPos)
{
	std::string texturePath = "Resources/Game/Field/unbreakable";
	texturePath += id + '0';
	texturePath += ".png";
	m_texture.loadFromFile(texturePath);
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(fieldPos.x + 16*myPos.x, fieldPos.y + 16*myPos.y);  
}


CUnbreakableBlock::~CUnbreakableBlock(void)
	{
	}
