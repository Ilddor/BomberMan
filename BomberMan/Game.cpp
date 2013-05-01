#include "Game.h"

void CGame::setWindowPointer(sf::RenderWindow* ptr)
{
	m_windowPtr = ptr;
}

void CGame::draw()
{
}

void CGame::handleEvent(sf::Event& ev)
{
	switch(ev.type)
	{
		case sf::Event::MouseButtonPressed :
			for(auto& it: m_controls)
			{
				if(it.getState() == m_state)
					it.mousePressed(ev.mouseButton);
			}
			break;
	}
}

void CGame::addControl(CControl control)
{
	m_controls.push_back(control);
}

CGame::CGame(void)
{
	m_state = GS_MENU;
	m_windowPtr = nullptr;
}


CGame::~CGame(void)
{
}