#include "Explosion.h"
#include <string>

void CExplosion::animate()
{
	if(m_animationState < 2 && !m_maxBlow)
	{
		m_sprite.setTexture(m_textureBase->m_textures[4][m_id*3 + m_animationState++]);
		if(m_animationState == 3)
			m_maxBlow = true;
	}
	else if(m_maxBlow && m_animationState > 0)
	{
		m_sprite.setTexture(m_textureBase->m_textures[4][m_id*3 + m_animationState--]);
	}
	else
	{
		//m_sprite.setColor(sf::Color(0,0,0,0));
		m_destroyed = true;	  
	}
}
void CExplosion::draw(sf::RenderWindow* window)
{
	window->draw(m_sprite);
}
bool CExplosion::destroy()
{
	//m_sprite.setColor(sf::Color(0,0,0,0));
	m_destroyed = true;
	return true;

}
void CExplosion::ticker(const sf::Clock& clock)
{
	m_lastAnimationTime += (clock.getElapsedTime()	- m_lastTick).asMilliseconds();
	if(m_lastAnimationTime > 500)
	{
		m_lastAnimationTime = 0;
		animate();
	}
	m_lastTick = clock.getElapsedTime();
}


CExplosion::CExplosion(int id, sf::Vector2f* fieldPos, sf::Vector2f position, std::list<CGameObject*>* objects, CTextureBase* texturebase)
{
	m_id = id;
	m_fieldPos = fieldPos;
	m_animationState = 0;
	m_textureBase = texturebase;
	m_lastTick = sf::Clock().getElapsedTime();
	m_lastAnimationTime = 0;
	m_destroyed = false;
	m_maxBlow = false;
	m_isLethal = true;
	m_position = position;
	if(id == 1)
		m_position.y -= 1;
	else if(id == 2)
		m_position.y += 1;
	else if(id == 3)
		m_position.x -= 1;
	else if(id == 4)
		m_position.x += 1;
	else if(id == 5)
		m_position.y -= 2;
	else if(id == 6)
		m_position.y += 2;
	else if(id == 7)
		m_position.x -= 2;
	else if(id == 8)
		m_position.x += 2;
	m_sprite.setTexture(m_textureBase->m_textures[4][m_id*3+0]);
	m_sprite.setPosition(sf::Vector2f(fieldPos->x + 16*m_position.x, fieldPos->y + 16*m_position.y));
}


CExplosion::~CExplosion(void)
	{
	}
