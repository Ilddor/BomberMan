#include "Player.h"

void CPlayer::setName(sf::String name)
{
	m_name = name;
}

void CPlayer::setPosition(sf::Vector2f pos)
{
	m_position = pos;
}

void CPlayer::setDestination(sf::Vector2f dst)
{
	m_destination = dst;
}

sf::String CPlayer::getName()
{
	return m_name;
}

sf::Vector2f CPlayer::getPosition()
{
	return m_position;
}

sf::Vector2f CPlayer::getDestination()
{
	return m_destination;
}

bool CPlayer::isMoving()
{
	return m_position != m_destination;
}

void CPlayer::receivePackets()
{
	while(true)
	{
	}
}

CPlayer::CPlayer(SOCKET socket)
{
	m_connectedSocket = socket;
}

CPlayer::CPlayer(void)
{

}


CPlayer::~CPlayer(void)
{
}
