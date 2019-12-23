#include <SFML/Graphics.hpp>

#include <chrono>
#include <ctime>
#include <string>		// String object
#include <vector>		// Vector object
#include <iostream>

#include "GameController.h"
#include "GameMenuController.h"
#include "EnemyController.h"
#include "TowerController.h"
#include "TowerAndEnemyController.h"
#include "Tower.h"
#include "GameState.h"
#include "Timer.h"

using sf::Vector2f;
using std::cout;
using std::endl;

sf::RectangleShape groundTile;
sf::CircleShape hoverRange;
sf::RectangleShape shadowTile;
sf::RectangleShape* _tamsCounter;
sf::RectangleShape* _livesCounter;
sf::RectangleShape* _wavesCounter;
sf::RectangleShape helpScreen;
sf::RectangleShape background;

sf::Text tamText, waveText, waveWord, healthText, text;

const std::vector<Vector2f> path = { Vector2f(15, 0), Vector2f(15, 4), 
    Vector2f(20, 4), Vector2f(22, 4), Vector2f(22, 8), Vector2f(10, 8), 
    Vector2f(10, 6), Vector2f(4, 6), Vector2f(4, 13), Vector2f(12, 13),
    Vector2f(12, 15), Vector2f(17, 15), Vector2f(17, 12), Vector2f(21, 12), 
    Vector2f(21, 18) };

sf::RenderWindow* window;
sf::Event event;

bool debug;

GameBoard::GameBoard(GameState* _gameState, TowerController* _towerController,
		int _width) :
		gameState(_gameState), towerController(_towerController), width(_width) {
	sf::Texture* _menuTexture = new sf::Texture;
	if (!_menuTexture->loadFromFile("images/menuButtons.png")) {
		std::cerr << "The texture does not exist" << std::endl;
	}
	_tamsCounter = new sf::RectangleShape(sf::Vector2f(280, 110));
	_tamsCounter->setPosition(10, 5);
	_tamsCounter->setTexture(_menuTexture);
	_tamsCounter->setTextureRect(sf::IntRect(0, 0, 416, 160));

	_livesCounter = new sf::RectangleShape(sf::Vector2f(280, 110));
	_livesCounter->setPosition(730, 5);
	_livesCounter->setTexture(_menuTexture);
	_livesCounter->setTextureRect(sf::IntRect(416, 0, 416, 160));

	_wavesCounter = new sf::RectangleShape(sf::Vector2f(360, 110));
	_wavesCounter->setPosition(330, 10);
	_wavesCounter->setTexture(_menuTexture);
	_wavesCounter->setTextureRect(sf::IntRect(0, 192, 768, 224));

	sf::Texture* _helpTexture = new sf::Texture;
	if (!_helpTexture->loadFromFile("assets/help_screen.png")) {
		std::cerr << "Error loading the help screen" << std::endl;
	}

	helpScreen = sf::RectangleShape(sf::Vector2f(1280, 720));
	helpScreen.setPosition(0, 0);
	helpScreen.setTexture(_helpTexture);

  sf::Texture* backTexture = new sf::Texture;
  if (!backTexture->loadFromFile("images/background.png")) {
    std::cerr << "Error loading the background" << std::endl;
  }

  background = sf::RectangleShape(sf::Vector2f(1280, 720));
  background.setPosition(0, 0);
  //background.setFillColor(sf::Color(153, 140, 85));
  background.setTexture(backTexture);

	tamText.setString(std::to_string(100));
	waveText.setString(std::to_string(0));
	healthText.setString(std::to_string(100));
	waveWord.setString("Wave");
	tamText.setPosition(140, 55);
	tamText.setCharacterSize(30);
	waveText.setPosition(560, 60);
	waveText.setCharacterSize(30);
	healthText.setPosition(830, 55);
	healthText.setCharacterSize(30);
	waveWord.setPosition(400, 60);
	waveWord.setCharacterSize(30);

	// Grass Tile Objects
  /*sf::Texture* grassTexture = new sf::Texture;
  if (!grassTexture->loadFromFile("images/grass.png")) {
    std::cerr << "Error loading the grass tile" << std::endl;
  }*/
	//grassTile = sf::RectangleShape(sf::Vector2f(Clickable::gridSize, Clickable::gridSize));
 // grassTile.setFillColor(sf::Color::Transparent);//(100, 250, 50)); // green
 //// grassTile.setTexture(grassTexture);
	//grassTile.setOutlineThickness(-1);
	//grassTile.setOutlineColor(sf::Color(0, 0, 0, 50));
	// Ground Tile Objects
  sf::Texture* groundTexture = new sf::Texture;
  if (!groundTexture->loadFromFile("images/ground.png")) {
    std::cerr << "Error loading the ground tile" << std::endl;
  }
	groundTile = sf::RectangleShape(sf::Vector2f(Clickable::gridSize, Clickable::gridSize));
	groundTile.setFillColor(sf::Color(110, 110, 100)); // brown
  groundTile.setTexture(groundTexture);
	//groundTile.setOutlineThickness(-1);
	//groundTile.setOutlineColor(sf::Color(0, 0, 0, 100));
	// Hover Object
	hoverRange = sf::CircleShape(Clickable::gridSize);
	hoverRange.setFillColor(sf::Color::Transparent);
	hoverRange.setOutlineColor(sf::Color::Red);
	hoverRange.setOutlineThickness(-2);
	// Shadow Object
	shadowTile = sf::RectangleShape(sf::Vector2f(Clickable::gridSize, Clickable::gridSize));
	shadowTile.setFillColor(sf::Color(255, 0, 0, 150));
}

bool GameBoard::gridSpaceAvailable(int gridX, int gridY) {
	if (gridStatus[gridX][gridY] == 0) {
		return true;
	} else
		return false;
}

bool GameBoard::towerIsPurchasable(TowerType type) {
	if (type != TowerType::empty) {
		if (gameState->getTams() >= gameState->getTowerProps(type)["tam"]) {
			return true;
		}
	}
	return false;
}

// Determine if any action needs ton be taken by
// cliking on the game board
void GameBoard::process(sf::Event event, sf::Vector2i mousePos) {
	if (mousePos.x >= width) {
		return;
	}

	int gridX = ceil(mousePos.x / Clickable::gridSize);
	int gridY = ceil(mousePos.y / Clickable::gridSize);
	if ((event.type == sf::Event::MouseButtonPressed)
			&& (event.mouseButton.button == sf::Mouse::Left)) {
		//Remove selected game tower. If double clicking a tower,
		// it will simply regain the connection by the towerController
		gameState->setBoardTower(nullptr);
		TowerType type = gameState->getPurchaseTower();
		// If an open space exists, fill the board with twos.
		if (towerIsPurchasable(type) && gridSpaceAvailable(gridX, gridY)) {
			gridStatus[gridX][gridY] = 2;
	//		gridStatus[gridX + 1][gridY] = 2;
	//		gridStatus[gridX][gridY + 1] = 2;
	//		gridStatus[gridX + 1][gridY + 1] = 2;
			sf::Vector2f spawnPos = sf::Vector2f(gridX * Clickable::gridSize,
					gridY * Clickable::gridSize);
			towerController->spawnTower(spawnPos, type);
			gameState->updateTamBy(-(gameState->getTowerProps(type)["tam"]));
		}
		//PRINT BOARD
		if (debug) {
			for (int i = 0; i < 18; i++) {
				for (int j = 0; j < 32; j++) {
					std::cout << gridStatus[j][i] << " ";
				}
				std::cout << std::endl;
			}
			std::cout << std::endl;
		}
	}
}

bool GameBoard::validatePos(int mouseX, int mouseY, int range) {
	int gridX = ceil(mouseX / Clickable::gridSize);
	int gridY = ceil(mouseY / Clickable::gridSize);
	for (int x = 0; x < range; x++) {
		for (int y = 0; y < range; y++) {
			if (gridStatus[gridX + x][gridY + y] != 0)
				return false;
		}
	}
	return true;
}

// Draws Map with Ground and Grass Objects
void GameBoard::render() {
	sf::Vector2i mousePos = gameState->mousePos;

	// Each square is to be 40 pixels wide,
	// with an exact height of 18 tiles

	// Draw Grass Everywhere
  window->draw(background);
// Draw Ground on Path Only
	for (unsigned int i = 0; i < path.size() - 1; i++) {
		sf::Vector2i curr = sf::Vector2i(path[i]);		// Current Vector2f
		sf::Vector2i next = sf::Vector2i(path[i + 1]);		// Next Vector2f
		if (curr.x == next.x) {			// If two Vector2fs vertical
			while (curr.y != next.y) {
				groundTile.setPosition(curr.x * Clickable::gridSize, curr.y * Clickable::gridSize);
				window->draw(groundTile);
				if (curr.y < next.y)
					curr.y++;		// Draw up or down until next Vector2f
				else
					curr.y--;
				gridStatus[curr.x][curr.y] = 1;
			}
		} else if (curr.y == next.y) {	// If two Vector2fs horizontal
			while (curr.x != next.x) {
				groundTile.setPosition(curr.x * Clickable::gridSize, curr.y * Clickable::gridSize);
				window->draw(groundTile);
				if (curr.x < next.x)
					curr.x++;		// Draw left or right until next Vector2f
				else
					curr.x--;
				gridStatus[curr.x][curr.y] = 1;
			}
		}
	}

	TowerType type = gameState->getPurchaseTower();
	if (type != TowerType::empty) {
		renderRange(mousePos.x, mousePos.y,
				gameState->getTowerProps(type)["range"]);
		renderShadow(mousePos.x, mousePos.y, 1);
	}
}

void GameBoard::renderLabels() {
	window->draw(*_tamsCounter);
	window->draw(*_livesCounter);
	window->draw(*_wavesCounter);
	window->draw(tamText);
	window->draw(waveText);
	window->draw(healthText);
	window->draw(waveWord);
}

// Draw Range
void GameBoard::renderRange(int mouseX, int mouseY, int range) {
  int gridX = ceil(mouseX / Clickable::gridSize) * Clickable::gridSize + Clickable::gridSize / 2;
  int gridY = ceil(mouseY / Clickable::gridSize) * Clickable::gridSize + Clickable::gridSize / 2;

	hoverRange.setRadius(range);
	hoverRange.setPosition(gridX - range, gridY - range);
	window->draw(hoverRange);
}

// Draw Placement Shadow
void GameBoard::renderShadow(int mouseX, int mouseY, int range) {
	int gridX = ceil(mouseX / Clickable::gridSize);
	int gridY = ceil(mouseY / Clickable::gridSize);
	shadowTile.setSize(sf::Vector2f(range * Clickable::gridSize, range * Clickable::gridSize));
	shadowTile.setPosition(gridX * Clickable::gridSize, gridY * Clickable::gridSize);
	window->draw(shadowTile);
}

GameController::GameController() {
}

void deathLoop() {
	sf::Texture* texture = new sf::Texture;
	if (!texture->loadFromFile("assets/game_over.png")) {
		std::cerr << "Error loading the help screen" << std::endl;
	}

	sf::RectangleShape deathScreen = sf::RectangleShape(
			sf::Vector2f(1280, 720));
	deathScreen.setPosition(0, 0);
	deathScreen.setTexture(texture);
	window->draw(deathScreen);
	window->display();
	while (true) {
		while (window->pollEvent(event)) {
			if (event.type == sf::Event::EventType::Closed
					|| (event.type == sf::Event::MouseButtonPressed)
					|| (event.type == sf::Event::KeyPressed)) {
				return;
			}
		}
	}
}

//! \brief MainMenu
void menu(sf::RenderWindow* window) {
  sf::RectangleShape backgroundBlack = sf::RectangleShape(sf::Vector2f(1280, 720));
  backgroundBlack.setPosition(0, 0);
  backgroundBlack.setFillColor(sf::Color(0, 0, 0, 200));/*
  sf::Texture* _menuTexture = new sf::Texture;
  if (!_menuTexture->loadFromFile("images/menuButtons.png")) {
    std::cerr << "The texture does not exist" << std::endl;
  }*/
  sf::IntRect _textureRect(sf::IntRect(1056, 165, 320, 128));
  sf::Vector2f _size(360, 110);
  sf::RectangleShape buttonStart(_size);
  buttonStart.setPosition(460, 100);
  buttonStart.setTexture(_menuTexture);
  buttonStart.setTextureRect(_textureRect);
  bool isMenu(1);
  int menuNum(0);
  while (isMenu && window->isOpen())
  {
    window->clear();
    while (window->pollEvent(event)) {
      if (event.type == sf::Event::EventType::Closed) {
        window->close();
      } else if (event.type == sf::Event::KeyPressed
        && event.key.code == sf::Keyboard::Escape) {
        isMenu = false;
      } else if (event.type == sf::Event::MouseButtonReleased
        && event.mouseButton.button == sf::Mouse::Left) {
        if (sf::IntRect(460, 100, 360, 110).contains(sf::Mouse::getPosition(*window))) {
          isMenu = false;
        }
      }
    }/*
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
      if (sf::IntRect(1056, 165, 320, 128).contains(sf::Mouse::getPosition(*window))) {
        isMenu = false;
      } 

    }*/
    window->draw(background);
    window->draw(backgroundBlack);
    window->draw(buttonStart);
    window->display();
  }
}

// Main
int main() {
// Initialization
  debug = false;
	window = new sf::RenderWindow(sf::VideoMode(1280, 720), "Tower Defence", sf::Style::Close);
	window->setFramerateLimit(60);
	sf::Font font;
	if (!font.loadFromFile("assets/georgia.ttf")) {
	} else {
		tamText.setFont(font);
		waveText.setFont(font);
		healthText.setFont(font);
		waveWord.setFont(font);
	}
	Timer* clk = new Timer();
	GameState* gameState = new GameState(clk);
	GameMenuController* gameMenuController = new GameMenuController(window,
			gameState);
	TowerController* towerController = new TowerController(window, gameState);
	EnemyController* enemyController = new EnemyController(window, gameState,
			path);
	GameBoard* gameBoard = new GameBoard(gameState, towerController,
			gameMenuController->getMenuPos().x);

	TowerAndEnemyController* attackController = new TowerAndEnemyController(
			window, gameState, enemyController, towerController->getTowerVec(),
			enemyController->getEnemyVec());

// TODO: Remove this temp enemy creating code
	//enemyController->spawnEnemy(sf::Vector2f(100, 100), EnemyType::fast);
	//enemyController->spawnEnemy(sf::Vector2f(500, 500), EnemyType::regular);

	gameMenuController->setDebug(debug);
  bool isMenu = true;
// Main game loop
	while (window->isOpen()) {
    if (isMenu) {
      menu(window);
      isMenu = false;
    }
		sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
		gameState->mousePos = mousePos;

		// Display the help menu
		if (gameState->getHelperState()) {
			window->clear();
			window->draw(helpScreen);
			window->display();
			while (gameState->getHelperState()) {
				while (window->pollEvent(event)) {
					if (event.type == sf::Event::EventType::Closed) {
						window->close();
						return 0;
					} else if ((event.type == sf::Event::MouseButtonReleased)
            && (event.mouseButton.button == sf::Mouse::Left)
            || (event.type == sf::Event::KeyPressed
              && event.key.code == sf::Keyboard::Escape)) {
						gameState->toggleHelpScreen();
					}
				}
			}
		}

		// Process
		while (window->pollEvent(event)) {
			if (event.type == sf::Event::EventType::Closed) {
				window->close();
      }
      else if (event.type == sf::Event::KeyPressed
        && event.key.code == sf::Keyboard::Escape) {
        isMenu = true;
      } else {
				gameMenuController->process(event, mousePos);
				gameBoard->process(event, mousePos);
				towerController->process(event, mousePos);
			}
		}

		gameMenuController->update();
		if (clk->newTick()) {
			//update
			enemyController->update();
			attackController->update();
		}

		if (gameState->dirtyBit) {
			waveText.setString(std::to_string(gameState->getCurrentWave()));
			healthText.setString(std::to_string(gameState->getHealth()));
			tamText.setString(std::to_string(gameState->getTams()));
			gameState->dirtyBit = false;
		}
		// Render
		window->clear();
		gameBoard->render();
		enemyController->render();
		towerController->render();
		gameMenuController->render();
		attackController->render();
		gameBoard->renderLabels();
		if (debug) {
			//text.setString(std::to_string(gridX) + "," + std::to_string(gridY));
			text.setString(std::to_string(clk->elapsedTicks()));
			text.setFont(font);
			text.setPosition(float(mousePos.x), float(mousePos.y));
			window->draw(text);
		}
		if (gameState->getHealth() < 1) {
			clk->stop();
			deathLoop();
			return 0;
		}
		window->display();
	} // End of main game loop
	return 0;
}
