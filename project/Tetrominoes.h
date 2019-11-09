#pragma once
#include <SFML/Graphics.hpp>
#include "Map.h"

enum TETR { T, Q, I, Z, S, J, L };
enum DIR { right, left, gravity };

class Tetrominoes
{
private:
	int m_size;
	sf::Texture texture;
	sf::Texture nextTexture;
	sf::Sprite sprite;
	sf::Sprite nextSprite;
	int nextTetr;
	sf::Vector2i coord1;
	sf::Vector2i coord2;
	sf::Vector2i coord3;
	sf::Vector2i coord4;
	TETR tetr;
	float currentTimeForMove = 0;
	float timeForMove = 1000;
	int currentPosForRotate = 0;
public:
	bool isMove = false;
	Tetrominoes(sf::Image &image, sf::Image &nextImage, int size);
	void chooseTypeTetr();
	void showNextTetr(sf::RenderWindow &window);
	bool createTetr(Map& map);
	bool checkLose(Map& map);
	bool checkColission(Map& map, DIR dir);
	void moveGravity(sf::RenderWindow &window, Map& map, float time);
	void moveLeft(sf::RenderWindow &window, Map& map);
	void moveRight(sf::RenderWindow &window, Map& map);
	void moveDown(bool changeSpeed);
	void rotateTetr(sf::RenderWindow &window, Map& map);
};