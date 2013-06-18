#include "GameField.h"
#include "UnbreakableBlock.h"
#include "BreakableBlock.h"
#include "PlayerObject.h"
#include "Bomb.h"

bool CGameField::isObjectAtPos(const sf::Vector2f& pos){
	for(std::list<CGameObject*>::iterator it = m_objects.begin(); it != m_objects.end(); it++)
	{
		if((*it)->getPos().x == pos.x && (*it)->getPos().y == pos.y)
			return true;	
	}
	return false;
}

void CGameField::ticker(const sf::Clock& clock)
{
	std::list<std::list<CGameObject*>::iterator> toRemove;
	for(std::list<CGameObject*>::iterator it = m_objects.begin(); it != m_objects.end(); it++)
	{
		if((*it)->isDestroyed())
			toRemove.push_back(it);
		else
			(*it)->ticker(clock);
	}
	for(std::list<std::list<CGameObject*>::iterator>::iterator it = toRemove.begin(); it != toRemove.end(); it++)
		m_objects.erase(*it);	
}

void CGameField::generateMap()
{
	sf::Image map;
	map.loadFromFile("Resources/map.bmp");
	m_size.x = map.getSize().x;
	m_size.y = map.getSize().y;
	sf::Color unbreakable(0,0,0,0);
	sf::Color breakable(255,0,0,0);
	sf::Color startPos(0,0,255,0);
	for(int i = 0; i < map.getSize().x; i++)
	{
		for(int j = 0; j < map.getSize().y; j++)
		{
			sf::Color tmp = map.getPixel(i,j);
			if(map.getPixel(i,j) == unbreakable)
				m_objects.push_back(new CUnbreakableBlock(0,sf::Vector2f(i,j),m_position, &m_textureBase));
			else if(map.getPixel(i,j) == breakable)
				m_objects.push_back(new CBreakableBlock(0,sf::Vector2f(i,j),m_position, &m_textureBase));
			else if(map.getPixel(i,j) == startPos)
				m_startPos = sf::Vector2f(i,j);
		}
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
	if((mouse.x >= this->m_position.x && mouse.x <= this->m_position.x+(this->m_size.x*16)) && (mouse.y >= this->m_position.y && mouse.y <= this->m_position.y+(this->m_size.y*16))){
		/*if (mouse.button == sf::Mouse::Left)
			temporaryHandleForPlayerObject->move(mouse.x, mouse.y);
		else if(mouse.button == sf::Mouse::Middle)
			temporaryHandleForPlayerObject->animate();
		else
			temporaryHandleForPlayerObject->animate();*/
		return true;
	}
	return false;
}

void CGameField::KeyPressed(sf::Event::KeyEvent& keyboard)
{
	//temporaryHandleForPlayerObject->KeyPressed(keyboard);
	/*char msg[10] = {'\0'};
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		//playerMove(0, -1, m_myPlayer);
		sprintf(msg, "MOV%02d%02d%02d", m_myPlayer, 0, -1);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		//playerMove(0, 1, m_myPlayer);
		sprintf(msg, "MOV%02d%02d%02d", m_myPlayer, 0, 1);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		//playerMove(-1, 0, m_myPlayer);
		sprintf(msg, "MOV%02d%02d%02d", m_myPlayer, -1, 0);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		//playerMove(1, 0, m_myPlayer);
		sprintf(msg, "MOV%02d%02d%02d", m_myPlayer, 1, 0);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		auto tmp = m_players.find(m_myPlayer)->second->getPos();
		bomb(tmp.x, tmp.y);
	}*/

}

void CGameField::draw(sf::RenderWindow* window)
{
	window->draw(m_field);
	for(std::list<CGameObject*>::iterator it = m_objects.begin(); it != m_objects.end(); it++)
	{
		(*it)->draw(window);	
	}
}

void CGameField::bomb(int x, int y)
{
	m_objects.push_back(new CBomb(&m_position, sf::Vector2f(x,y), &m_objects, &m_textureBase));
}

void CGameField::playerMove(int x, int y, int playerID)
{
	m_players.find(playerID)->second->move(sf::Vector2f(x,y));
}

void CGameField::setPlayerPos(int x, int y, int playerID)
{
	m_players.find(playerID)->second->setPos(sf::Vector2f(x,y));
}

sf::Vector2f CGameField::getPlayerPos()
{
	return m_players.find(m_myPlayer)->second->getPos();
}

void CGameField::addPlayer(int id, int x, int y)
{
	sf::Vector2f pos(x, y);
	auto tmp = new CPlayerObject(1, &m_position, &pos, &m_objects, &m_textureBase);
	m_objects.push_back(tmp);
	m_players.insert(std::make_pair(id, tmp));
}

bool CGameField::isPlayerMoving()
{
	if(!m_players.empty())
		return m_players.find(m_myPlayer)->second->isMoving();
	else
		return true;
}

CGameField::CGameField(EGameStates state): CControl(state)
{
	m_position.x = 20;
	m_position.y = 20;
	generateMap();
	m_field.setPosition((sf::Vector2f)m_position);
	m_field.setSize(sf::Vector2f(16*m_size.x,16*m_size.y));
	sf::Color fieldColor;
	fieldColor.r = 16;
	fieldColor.g = 120;
	fieldColor.b = 48;
	fieldColor.a = 255;
	m_field.setFillColor(fieldColor);
	
	//temporaryHandleForPlayerObject = new CPlayerObject(1,&m_position, &m_startPos, &m_objects);
	//m_objects.push_back(temporaryHandleForPlayerObject);
}


CGameField::~CGameField(void)
{
}