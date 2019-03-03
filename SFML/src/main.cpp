#include <SFML/Graphics.hpp>

#include "includes.h"

int main()
{
	// create the window
	sf::RenderWindow window(sf::VideoMode(512, 256), "Particles");
	window.setFramerateLimit(60);
	

	// create the particle system


	// create a clock to track the elapsed time
	

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


		window.display();




	}

	return 0;
}