#include "raycast.h"

#include <cmath>
#include "SFML/Graphics.hpp"

raycast::raycast(int width,int height, player & p, texturesheet& t, sf::RenderWindow& rw):
	m_width(width),m_height(height), m_player(&p), m_textureSheet(&t),m_window(&rw)
{

}

raycast::~raycast()
{
}
using namespace std;
void raycast::update()
{

	int WorldMap[24][24] =
	{
	  {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,7,7,7,7,7,7,7,7},
	  {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
	  {4,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
	  {4,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
	  {4,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
	  {4,0,4,0,0,0,0,5,5,5,5,5,5,5,5,5,7,7,0,7,7,7,7,7},
	  {4,0,5,0,0,0,0,5,0,5,0,5,0,5,0,5,7,0,0,0,7,7,7,1},
	  {4,0,6,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
	  {4,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,7,1},
	  {4,0,8,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
	  {4,0,0,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,7,7,7,1},
	  {4,0,0,0,0,0,0,5,5,5,5,0,5,5,5,5,7,7,7,7,7,7,7,1},
	  {6,6,6,6,6,6,6,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
	  {8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
	  {6,6,6,6,6,6,0,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
	  {4,4,4,4,4,4,0,4,4,4,6,0,6,2,2,2,2,2,2,2,3,3,3,3},
	  {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
	  {4,0,0,0,0,0,0,0,0,0,0,0,6,2,0,0,5,0,0,2,0,0,0,2},
	  {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
	  {4,0,6,0,6,0,0,0,0,4,6,0,0,0,0,0,5,0,0,0,0,0,0,2},
	  {4,0,0,5,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
	  {4,0,6,0,6,0,0,0,0,4,6,0,6,2,0,0,5,0,0,2,0,0,0,2},
	  {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
	  {4,4,4,4,4,4,4,4,4,4,1,1,1,2,2,2,2,2,2,3,3,3,3,3}
	};


	auto _player= m_player->getPositionAndDirection();
	for (int x = 0; x < m_width; x++)
	{

		double planeX = _player.yDir, planeY = -_player.xDir;
		double cameraX = 2 * x / double(m_width) - 1; //x-coordinate in camera space

		double rayDirX = _player.xDir + planeX * cameraX;
		double rayDirY = _player.yDir + planeY * cameraX;

		int mapX = int(_player.x);
		int mapY = int(_player.y);

		//length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;

		//length of ray from one x or y-side to next x or y-side
		double deltaDistX = std::abs(1 / rayDirX);
		double deltaDistY = std::abs(1 / rayDirY);
		double perpWallDist;
		int stepX;
		int stepY;

		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?
		//calculate step and initial sideDist
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (_player.x - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - _player.x) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (_player.y - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - _player.y) * deltaDistY;
		}

		//perform DDA
		while (hit == 0)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			//Check if ray has hit a wall
			if (WorldMap[mapY][mapX] > 0) hit = 1;
		}
		//Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
		if (side == 0) perpWallDist = (mapX - _player.x + ((1 - stepX) >> 1)) / rayDirX;
		else           perpWallDist = (mapY - _player.y + ((1 - stepY) >> 1)) / rayDirY;

		//Calculate height of line to draw on screen
		int lineHeight = (int)(m_height / perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -(lineHeight >> 1) + (m_height >> 1);
		//if (drawStart < 0)drawStart = 0;
		int drawEnd = (lineHeight >> 1) + (m_height >> 1);
		//if (drawEnd >= m_height)drawEnd = m_height- 1;

		int texNum = WorldMap[mapY][mapX]-1;
		double wallX; //where exactly the wall was hit
		if (side == 0) wallX = _player.y + perpWallDist * rayDirY;
		else           wallX = _player.x + perpWallDist * rayDirX;
		wallX -= floor((wallX));


		int texWidth = 64;
		int texX = int(wallX * double(texWidth));
		if (side == 0 && rayDirX > 0) texX = texWidth - texX - 1;
		if (side == 1 && rayDirY < 0) texX = texWidth - texX - 1;

		sf::Sprite s = sf::Sprite(*m_textureSheet, sf::IntRect((texNum <<6) + texX, 0, 1, 64));
		s.setPosition(x, drawStart);

		int asd = 4;
		int adfasd = asd << 6;
		int gffsd = asd * 64;


		double yscale = double(drawEnd - drawStart)/64;
	
		s.setScale(1, yscale);
		m_window->draw(s);
		
	}
}
