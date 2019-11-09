#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Map.h"
#include "Tetrominoes.h"

bool startGame()
{
	sf::RenderWindow window(sf::VideoMode(608, 832), "Tetris");
	sf::Image mapImage;//объект изображения для карты
	mapImage.loadFromFile("images/map.png");//загружаем файл для карты

	sf::Font font;//шрифт 
	font.loadFromFile("font/CyrilicOld.ttf");//передаем нашему шрифту файл шрифта
	Map map(mapImage, font);

	sf::Image tetrImage;//объект изображения для карты
	tetrImage.loadFromFile("images/tetrominoes.png");//загружаем файл для карты
	sf::Image nextTetrImage;//объект изображения для карты
	nextTetrImage.loadFromFile("images/nextTetrominoes.png");//загружаем файл для карты
	Tetrominoes tetr(tetrImage, nextTetrImage, 32);

	sf::Music music;//создаем объект музыки
	music.openFromFile("music/music.ogg");//загружаем файл
	music.play();//воспроизводим музыку
	music.setLoop(true);

	std::srand(time(NULL));
	sf::Clock clock;
	bool isLose = false;

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 800;
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Left)
				{
					tetr.moveLeft(window, map);
				}
				if (event.key.code == sf::Keyboard::Right)
				{
					tetr.moveRight(window, map);
				}
				if (event.key.code == sf::Keyboard::Down)
				{
					tetr.moveDown(true);
				}
				if (event.key.code == sf::Keyboard::Up)
				{
					tetr.rotateTetr(window, map);
				}
			}
			if (event.type == sf::Event::KeyReleased)
				if (event.key.code == sf::Keyboard::Down)
				{
					tetr.moveDown(false);
				}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)) { return true; }//если таб, то перезагружаем игру
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) { return false; }//если эскейп, то выходим из игры

		window.clear();

		map.drawMap(window);
		map.drawInformation(window);
		
		if (!isLose)
		{
			map.clearRow();
			map.complicateTheGame();
			if (!tetr.isMove)
			{
				tetr.chooseTypeTetr();
				if(tetr.createTetr(map)) 
					isLose = true;
			}
			else
			{
				tetr.moveGravity(window, map, time);
				tetr.showNextTetr(window);
			}
		}
		else
		{
			map.drawYouDied(window);
		}
		window.display();
	}
}

void gameRunning() 
{//ф-ция перезагружает игру , если это необходимо
	if (startGame()) { gameRunning(); }////если startGame() == true, то вызываем занова ф-цию isGameRunning, которая в свою очередь опять вызывает startGame() 
}

int main()
{
	gameRunning();
	return 0;
}