#include <SFML\Graphics.hpp>

int main()
{
	sf::RenderWindow Window(sf::VideoMode(600,400, 32), "Bomber Man, by Ilddor and kamilosxd678");

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
			}
		}
		Window.clear();

		Window.display();
	}

	return 0;
}