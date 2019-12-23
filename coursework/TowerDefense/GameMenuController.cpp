#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "GameMenuController.h"
#include "Clickable.h"
#include "TowerButton.h"
#include "MenuButton.h"

// The position is relative to the top left of the menu region,
// so zero is used as the start menu height
sf::Vector2f GameMenuController::menuPosition(float xCubits, float yCubits) {
	return sf::Vector2f(menuPos.x + (xCubits * Clickable::gridSize),
			menuPos.y + (yCubits * Clickable::gridSize));
}

sf::Vector2f GameMenuController::getMenuPos() {
	return this->menuPos;
}

GameMenuController::GameMenuController(sf::RenderWindow* windowPointer,
		GameState* gameState) :
		windowPointer(windowPointer), gameState(gameState) {
	float menuRatio = 0.2, towerButtonCubits = 1.9 * Clickable::gridSize, 
    menuButtonCubits = 1.8 * Clickable::gridSize;

	gameSize = sf::Vector2f(windowPointer->getSize());
	menuPos = sf::Vector2f(gameSize.x - (gameSize.x * menuRatio), 0);
	// -----------------------
	// Menu Borders
	// -----------------------
	sf::RectangleShape* _drawable = new sf::RectangleShape(
			sf::Vector2f(gameSize.x - menuPos.x, gameSize.y));
	_drawable->setFillColor(sf::Color(150, 150, 151)); 
	_drawable->setPosition(menuPos.x, 0);
	_drawable->setOutlineThickness(-14);
	_drawable->setOutlineColor(sf::Color(160, 97, 0));
	drawVec.push_back(_drawable);

	// -----------------------
	// Tower Buttons
	// -----------------------
	sf::Texture* _textureTP = new sf::Texture;
	if (!_textureTP->loadFromFile("images/towers/towerP.png")) {
		std::cerr << "The texture does not exist" << std::endl;
	}
	texturesVector.push_back(_textureTP);
  sf::Texture* _textureTM = new sf::Texture;
  if (!_textureTM->loadFromFile("images/towers/towerM.png")) {
    std::cerr << "The texture does not exist" << std::endl;
  }
  texturesVector.push_back(_textureTM);
  sf::Texture* _textureTU = new sf::Texture;
  if (!_textureTU->loadFromFile("images/towers/towerU.png")) {
    std::cerr << "The texture does not exist" << std::endl;
  }
  texturesVector.push_back(_textureTU);
	std::cerr << menuPos.x << ", " << menuPos.y << std::endl;
	std::map<string, int> props1 = gameState->getTowerProps(TowerType::physic);
	std::map<string, int> props2 = gameState->getTowerProps(TowerType::magic);
	std::map<string, int> props3 = gameState->getTowerProps(TowerType::ultimate);
	TowerButton* _clickable;
	_clickable = new TowerButton(menuPosition(1.4, 2.2), towerButtonCubits,
			_textureTP, to_string(props1["tam"]),
			"Damage: " + to_string(props1["damage"]) + "\nRate: "
					+ to_string(props1["cooldown"]), TowerType::physic,
			gameState);
	_clickable->setTextureRect(sf::IntRect(5, -2, 75, 86));
	towerButtonVec.push_back(_clickable);

	_clickable = new TowerButton(menuPosition(1.4, 6.2), towerButtonCubits,
			_textureTM, to_string(props2["tam"]),
			"Damage: " + to_string(props2["damage"]) + "\nRate: "
					+ to_string(props2["cooldown"]), TowerType::magic,
			gameState);
	_clickable->setTextureRect(sf::IntRect(5, -2, 75, 86));
	towerButtonVec.push_back(_clickable);

	_clickable = new TowerButton(menuPosition(1.4, 10.2), towerButtonCubits,
			_textureTU, to_string(props3["tam"]),
			"Damage: " + to_string(props3["damage"]) + "\nRate: "
					+ to_string(props3["cooldown"]), TowerType::ultimate,
			gameState);
	_clickable->setTextureRect(sf::IntRect(5, -2, 75, 86));
	towerButtonVec.push_back(_clickable);

	// -------------------------
	// Menu Buttons
	// -------------------------
	sf::Texture* _menuTexture = new sf::Texture;
	if (!_menuTexture->loadFromFile("images/menuButtons.png")) {
		std::cerr << "The menu texture does not exist" << std::endl;
	}
	texturesVector.push_back(_menuTexture);
	music = new sf::Music;
	if (!music->openFromFile("assets/give_it_up_.ogg"))
		std::cerr << "The music file was not found" << std::endl;
	music->setLoop(true);
	MenuButton* _sound = new VolumeButton(menuPosition(0.3, 0.3),
			menuButtonCubits, menuButtonCubits, _menuTexture, music);
	_sound->setTextureRect(sf::IntRect(896, 0, 128, 128));
	clickVec.push_back(_sound);
	MenuButton* _help = new InfoButton(menuPosition(4.3, 0.3),
			menuButtonCubits, menuButtonCubits, _menuTexture, gameState);
	_help->setTextureRect(sf::IntRect(896, 128, 128, 128));
	clickVec.push_back(_help);
	MenuButton* _pause = new PauseButton(menuPosition(2.3, 0.3),
			menuButtonCubits, menuButtonCubits, _menuTexture, gameState->timer);
	_pause->setTextureRect(sf::IntRect(896, 384, 128, 128));
	clickVec.push_back(_pause);
	UpgradeButton* _upgrade = new UpgradeButton(menuPosition(0.2, 14.35), 240,
			128, _menuTexture, gameState);
	_upgrade->setTextureRect(sf::IntRect(1060, 384, 300, 128));
	this->upgradeButton = _upgrade;
	clickVec.push_back(_upgrade);
}

GameMenuController::~GameMenuController() {
	for (sf::Drawable* d : drawVec) {
    //d;
		d = nullptr;
	}
	for (Clickable* c : towerButtonVec) {
		sf::Vector2f temp = c->getPosition();
		temp.x = (temp.x - menuPos.x) / Clickable::gridSize;
		temp.y = (temp.y - menuPos.y) / Clickable::gridSize;
		delete c;
		c = nullptr;
	}
	for (Clickable* c : clickVec) {
		sf::Vector2f temp = c->getPosition();
		temp.x = (temp.x - menuPos.x) / Clickable::gridSize;
		temp.y = (temp.y - menuPos.y) / Clickable::gridSize;
		delete c;
		c = nullptr;
	}
	for (sf::Texture* t : texturesVector) {
		delete t;
		t = nullptr;
	}

	// Delete menu assets
	music->stop();
}

void GameMenuController::setDebug(bool mode) {
	if (mode) {
		for (Clickable* c : towerButtonVec) {
			c->setDebug(true);
		}
		for (Clickable* c : clickVec) {
			c->setDebug(true);
		}
	}
}

// Handle windowPointer events
void GameMenuController::process(sf::Event event, sf::Vector2i mousePos) {
	// Clear the selectedTower if the menu is selected
	if ((mousePos.x >= menuPos.x)
			&& gameState->getPurchaseTower() != TowerType::empty
			&& (event.type == sf::Event::MouseButtonPressed)
			&& (event.mouseButton.button == sf::Mouse::Left)) {
		gameState->setPurchaseTower(TowerType::empty);
	}
	for (Clickable* c : towerButtonVec) {
		c->process(event, mousePos);
	}
	for (Clickable* c : clickVec) {
		c->process(event, mousePos);
	}
}

void GameMenuController::update() {
	// TODO: Check the upgrade cost of the tower to toggle opacity
	// TODO: If the selectedTower.isUpgradeable then allow the button to be clicked

	if (gameState->getBoardTower() != nullptr
			&& (gameState->getTams()
					>= gameState->getBoardTower()->getUpgradeCost())) {
		upgradeButton->setTransparency(255);
		upgradeButton->setCanUpgrade(true);
	} else {
		upgradeButton->setTransparency(180);
		upgradeButton->setCanUpgrade(false);
	}
	for (TowerButton* f : towerButtonVec) {
		if (f->getTowerType() == gameState->getPurchaseTower()) {
			f->setTransparency(255);
		} else {
			f->setTransparency(180);
		}
	}
}
void GameMenuController::render() {
	for (sf::Drawable* d : drawVec) {
		windowPointer->draw(*d);
	}
	for (Clickable* c : towerButtonVec) {
		c->render(*windowPointer);
	}
	for (Clickable* c : clickVec) {
		c->render(*windowPointer);
	}
	for (TowerButton* c : towerButtonVec) {
		c->renderText(*windowPointer);
	}
}

