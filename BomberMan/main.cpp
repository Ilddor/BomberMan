#include <SFML\Graphics.hpp>

#include "Game.h"
#include "Button.h"

int main()
{
	sf::RenderWindow Window(sf::VideoMode(600,400, 32), "Bomber Man, by Ilddor and kamilosxd678");

	CGame game;

	game.addControl(CButton(EGameStates::GS_MENU));

	sf::Event Event;
	while(Window.isOpen())
	{
		while(Window.pollEvent(Event))
		{
			switch(Event.type)
			{
			case sf::Event::Closed :
				Window.close();
				break;
			default :
				game.handleEvent(Event);
				break;
			}
		}
		Window.clear();

		Window.display();
	}

	return 0;
}