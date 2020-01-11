#include "Tower.h"
#include "TowerController.h"

TowerController::TowerController(std::shared_ptr<sf::RenderWindow> _window, 
  std::shared_ptr<GameState> _gameState)
  : window(_window)
  , gameState(_gameState) {
  towerVec = std::make_shared<std::vector<std::shared_ptr<Tower>>>();
  if (!ultimateTexture.loadFromFile("images/towers/towerU.png")) {
    std::cerr << "The tower texture (ultimate) could not be loaded" << std::endl;
  }
  if (!magicTexture.loadFromFile("images/towers/towerM.png")) {
    std::cerr << "The tower texture (magic) could not be loaded" << std::endl;
  }
  if (!physicTexture.loadFromFile("images/towers/towerP.png")) {
    std::cerr << "The tower texture (physic) could not be loaded" << std::endl;
  }
}

std::shared_ptr<Tower> TowerController::spawnTower(sf::Vector2f position, TowerType type,
  float damage, float range, float baseCooldown, int upgradeCost) {
  if (type == TowerType::empty) {
    return nullptr;
  } else {
    std::shared_ptr<sf::Texture> texture(std::make_shared<sf::Texture>());
    switch (type) {
    case (TowerType::ultimate):
      texture = std::make_shared<sf::Texture>(ultimateTexture);
      break;
    case(TowerType::magic):
      texture = std::make_shared<sf::Texture>(magicTexture);
      break;
    case(TowerType::physic):
      texture = std::make_shared<sf::Texture>(physicTexture);
      break;
    default:
      texture = std::make_shared<sf::Texture>(ultimateTexture);
      break;
    }
  std::map<std::string, int> props = gameState->getTowerProps(type);
  float _damage(damage < 0 ? props["damage"] : damage);
  float _range(range < 0 ? props["range"] : range);
  float _cooldown(baseCooldown < 0 ? props["cooldown"] : baseCooldown);
  std::shared_ptr<Tower> tower = std::make_shared<Tower>(position, texture, type, _damage, _range,
    _cooldown, upgradeCost);
  towerVec->push_back(tower);
  return tower;
  }
}

void TowerController::process(const sf::Event& event,
		const sf::Vector2i& mousePos) {
	for (auto tower : *towerVec.get()) {
		tower->process(event, mousePos);
		if (tower->wasClicked) {
			gameState->setBoardTower(tower);
			gameState->setPurchaseTower(TowerType::empty);
			tower->wasClicked = false;
		}
	}
}

void TowerController::render() {
	sf::CircleShape range;
	sf::Vector2f pos;
	range.setFillColor(sf::Color::Transparent);
	range.setOutlineColor(sf::Color::Red);
	range.setOutlineThickness(-2);
	for (auto tower : *towerVec) {
		window->draw(tower->getTowerSprite());
		if (gameState->getBoardTower() == tower) {
      pos = tower->getPosition();
			range.setRadius(tower->getRange());
      switch (tower.get()->getTowerType()) {
      case TowerType::physic:
        range.setOutlineColor(sf::Color::Red);
        break;
      case TowerType::magic:
        range.setOutlineColor(sf::Color::Magenta);
        break;
      case TowerType::ultimate:
        range.setOutlineColor(sf::Color::Green);
        break;
      }
			pos.x = pos.x - tower->getRange() + Clickable::gridSize / 2;
			pos.y = pos.y - tower->getRange() + Clickable::gridSize / 2;
			range.setPosition(pos);
			window->draw(range);
		}
	}
}

std::shared_ptr<std::vector<std::shared_ptr<Tower>>> TowerController::getTowerVec() {
	return this->towerVec;
}

bool TowerController::saveData(const std::string path) {
  bool success(true);
  std::ptrdiff_t vecsize(towerVec->size());
  std::ofstream fout;
  fout.open(path, std::ofstream::binary | std::ofstream::out | std::ofstream::trunc);
  fout.write((char*)& vecsize, sizeof(vecsize));
  fout.close();
  for (auto it : *towerVec) {
    if (!it->saveData(path)) {
      success = false;
    }
  }
  return success;
}

bool TowerController::loadData(const std::string path) {
  bool success(true);
  std::ifstream fin;
  fin.open(path, std::ofstream::binary | std::ofstream::in);
  if (fin.is_open()) {
    sf::Vector2f pos(0, 0);
    TowerType type(TowerType::empty);
    float towerDamage(0.0f);
    float towerRange(0.0f);
    float baseCooldown(0.0f);
    int upgradeCost(0);
    std::ptrdiff_t amount(0);
    if (!fin.read((char*)& amount, sizeof(amount))) {
      success = false;
    } else {
      std::ptrdiff_t loadedAmount(0);
      while (fin.read((char*)& pos, sizeof(pos))
        && fin.read((char*)& type, sizeof(type))
        && fin.read((char*)& towerDamage, sizeof(towerDamage))
        && fin.read((char*)& towerRange, sizeof(towerRange))
        && fin.read((char*)& baseCooldown, sizeof(baseCooldown))
        && fin.read((char*)& upgradeCost, sizeof(upgradeCost))) {
        ++loadedAmount;
        spawnTower(pos, type, towerDamage,
          towerRange, baseCooldown, upgradeCost);
      }
      if (amount != loadedAmount) {
        success = false;
      }
    }
  }
  fin.close();
  if (!success) {
    std::cerr << "loading towerController data failed" << std::endl;
  }
  return success;
}

void TowerController::setDefault() {
  towerVec->clear();
}
