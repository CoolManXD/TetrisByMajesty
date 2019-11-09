#include "Map.h"
#include <string>
Map::Map(sf::Image &image, sf::Font &font)
{
	texture.loadFromImage(image);//заряжаем текстуру картинкой
	sprite.setTexture(texture);//заливаем текстуру спрайтом

	tetrisText.setFont(font);
	tetrisText.setCharacterSize(32);
	tetrisText.setFillColor(sf::Color::Red);//покрасили текст в красный. если убрать эту строку, то по умолчанию он белый
	tetrisText.setStyle(sf::Text::Bold | sf::Text::Underlined);//жирный и подчеркнутый текст. по умолчанию он "худой":)) и не подчеркнутый
	tetrisText.setString("TETRIS");
	tetrisText.setPosition(250, 45);
	//sf::Text tetris("", font, 32);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
	scoreText.setFont(font);
	scoreText.setCharacterSize(32);
	scoreText.setFillColor(sf::Color::Red);//покрасили текст в красный. если убрать эту строку, то по умолчанию он белый
	scoreText.setStyle(sf::Text::Bold);//жирный и подчеркнутый текст. по умолчанию он "худой":)) и не подчеркнутый
	scoreText.setString("");
	scoreText.setPosition(400, 360);

	nextTetrText.setFont(font);
	nextTetrText.setCharacterSize(25);
	nextTetrText.setFillColor(sf::Color::Black);//покрасили текст в красный. если убрать эту строку, то по умолчанию он белый
	nextTetrText.setStyle(sf::Text::Bold);//жирный и подчеркнутый текст. по умолчанию он "худой":)) и не подчеркнутый
	nextTetrText.setString("Next \n tetrominoes");
	nextTetrText.setPosition(400, 128);

	escapeText.setFont(font);
	escapeText.setCharacterSize(20);
	escapeText.setFillColor(sf::Color::Black);//покрасили текст в красный. если убрать эту строку, то по умолчанию он белый
	escapeText.setStyle(sf::Text::Bold);//жирный и подчеркнутый текст. по умолчанию он "худой":)) и не подчеркнутый
	escapeText.setString("Press ESCAPE \n to exit");
	escapeText.setPosition(390, 724);

	tabText.setFont(font);
	tabText.setCharacterSize(20);
	tabText.setFillColor(sf::Color::Black);//покрасили текст в красный. если убрать эту строку, то по умолчанию он белый
	tabText.setStyle(sf::Text::Bold);//жирный и подчеркнутый текст. по умолчанию он "худой":)) и не подчеркнутый
	tabText.setString("Press TAB to \n restart game");
	tabText.setPosition(390, 660);

	youDiedText.setFont(font);
	youDiedText.setCharacterSize(30);
	youDiedText.setFillColor(sf::Color::Red);//покрасили текст в красный. если убрать эту строку, то по умолчанию он белый
	youDiedText.setStyle(sf::Text::Bold);//жирный и подчеркнутый текст. по умолчанию он "худой":)) и не подчеркнутый
	youDiedText.setString("~YOU DIED~");
	youDiedText.setPosition(390, 445);

	controlText.setFont(font);
	controlText.setCharacterSize(20);
	controlText.setFillColor(sf::Color::Black);//покрасили текст в красный. если убрать эту строку, то по умолчанию он белый
	controlText.setStyle(sf::Text::Bold);//жирный и подчеркнутый текст. по умолчанию он "худой":)) и не подчеркнутый
	controlText.setString("Use arrow keys \nLeft - move left \nRight - move right \nUp - rotate \nDown - speed up \n            the fall");
	controlText.setPosition(390, 520);
}
void Map::drawMap(sf::RenderWindow &window)
{
	/////////////////////////////Рисуем карту/////////////////////
	for (int i = 0; i < HEIGHT_MAP; i++)
		for (int j = 0; j < WIDTH_MAP; j++)
		{
			if (TileMap[i][j] == ' ')  sprite.setTextureRect(sf::IntRect(0, 0, 32, 32)); //если встретили символ пробел, то рисуем 1й квадратик
			if (TileMap[i][j] == '0')  sprite.setTextureRect(sf::IntRect(32, 0, 32, 32));//если встретили символ s, то рисуем 2й квадратик
			if (TileMap[i][j] == 'z')  sprite.setTextureRect(sf::IntRect(64, 0, 32, 32));//если встретили символ s, то рисуем 2й квадратик
			if (TileMap[i][j] == 'i')  sprite.setTextureRect(sf::IntRect(96, 0, 32, 32));//если встретили символ s, то рисуем 2й квадратик
			if (TileMap[i][j] == 'l')  sprite.setTextureRect(sf::IntRect(128, 0, 32, 32));//если встретили символ s, то рисуем 2й квадратик
			if (TileMap[i][j] == 'j')  sprite.setTextureRect(sf::IntRect(160, 0, 32, 32));//если встретили символ s, то рисуем 2й квадратик
			if (TileMap[i][j] == 's')  sprite.setTextureRect(sf::IntRect(192, 0, 32, 32));//если встретили символ s, то рисуем 2й квадратик
			if (TileMap[i][j] == 'q')  sprite.setTextureRect(sf::IntRect(224, 0, 32, 32));//если встретили символ s, то рисуем 2й квадратик
			if (TileMap[i][j] == 't')  sprite.setTextureRect(sf::IntRect(256, 0, 32, 32));//если встретили символ s, то рисуем 2й квадратик

			sprite.setPosition(j * 32, i * 32);//по сути раскидывает квадратики, превращая в карту. то есть задает каждому из них позицию. если убрать, то вся карта нарисуется в одном квадрате 32*32 и мы увидим один квадрат
			window.draw(sprite);//рисуем квадратики на экран
		}
}

void Map::clearRow()
{
	int rows = 0;
	bool find = true;
	for (int i = 24; i >= 4; i--)
	{
		for (int j = 1; j <= 10; j++)
		{
			if (TileMap[i][j] == ' ')
			{
				find = false;
				break;
			}
		}
		if (find == true)
		{
			for (int j = 1; j <= 10; j++)
				TileMap[i][j] = ' ';
			rows++;
			pullDown(i - 1);
		}
		find = true;
	}
	score += (rows * rows * 100 / 2);
}

void Map::pullDown(int h)
{
	for (int i = h; i >= 4; i--)
	{
		for (int j = 1; j <= 10; j++)
		{
			std::swap(TileMap[i][j], TileMap[i + 1][j]);
		}
	}
}

void Map::complicateTheGame()
{
	if (changeSpeed < 850)
		changeSpeed = score * 0.1;
}

void Map::drawInformation(sf::RenderWindow &window)
{
	scoreText.setString("Score:\n" + std::to_string(score));
	window.draw(tetrisText);
	window.draw(scoreText);
	window.draw(nextTetrText);
	window.draw(escapeText);
	window.draw(tabText);
	window.draw(controlText);
}

void Map::drawYouDied(sf::RenderWindow &window)
{
	window.draw(youDiedText);
}