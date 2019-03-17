#include <SFML/Graphics.hpp>
#include <string>
#include "texturesheet.h"
#include "player.h"
#include <iostream>
#include "raycast.h"
int main()

{


	// create the window
	static sf::RenderWindow window(sf::VideoMode(640, 480), "Wolfenstein");
	window.setFramerateLimit(30);

	texturesheet ts=texturesheet(L"textures/", 11);

	auto s=sf::Sprite(ts);

	player p = player();
	raycast r = raycast(640,480, p, ts, window);


	// run the main loop
	while (window.isOpen())
	{
		sf::Clock c;
		// handle events
		sf::Event event;
		while (window.pollEvent(event))
		{	
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;
				
			}
		}

		window.clear(sf::Color::White);
		p.update();
		

		//auto dsf = 1/c.getElapsedTime().asSeconds() ;

		//std::cout << c.getElapsedTime().asSeconds() <<std::endl;
		r.update();
		//c.restart();
		window.display();
	}
	return 0;
}