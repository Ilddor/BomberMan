#include "GameField.h"
#include "UnbreakableBlock.h"
#include "PlayerObject.h"

bool CGameField::isObjectAtPos(const sf::Vector2f& pos){
	for(std::list<CGameObject*>::iterator it = m_objects.begin(); it != m_objects.end(); it++)
	{
		if((*it)->getPos().x == pos.x && (*it)->getPos().y == pos.y)
			return true;	
	}
	return false;
}

void CGameField::generateBorder()
{
	for(int i = 0; i < m_size.x; i++){
		m_objects.push_back(new CUnbreakableBlock(0, sf::Vector2f(i,0), m_position));
	}
	for(int i = 1; i < m_size.y-1; i++){
		m_objects.push_back(new CUnbreakableBlock(0, sf::Vector2f(0,i), m_position));
		m_objects.push_back(new CUnbreakableBlock(0, sf::Vector2f(m_size.x-1,i), m_position));
	}
	for(int i = 0; i < m_size.x; i++){
		m_objects.push_back(new CUnbreakableBlock(0, sf::Vector2f(i,m_size.y-1), m_position));
	}
}

bool CGameField::mousePressed(sf::Event::MouseButtonEvent& mouse)
{
/*
	sf::Vector2f point(mouse.x, mouse.y);
	if(m_sprite.getGlobalBounds().contains(point))
	{
		if(!m_function._Empty() && mouse.button == sf::Mouse::Left)
			m_function();
		return true;
	}
	else */
		return false;
}

void CGameField::KeyPressed(sf::Event::KeyEvent& keyboard)
{
	temporaryHandleForPlayerObject->KeyPressed(keyboard);
}

void CGameField::draw(sf::RenderWindow* window)
{
	window->draw(m_field);
	for(std::list<CGameObject*>::iterator it = m_objects.begin(); it != m_objects.end(); it++)
	{
		(*it)->draw(window);	
	}
}

CGameField::CGameField(EGameStates state): CControl(state)
{
	m_position.x = 20.0;
	m_position.y = 20.0;
	m_size.x = 35;
	m_size.y = 32;
	m_startPos.x = 1;
	m_startPos.y = 1;
	m_field.setPosition(m_position);
	m_field.setSize(sf::Vector2f(16*m_size.x,16*m_size.y));
	sf::Color fieldColor;
	fieldColor.r = 16;
	fieldColor.g = 120;
	fieldColor.b = 48;
	fieldColor.a = 255;
	m_field.setFillColor(fieldColor);
	generateBorder();
	temporaryHandleForPlayerObject = new CPlayerObject(1,&m_position, &m_startPos);
	m_objects.push_back(temporaryHandleForPlayerObject);
}


CGameField::~CGameField(void)
{
}