#include "Bomb.h"
#include "Explosion.h"
#include "TextureBase.h"

void CBomb::animate()
{
	if(m_animationState < 2)
	{
		m_animationState++;
		m_sprite.setTexture(m_textureBase->m_textures[0][m_animationState]);
	}
	else
	{
		m_sprite.setColor(sf::Color(0,0,0,255));
		m_destroyed = true;	  
		explode();
	}
}
void CBomb::explode()
{
	//CExplosion(int id, sf::Vector2f* fieldPos, sf::Vector2f position, std::list<CGameObject*>* objects)
	EDestroyResult boomEffect = destroyObjectAt(m_position);
	m_objects->push_back(new CExplosion(0, m_fieldPos, m_position, m_objects, m_textureBase));
	//UP
	boomEffect = destroyObjectAt(sf::Vector2f(m_position.x, m_position.y-1));
	if(boomEffect != EDestroyResult::DR_FAIL)
	{
		m_objects->push_back(new CExplosion(1, m_fieldPos, m_position, m_objects, m_textureBase));
		if(boomEffect == EDestroyResult::DR_NONE)
			if(destroyObjectAt(sf::Vector2f(m_position.x, m_position.y-2)) != EDestroyResult::DR_FAIL)
				m_objects->push_back(new CExplosion(5, m_fieldPos, m_position, m_objects, m_textureBase));
	}
	//Down
	boomEffect = destroyObjectAt(sf::Vector2f(m_position.x, m_position.y+1));
	if(boomEffect != EDestroyResult::DR_FAIL)
	{
		m_objects->push_back(new CExplosion(2, m_fieldPos, m_position, m_objects, m_textureBase));
		if(boomEffect == EDestroyResult::DR_NONE)
			if(destroyObjectAt(sf::Vector2f(m_position.x, m_position.y+2)) != EDestroyResult::DR_FAIL)
				m_objects->push_back(new CExplosion(6, m_fieldPos, m_position, m_objects, m_textureBase));
	}
	//Left
	boomEffect = destroyObjectAt(sf::Vector2f(m_position.x-1, m_position.y));
	if(boomEffect != EDestroyResult::DR_FAIL)
	{
		m_objects->push_back(new CExplosion(3, m_fieldPos, m_position, m_objects, m_textureBase));
		if(boomEffect == EDestroyResult::DR_NONE)
			if(destroyObjectAt(sf::Vector2f(m_position.x-2, m_position.y)) != EDestroyResult::DR_FAIL)
				m_objects->push_back(new CExplosion(7, m_fieldPos, m_position, m_objects, m_textureBase));
	}
	//Right
	boomEffect = destroyObjectAt(sf::Vector2f(m_position.x+1, m_position.y));
	if(boomEffect != EDestroyResult::DR_FAIL)
	{
		m_objects->push_back(new CExplosion(4, m_fieldPos, m_position, m_objects, m_textureBase));
		if(boomEffect == EDestroyResult::DR_NONE)
			if(destroyObjectAt(sf::Vector2f(m_position.x+2, m_position.y)) != EDestroyResult::DR_FAIL)
				m_objects->push_back(new CExplosion(8, m_fieldPos, m_position, m_objects, m_textureBase));
		
	} 	
}
void CBomb::draw(sf::RenderWindow* window)
{
	window->draw(m_sprite);
}
bool CBomb::destroy()
{
	return false;
}
void CBomb::ticker(const sf::Clock& clock)
{
	m_lastAnimationTime += (clock.getElapsedTime()	- m_lastTick).asMilliseconds();
	if(m_lastAnimationTime > 500)
	{
		m_lastAnimationTime = 0;
		animate();
	}
	m_lastTick = clock.getElapsedTime();
}

CBomb::CBomb(sf::Vector2f* fieldPos, sf::Vector2f position, std::list<CGameObject*>* objects, CTextureBase* texturebase)
{
	m_destroyed = false;
	m_objects = objects;
	m_textureBase = texturebase;
	m_position = position;
	m_fieldPos = fieldPos;
	m_sprite.setTexture(m_textureBase->m_textures[0][0]);
	m_sprite.setPosition(sf::Vector2f(fieldPos->x + 16*position.x, fieldPos->y + 16*position.y));
	m_animationState = 0;
	m_lastTick = sf::Clock().getElapsedTime();
	m_lastAnimationTime = 0;
	m_isLethal = false;
}


CBomb::~CBomb(void)
	{
	}
