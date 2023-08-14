#include "Game.h"

void Game::initVars()
{
	this->window = nullptr;
	std::vector<sf::Color> temp;
	for (int j = 0; j < 20; j++) {
		temp.push_back(sf::Color::Black);
	}

	for (int i = 0; i < 15; i++) {
		this->shapes.push_back(temp);
	}
}

void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(600, 800), "Tetris MegaDEMO 2008");
	this->window->setFramerateLimit(5);
}

void Game::initShapes()
{	
	this->shapeInfo.clear();
	int x = 0;
	//int x = rand() % 5;
	for (int i = 0; i < 4; i++) {
		if (this->shapeCoords[x][i] % 2 == 1) {
			this->shapes[0][this->shapeCoords[x][i] / 2] = sf::Color::Green;
			this->shapeInfo.push_back({ 0, this->shapeCoords[x][i] / 2 });
		}
		else {
			this->shapes[1][this->shapeCoords[x][i] / 2 - 1] = sf::Color::Green;
			this->shapeInfo.push_back({ 1, this->shapeCoords[x][i] / 2 - 1});
		}
	}
}

void Game::updateShapes()
{
	if (this->returnShapeDown() + 1 >= 20 || this->conflictShapes()) {
		// если дошла конца
		this->initShapes();
	}
	else {
		// Движение вниз фигуры
		for (int i = 3; i > -1; i--) {
			int getZero = std::get<0>(this->shapeInfo[i]);
			int getOne = std::get<1>(this->shapeInfo[i]);
			this->shapes[getZero][getOne] = sf::Color::Black;
			this->shapes[getZero][getOne + 1] = sf::Color::Green;
			this->shapeInfo[i] = { getZero, getOne + 1 };
		}
	}
}

void Game::updateArray()
{
	for (int i = 0; i < 15; i++) {
		bool flag = true;
		for (int j = 0; j < 20; j++) {
			if (this->shapes[i][j] == sf::Color::Black) {
				flag = false;
				break;
			}
		}
		if (flag) {
			for (int j = 0; j < 20; j++) {
				this->shapes[i][j] = sf::Color::Black;
			}
		}
	}
}

Game::Game()
{
	this->initVars();
	this->initWindow();
	this->initShapes();
}

Game::~Game()
{
	delete this->window;
}

void Game::pollEvents()
{
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type) {
			case (sf::Event::Closed):
				this->window->close();
				break;
			case (sf::Event::KeyPressed):
				if (ev.key.code == sf::Keyboard::Right) {
					this->moveShape(1);
				}
				else if (ev.key.code == sf::Keyboard::Left) {
					this->moveShape(-1);
				}
				else if (ev.key.code == sf::Keyboard::Down) {
					this->shape.setPosition(this->shape.getPosition().x, this->shape.getPosition().y + 10.f);
				}
				else if (ev.key.code == sf::Keyboard::Up) {
					if (this->shape.getRotation() == 0.f) {
						this->shape.setRotation(this->shape.getRotation() - 90.f);
					} else this->shape.setRotation(this->shape.getRotation() + 90.f);
				}
				break;
		}
	}
}

const bool Game::running() const
{
	return this->window->isOpen();
}

void Game::update()
{
	this->pollEvents();
	this->updateShapes();
	this->updateArray();
}

void Game::render()
{
	this->window->clear();
	this->drawArray();
	this->window->display();
}

void Game::drawArray()
{
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 20; j++) {
			sf::RectangleShape rectangle(sf::Vector2f(40.f, 40.f));
			rectangle.setFillColor(this->shapes[i][j]);
			rectangle.setPosition(i * 40.f, j * 40.f);
			this->window->draw(rectangle);
		}
	}
}

void Game::moveShape(int move)
{
	for (int i = 0; i < 4; i++) {
		int getZero = std::get<0>(this->shapeInfo[i]);
		if (getZero + move > 40 || getZero + move < 0) {
			return;
		}
	}
	// Можно слиять
	for (int i = 0; i < 4; i++) {
		int getZero = std::get<0>(this->shapeInfo[i]);
		int getOne = std::get<1>(this->shapeInfo[i]);
		this->shapes[getZero][getOne] = sf::Color::Black;
		this->shapes[getZero + move][getOne] = sf::Color::Green;
		this->shapeInfo[i] = { getZero + move, getOne };
	}
}

int Game::returnShapeDown()
{
	int check = 0;
	std::tuple<int, int> temp = {0, 0};
	for (std::tuple<int, int> x : this->shapeInfo) {
		if (std::get<1>(x) > check) {
			temp = x;
			check = std::get<1>(x);
		}
	}
	return check;
}

bool Game::conflictShapes()
{
	for (std::tuple<int, int> x : this->shapeInfo) {
		if (std::get<1>(x) < 20 && !this->itSelf({ std::get<0>(x), std::get<1>(x) + 1 })) {
			if (this->shapes[std::get<0>(x)][std::get<1>(x) + 1] == sf::Color::Green) {
				return true;
			}
		}
	}
	return false;
}

bool Game::itSelf(std::tuple<int, int> to_check)
{
	for (std::tuple<int, int> x : this->shapeInfo) {
		if (x == to_check) {
			return true;
		}
	}
	return false;
}

/*
TODO:
Очистка линии работает не правильно
Сделать повороты
Переделать проверку столкновений

*/