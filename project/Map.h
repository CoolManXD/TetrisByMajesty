#pragma once
#include <SFML/Graphics.hpp>
//#include "Tetrominoes.h"
class Tetrominoes;

class Map
{
private:
	static const int HEIGHT_MAP = 26;//размер карты высота
	static const int WIDTH_MAP = 19;//размер карты ширина 
	sf::String TileMap[HEIGHT_MAP] = {
		"0000000000000000000",
		"                   ",
		"                   ",
		"0000000000000000000",
		"0          0      0",
		"0          0      0",
		"0          0      0",
		"0          0      0",
		"0          0      0",
		"0          0      0",
		"0          00000000",
		"0          0      0",
		"0          0      0",
		"0          0      0",
		"0          0      0",
		"0          0      0",
		"0          0      0",
		"0          0      0",
		"0          0      0",
		"0          0      0",
		"0          0      0",
		"0          0      0",
		"0          0      0",
		"0          0      0",
		"0          0      0",
		"0000000000000000000",
	};
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Text tetrisText;
	sf::Text scoreText;
	sf::Text nextTetrText;
	sf::Text escapeText;
	sf::Text tabText;
	sf::Text youDiedText;
	sf::Text controlText;
	int score = 0;
	int changeSpeed = 0;
public:
	Map(sf::Image &image, sf::Font &font);
	void drawMap(sf::RenderWindow &window);
	void clearRow();
	void pullDown(int h);
	void drawInformation(sf::RenderWindow &window);
	void drawYouDied(sf::RenderWindow &window);
	void complicateTheGame();
	//friend void Tetrominoes::checkColission(Map& map, DIR dir);
	friend class Tetrominoes;
};