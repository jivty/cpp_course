#include "Tower.h"
#include "TowerController.h"


TowerController::TowerController(sf::RenderWindow* _window, GameState* _gameState) :
		window(_window), gameState(_gameState) {
	ultimateTexture = new sf::Texture;
	magicTexture = new sf::Texture;
	physicTexture = new sf::Texture;
	ultimateTexture->loadFromFile("images/towers/towerU.png");
	magicTexture->loadFromFile("images/towers/towerM.png");
	physicTexture->loadFromFile("images/towers/towerP.png");
	towerVec = new std::vector<Tower*>;
}

TowerController::~TowerController() {
	for (Tower* tower : *towerVec) {
		delete tower;
		tower = nullptr;
	}
	delete ultimateTexture;
	delete magicTexture;
	delete physicTexture;
}

Tower* TowerController::spawnTower(sf::Vector2f position, TowerType type) {
	Tower* tower;
	sf::Texture* texture = ultimateTexture; //visual studio wants texture to be initilized to something
	if (type == TowerType::empty) {
		return nullptr;
	} else if (type == TowerType::ultimate) {
		texture = ultimateTexture;
	} else if (type == TowerType::magic) {
		texture = magicTexture;
	} else if (type == TowerType::physic) {
		texture = physicTexture;
	}
	std::map<string, int> props = gameState->getTowerProps(type);
	tower = new Tower(position, texture, type, props["damage"], props["range"],
			props["cooldown"]);
	towerVec->push_back(tower);
	return tower;
}

void TowerController::process(const sf::Event& event,
		const sf::Vector2i& mousePos) {
	for (Tower* tower : *towerVec) {
		tower->process(event, mousePos);
		if (tower->wasClicked) {
			gameState->setBoardTower(tower);
			gameState->setPurchaseTower(TowerType::empty);
			tower->wasClicked = false;
		}
	}
}

void TowerController::update() {
}

void TowerController::render() {
	sf::CircleShape range;
	sf::Vector2f pos;
	range.setFillColor(sf::Color::Transparent);
	range.setOutlineColor(sf::Color::Red);
	range.setOutlineThickness(-2);
	for (Tower* tower : *towerVec) {
		window->draw(tower->getTowerSprite());

		if (gameState->getBoardTower() == tower) {
			pos = tower->getOriginalTowerPosition();
			range.setRadius(tower->getRange());
			pos.x = pos.x - tower->getRange() + Clickable::gridSize / 2;
			pos.y = pos.y - tower->getRange() + Clickable::gridSize / 2;
			range.setPosition(pos);
			window->draw(range);
		}
	}
}

std::vector<Tower*>* TowerController::getTowerVec() {
	return this->towerVec;
}

