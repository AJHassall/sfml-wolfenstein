#include "player.h"
#include "SFML/Graphics.hpp"


const float player::m_movespeed = 0.1f;
const float player::m_rotatespeed = 0.1f;
player::player() 
{
}

player::~player()
{
}

void player::update() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		// left key is pressed: move our character
		RotateAntiClockWise();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		// left key is pressed: move our character
		RotateClockWise();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		// left key is pressed: move our character
		MoveForward();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		// left key is pressed: move our character
		MoveBackwards();
	}
}