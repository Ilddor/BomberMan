#include "PlayerObject.h"
#include "Bomb.h"
#include <iostream>
#include <string>

void CPlayerObject::KeyPressed(sf::Event::KeyEvent& keyboard)
{
	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		move(sf::Vector2f(0.0,-1.0));
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		move(sf::Vector2f(0.0,1.0));
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		move(sf::Vector2f(-1.0,0.0));
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		move(sf::Vector2f(1.0,0.0));
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		m_objects->push_back(new CBomb(m_fieldPos, m_position, m_objects, &m_textureBase));*/	
}

bool CPlayerObject::isDead()
{
	return m_direction == EDirections::D_DEATH;
}

void CPlayerObject::ticker(const sf::Clock& clock)
{
	if(m_goalPosition != m_position)
	{
		float movement = (96.f * (float)(clock.getElapsedTime()	- m_lastTick).asSeconds())/16.f;
		if(isObjectLethal(m_goalPosition))
			destroy();
		if(m_direction == EDirections::D_NORTH)
		{
			if(m_position.y - movement <= m_goalPosition.y)
				m_position = m_goalPosition;
			else
				m_position.y -= movement;
		}
		else if(m_direction == EDirections::D_SOUTH)
		{
			if(m_position.y + movement >= m_goalPosition.y)
				m_position = m_goalPosition;
			else
				m_position.y += movement;
		}
		else if(m_direction == EDirections::D_EAST)
		{
			if(m_position.x + movement >= m_goalPosition.x)
				m_position = m_goalPosition;
			else
				m_position.x += movement;
		}
		else if(m_direction == EDirections::D_WEST)
		{
			if(m_position.x - movement <= m_goalPosition.x)
				m_position = m_goalPosition;
			else
				m_position.x -= movement;
		}
		m_sprite.setPosition(sf::Vector2f(m_fieldPos->x + 16*m_position.x, m_fieldPos->y + 16*m_position.y - 8));
		m_lastAnimationTime += (clock.getElapsedTime()	- m_lastTick).asMilliseconds();
		if(m_lastAnimationTime > 82)
		{
			m_lastAnimationTime = 0;
			animate();
		}
		m_lastTick = clock.getElapsedTime();
	}
	else if(m_direction == EDirections::D_DEATH)
	{
		m_lastAnimationTime += (clock.getElapsedTime()	- m_lastTick).asMilliseconds();
		if(m_lastAnimationTime > 750)
		{
			m_lastAnimationTime = 0;
			animate();
		}
		m_lastTick = clock.getElapsedTime();
	}
	else
		m_lastTick = clock.getElapsedTime();	
}

void CPlayerObject::animate()
{
	if(m_direction != EDirections::D_DEATH){
		m_animationState += m_animationMultiplier;
		if(m_animationState == 2)
			m_animationMultiplier = -1;
		if(m_animationState == 0)
			m_animationMultiplier = 1;
	}
	else {
		m_animationState++;
		if(m_animationState == 3){
			m_sprite.setColor(sf::Color(0,0,0,0));
			m_destroyed = true;
		}
	}
	if(m_direction == EDirections::D_DEATH)
		m_sprite.setTexture(m_textureBase->m_textures[3][12 + m_animationState]);		
}

void CPlayerObject::move(int x, int y)
{
	return;
	sf::Vector2f goalPos = calculatePositionOnGameField(x,y);
	sf::Vector2f moveVector(0,0);
	EDirections actualDirection = m_direction;
	if(goalPos.x < m_position.x)
		moveVector.x = -1;
	else if(goalPos.x > m_position.x)
		moveVector.x = 1;
	if(goalPos.y < m_position.y)
		moveVector.y = -1;
	else if(goalPos.y > m_position.y)
		moveVector.y = 1;
	if(!isObjectAtPos(m_position + moveVector)){
		
		if(moveVector.x < 0)
			m_direction = EDirections::D_WEST;
		else if(moveVector.x > 0)
			m_direction = EDirections::D_EAST;
		else if(moveVector.y < 0)
			m_direction = EDirections::D_NORTH;
		else if(moveVector.y > 0)
			m_direction = EDirections::D_SOUTH;
		//m_position += moveVector;
		//m_sprite.setPosition(sf::Vector2f(m_fieldPos->x + 16*m_position.x, m_fieldPos->y + 16*m_position.y - 8));
		m_goalPosition = m_position + moveVector;
	}
	if(actualDirection != m_direction)
		m_animationState = 1;	
	//animate();	
}
void CPlayerObject::move(sf::Vector2f moveVector)
{
	EDirections actualDirection = m_direction;
	if(m_goalPosition == m_position){
		if(!isObjectAtPos(m_position + moveVector))
		{
			if(moveVector.x < 0)
			{
				m_direction = EDirections::D_WEST;
				m_sprite.setTexture(m_textureBase->m_textures[3][3 + m_animationState]);
			}
			else if(moveVector.x > 0)
			{
				m_direction = EDirections::D_EAST;
				m_sprite.setTexture(m_textureBase->m_textures[3][6 + m_animationState]);
			}
			else if(moveVector.y < 0)
			{
				m_direction = EDirections::D_NORTH;
				m_sprite.setTexture(m_textureBase->m_textures[3][9 + m_animationState]);
			}
			else if(moveVector.y > 0)
			{
				m_direction = EDirections::D_SOUTH;
				m_sprite.setTexture(m_textureBase->m_textures[3][0 + m_animationState]);
			}
			m_goalPosition = m_goalPosition + moveVector;
		}
		else if(isObjectLethal(m_position + moveVector))
		{
			m_position += moveVector;
			destroy();
		}
	}
	if(actualDirection != m_direction)
		m_animationState = 1;	
}

void CPlayerObject::draw(sf::RenderWindow* window)
{
	window->draw(m_sprite);
}

bool CPlayerObject::destroy()
{
	m_sprite.setPosition(sf::Vector2f(m_fieldPos->x + 16*m_position.x, m_fieldPos->y + 16*m_position.y - 8));
	m_direction = EDirections::D_DEATH;
	m_animationState = 0;
	m_animationMultiplier = 1;
	return true;
}

void CPlayerObject::setPos(sf::Vector2f pos)
{
	m_position = pos;
}

bool CPlayerObject::isMoving()
{
	return m_position != m_goalPosition;
}

CPlayerObject::CPlayerObject(int id, sf::Vector2f* fieldPos, sf::Vector2f* startPos, std::list<CGameObject*>* objects, CTextureBase* texturebase)
{
	m_isLethal = false;
	m_destroyed = false;
	m_textureBase = texturebase;
	m_direction = EDirections::D_SOUTH;
	m_objects = objects;
	m_fieldPos = fieldPos;
	m_startPos = startPos;
	m_position = *m_startPos;
	m_animationState = 1;
	m_animationMultiplier = 1;
	m_sprite.setTexture(m_textureBase->m_textures[3][1]);
	m_sprite.setPosition(sf::Vector2f(fieldPos->x + 16*startPos->x, fieldPos->y + 16*startPos->y - 8));
	m_goalPosition = m_position;
	m_lastTick = sf::Clock().getElapsedTime();
	m_lastAnimationTime = 0;
}


CPlayerObject::~CPlayerObject(void)
	{
	}
