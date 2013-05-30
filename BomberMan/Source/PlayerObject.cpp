#include "PlayerObject.h"
#include <iostream>

void KeyPressed(sf::Event::KeyEvent& keyboard){
	
		std::cout << "Ide do gory" << std::endl;
}

void CPlayerObject::draw(sf::RenderWindow* window)
{
	window->draw(m_sprite);
}

void CPlayerObject::destroy()
{

}

CPlayerObject::CPlayerObject(int id, sf::Vector2f* fieldPos, sf::Vector2f* startPos)
{
	m_fieldPos = fieldPos;
	m_startPos = startPos;
	m_texture.loadFromFile("Resources/Game/Players/player1_01.png");
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(sf::Vector2f(fieldPos->x + 16*startPos->x, fieldPos->y + 16*startPos->y - 8));
}


CPlayerObject::~CPlayerObject(void)
	{
	}
