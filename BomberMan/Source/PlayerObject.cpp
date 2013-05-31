#include "PlayerObject.h"
#include <iostream>

bool CPlayerObject::isObjectAtPos(const sf::Vector2f& pos){
	for(std::list<CGameObject*>::iterator it = m_objects->begin(); it != m_objects->end(); it++)
	{
		if((*it)->getPos().x == pos.x && (*it)->getPos().y == pos.y)
			return true;	
	}
	return false;
}

void CPlayerObject::KeyPressed(sf::Event::KeyEvent& keyboard)
{
		std::cout << "Ide do gory" << std::endl;
}

sf::Vector2f CPlayerObject::calculatePositionOnGameField(int x, int y)
{
	//We presume that function is called only when clicked on gamefield, so additional check of coords is not required. 
	return sf::Vector2f((((x - m_startPos->x) - ((int)(x - m_startPos->x) % 16))/16)-1,(((y - m_startPos->y) - ((int)(y - m_startPos->y) % 16))/16)-1);
}

void CPlayerObject::move(int x, int y)
{
	sf::Vector2f goalPos = calculatePositionOnGameField(x,y);
	sf::Vector2f moveVector(0,0);
	if(goalPos.x < m_position.x)
		moveVector.x = -1;
	else if(goalPos.x > m_position.x)
		moveVector.x = 1;
	if(goalPos.y < m_position.y)
		moveVector.y = -1;
	else if(goalPos.y > m_position.y)
		moveVector.y = 1;
	if(!isObjectAtPos(m_position + moveVector)){
		m_position += moveVector;
		m_sprite.setPosition(sf::Vector2f(m_fieldPos->x + 16*m_position.x, m_fieldPos->y + 16*m_position.y - 8));
	}		
}

void CPlayerObject::draw(sf::RenderWindow* window)
{
	window->draw(m_sprite);
}

void CPlayerObject::destroy()
{

}

CPlayerObject::CPlayerObject(int id, sf::Vector2f* fieldPos, sf::Vector2f* startPos, std::list<CGameObject*>* objects)
{
	m_objects = objects;
	m_fieldPos = fieldPos;
	m_startPos = startPos;
	m_position = *m_startPos;
	m_texture.loadFromFile("Resources/Game/Players/player1_01.png");
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(sf::Vector2f(fieldPos->x + 16*startPos->x, fieldPos->y + 16*startPos->y - 8));
}


CPlayerObject::~CPlayerObject(void)
	{
	}
