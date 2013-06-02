#include "TextField.h"

bool CTextField::mousePressed(sf::Event::MouseButtonEvent& mouse)
{
	sf::Vector2f point(mouse.x, mouse.y);
	if(m_background.getGlobalBounds().contains(point))
		return true;
	else
		return false;
}

void CTextField::KeyPressed(sf::Event::KeyEvent& keyboard)
{
	if(keyboard.code == sf::Keyboard::BackSpace && !m_text.getString().isEmpty())
	{
		sf::String tmp = m_text.getString();
		tmp.erase(tmp.getSize()-1);
		m_text.setString(tmp);
	}
	else if(keyboard.code >= sf::Keyboard::A && keyboard.code <= sf::Keyboard::Z)
	{
		sf::String tmp = m_text.getString();
		if(keyboard.shift)
			tmp.insert(tmp.getSize(), (char)(65+keyboard.code));
		else
			tmp.insert(tmp.getSize(), (char)(97+keyboard.code));
		m_text.setString(tmp);
	}
	else if(keyboard.code >= sf::Keyboard::Num0 && keyboard.code <= sf::Keyboard::Num9)
	{
		sf::String tmp = m_text.getString();
		tmp.insert(tmp.getSize(), (char)(22+keyboard.code));
		m_text.setString(tmp);
	}
	else if(keyboard.code == sf::Keyboard::Period)
	{
		sf::String tmp = m_text.getString();
		tmp.insert(tmp.getSize(), '.');
		m_text.setString(tmp);
	}
}

void CTextField::draw(sf::RenderWindow* window)
{
	window->draw(m_background);
	window->draw(m_text);
}

sf::String CTextField::getString()
{
	return m_text.getString();
}

CTextField::CTextField(EGameStates state, sf::Vector2f position, sf::Vector2f size): CControl(state)
{
	m_background.setPosition(position);
	m_background.setSize(size);
	m_background.setFillColor(sf::Color(100,100,100));

	m_font.loadFromFile("Resources/arial.ttf");

	m_text.setPosition(position+sf::Vector2f(5,0));
	m_text.setCharacterSize(25);
	m_text.setColor(sf::Color::Red);
	m_text.setStyle(sf::Text::Regular);
	m_text.setFont(m_font);
}


CTextField::~CTextField(void)
{
}
