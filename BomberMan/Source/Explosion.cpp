#include "Explosion.h"
#include <string>

void CExplosion::animate()
{
	if(m_animationState < 3 && !m_maxBlow)
	{
		m_animationState++;
		m_sprite.setTexture(m_textures[m_animationState]);
		if(m_animationState == 3)
			m_maxBlow = true;
	}
	else if(m_maxBlow && m_animationState > 0)
	{
		m_animationState--;
		m_sprite.setTexture(m_textures[m_animationState]);
	
	}
	else
	{
		m_sprite.setColor(sf::Color(0,0,0,0));
		m_destroyed = true;	  
	}
}
void CExplosion::draw(sf::RenderWindow* window)
{
	window->draw(m_sprite);
}
bool CExplosion::destroy()
{
	m_sprite.setColor(sf::Color(0,0,0,0));
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


CExplosion::CExplosion(int id, sf::Vector2f* fieldPos, sf::Vector2f position, std::list<CGameObject*>* objects)
{
	m_id = id;
	m_fieldPos = fieldPos;
	sf::Texture m_textures[3];
	m_animationState = 0;
	m_lastTick = sf::Clock().getElapsedTime();
	m_lastAnimationTime = 0;
	m_destroyed = false;
	m_maxBlow = false;
	m_position = position;
	std::string path = "Resources/Game/Explosion/explosion_";
	std::string place = "mid";
	if(id == 1)
	{
		m_position.y -= 1;
		place = "up";
	}
	else if(id == 2)
	{
		m_position.y += 1;
		place = "down";
	}
	else if(id == 3)
	{
		m_position.x -= 1;
		place = "left";
	}
	else if(id == 4)
	{
		m_position.x += 1;
		place = "right";
	}
	else if(id == 5)
	{
		m_position.y -= 2;
		place = "top";
	}
	else if(id == 6)
	{
		m_position.y += 2;
		place = "bot";
	}
	else if(id == 7)
	{
		m_position.x -= 2;
		place = "east";
	}
	else if(id == 8)
	{
		m_position.x += 2;
		place = "west";
	}
	for(int i = 0; i < 3; i++)
	{
		m_textures[i].loadFromFile(path + (char)(i+'0') + "_" + place + ".png");
	}
	m_sprite.setTexture(m_textures[0]);
	m_sprite.setPosition(sf::Vector2f(fieldPos->x + 16*position.x, fieldPos->y + 16*position.y));
}


CExplosion::~CExplosion(void)
	{
	}
