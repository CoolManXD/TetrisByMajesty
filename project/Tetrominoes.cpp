#include "Tetrominoes.h"
#include "Map.h"
#include <iostream>

Tetrominoes::Tetrominoes(sf::Image &image, sf::Image &nextImage, int size) : m_size(size)
{
	texture.loadFromImage(image);//заряжаем текстуру картинкой
	sprite.setTexture(texture);//заливаем текстуру спрайтом
	nextTexture.loadFromImage(nextImage);//заряжаем текстуру картинкой
	nextSprite.setTexture(nextTexture);
	nextSprite.setPosition(416, 224);
	std::srand(time(NULL));
	nextTetr = rand() % 7 + 1;
}

void Tetrominoes::chooseTypeTetr()
{
	currentPosForRotate = 0;
	std::srand(time(NULL));
	switch (nextTetr)
	{
	case 1: tetr = T; sprite.setTextureRect(sf::IntRect(192, 0, 32, 32)); break;
	case 2: tetr = Q; sprite.setTextureRect(sf::IntRect(160, 0, 32, 32)); break;
	case 3: tetr = I; sprite.setTextureRect(sf::IntRect(32, 0, 32, 32)); break;
	case 4: tetr = Z; sprite.setTextureRect(sf::IntRect(0, 0, 32, 32)); break;
	case 5: tetr = S; sprite.setTextureRect(sf::IntRect(128, 0, 32, 32)); break;
	case 6: tetr = J; sprite.setTextureRect(sf::IntRect(96, 0, 32, 32)); break;
	case 7: tetr = L; sprite.setTextureRect(sf::IntRect(64, 0, 32, 32)); break;
	}
	nextTetr = rand() % 7 + 1;
	switch (nextTetr)
	{
	case 1: nextSprite.setTextureRect(sf::IntRect(224, 64, 96, 64)); break;
	case 2: nextSprite.setTextureRect(sf::IntRect(224, 0, 64, 64)); break;
	case 3: nextSprite.setTextureRect(sf::IntRect(96, 0, 128, 32)); break;
	case 4: nextSprite.setTextureRect(sf::IntRect(0, 0, 96, 64)); break;
	case 5: nextSprite.setTextureRect(sf::IntRect(0, 64, 96, 64)); break;
	case 6: nextSprite.setTextureRect(sf::IntRect(96, 32, 64, 96)); break;
	case 7: nextSprite.setTextureRect(sf::IntRect(160, 32, 64, 96)); break;
	}
}

void Tetrominoes::showNextTetr(sf::RenderWindow &window)
{
	window.draw(nextSprite);
}

bool Tetrominoes::createTetr(Map& map)
{
	int pos = rand() % 3 + 3;
	switch (tetr)
	{
	case T:
		coord1.x = 32 * pos + 32; coord1.y = 128;
		coord2.x = 32 * pos; coord2.y = 128;
		coord3.x = 32 * pos + 64; coord3.y = 128;
		coord4.x = 32 * pos + 32; coord4.y = 160; break;
	case Q:
		coord1.x = 32 * pos; coord1.y = 128;
		coord2.x = 32 * pos + 32; coord2.y = 128;
		coord3.x = 32 * pos; coord3.y = 160;
		coord4.x = 32 * pos + 32; coord4.y = 160; break;
	case I:
		coord1.x = 32 * pos + 32; coord1.y = 128;
		coord2.x = 32 * pos; coord2.y = 128;
		coord3.x = 32 * pos + 64; coord3.y = 128;
		coord4.x = 32 * pos + 96; coord4.y = 128; break;
	case Z:
		coord1.x = 32 * pos + 32; coord1.y = 128;
		coord2.x = 32 * pos; coord2.y = 128;
		coord3.x = 32 * pos + 32; coord3.y = 160;
		coord4.x = 32 * pos + 64; coord4.y = 160; break;
	case S:
		coord1.x = 32 * pos + 32; coord1.y = 128;
		coord2.x = 32 * pos; coord2.y = 160;
		coord3.x = 32 * pos + 32; coord3.y = 160;
		coord4.x = 32 * pos + 64; coord4.y = 128; break;
	case J:
		coord1.x = 32 * pos + 32; coord1.y = 160;
		coord2.x = 32 * pos + 32; coord2.y = 128;
		coord3.x = 32 * pos + 32; coord3.y = 192;
		coord4.x = 32 * pos; coord4.y = 192; break;
	case L:
		coord1.x = 32 * pos + 32; coord1.y = 160;
		coord2.x = 32 * pos + 32; coord2.y = 128;
		coord3.x = 32 * pos + 32; coord3.y = 192;
		coord4.x = 32 * pos + 64; coord4.y = 192; break;
	}
	if (checkLose(map)) return true;
	isMove = true;
	return false;
}

bool Tetrominoes::checkLose(Map& map)
{
	if (map.TileMap[coord1.y / 32][coord1.x / 32] != ' ' || map.TileMap[coord2.y / 32][coord2.x / 32] != ' ' ||
		map.TileMap[coord3.y / 32][coord3.x / 32] != ' ' || map.TileMap[coord4.y / 32][coord4.x / 32] != ' ')
		return true;
	return false;
}

bool Tetrominoes::checkColission(Map& map, DIR dir)
{
	switch (dir)
	{
	case gravity:
	{
		if (map.TileMap[int((coord1.y + 32) / 32)][int(coord1.x / 32)] != ' ' || map.TileMap[int((coord2.y + 32) / 32)][int(coord2.x / 32)] != ' ' ||
			map.TileMap[int((coord3.y + 32) / 32)][int(coord3.x / 32)] != ' ' || map.TileMap[int((coord4.y + 32) / 32)][int(coord4.x / 32)] != ' ')
		{
			switch (tetr)
			{
			case T:
				map.TileMap[int((coord1.y + 32) / 32 - 1)][int(coord1.x / 32)] = 't';
				map.TileMap[int((coord2.y + 32) / 32 - 1)][int(coord2.x / 32)] = 't';
				map.TileMap[int((coord3.y + 32) / 32 - 1)][int(coord3.x / 32)] = 't';
				map.TileMap[int((coord4.y + 32) / 32 - 1)][int(coord4.x / 32)] = 't'; break;
			case Q: 
				map.TileMap[int((coord1.y + 32) / 32 - 1)][int(coord1.x / 32)] = 'q';
				map.TileMap[int((coord2.y + 32) / 32 - 1)][int(coord2.x / 32)] = 'q';
				map.TileMap[int((coord3.y + 32) / 32 - 1)][int(coord3.x / 32)] = 'q';
				map.TileMap[int((coord4.y + 32) / 32 - 1)][int(coord4.x / 32)] = 'q'; break;
			case I: 
				map.TileMap[int((coord1.y + 32) / 32 - 1)][int(coord1.x / 32)] = 'i';
				map.TileMap[int((coord2.y + 32) / 32 - 1)][int(coord2.x / 32)] = 'i';
				map.TileMap[int((coord3.y + 32) / 32 - 1)][int(coord3.x / 32)] = 'i';
				map.TileMap[int((coord4.y + 32) / 32 - 1)][int(coord4.x / 32)] = 'i'; break;
			case Z: 
				map.TileMap[int((coord1.y + 32) / 32 - 1)][int(coord1.x / 32)] = 'z';
				map.TileMap[int((coord2.y + 32) / 32 - 1)][int(coord2.x / 32)] = 'z';
				map.TileMap[int((coord3.y + 32) / 32 - 1)][int(coord3.x / 32)] = 'z';
				map.TileMap[int((coord4.y + 32) / 32 - 1)][int(coord4.x / 32)] = 'z'; break;
			case S: 
				map.TileMap[int((coord1.y + 32) / 32 - 1)][int(coord1.x / 32)] = 's';
				map.TileMap[int((coord2.y + 32) / 32 - 1)][int(coord2.x / 32)] = 's';
				map.TileMap[int((coord3.y + 32) / 32 - 1)][int(coord3.x / 32)] = 's';
				map.TileMap[int((coord4.y + 32) / 32 - 1)][int(coord4.x / 32)] = 's'; break;
			case J:
				map.TileMap[int((coord1.y + 32) / 32 - 1)][int(coord1.x / 32)] = 'j';
				map.TileMap[int((coord2.y + 32) / 32 - 1)][int(coord2.x / 32)] = 'j';
				map.TileMap[int((coord3.y + 32) / 32 - 1)][int(coord3.x / 32)] = 'j';
				map.TileMap[int((coord4.y + 32) / 32 - 1)][int(coord4.x / 32)] = 'j'; break;
			case L: 
				map.TileMap[int((coord1.y + 32) / 32 - 1)][int(coord1.x / 32)] = 'l';
				map.TileMap[int((coord2.y + 32) / 32 - 1)][int(coord2.x / 32)] = 'l';
				map.TileMap[int((coord3.y + 32) / 32 - 1)][int(coord3.x / 32)] = 'l';
				map.TileMap[int((coord4.y + 32) / 32 - 1)][int(coord4.x / 32)] = 'l'; break;
			}
			return true;
		}
		break;
	}
	case left:
	{
		if (map.TileMap[int(coord1.y / 32)][int((coord1.x - 32) / 32)] != ' ' || map.TileMap[int(coord2.y / 32)][int((coord2.x - 32) / 32)] != ' ' ||
			map.TileMap[int(coord3.y / 32)][int((coord3.x - 32) / 32)] != ' ' || map.TileMap[int(coord4.y / 32)][int((coord4.x - 32) / 32)] != ' ')
		{
			return true;
		}
		break;
	}
	case right:
	{
		if (map.TileMap[int(coord1.y / 32)][int((coord1.x + 32) / 32)] != ' ' || map.TileMap[int(coord2.y / 32)][int((coord2.x + 32) / 32)] != ' ' ||
			map.TileMap[int(coord3.y / 32)][int((coord3.x + 32) / 32)] != ' ' || map.TileMap[int(coord4.y / 32)][int((coord4.x + 32) / 32)] != ' ')
		{
			return true;
		}
		break;
	}
	}
	return false;
}

void Tetrominoes::moveGravity(sf::RenderWindow &window, Map& map, float time)
{
	currentTimeForMove += time;
	if (timeForMove == 50) timeForMove += map.changeSpeed;
	if (currentTimeForMove > timeForMove - map.changeSpeed)
	{
		if (checkColission(map, gravity))
			isMove = false;
		else
		{
			coord1.y += 32;
			coord2.y += 32;
			coord3.y += 32;
			coord4.y += 32;
		}
		currentTimeForMove = 0;
	}
	sprite.setPosition(coord1.x, coord1.y);
	window.draw(sprite);
	sprite.setPosition(coord2.x, coord2.y);
	window.draw(sprite);
	sprite.setPosition(coord3.x, coord3.y);
	window.draw(sprite);
	sprite.setPosition(coord4.x, coord4.y);
	window.draw(sprite);
}

void Tetrominoes::moveLeft(sf::RenderWindow &window, Map& map)
{
	
	if (!checkColission(map, left))
	{
		coord1.x -= 32;
		coord2.x -= 32;
		coord3.x -= 32;
		coord4.x -= 32;
		sprite.setPosition(coord1.x, coord1.y);
		window.draw(sprite);
		sprite.setPosition(coord2.x, coord2.y);
		window.draw(sprite);
		sprite.setPosition(coord3.x, coord3.y);
		window.draw(sprite);
		sprite.setPosition(coord4.x, coord4.y);
		window.draw(sprite);
	}
}

void Tetrominoes::moveRight(sf::RenderWindow &window, Map& map)
{

	if (!checkColission(map, right))
	{
		coord1.x += 32;
		coord2.x += 32;
		coord3.x += 32;
		coord4.x += 32;
		sprite.setPosition(coord1.x, coord1.y);
		window.draw(sprite);
		sprite.setPosition(coord2.x, coord2.y);
		window.draw(sprite);
		sprite.setPosition(coord3.x, coord3.y);
		window.draw(sprite);
		sprite.setPosition(coord4.x, coord4.y);
		window.draw(sprite);
	}
}

void Tetrominoes::moveDown(bool changeSpeed)
{
	if (changeSpeed)
		timeForMove = 50;
	else
		timeForMove = 1000;
}

void Tetrominoes::rotateTetr(sf::RenderWindow &window, Map& map)
{
	switch (tetr)
	{
	case T:
		switch (currentPosForRotate)
		{
		case 0:
			{
				if (map.TileMap[int((coord3.y - 32) / 32)][int((coord3.x - 32) / 32)] == ' ')
				{
					coord3.x -= 32;
					coord3.y -= 32;
					currentPosForRotate++;
				}
				break;
			}
		case 1:
			{
				if (map.TileMap[int((coord4.y - 32) / 32)][int((coord4.x + 32) / 32)] == ' ')
				{
					coord4.x += 32;
					coord4.y -= 32;
					currentPosForRotate++;
				}
				break;
			}
		case 2:
			{
				if (map.TileMap[int((coord2.y + 32) / 32)][int((coord2.x + 32) / 32)] == ' ')
				{
					coord2.x += 32;
					coord2.y += 32;
					currentPosForRotate++;
				}
				break;
			}
		case 3:
			{
				if (map.TileMap[int((coord1.y) / 32)][int((coord1.x - 32) / 32)] == ' ')
				{
					coord2.x = coord1.x - 32;
					coord2.y = coord1.y;
					coord3.x = coord1.x + 32;
					coord3.y = coord1.y;
					coord4.x = coord1.x;
					coord4.y = coord1.y + 32;
					currentPosForRotate++;
				}
				break;
			}
		}
		if (currentPosForRotate > 3) currentPosForRotate = 0;
		break;
	case I:
		switch (currentPosForRotate)
		{
		case 0:
		{
			if (map.TileMap[int((coord1.y - 32) / 32)][int((coord1.x) / 32)] == ' ' && map.TileMap[int((coord1.y + 32) / 32)][int((coord1.x) / 32)] == ' ' &&
				map.TileMap[int((coord1.y + 64) / 32)][int((coord1.x) / 32)] == ' ')
			{
				coord2.x = coord1.x;
				coord2.y = coord1.y - 32;
				coord3.x = coord1.x;
				coord3.y = coord1.y + 32;
				coord4.x = coord1.x;
				coord4.y = coord1.y + 64;
				currentPosForRotate++;
			}
			break;
		}
		case 1:
		{
			if (map.TileMap[int((coord1.y) / 32)][int((coord1.x - 32) / 32)] == ' ' && map.TileMap[int((coord1.y) / 32)][int((coord1.x + 32) / 32)] == ' ' &&
				map.TileMap[int((coord1.y) / 32)][int((coord1.x + 64) / 32)] == ' ')
			{
				coord2.x = coord1.x - 32;
				coord2.y = coord1.y;
				coord3.x = coord1.x + 32;
				coord3.y = coord1.y;
				coord4.x = coord1.x + 64;
				coord4.y = coord1.y;
				currentPosForRotate++;
			}
			break;
		}
		}
		if (currentPosForRotate > 1) currentPosForRotate = 0;
		break;
	case Z:
		switch (currentPosForRotate)
		{
		case 0:
		{
			if (map.TileMap[int((coord1.y - 32) / 32)][int((coord1.x) / 32)] == ' ' && map.TileMap[int((coord1.y + 32) / 32)][int((coord1.x - 32) / 32)] == ' ')
			{
				coord3.y = coord3.y - 64;
				coord4.x = coord4.x - 64;
				currentPosForRotate++;
			}
			break;
		}
		case 1:
		{
			if (map.TileMap[int((coord1.y + 32) / 32)][int((coord1.x) / 32)] == ' ' && map.TileMap[int((coord1.y + 32) / 32)][int((coord1.x + 32) / 32)] == ' ')
			{
				coord3.y = coord3.y + 64;
				coord4.x = coord4.x + 64;
				currentPosForRotate++;
			}
			break;
		}
		}
		if (currentPosForRotate > 1) currentPosForRotate = 0;
		break;
	case S:
		switch (currentPosForRotate)
		{
		case 0:
		{
			if (map.TileMap[int((coord1.y - 32) / 32)][int((coord1.x) / 32)] == ' ' && map.TileMap[int((coord1.y + 32) / 32)][int((coord1.x + 32) / 32)] == ' ')
			{
				coord3.y = coord3.y - 64;
				coord2.x = coord2.x + 64;
				currentPosForRotate++;
			}
			break;
		}
		case 1:
		{
			if (map.TileMap[int((coord1.y + 32) / 32)][int((coord1.x) / 32)] == ' ' && map.TileMap[int((coord1.y + 32) / 32)][int((coord1.x - 32) / 32)] == ' ')
			{
				coord3.y = coord3.y + 64;
				coord2.x = coord2.x - 64;
				currentPosForRotate++;
			}
			break;
		}
		}
		if (currentPosForRotate > 1) currentPosForRotate = 0;
		break;
	case J:
		switch (currentPosForRotate)
		{
		case 0:
			{
				if (map.TileMap[int((coord1.y) / 32)][int((coord1.x - 32) / 32)] == ' ' && map.TileMap[int((coord1.y - 32) / 32)][int((coord1.x - 32) / 32)] == ' ' &&
					map.TileMap[int((coord1.y) / 32)][int((coord1.x + 32) / 32)] == ' ')
				{
					coord2.x = coord1.x + 32;
					coord2.y = coord1.y;
					coord3.x = coord1.x - 32;
					coord3.y = coord1.y;
					coord4.y = coord4.y - 64;
					currentPosForRotate++;
				}
				break;
			}
		case 1:
			{
			if (map.TileMap[int((coord1.y + 32) / 32)][int((coord1.x) / 32)] == ' ' && map.TileMap[int((coord1.y - 32) / 32)][int((coord1.x) / 32)] == ' ' &&
				map.TileMap[int((coord1.y - 32) / 32)][int((coord1.x + 32) / 32)] == ' ')
			{
				coord2.x = coord1.x;
				coord2.y = coord1.y + 32;
				coord3.x = coord1.x;
				coord3.y = coord1.y - 32;
				coord4.x = coord4.x + 64;
				currentPosForRotate++;
			}
			break;
			}
		case 2:
			{
			if (map.TileMap[int((coord1.y) / 32)][int((coord1.x - 32) / 32)] == ' ' && map.TileMap[int((coord1.y) / 32)][int((coord1.x + 32) / 32)] == ' ' &&
				map.TileMap[int((coord1.y + 32) / 32)][int((coord1.x + 32) / 32)] == ' ')
			{
				coord2.x = coord1.x - 32;
				coord2.y = coord1.y;
				coord3.x = coord1.x + 32;
				coord3.y = coord1.y;
				coord4.y = coord4.y + 64;
				currentPosForRotate++;
			}
			break;
			}
		case 3:
			{
			if (map.TileMap[int((coord1.y - 32) / 32)][int((coord1.x) / 32)] == ' ' && map.TileMap[int((coord1.y + 32) / 32)][int((coord1.x) / 32)] == ' ' &&
				map.TileMap[int((coord1.y + 32) / 32)][int((coord1.x - 32) / 32)] == ' ')
			{
				coord2.x = coord1.x;
				coord2.y = coord1.y - 32;
				coord3.x = coord1.x;
				coord3.y = coord1.y + 32;
				coord4.x = coord4.x - 64;
				currentPosForRotate++;
			}
			break;
			}
		}
		if (currentPosForRotate > 3) currentPosForRotate = 0;
		break;
	case L:
		switch (currentPosForRotate)
		{
		case 0:
		{
			if (map.TileMap[int((coord1.y) / 32)][int((coord1.x - 32) / 32)] == ' ' && map.TileMap[int((coord1.y + 32) / 32)][int((coord1.x - 32) / 32)] == ' ' &&
				map.TileMap[int((coord1.y) / 32)][int((coord1.x + 32) / 32)] == ' ')
			{
				coord2.x = coord1.x + 32;
				coord2.y = coord1.y;
				coord3.x = coord1.x - 32;
				coord3.y = coord1.y;
				coord4.x = coord4.x - 64;
				currentPosForRotate++;
			}
			break;
		}
		case 1:
		{
			if (map.TileMap[int((coord1.y + 32) / 32)][int((coord1.x) / 32)] == ' ' && map.TileMap[int((coord1.y - 32) / 32)][int((coord1.x) / 32)] == ' ' &&
				map.TileMap[int((coord1.y - 32) / 32)][int((coord1.x - 32) / 32)] == ' ')
			{
				coord2.x = coord1.x;
				coord2.y = coord1.y + 32;
				coord3.x = coord1.x;
				coord3.y = coord1.y - 32;
				coord4.y = coord4.y - 64;
				currentPosForRotate++;
			}
			break;
		}
		case 2:
		{
			if (map.TileMap[int((coord1.y) / 32)][int((coord1.x - 32) / 32)] == ' ' && map.TileMap[int((coord1.y) / 32)][int((coord1.x + 32) / 32)] == ' ' &&
				map.TileMap[int((coord1.y - 32) / 32)][int((coord1.x + 32) / 32)] == ' ')
			{
				coord2.x = coord1.x - 32;
				coord2.y = coord1.y;
				coord3.x = coord1.x + 32;
				coord3.y = coord1.y;
				coord4.x = coord4.x + 64;
				currentPosForRotate++;
			}
			break;
		}
		case 3:
		{
			if (map.TileMap[int((coord1.y - 32) / 32)][int((coord1.x) / 32)] == ' ' && map.TileMap[int((coord1.y + 32) / 32)][int((coord1.x) / 32)] == ' ' &&
				map.TileMap[int((coord1.y + 32) / 32)][int((coord1.x + 32) / 32)] == ' ')
			{
				coord2.x = coord1.x;
				coord2.y = coord1.y - 32;
				coord3.x = coord1.x;
				coord3.y = coord1.y + 32;
				coord4.y = coord4.y + 64;
				currentPosForRotate++;
			}
			break;
		}
		}
		if (currentPosForRotate > 3) currentPosForRotate = 0;
		break;
	}
	sprite.setPosition(coord1.x, coord1.y);
	window.draw(sprite);
	sprite.setPosition(coord2.x, coord2.y);
	window.draw(sprite);
	sprite.setPosition(coord3.x, coord3.y);
	window.draw(sprite);
	sprite.setPosition(coord4.x, coord4.y);
	window.draw(sprite);
}