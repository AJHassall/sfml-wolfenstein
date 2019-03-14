#include <SFML/Graphics.hpp>
#include <string>
#include "texturesheet.h"
#include "player.h"
#include "raycast.h"
int main()

{



	// create the window
	static sf::RenderWindow window(sf::VideoMode(640, 480), "Wolfenstein");
	window.setFramerateLimit(30);

	texturesheet ts=texturesheet(L"D:/Dev/C++/SFML/textures", 11);

	auto s=sf::Sprite(ts);

	player p = player();
	raycast r = raycast(640, p, ts, window);


	// run the main loop
	while (window.isOpen())
	{
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

		window.clear(sf::Color::Black);
		r.update();
		window.display();

	}
	return 0;
}