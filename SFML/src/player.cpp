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
		RotateAntiClockWise();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		RotateClockWise();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		MoveForward();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		MoveBackwards();
	}
}