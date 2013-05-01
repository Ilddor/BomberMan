#include <iostream>
#include <SFML\Graphics.hpp>

#include "Game.h"
#include "Button.h"

int main()
{
	sf::RenderWindow Window(sf::VideoMode(600,600, 32), "Bomber Man, by Ilddor and kamilosxd678");

	CGame game;
	game.setWindowPointer(&Window);

	game.addControl(new CButton(EGameStates::GS_MENU,"create.png", sf::Vector2f(243,50), [&](){
		game.setGameState(EGameStates::GS_CREATE);
	}));
	game.addControl(new CButton(EGameStates::GS_MENU,"join.png", sf::Vector2f(230,100), [&](){
		game.setGameState(EGameStates::GS_JOIN);
	}));

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
		Window.clear(sf::Color::White);

		game.draw();

		Window.display();
	}

	return 0;
}