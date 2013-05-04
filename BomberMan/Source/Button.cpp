#include "Button.h"

bool CButton::mousePressed(sf::Event::MouseButtonEvent& mouse)
{
	sf::Vector2f point(mouse.x, mouse.y);
	if(m_sprite.getGlobalBounds().contains(point))
	{
		if(!m_function._Empty() && mouse.button == sf::Mouse::Left)
			m_function();
		return true;
	}
	else
		return false;
}

void CButton::KeyPressed(sf::Event::KeyEvent& keyboard)
{
}

void CButton::draw(sf::RenderWindow* window)
{
	window->draw(m_sprite);
}

CButton::CButton(EGameStates state, std::string pathToImg, sf::Vector2f position, std::function<void()> func): CControl(state)
{
	m_function = func;
	m_texture.loadFromFile(pathToImg);
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(position);
}

CButton::~CButton(void)
{
}
