#pragma once

#include <iostream>
#include <ctime>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <vector>
#include <tuple>


class Game
{
private:
	int shapeCoords[5][4] = { {1, 3, 5, 7}, {1, 2, 3, 4}, {2, 3, 4, 5}, {1, 3, 4, 6}, {2, 3, 4, 6} }; // ������ ���������� ��� ��������� �����
	sf::RenderWindow* window;
	sf::Event ev;

	std::tuple<int, int> centerShape;
	std::vector<std::tuple<int, int>> shapeInfo; // ������ ��������� ������� ������ 
	std::vector<std::vector<sf::Color>> shapes; // ������ ����. ������ 600 - ���� ������ 20 ����. ������ 800  - ���� ������ 40 ����. [30][20]
	sf::ConvexShape shape; 

	void initVars();
	void initWindow();
	void initShapes();
	void updateShapes();
	void updateArray();
public:
	Game();
	virtual ~Game();
	void pollEvents();
	const bool running() const;
	void update();
	void render();
	void drawArray();
	void moveShape(int move);
	void rotateShape();
	int returnShapeDown();
	bool conflictShapes();
	bool highCheck();
	bool isNonLine();
	bool itSelf(std::tuple<int, int> to_check);
}; 
