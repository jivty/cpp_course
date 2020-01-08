#include "GameMenuController.h"
#include "Clickable.h"
#include "TowerButton.h"
#include "MenuButton.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

sf::Vector2f GameMenuController::menuPosition(float xCubits, float yCubits) {
	return sf::Vector2f(menuPos.x + (xCubits * Clickable::gridSize),
			menuPos.y + (yCubits * Clickable::gridSize));
}

sf::Vector2f GameMenuController::getMenuPos() {
	return this->menuPos;
}

GameMenuController::GameMenuController(std::shared_ptr<sf::RenderWindow> windowPointer,
		std::shared_ptr<GameState> gameState) 
  :	windowPointer(windowPointer)
  , gameState(gameState) {
	float menuRatio = 0.2, towerButtonCubits = 1.9 * Clickable::gridSize, 
    menuButtonCubits = 1.8 * Clickable::gridSize;

	gameSize = sf::Vector2f(windowPointer->getSize());
	menuPos = sf::Vector2f(gameSize.x - (gameSize.x * menuRatio), 0);\
	std::shared_ptr<sf::RectangleShape> _drawable(std::make_shared<sf::RectangleShape>(
			sf::Vector2f(gameSize.x - menuPos.x, gameSize.y)));
	_drawable->setFillColor(sf::Color(150, 150, 151)); 
	_drawable->setPosition(menuPos.x, 0);
	_drawable->setOutlineThickness(-14);
	_drawable->setOutlineColor(sf::Color(160, 97, 0));
	drawVec.push_back(_drawable);

  std::shared_ptr<sf::Texture> _textureTP(std::make_shared<sf::Texture>());
	if (!_textureTP->loadFromFile("images/towers/towerP.png")) {
		std::cerr << "The texture does not exist" << std::endl;
	}
	texturesVector.push_back(_textureTP);
  std::shared_ptr<sf::Texture> _textureTM(std::make_shared<sf::Texture>());
  if (!_textureTM->loadFromFile("images/towers/towerM.png")) {
    std::cerr << "The texture does not exist" << std::endl;
  }
  texturesVector.push_back(_textureTM);
  std::shared_ptr<sf::Texture> _textureTU(std::make_shared<sf::Texture>());
  if (!_textureTU->loadFromFile("images/towers/towerU.png")) {
    std::cerr << "The texture does not exist" << std::endl;
  }
  texturesVector.push_back(_textureTU);
	std::cerr << menuPos.x << ", " << menuPos.y << std::endl;
	std::map<string, int> props1 = gameState->getTowerProps(TowerType::physic);
	std::map<string, int> props2 = gameState->getTowerProps(TowerType::magic);
	std::map<string, int> props3 = gameState->getTowerProps(TowerType::ultimate);

  std::shared_ptr<sf::Texture> _menuTexture(std::make_shared<sf::Texture>());
  if (!_menuTexture->loadFromFile("images/menuButtons.png")) {
    std::cerr << "The menu texture does not exist" << std::endl;
  }
  texturesVector.push_back(_menuTexture);

	std::shared_ptr<TowerButton> _clickable;
	_clickable = std::make_shared<TowerButton>(menuPosition(1.4, 2.2), towerButtonCubits,
			_textureTP, to_string(props1["gold"]),
			"Damage: " + to_string(props1["damage"]) + "\nRate: "
					+ to_string(props1["cooldown"]), TowerType::physic,
			gameState, _menuTexture);
	_clickable->setTextureRect(sf::IntRect(5, -2, 75, 86));
	towerButtonVec.push_back(_clickable);

	_clickable = std::make_shared<TowerButton>(menuPosition(1.4, 6.2), towerButtonCubits,
			_textureTM, to_string(props2["gold"]),
			"Damage: " + to_string(props2["damage"]) + "\nRate: "
					+ to_string(props2["cooldown"]), TowerType::magic,
			gameState, _menuTexture);
	_clickable->setTextureRect(sf::IntRect(5, -2, 75, 86));
	towerButtonVec.push_back(_clickable);

	_clickable = std::make_shared<TowerButton>(menuPosition(1.4, 10.2), towerButtonCubits,
			_textureTU, to_string(props3["gold"]),
			"Damage: " + to_string(props3["damage"]) + "\nRate: "
					+ to_string(props3["cooldown"]), TowerType::ultimate,
			gameState, _menuTexture);
	_clickable->setTextureRect(sf::IntRect(5, -2, 75, 86));
	towerButtonVec.push_back(_clickable);

  music = gameState->getMusic();
	std::shared_ptr<MenuButton> _sound(std::make_shared<VolumeButton>(menuPosition(0.3, 0.3),
			menuButtonCubits, menuButtonCubits, _menuTexture, music));
	_sound->setTextureRect(sf::IntRect(896, 0, 128, 128));
	clickVec.push_back(_sound);
  std::shared_ptr<MenuButton> _help(std::make_shared<InfoButton>(menuPosition(4.3, 0.3),
			menuButtonCubits, menuButtonCubits, _menuTexture, gameState));
	_help->setTextureRect(sf::IntRect(896, 128, 128, 128));
	clickVec.push_back(_help);
  std::shared_ptr<MenuButton> _pause(std::make_shared<PauseButton>(menuPosition(2.3, 0.3),
			menuButtonCubits, menuButtonCubits, _menuTexture, gameState->timer));
	_pause->setTextureRect(sf::IntRect(896, 384, 128, 128));
	clickVec.push_back(_pause);
	std::shared_ptr<UpgradeButton> _upgrade(std::make_shared<UpgradeButton>(menuPosition(0.2, 14.35),
    240, 128, _menuTexture, gameState));
	_upgrade->setTextureRect(sf::IntRect(1060, 384, 300, 128));
	this->upgradeButton = _upgrade;
	clickVec.push_back(_upgrade);
}

GameMenuController::~GameMenuController() {
}

void GameMenuController::setDebug(bool mode) {
	if (mode) {
		for (auto c : towerButtonVec) {
			c->setDebug(true);
		}
		for (auto c : clickVec) {
			c->setDebug(true);
		}
	}
}

void GameMenuController::process(sf::Event event, sf::Vector2i mousePos) {
	if ((mousePos.x >= menuPos.x)
			&& gameState->getPurchaseTower() != TowerType::empty
			&& (event.type == sf::Event::MouseButtonPressed)
			&& (event.mouseButton.button == sf::Mouse::Left)) {
		gameState->setPurchaseTower(TowerType::empty);
	}
	for (auto c : towerButtonVec) {
		c->process(event, mousePos);
	}
	for (auto c : clickVec) {
		c->process(event, mousePos);
	}
}

void GameMenuController::update() {
	if (gameState->getBoardTower() != nullptr
			&& (gameState->getGold()
					>= gameState->getBoardTower()->getUpgradeCost())) {
		upgradeButton->setTransparency(255);
		upgradeButton->setCanUpgrade(true);
	} else {
		upgradeButton->setTransparency(180);
		upgradeButton->setCanUpgrade(false);
	}
	for (auto f : towerButtonVec) {
		if (f->getTowerType() == gameState->getPurchaseTower()) {
			f->setTransparency(255);
		} else {
			f->setTransparency(180);
		}
	}
}

void GameMenuController::render() {
	for (auto d : drawVec) {
		windowPointer->draw(*d);
	}
	for (auto c : towerButtonVec) {
		c->render(*windowPointer);
	}
	for (auto c : clickVec) {
		c->render(*windowPointer);
	}
	for (auto c : towerButtonVec) {
		c->renderText(*windowPointer);
	}
}
