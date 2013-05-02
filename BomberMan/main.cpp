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
		game.startServer();
	}));
	game.addControl(new CButton(EGameStates::GS_MENU,"join.png", sf::Vector2f(230,100), [&](){
		game.setGameState(EGameStates::GS_JOIN);
	}));
	game.addControl(new CButton(EGameStates::GS_CREATE,"start.png", sf::Vector2f(243,550), [&](){
		//game.setGameState(EGameStates::GS_JOIN);
	}));
	game.addControl(new CButton(EGameStates::GS_JOIN,"joinS.png", sf::Vector2f(100,550), [&](){
		//game.setGameState(EGameStates::GS_JOIN);
	}));
	game.addControl(new CButton(EGameStates::GS_CREATE,"back.png", sf::Vector2f(520,550), [&](){
		game.setGameState(EGameStates::GS_MENU);
		game.stopServer();
	}));
	game.addControl(new CButton(EGameStates::GS_JOIN,"back.png", sf::Vector2f(520,550), [&](){
		game.setGameState(EGameStates::GS_MENU);
	}));
	game.addControl(new CButton(EGameStates::GS_GAME,"back.png", sf::Vector2f(520,550), [&](){
		game.setGameState(EGameStates::GS_MENU);
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