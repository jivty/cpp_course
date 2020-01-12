#include "GameController.h"
#include "GameMenuController.h"
#include "EnemyController.h"
#include "BulletController.h"
#include "Timer.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>

sf::Event event;

GameBoard::GameBoard(std::shared_ptr<GameState> _gameState,
  std::shared_ptr<TowerController> _towerController, int _width,
  std::shared_ptr<sf::RenderWindow>& _window)
  : gameState(_gameState)
  , towerController(_towerController)
  , width(_width)
  , window(_window) {
  difficulty = _gameState->getDifficulty();
  _goldCounter = std::make_unique<sf::RectangleShape>(sf::Vector2f(280, 110));
  _goldCounter->setPosition(10, 5);
  _livesCounter = std::make_unique<sf::RectangleShape>(sf::Vector2f(280, 110));
  _livesCounter->setPosition(730, 5);
  _wavesCounter = std::make_unique<sf::RectangleShape>(sf::Vector2f(360, 110));
  _wavesCounter->setPosition(330, 10);
  if (!_menuTexture->loadFromFile("images/menuButtons.png")) {
    std::cerr << "The texture does not exist" << std::endl;
  }
  else {
    _goldCounter->setTexture(_menuTexture.get());
    _goldCounter->setTextureRect(sf::IntRect(0, 0, 416, 160));
    _livesCounter->setTexture(_menuTexture.get());
    _livesCounter->setTextureRect(sf::IntRect(416, 0, 416, 160));
    _wavesCounter->setTexture(_menuTexture.get());
    _wavesCounter->setTextureRect(sf::IntRect(0, 192, 768, 224));
  }

  if (!font.loadFromFile("font/georgia.ttf")) {
    std::cerr << "Error loading the font" << std::endl;
  }
  else {
    goldText.setFont(font);
    waveText.setFont(font);
    healthText.setFont(font);
    waveWord.setFont(font);
    textNewGame.setFont(font);
    textCloseGame.setFont(font);
    textContGame.setFont(font);
    textLoading.setFont(font);
    textLevel1.setFont(font);
    textLevel2.setFont(font);
    textLevel3.setFont(font);
    textLevel4.setFont(font);
    textBack.setFont(font);
    textSaving.setFont(font);
    textYes.setFont(font);
    textNo.setFont(font);
    textCancel.setFont(font);
    textConfirmation.setFont(font);
  }

  if (!_helpTexture->loadFromFile("images/helpScreen.png")) {
    std::cerr << "Error loading the help screen" << std::endl;
  }
  helpScreen = sf::RectangleShape(sf::Vector2f(1280, 720));
  helpScreen.setPosition(0, 0);
  helpScreen.setTexture(_helpTexture.get());

  if (!deathscreentexture->loadFromFile("images/game_over.png")) {
    std::cerr << "Error loading the death screen" << std::endl;
  }
  deathScreen.setSize(sf::Vector2f(1280, 720));
  deathScreen.setPosition(0, 0);
  deathScreen.setTexture(deathscreentexture.get());

  background = sf::RectangleShape(sf::Vector2f(1280, 720));
  background.setPosition(0, 0);
  if (!_backTexture->loadFromFile("images/background.png")) {
    std::cerr << "Error loading the background" << std::endl;
  }
  else {
    background.setTexture(_backTexture.get());
  }

  goldText.setString(std::to_string(_gameState->getGold()));
  waveText.setString(std::to_string(_gameState->getCurrentWave()));
  healthText.setString(std::to_string(_gameState->getHealth()));
  waveWord.setString("Wave");
  textNewGame.setString("New game");
  textCloseGame.setString("Exit");
  textContGame.setString("Continue");
  textLoading.setString("Loading...");
  textLevel1.setString("Easy");
  textLevel2.setString("Medium");
  textLevel3.setString("Hard");
  textLevel4.setString("Impossible");
  textBack.setString("Back");
  textSaving.setString("Save the game?");
  textYes.setString("Yes");
  textNo.setString("No");
  textCancel.setString("Cancel");
  textConfirmation.setString("Are you sure?");

  goldText.setFillColor(sf::Color(230, 230, 230, 255));
  waveText.setFillColor(sf::Color(230, 230, 230, 255));
  healthText.setFillColor(sf::Color(230, 230, 230, 255));
  waveWord.setFillColor(sf::Color(230, 230, 230, 255));
  textNewGame.setFillColor(sf::Color(230, 230, 230, 255));
  textCloseGame.setFillColor(sf::Color(230, 230, 230, 255));
  textContGame.setFillColor(sf::Color(230, 230, 230, 255));
  textLoading.setFillColor(sf::Color(230, 230, 230, 255));
  textLevel1.setFillColor(sf::Color(230, 230, 230, 255));
  textLevel2.setFillColor(sf::Color(230, 230, 230, 255));
  textLevel3.setFillColor(sf::Color(230, 230, 230, 255));
  textLevel4.setFillColor(sf::Color(230, 230, 230, 255));
  textBack.setFillColor(sf::Color(230, 230, 230, 255));
  textSaving.setFillColor(sf::Color(230, 230, 230, 255));
  textYes.setFillColor(sf::Color(230, 230, 230, 255));
  textNo.setFillColor(sf::Color(230, 230, 230, 255));
  textCancel.setFillColor(sf::Color(230, 230, 230, 255));
  textConfirmation.setFillColor(sf::Color(230, 230, 230, 255));

  goldText.setPosition(140, 55);
  goldText.setCharacterSize(30);
  waveText.setPosition(560, 60);
  waveText.setCharacterSize(30);
  healthText.setPosition(830, 55);
  healthText.setCharacterSize(30);
  waveWord.setPosition(400, 60);
  waveWord.setCharacterSize(30);
  textContGame.setPosition(575, 136);
  textContGame.setCharacterSize(30);
  textNewGame.setPosition(570, 336);
  textNewGame.setCharacterSize(30);
  textCloseGame.setPosition(610, 536);
  textCloseGame.setCharacterSize(30);
  textLoading.setPosition(507, 300);
  textLoading.setCharacterSize(60);
  textLevel1.setPosition(335, 136);
  textLevel1.setCharacterSize(30);
  textLevel2.setPosition(855, 136);
  textLevel2.setCharacterSize(30);
  textLevel3.setPosition(332, 336);
  textLevel3.setCharacterSize(30);
  textLevel4.setPosition(840, 336);
  textLevel4.setCharacterSize(30);
  textBack.setPosition(607, 536);
  textBack.setCharacterSize(30);
  textSaving.setPosition(524, 307);
  textSaving.setCharacterSize(35);
  textConfirmation.setPosition(536, 307);
  textConfirmation.setCharacterSize(35);
  textYes.setPosition(511, 363);
  textYes.setCharacterSize(26);
  textNo.setPosition(623, 363);
  textNo.setCharacterSize(26);
  textCancel.setPosition(708, 363);
  textCancel.setCharacterSize(26);

  groundTile = sf::RectangleShape(sf::Vector2f(Clickable::gridSize, Clickable::gridSize));
  groundTile.setFillColor(sf::Color(110, 110, 100));
  if (!_groundTexture->loadFromFile("images/ground.png")) {
    std::cerr << "Error loading the ground tile" << std::endl;
  } else {
    groundTile.setTexture(_groundTexture.get());
  }

	hoverRange = sf::CircleShape(Clickable::gridSize);
	hoverRange.setFillColor(sf::Color::Transparent);
	hoverRange.setOutlineColor(sf::Color::Red);
	hoverRange.setOutlineThickness(-2);

	shadowTile = sf::RectangleShape(sf::Vector2f(Clickable::gridSize, Clickable::gridSize));
	shadowTile.setFillColor(sf::Color(0, 255, 0, 150));

  menuBackground = sf::RectangleShape(sf::Vector2f(1280, 720));
  menuBackground.setPosition(0, 0);
  menuBackground.setTexture(_backTexture.get());
  menuBackground.setFillColor(sf::Color(255, 255, 255, 120));
  sf::IntRect _textureRect(sf::IntRect(1056, 165, 320, 128));
  sf::Vector2f _size(360, 110);
  buttonNewGame.setSize(_size);
  buttonNewGame.setPosition(460, 300);
  buttonNewGame.setTexture(_menuTexture.get());
  buttonNewGame.setTextureRect(_textureRect);
  buttonCloseGame.setSize(_size);
  buttonCloseGame.setPosition(460, 500);
  buttonCloseGame.setTexture(_menuTexture.get());
  buttonCloseGame.setTextureRect(_textureRect);
  buttonContGame.setSize(_size);
  buttonContGame.setPosition(460, 100);
  buttonContGame.setTexture(_menuTexture.get());
  buttonContGame.setTextureRect(_textureRect);
  buttonSound = std::make_shared<VolumeButton>(sf::Vector2f(1178, 30),
    1.8 * Clickable::gridSize, 1.8 * Clickable::gridSize, _menuTexture, gameState->getMusic());
  buttonSound->setTextureRect(sf::IntRect(896, 0, 128, 128));
  buttonLevel1.setSize(_size);
  buttonLevel1.setPosition(187, 100);
  buttonLevel1.setTexture(_menuTexture.get());
  buttonLevel1.setTextureRect(_textureRect);
  buttonLevel2.setSize(_size);
  buttonLevel2.setPosition(733, 100);
  buttonLevel2.setTexture(_menuTexture.get());
  buttonLevel2.setTextureRect(_textureRect);
  buttonLevel3.setSize(_size);
  buttonLevel3.setPosition(187, 300);
  buttonLevel3.setTexture(_menuTexture.get());
  buttonLevel3.setTextureRect(_textureRect);
  buttonLevel4.setSize(_size);
  buttonLevel4.setPosition(733, 300);
  buttonLevel4.setTexture(_menuTexture.get());
  buttonLevel4.setTextureRect(_textureRect);
  menuAsking.setSize(sf::Vector2f(560,240));
  menuAsking.setPosition(360, 240);
  menuAsking.setTexture(_menuTexture.get());
  menuAsking.setTextureRect(_textureRect);
  buttonYes.setSize(sf::Vector2f(100, 50));
  buttonYes.setPosition(483, 355);
  buttonYes.setFillColor(sf::Color::Transparent);
  buttonYes.setOutlineThickness(-2);
  buttonYes.setOutlineColor(sf::Color(180, 190, 180, 10));
  buttonNo.setSize(sf::Vector2f(100, 50));
  buttonNo.setPosition(590, 355);
  buttonNo.setFillColor(sf::Color::Transparent);
  buttonNo.setOutlineThickness(-2);
  buttonNo.setOutlineColor(sf::Color(180, 190, 180, 10));
  buttonCancel.setSize(sf::Vector2f(100, 50));
  buttonCancel.setPosition(697, 355);
  buttonCancel.setFillColor(sf::Color::Transparent);
  buttonCancel.setOutlineThickness(-2);
  buttonCancel.setOutlineColor(sf::Color(180, 190, 180, 10));

  std::ptrdiff_t size(path.size());
  size -= 1;
  for (std::ptrdiff_t i(0); i < size; i++) {
    sf::Vector2i curr = sf::Vector2i(path[i]);
    sf::Vector2i next = sf::Vector2i(path[i + 1]);
    if (curr.x == next.x) {
      while (curr.y != next.y) {
        if (curr.y < next.y)
          curr.y++;
        else
          curr.y--;
        gridStatus[curr.x][curr.y] = 1;
      }
    }
    else if (curr.y == next.y) {
      while (curr.x != next.x) {
        if (curr.x < next.x)
          curr.x++;
        else
          curr.x--;
        gridStatus[curr.x][curr.y] = 1;
      }
    }
  }
}

void GameBoard::updCounters() {
  goldText.setString(std::to_string(gameState->getGold()));
  waveText.setString(std::to_string(gameState->getCurrentWave()));
  healthText.setString(std::to_string(gameState->getHealth()));
}

bool GameBoard::gridSpaceAvailable(int gridX, int gridY) {
	if (gridStatus[gridX][gridY] == 0) {
		return true;
	} else
		return false;
}

bool GameBoard::towerIsPurchasable(TowerType type) {
	if (type != TowerType::empty) {
		if (gameState->getGold() >= gameState->getTowerProps(type)["gold"]) {
			return true;
		}
	}
	return false;
}

void GameBoard::process(sf::Event event, sf::Vector2i mousePos) {
	if (mousePos.x >= width) {
		return;
	}

	int gridX = ceil(mousePos.x / Clickable::gridSize);
	int gridY = ceil(mousePos.y / Clickable::gridSize);
	if ((event.type == sf::Event::MouseButtonPressed)
			&& (event.mouseButton.button == sf::Mouse::Left)) {
		gameState->setBoardTower(nullptr);
		TowerType type = gameState->getPurchaseTower();
		if (towerIsPurchasable(type) && gridSpaceAvailable(gridX, gridY)) {
			gridStatus[gridX][gridY] = 2;
			sf::Vector2f spawnPos = sf::Vector2f(gridX * Clickable::gridSize,
					gridY * Clickable::gridSize);
			towerController->spawnTower(spawnPos, type);
			gameState->updateGoldBy(-(gameState->getTowerProps(type)["gold"]));
		}
	}
}

void GameBoard::render() {
	sf::Vector2i mousePos = gameState->mousePos;
  window->draw(background);
  std::ptrdiff_t size(path.size());
  size -= 1;
	for (std::ptrdiff_t i(0); i < size; i++) {
		sf::Vector2i curr = sf::Vector2i(path[i]);
		sf::Vector2i next = sf::Vector2i(path[i + 1]);
		if (curr.x == next.x) {
			while (curr.y != next.y) {
				groundTile.setPosition(curr.x * Clickable::gridSize, curr.y * Clickable::gridSize);
				window->draw(groundTile);
				if (curr.y < next.y)
					curr.y++;
				else
					curr.y--;
			}
		} else if (curr.y == next.y) {
			while (curr.x != next.x) {
				groundTile.setPosition(curr.x * Clickable::gridSize, curr.y * Clickable::gridSize);
				window->draw(groundTile);
				if (curr.x < next.x)
					curr.x++;
				else
					curr.x--;
			}
		}
	}
	TowerType type = gameState->getPurchaseTower();
	if (type != TowerType::empty) {
		renderRange(mousePos.x, mousePos.y,
				gameState->getTowerProps(type)["range"], type);
		renderShadow(mousePos.x, mousePos.y, 1);
	}
}

void GameBoard::renderLabels() {
	window->draw(*_goldCounter);
	window->draw(*_livesCounter);
	window->draw(*_wavesCounter);
	window->draw(goldText);
	window->draw(waveText);
	window->draw(healthText);
	window->draw(waveWord);
}

void GameBoard::renderRange(int mouseX, int mouseY, int range, TowerType type) {
  int gridX = ceil(mouseX / Clickable::gridSize) * Clickable::gridSize + Clickable::gridSize / 2;
  int gridY = ceil(mouseY / Clickable::gridSize) * Clickable::gridSize + Clickable::gridSize / 2;
  switch (type) {
  case TowerType::physic:
    hoverRange.setOutlineColor(sf::Color::Red);
    break;
  case TowerType::magic:
    hoverRange.setOutlineColor(sf::Color::Magenta);
    break;
  case TowerType::ultimate:
    hoverRange.setOutlineColor(sf::Color::Green);
    break;
  }
	hoverRange.setRadius(range);
	hoverRange.setPosition(gridX - range, gridY - range);
	window->draw(hoverRange);
}

void GameBoard::renderShadow(int mouseX, int mouseY, int range) {
	int gridX = ceil(mouseX / Clickable::gridSize);
	int gridY = ceil(mouseY / Clickable::gridSize);
	shadowTile.setSize(sf::Vector2f(range* Clickable::gridSize, range* Clickable::gridSize));
	shadowTile.setPosition(gridX * Clickable::gridSize, gridY * Clickable::gridSize);
  if (gridSpaceAvailable(gridX, gridY) && towerIsPurchasable(gameState->getPurchaseTower())) {
    shadowTile.setFillColor(sf::Color(0, 255, 0, 150));
  } else {
    shadowTile.setFillColor(sf::Color(255, 0, 0, 150));
  }
	window->draw(shadowTile);
}

bool GameBoard::saveData(const std::string path) {
  bool success(false);
  std::ofstream fout;
  fout.open(path, std::ofstream::binary | std::ofstream::out | std::ofstream::trunc);
  if (fout.is_open()
    && fout.write((char*)& isRunning, sizeof(isRunning))
    && fout.write((char*)& isEndGame, sizeof(isEndGame))
    && fout.write((char*)& difficulty, sizeof(difficulty))
    && fout.write((char*)& gridStatus, sizeof(gridStatus))) {
    success = true;
  }
  fout.close();
  return success;
}

bool GameBoard::loadData(const std::string path) {
  bool success(false);
  std::ifstream fin;
  fin.open(path, std::ofstream::binary | std::ofstream::in);
  if (fin.is_open()
    && fin.read((char*)& isRunning, sizeof(isRunning))
    && fin.read((char*)& isEndGame, sizeof(isEndGame))
    && fin.read((char*)& difficulty, sizeof(difficulty))
    && fin.read((char*)& gridStatus, sizeof(gridStatus))) {
    success = true;
  }
  fin.close();
  if (!success) {
    std::cerr << "loading gameboard data failed" << std::endl;
  }
  return success;
}

void GameBoard::setDefault() {
  isRunning = false;
  isEndGame = false;
  difficulty = 0;
  for (int* grid : gridStatus) {
    *grid = 0;
  }
}

void GameBoard::saveMusicSettings() {
  std::ofstream fout;
  bool musicStatus(gameState->getMusicStatus());
  fout.open("data/musicsettings.txt", std::ofstream::binary | std::ofstream::out | std::ofstream::trunc);
  if (!fout.is_open()) {
    std::cerr << "musicsettings.txt isn't opened for writing" << std::endl;
  } else {
    if (!fout.write((char*)& musicStatus, sizeof(musicStatus))) {
      std::cerr << "failed saving music settings" << std::endl;
    }
  }
  fout.close();
}

bool GameBoard::loadMusicSettings() {
  std::ifstream fin;
  bool musicStatus(true);
  fin.open("data/musicsettings.txt", std::ifstream::binary | std::ifstream::in);
  if (!fin.is_open()) {
    std::cerr << "musicsettings.txt isn't opened for reading" << std::endl;
  } else {
    if (!fin.read((char*)& musicStatus, sizeof(musicStatus))) {
      std::cerr << "failed loading music settings" << std::endl;
    }
  }
  fin.close();
  return musicStatus;
}

void saveGame(std::shared_ptr<GameState>& gamestate,
  std::shared_ptr<TowerController>& tower, std::shared_ptr<EnemyController>& enemy,
  std::shared_ptr<GameBoard>& gameboard) {
  if (!gamestate->saveData("data/dataGS.txt")
    || !tower->saveData("data/dataTC.txt")
    || !enemy->saveData("data/dataEC.txt")
    || !gameboard->saveData("data/dataGB.txt")) {
    std::cerr << "failed saving game" << std::endl;
    std::ofstream fempty;
    fempty.open("data/dataGS.txt", std::ofstream::out);
    fempty.close();
    fempty.open("data/dataTC.txt", std::ofstream::out);
    fempty.close();
    fempty.open("data/dataEC.txt", std::ofstream::out);
    fempty.close();
    fempty.open("data/dataGB.txt", std::ofstream::out);
    fempty.close();
  }
}

void loadGame(std::shared_ptr<GameState>& gamestate,
  std::shared_ptr<TowerController>& tower, std::shared_ptr<EnemyController>& enemy,
  std::shared_ptr<GameBoard>& gameboard, std::shared_ptr<BulletController>& tae) {
  if (!gamestate->loadData("data/dataGS.txt")
    || !tower->loadData("data/dataTC.txt")
    || !enemy->loadData("data/dataEC.txt")
    || !gameboard->loadData("data/dataGB.txt")) {
    std::cerr << "failed loading game" << std::endl;
    gamestate->setDefault();
    tower->setDefault();
    enemy->setDefault();
    gameboard->setDefault();
  } else {
    tae->update();
    gameboard->updCounters();
  }
}

void GameBoard::deathloop() {
  isRunning = false;
  isEndGame = true;
  window->draw(menuBackground);
	window->draw(deathScreen);
	window->display();
	while (!isRestarted && isEndGame && !isRunning && window->isOpen()) {
		while (window->pollEvent(event)) {
			if (event.type == sf::Event::EventType::Closed) {
        saveMusicSettings();
        window->close();
      } else if ((event.type == sf::Event::MouseButtonPressed)
        || (event.type == sf::Event::KeyPressed 
          && event.key.code == sf::Keyboard::Escape)) {
        isMenu = true;
        menu();
      }
		}
	}
}

void GameBoard::showMenu(const bool cont = false) {

  window->clear();
  window->draw(menuBackground);
  window->draw(buttonNewGame);
  window->draw(textNewGame);
  window->draw(buttonCloseGame);
  window->draw(textCloseGame);
  if (cont) {
    buttonContGame.setFillColor(sf::Color(255, 255, 255, 255));
    textContGame.setFillColor(sf::Color(230, 230, 230, 255));
  } else {
    buttonContGame.setFillColor(sf::Color(200, 200, 200, 200));
    textContGame.setFillColor(sf::Color(200, 200, 200, 200));
  }
  window->draw(buttonContGame);
  window->draw(textContGame);
  buttonSound->render(*window);
  bool isPlaying = gameState->getMusic()->getStatus() == sf::SoundSource::Status::Playing ? true : false;
  buttonSound->turnColor(isPlaying);
  window->display();
}

void GameBoard::menu() {
  while (isMenu && window->isOpen())
  {
    if (isRunning && !isEndGame) {
      showMenu(true);
    }
    else {
      showMenu(false);
    }
    while (window->pollEvent(event)) {
      if (event.type == sf::Event::EventType::Closed) {
        if (isRunning && !isEndGame) {
          isMenuAsking = true;
          menuSaving();
        } else {
          saveMusicSettings();
          window->close();
        }
      } else if (event.type == sf::Event::KeyPressed
        && event.key.code == sf::Keyboard::Escape 
        && isRunning && !isEndGame) {
        isMenu = false;
      } else if (event.type == sf::Event::MouseButtonReleased
        && event.mouseButton.button == sf::Mouse::Left) {
        if (isRunning && !isEndGame && sf::IntRect(460, 100, 360, 110).contains(sf::Mouse::getPosition(*window))) {
          isMenu = false;
        } else if (sf::IntRect(460, 300, 360, 110).contains(sf::Mouse::getPosition(*window))) {
          if (isRunning) {
            isMenuAsking = true;
            menuConfirmation();
          } else {
            isMenuNewGame = true;
            menuNewGame();
          }
        } else if (sf::IntRect(460, 500, 360, 110).contains(sf::Mouse::getPosition(*window))) {
          if (isRunning && !isEndGame) {
            isMenuAsking = true;
            menuSaving();
          } else {
            saveMusicSettings();
            window->close();
          }
        } else if (sf::IntRect(1178, 30, 72, 72).contains(sf::Mouse::getPosition(*window))) {
          bool onoff(!gameState->getMusicStatus());
          buttonSound->turnColor(onoff);
          if (onoff) {
            gameState->getMusic()->play();
          } else {
            gameState->getMusic()->pause();
          }
        }
      }
    }
  }
}

void GameBoard::showMenuNewGame() {
  window->clear();
  window->draw(menuBackground);
  window->draw(buttonCloseGame);
  window->draw(textBack);
  window->draw(buttonLevel1);
  window->draw(textLevel1);
  window->draw(buttonLevel2);
  window->draw(textLevel2);
  window->draw(buttonLevel3);
  window->draw(textLevel3);
  window->draw(buttonLevel4);
  window->draw(textLevel4);
  buttonSound->render(*window);
  bool isPlaying = gameState->getMusic()->getStatus() == sf::SoundSource::Status::Playing ? true : false;
  buttonSound->turnColor(isPlaying);
  window->display();
}

void GameBoard::menuNewGame() {
  while (isMenuNewGame && window->isOpen())
  {
    showMenuNewGame();
    while (window->pollEvent(event)) {
      if (event.type == sf::Event::EventType::Closed) {
        if (isRunning && !isEndGame) {
          isMenuAsking = true;
          menuSaving();
        }
        else {
          isMenuNewGame = false;
          saveMusicSettings();
          window->close();
        }
      } else if (event.type == sf::Event::KeyPressed
        && event.key.code == sf::Keyboard::Escape) {
        isMenuNewGame = false;
      } else if (event.type == sf::Event::MouseButtonReleased
        && event.mouseButton.button == sf::Mouse::Left) {
        if (sf::IntRect(460, 500, 360, 110).contains(sf::Mouse::getPosition(*window))) {
          isMenuNewGame = false;
        } else if (sf::IntRect(187, 100, 360, 110).contains(sf::Mouse::getPosition(*window))) {
          difficulty = 1;
          isMenuNewGame = false;
          isMenu = false;
          isRestarted = true;
        } else if (sf::IntRect(733, 100, 360, 110).contains(sf::Mouse::getPosition(*window))) {
          difficulty = 2;
          isMenuNewGame = false;
          isMenu = false;
          isRestarted = true;
        } else if (sf::IntRect(187, 300, 360, 110).contains(sf::Mouse::getPosition(*window))) {
          difficulty = 3;
          isMenuNewGame = false;
          isMenu = false;
          isRestarted = true;
        } else if (sf::IntRect(733, 300, 360, 110).contains(sf::Mouse::getPosition(*window))) {
          difficulty = 4;
          isMenuNewGame = false;
          isMenu = false;
          isRestarted = true;
        } else if (sf::IntRect(1178, 30, 72, 72).contains(sf::Mouse::getPosition(*window))) {
          bool onoff(!gameState->getMusicStatus());
          buttonSound->turnColor(onoff);
          if (onoff) {
            gameState->getMusic()->play();
          }
          else {
            gameState->getMusic()->pause();
          }
        }
      }
    }
  }
}

void GameBoard::showMenuAsking(const bool SaveConf) {
  menuBackground.setFillColor(sf::Color(100, 100, 100, 100));
  window->draw(menuBackground);
  window->draw(menuAsking);
  if (SaveConf) {
    window->draw(textSaving);
  } else {
    window->draw(textConfirmation);
  }
  window->draw(buttonYes);
  window->draw(textYes);
  if (SaveConf) {
    window->draw(buttonNo);
    window->draw(textNo);
  }
  window->draw(buttonCancel);
  window->draw(textCancel);
  window->display();
  menuBackground.setFillColor(sf::Color(255, 255, 255, 120));
}

void GameBoard::menuSaving() {
  while (isMenuAsking && window->isOpen())
  {
    showMenuAsking(true);
    while (window->pollEvent(event)) {
      if (event.type == sf::Event::EventType::Closed) {
        isMenuAsking = false;
        saveMusicSettings();
        window->close();
      }
      else if (event.type == sf::Event::KeyPressed
        && event.key.code == sf::Keyboard::Escape) {
        isMenuAsking = false;
      }
      else if (event.type == sf::Event::MouseButtonReleased
        && event.mouseButton.button == sf::Mouse::Left) {
        if (!sf::IntRect(360, 240, 560, 240).contains(sf::Mouse::getPosition(*window))) {
          isMenuAsking = false;
        } else if (sf::IntRect(483, 355, 100, 50).contains(sf::Mouse::getPosition(*window))) {
          isMenuAsking = false;
          saveMusicSettings();
          isSaveAndQuit = true;
          isMenuNewGame = false;
          isMenu = false;
        } else if (sf::IntRect(590, 355, 100, 50).contains(sf::Mouse::getPosition(*window))) {
          isMenuAsking = false;
          saveMusicSettings();
          window->close();
        } else if (sf::IntRect(697, 355, 100, 50).contains(sf::Mouse::getPosition(*window))) {
          isMenuAsking = false;
        }
      }
    }
  }
}

void GameBoard::menuConfirmation() {
  while (isMenuAsking && window->isOpen())
  {
    showMenuAsking(false);
    while (window->pollEvent(event)) {
      if (event.type == sf::Event::EventType::Closed) {
        if (isRunning && !isEndGame) {
          isMenuAsking = true;
          menuSaving();
        }
        else {
          isMenuNewGame = false;
          saveMusicSettings();
          window->close();
        }
      }
      else if (event.type == sf::Event::KeyPressed
        && event.key.code == sf::Keyboard::Escape) {
        isMenuAsking = false;
      }
      else if (event.type == sf::Event::MouseButtonReleased
        && event.mouseButton.button == sf::Mouse::Left) {
        if (!sf::IntRect(360, 240, 560, 240).contains(sf::Mouse::getPosition(*window))) {
          isMenuAsking = false;
        } else if (sf::IntRect(483, 355, 100, 50).contains(sf::Mouse::getPosition(*window))) {
          isMenuAsking = false;
          isMenuNewGame = true;
          menuNewGame();
        } else if (sf::IntRect(697, 355, 100, 50).contains(sf::Mouse::getPosition(*window))) {
          isMenuAsking = false;
        }
      }
    }
  }
}

void startNewGame(std::shared_ptr<sf::RenderWindow> &window, std::shared_ptr<Timer> &timer,
  std::shared_ptr<GameState> &gamestate, std::shared_ptr<GameMenuController> &gamemenu,
  std::shared_ptr<TowerController> &tower, std::shared_ptr<EnemyController> &enemy,
  std::shared_ptr<GameBoard> &gameboard, std::shared_ptr<BulletController> &tae) {
  gameboard->showLoading();
  timer = std::make_shared<Timer>();
  gamestate->timer = timer;
  gamestate->startGame(gameboard->difficulty);
  gamemenu = std::make_shared<GameMenuController>(window, gamestate);
  tower = std::make_shared<TowerController>(window, gamestate);
  enemy = std::make_shared<EnemyController>(window, gamestate, gameboard->path);
  gameboard = std::make_shared<GameBoard>(gamestate, tower, gamemenu->getMenuPos().x, window);
  tae = std::make_shared<BulletController>(window, gamestate, enemy, tower->getTowerVec(), enemy->getEnemyVec());
  gameboard->isEndGame = false;
  gameboard->isRunning = true;
  gameboard->isRestarted = false;
  gameboard->isMenu = false;
}

void GameBoard::showLoading() {
  menuBackground.setFillColor(sf::Color(100, 100, 100, 230));
  window->draw(menuBackground);
  window->draw(textLoading);
  window->display();
  menuBackground.setFillColor(sf::Color(255, 255, 255, 120));
}

int main() {
  std::shared_ptr<sf::RenderWindow> window;
	window = std::make_shared<sf::RenderWindow>(sf::VideoMode(1280, 720), 
    "Tower Defence", sf::Style::Close);
	window->setFramerateLimit(60);
	std::shared_ptr<Timer> clk(std::make_shared<Timer>());
	std::shared_ptr<GameState> gameState(std::make_shared<GameState>(clk));
	std::shared_ptr<GameMenuController> gameMenuController(
    std::make_shared<GameMenuController>(window, gameState));
	std::shared_ptr<TowerController> towerController(std::make_shared<TowerController>(window, gameState));
	std::shared_ptr<GameBoard> gameBoard(std::make_shared<GameBoard>(gameState, towerController,
			gameMenuController->getMenuPos().x, window));
  std::shared_ptr<EnemyController> enemyController(std::make_shared<EnemyController>(window, gameState,
    gameBoard->path));
	std::shared_ptr<BulletController> attackController(std::make_shared<BulletController>(
			window, gameState, enemyController, towerController->getTowerVec(),
			enemyController->getEnemyVec()));
  loadGame(gameState, towerController, 
    enemyController, gameBoard, attackController);
  if (gameBoard->loadMusicSettings()) {
    gameState->getMusic()->play();
  }

	while (window->isOpen()) {
    if (gameBoard->isMenu) {
      gameBoard->menu();
    }
    if (gameBoard->isRestarted) {
      startNewGame(window, clk, gameState, gameMenuController, towerController, 
        enemyController, gameBoard, attackController);
    }
		sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
		gameState->mousePos = mousePos;

    while (gameState->getHelperState() && window->isOpen()) {
      window->clear();
      gameBoard->renderLabels();
      window->draw(gameBoard->helpScreen);
      window->display();
      while (window->pollEvent(event)) {
        if (event.type == sf::Event::EventType::Closed) {
          if (gameBoard->isRunning && !gameBoard->isEndGame) {
            gameBoard->isMenuAsking = true;
            gameBoard->menuSaving();
            if (gameBoard->isSaveAndQuit) {
              gameState->toggleHelpScreen();
            }
          } else {
            gameBoard->saveMusicSettings();
            window->close();
          }
        } else if ((event.type == sf::Event::MouseButtonReleased)
          && (event.mouseButton.button == sf::Mouse::Left)
          || (event.type == sf::Event::KeyPressed
            && event.key.code == sf::Keyboard::Escape)) {
          gameState->toggleHelpScreen();
        }
      }
    }
		while (window->pollEvent(event)) {
			if (event.type == sf::Event::EventType::Closed) {
        if (gameBoard->isRunning && !gameBoard->isEndGame) {
          gameBoard->isMenuAsking = true;
          gameBoard->menuSaving();
        } else {
          gameBoard->saveMusicSettings();
          window->close();
        }
      }
      else if (event.type == sf::Event::KeyPressed
        && event.key.code == sf::Keyboard::Escape) {
        if (gameState->getBoardTower() != nullptr) {
          gameState->setBoardTower(nullptr);
        } else if (gameState->getPurchaseTower() != TowerType::empty) {
          gameState->setPurchaseTower(TowerType::empty);
        } else {
          gameBoard->isMenu = true;
        }
      } else if (!gameBoard->isEndGame && gameBoard->isRunning) {
				gameMenuController->process(event, mousePos);
				gameBoard->process(event, mousePos);
				towerController->process(event, mousePos);
			}
		}

    if (gameBoard->isSaveAndQuit) {
      gameBoard->isSaveAndQuit = false;
      saveGame(gameState, towerController,
        enemyController, gameBoard);
      window->close();
    } else {
      if (!gameBoard->isEndGame && gameBoard->isRunning) {
        gameMenuController->update();
        if (clk->newTick()) {
          enemyController->update();
          attackController->update();
        }

        if (gameState->dirtyBit) {
          gameBoard->updCounters();
          gameState->dirtyBit = false;
        }
        window->clear();
        gameBoard->render();
        enemyController->render();
        towerController->render();
        gameMenuController->render();
        attackController->render();
        gameBoard->renderLabels();
        if (gameState->getHealth() < 1) {
          clk->stop();
          gameBoard->deathloop();
        }
      }
      window->display();
    }
	}
	return 0;
}
