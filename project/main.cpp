#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Map.h"
#include "Tetrominoes.h"

bool startGame()
{
	sf::RenderWindow window(sf::VideoMode(608, 832), "Tetris");
	sf::Image mapImage;//������ ����������� ��� �����
	mapImage.loadFromFile("images/map.png");//��������� ���� ��� �����

	sf::Font font;//����� 
	font.loadFromFile("font/CyrilicOld.ttf");//�������� ������ ������ ���� ������
	Map map(mapImage, font);

	sf::Image tetrImage;//������ ����������� ��� �����
	tetrImage.loadFromFile("images/tetrominoes.png");//��������� ���� ��� �����
	sf::Image nextTetrImage;//������ ����������� ��� �����
	nextTetrImage.loadFromFile("images/nextTetrominoes.png");//��������� ���� ��� �����
	Tetrominoes tetr(tetrImage, nextTetrImage, 32);

	sf::Music music;//������� ������ ������
	music.openFromFile("music/music.ogg");//��������� ����
	music.play();//������������� ������
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
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)) { return true; }//���� ���, �� ������������� ����
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) { return false; }//���� ������, �� ������� �� ����

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
{//�-��� ������������� ���� , ���� ��� ����������
	if (startGame()) { gameRunning(); }////���� startGame() == true, �� �������� ������ �-��� isGameRunning, ������� � ���� ������� ����� �������� startGame() 
}

int main()
{
	gameRunning();
	return 0;
}