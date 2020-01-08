#include "EnemyController.h"
#include "Enemy.h"

EnemyController::EnemyController(std::shared_ptr<sf::RenderWindow> _window,
		std::shared_ptr<GameState> _gameState, const std::vector<sf::Vector2f> _path)
  :	window(_window)
  , gameState(_gameState)
  , pathInCubits(_path) {
  enemyVec = std::make_shared<std::vector<shared_ptr<Enemy>>>();
  switch (gameState->getDifficulty()) {
  case 1:
    modifier = 1.1f;
    break;
  case 2:
    modifier = 1.5f;
    break;
  case 3:
    modifier = 1.5f;
    break;
  case 4:
    modifier = 2.0f;
    break;
  dafault:
    modifier = 1.0f;
    break;
  }
	if (!enemySpriteS.loadFromFile("images/enemies/skeleton.png")) {
		std::cerr << "The enemy texture (skeleton) could not be loaded" << std::endl;
  } 
  if (!enemySpriteD.loadFromFile("images/enemies/demon.png")) {
    std::cerr << "The enemy texture (demon) could not be loaded" << std::endl;
  }
  if (!enemySpriteL.loadFromFile("images/enemies/lancer.png")) {
    std::cerr << "The enemy texture (lancer) could not be loaded" << std::endl;
  }
  if (!enemySpriteR.loadFromFile("images/enemies/rhino.png")) {
    std::cerr << "The enemy texture (rhino) could not be loaded" << std::endl;
  } 
  counter = 0;
  wave = 1;
}

std::shared_ptr<Enemy> EnemyController::spawnEnemy(sf::Vector2f position,
		EnemyType type, int health = -1, int targetPath = 0) {
  if (type == EnemyType::empty) {
    return nullptr;
  }
	std::shared_ptr<Enemy> enemy(std::make_shared<Enemy>());
	std::map<std::string, int> props;
  float modifierSpeed(modifier);
  if (modifierSpeed > 8) {
    modifierSpeed = 8;
  }
  std::shared_ptr<sf::Texture> texture(nullptr);
  int _health = -1;
	switch (type) {
  case EnemyType::skeleton:
    props = gameState->getEnemyProps(type);
    _health = (health < 0 ? props["health"] * modifier : health);
    texture = std::make_shared<sf::Texture>(enemySpriteS);
    enemy = std::make_shared<Enemy>(position, enemyBaseSize, texture,
      props["gold"] * modifier * gameState->getDifficulty(), _health, props["damage"] * modifier,
      props["speed"] * modifierSpeed, EnemyType::skeleton, targetPath);
    break;
  case EnemyType::demon:
    props = gameState->getEnemyProps(type);
    _health = (health < 0 ? props["health"] * modifier : health);
    texture = std::make_shared<sf::Texture>(enemySpriteD);
    enemy = std::make_shared<Enemy>(position, enemyBaseSize, texture,
      props["gold"] * modifier * gameState->getDifficulty(), _health, props["damage"] * modifier,
      props["speed"] * modifierSpeed, EnemyType::demon, targetPath);
    break;
	case EnemyType::lancer:
		props = gameState->getEnemyProps(type);
    _health = (health < 0 ? props["health"] * modifier : health);
    texture = std::make_shared<sf::Texture>(enemySpriteL);
		enemy = std::make_shared<Enemy>(position, enemyBaseSize, texture,
				props["gold"] * modifier * gameState->getDifficulty(), _health, props["damage"] * modifier,
				props["speed"] * modifierSpeed, EnemyType::lancer, targetPath);
		break;
  case EnemyType::rhino:
    props = gameState->getEnemyProps(type);
    _health = (health < 0 ? props["health"] * modifier : health);
    texture = std::make_shared<sf::Texture>(enemySpriteR);
    enemy = std::make_shared<Enemy>(position, enemyBaseSize, texture,
      props["gold"] * modifier * gameState->getDifficulty(), _health, props["damage"] * modifier,
      props["speed"] * modifierSpeed, EnemyType::rhino, targetPath);
    break;
	}
	enemyVec->push_back(enemy);
	return enemy;
}

void EnemyController::enemyWave(EnemyType type) {
  spawnEnemy(sf::Vector2f(15 * Clickable::gridSize, -1), type);
}

void EnemyController::waveOne() {
	if (counter == 50 || counter == 150 || counter == 300
      || counter == 450) {
		enemyWave(EnemyType::rhino);
	}
	if (counter == 100 || counter == 350 || counter == 500) {
		enemyWave(EnemyType::skeleton);
	}
  if (counter == 200 || counter == 250) {
    enemyWave(EnemyType::lancer);
  }
	if (counter >= 1000) {
		counter = 0;
    wave++;
		gameState->setCurrentWave(gameState->getCurrentWave() + 1);
	}
}

void EnemyController::waveTwo() {
	if (counter == 50 || counter == 450) {
		enemyWave(EnemyType::rhino);
	}
	if (counter == 100 || counter == 150 || counter == 250
			|| counter == 375 || counter == 450) {
		enemyWave(EnemyType::skeleton);
	}
  if (counter == 200 || counter == 300 || counter == 400) {
    enemyWave(EnemyType::lancer);
  }
	if (counter >= 1000) {
		counter = 0;
    wave++;
    gameState->updateHealthBy(1);
		gameState->setCurrentWave(gameState->getCurrentWave() + 1);
	}
}

void EnemyController::waveThree() {
  if (counter == 500 || counter == 525) {
    enemyWave(EnemyType::rhino);
  }
  if (counter == 200 || counter == 450) {
    enemyWave(EnemyType::skeleton);
  }
  if (counter == 50 || counter == 75 || counter == 100
    || counter == 125 || counter == 150 || counter == 350) {
    enemyWave(EnemyType::lancer);
  }
  if (counter >= 1000) {
    counter = 0;
    wave++;
    gameState->updateHealthBy(1);
    gameState->setCurrentWave(gameState->getCurrentWave() + 1);
  }
}

void EnemyController::waveFour() {
  if (counter == 500 || counter ==550) {
    enemyWave(EnemyType::rhino);
  }
  if (counter == 25 || counter == 50 || counter == 75
    || counter == 100) {
    enemyWave(EnemyType::skeleton);
  }
  if (counter == 200 || counter == 400) {
    enemyWave(EnemyType::lancer);
  }
  if (counter == 250 || counter == 300 || counter == 350) {
    enemyWave(EnemyType::demon);
  }
  if (counter >= 1000) {
    counter = 0;
    this->modifier *= 2;
    gameState->updateHealthBy(gameState->getDifficulty());
    if (gameState->getCurrentWave() >= 20) {
      wave = 0;
    } else {
      wave = 1;
    }
    gameState->setCurrentWave(gameState->getCurrentWave() + 1);
  }
}

void EnemyController::waveEND() {
  if (counter == 50 || counter == 325 || counter == 20
    || counter == 25 || counter == 70 || counter == 980
    || counter == 125 || counter == 225 || counter == 750
    || counter == 850 || counter == 950 || counter == 525) {
    enemyWave(EnemyType::rhino);
  }
  if (counter == 100 || counter == 200 || counter == 300
    || counter == 400 || counter == 500 || counter == 600
    || counter == 700 || counter == 800 || counter == 900) {
    enemyWave(EnemyType::skeleton);
  }
  if (counter == 100 || counter == 250 || counter == 350
    || counter == 460 || counter == 560 || counter == 650) {
    enemyWave(EnemyType::lancer);
  }
  if (counter == 111 || counter == 222 || counter == 333
    || counter == 444 || counter == 555 || counter == 666
    || counter == 777 || counter == 888 || counter == 999) {
    enemyWave(EnemyType::demon);
  }
  if (counter >= 1000) {
    counter = 0;
    this->modifier *= 3;
    //wave++;
    gameState->setCurrentWave(gameState->getCurrentWave() + 1);
  }
}

void EnemyController::removeEnemy(std::shared_ptr<Enemy> targetEnemy) {
  for (auto enemy(enemyVec->begin()); enemy != enemyVec->end();++enemy) {
		if (*enemy == targetEnemy) {
			targetEnemy = nullptr;
      enemyVec->erase(enemy);
			break;
		}
	}
}

void EnemyController::dealDamage(std::shared_ptr<Enemy> enemy, int damage) {
	if (enemy != nullptr && enemy->reduceHealth(damage) <= 0) {
		gameState->updateGoldBy(enemy->getGoldValue());
		removeEnemy(enemy);
	}
}

void EnemyController::update() {
  wave %= 5;
  switch (wave) {
  case 1:
    waveOne();
    break;
  case 2:
    waveTwo();
    break;
  case 3:
    waveThree();
    break;
  case 4:
    waveFour();
    break;
  default:
    waveEND();
  }

  sf::Vector2f currentPos, targetPos, distancePos;
  int maxPathIndex = pathInCubits.size();
  float pixelSpeed;
  for (std::shared_ptr<Enemy> enemy : *enemyVec) {
    if (enemy->getPathIndex() == maxPathIndex) {
      gameState->updateHealthBy(-(enemy->getDamage()));
      removeEnemy(enemy);
      break;
    }
    currentPos = enemy->getPosition();
    targetPos = pathInCubits[enemy->getPathIndex()];
    targetPos = sf::Vector2f(
      (pathInCubits[enemy->getPathIndex()].x * Clickable::gridSize),
      (pathInCubits[enemy->getPathIndex()].y * Clickable::gridSize));
    distancePos = targetPos - currentPos;

    if (distancePos.x == 0 && distancePos.y == 0) {
      enemy->increasePathIndex();
    }
    else {
      pixelSpeed = enemy->getPixelSpeed();
      if (distancePos.x != 0 && (abs(distancePos.x) < pixelSpeed)) {
        pixelSpeed = abs(distancePos.x);
      }
      else if (distancePos.y != 0 && abs(distancePos.y) < pixelSpeed) {
        pixelSpeed = abs(distancePos.y);
      }
      int y(0);
    }
    if (distancePos.x > 0) {
      currentPos.x += pixelSpeed;
      enemy->dir = true;
    }
    else if (distancePos.x < 0) {
      currentPos.x -= pixelSpeed;
      enemy->dir = false;
    }
    else if (distancePos.y > 0) {
      currentPos.y += pixelSpeed;
    }
    else if (distancePos.y < 0) {
      currentPos.y -= pixelSpeed;
    }
    if (counter % 5 == 0) {
      enemy->nextFrame();
    }
    enemy->setPosition(currentPos);
  }
  counter++;
}

void EnemyController::render() {
	for (shared_ptr<Enemy> enemy : *enemyVec) {
		enemy->render(window);
	}
}

float EnemyController::getModifier() {
	return this->modifier;
}

void EnemyController::setModifier(float _modifier) {
	this->modifier = _modifier;
}

std::shared_ptr<std::vector<shared_ptr<Enemy>>> EnemyController::getEnemyVec() const {
	return this->enemyVec;
}

bool EnemyController::saveData(const std::string path) {
  bool success(false);
  std::ofstream fout;
  fout.open(path, std::ofstream::binary | std::ofstream::out | std::ofstream::trunc);
  if (fout.is_open()
    && fout.write((char*)& wave, sizeof(wave))
    && fout.write((char*)& modifier, sizeof(modifier))) {
    success = true;
  }
  fout.close();
  return success;
}

bool EnemyController::loadData(const std::string path) {
  bool success(false);
  std::ifstream fin;
  fin.open(path, std::ofstream::binary | std::ofstream::in);
  if (fin.is_open()
    && fin.read((char*)& wave, sizeof(wave))
    && fin.read((char*)& modifier, sizeof(modifier))) {
    success = true;
  }
  fin.close();
  if (!success) {
    std::cerr << "loading enemyController data failed" << std::endl;
  }
  return success;
}

void EnemyController::setDefault() {
  counter = 0;
  wave = 1;
  modifier = 1.0f;
  enemyVec->clear();
}
