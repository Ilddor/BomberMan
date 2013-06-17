#include <iostream>
#include <SFML\Graphics.hpp>

#include "Game.h"
#include "Button.h"
#include "TextField.h"
#include "GameField.h"

int main()
{
	sf::RenderWindow Window(sf::VideoMode(600,600, 32), "Bomber Man, by Ilddor and kamilosxd678");

	CGame game;
	game.setWindowPointer(&Window);

	//game.addControl("createGame(MENU)", new CButton(EGameStates::GS_MENU,"Resources/create.png", sf::Vector2f(243,50), [&](){
	//	game.setGameState(EGameStates::GS_CREATE);
	//}));
	game.addControl("joinGame(MENU)", new CButton(EGameStates::GS_MENU,"Resources/join.png", sf::Vector2f(230,100), [&](){
		game.setGameState(EGameStates::GS_JOIN);
	}));
	game.addControl("startGame(CREATE)", new CButton(EGameStates::GS_CREATE,"Resources/start.png", sf::Vector2f(243,550), [&](){
		//game.setGameState(EGameStates::GS_GAME);
	}));
	game.addControl("joinGame(JOIN)", new CButton(EGameStates::GS_JOIN,"Resources/joinS.png", sf::Vector2f(100,550), [&](){
		game.connectToServer();
	}));
	game.addControl("back(CREATE)", new CButton(EGameStates::GS_CREATE,"Resources/back.png", sf::Vector2f(520,550), [&](){
		game.setGameState(EGameStates::GS_MENU);
		game.stopServer();
	}));
	game.addControl("back(JOIN)", new CButton(EGameStates::GS_JOIN,"Resources/back.png", sf::Vector2f(520,550), [&](){
		game.setGameState(EGameStates::GS_MENU);
	}));
	game.addControl("back(GAME)", new CButton(EGameStates::GS_GAME,"Resources/back.png", sf::Vector2f(520,550), [&](){
		game.setGameState(EGameStates::GS_MENU);
		game.disconnect();
	}));
	game.addControl("back(JOINED)", new CButton(EGameStates::GS_JOINED,"Resources/back.png", sf::Vector2f(520,550), [&](){
		game.setGameState(EGameStates::GS_MENU);
		game.disconnect();
	}));
	game.addControl("rdy(JOINED)", new CButton(EGameStates::GS_JOINED,"Resources/rdy.png", sf::Vector2f(220,550), [&](){
		game.rdy();
	}));
	game.addControl("ip(JOIN)", new CTextField(EGameStates::GS_JOIN, sf::Vector2f(180,550)));
	game.addControl("name(CREATE)", new CTextField(EGameStates::GS_CREATE, sf::Vector2f(10,450)));
	game.addControl("startServer(CREATE)", new CButton(EGameStates::GS_CREATE,"Resources/startServ.png", sf::Vector2f(243,450), [&](){
		game.startServer();
	}));
	game.addControl("name(JOIN)", new CTextField(EGameStates::GS_JOIN, sf::Vector2f(200,280)));
	game.addControl("gameField(GAME)", new CGameField(EGameStates::GS_GAME));
	game.addControl("createGame(DEBUG_CREATE)", new CButton(EGameStates::GS_CREATE,"Resources/create.png", sf::Vector2f(243,50), [&](){
		game.setGameState(EGameStates::GS_GAME);
	}));
	sf::Event Event;
	sf::Clock Clock;
	while(Window.isOpen())
	{
		while(Window.pollEvent(Event))
		{
			switch(Event.type)
			{
			case sf::Event::Closed :
				game.disconnect();
				Window.close();
				break;
			default :
				game.handleEvent(Event);
				break;
			}
		}
		Window.clear(sf::Color::White);
		game.ticker(Clock);
		game.draw();

		Window.display();
	}

	return 0;
}