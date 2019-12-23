#include "EnemyController.h"
#include "Enemy.h"

EnemyController::EnemyController(sf::RenderWindow* _window,
		GameState* _gameState, const std::vector<sf::Vector2f> _path) :
		window(_window), gameState(_gameState), pathInCubits(_path) {
	enemyVec = new std::vector<shared_ptr<Enemy>>;
	modifier = 1;
	enemySpriteS = new sf::Texture;
	if (!enemySpriteS->loadFromFile("images/enemies/skeleton.png")) {
		std::cerr << "The enemy texture (skeleton) could not be loaded" << std::endl;
  } 
  enemySpriteD= new sf::Texture;
  if (!enemySpriteD->loadFromFile("images/enemies/demon.png")) {
    std::cerr << "The enemy texture (demon) could not be loaded" << std::endl;
  } 
  enemySpriteL = new sf::Texture;
  if (!enemySpriteL->loadFromFile("images/enemies/lancer.png")) {
    std::cerr << "The enemy texture (lancer) could not be loaded" << std::endl;
  } 
  enemySpriteR = new sf::Texture;
  if (!enemySpriteR->loadFromFile("images/enemies/rhino.png")) {
    std::cerr << "The enemy texture (rhino) could not be loaded" << std::endl;
  } 
}

// This is used to produce enemy, and will be placed
// within the enemyVec vector
std::shared_ptr<Enemy> EnemyController::spawnEnemy(sf::Vector2f position,
		EnemyType type) {
	std::shared_ptr<Enemy> enemy = nullptr;
	std::map<std::string, int> props;
  float modifierSpeed(modifier);
  if (modifierSpeed > 30) {
    modifierSpeed = 30;
  }
	switch (type) {
  case EnemyType::skeleton:
    props = gameState->getEnemyProps(type);
    enemy = std::make_shared<Enemy>(position, enemyBaseSize, enemySpriteS,
      props["tam"] * modifier, props["health"] * modifier, props["damage"] * modifier,
      props["speed"] * modifierSpeed, EnemyType::skeleton);
    break;
  case EnemyType::demon:
    props = gameState->getEnemyProps(type);
    enemy = std::make_shared<Enemy>(position, enemyBaseSize, enemySpriteD,
      props["tam"] * modifier, props["health"] * modifier, props["damage"] * modifier,
      props["speed"] * modifierSpeed, EnemyType::demon);
    break;
	case EnemyType::lancer:
		props = gameState->getEnemyProps(type);
		enemy = std::make_shared<Enemy>(position, enemyBaseSize, enemySpriteL,
				props["tam"] * modifier, props["health"] * modifier, props["damage"] * modifier,
				props["speed"] * modifierSpeed, EnemyType::lancer);
		break;
  case EnemyType::rhino:
    props = gameState->getEnemyProps(type);
    enemy = std::make_shared<Enemy>(position, enemyBaseSize, enemySpriteR,
      props["tam"] * modifier, props["health"] * modifier, props["damage"] * modifier,
      props["speed"] * modifierSpeed, EnemyType::rhino);
    break;
	}
	enemyVec->push_back(enemy);
	//std::cout << "Enemy added" << std::endl;
	return enemy;
}

int counter = 0;
int wave = 1;
void EnemyController::enemyWave(EnemyType type) {
  spawnEnemy(sf::Vector2f(15 * Clickable::gridSize, -1), type);
}

void EnemyController::waveOne() {
	if (::counter == 50 || ::counter == 150 || ::counter == 300
      || ::counter == 450) {
		enemyWave(EnemyType::rhino);
	}
	if (::counter == 100 || ::counter == 350 || ::counter == 500) {
		enemyWave(EnemyType::skeleton);
	}
  if (::counter == 200 || ::counter == 250) {
    enemyWave(EnemyType::lancer);
  }
	if (::counter >= 1000) {
		::counter = 0;
		//this->modifier *= 1.2;
    ::wave++;
		gameState->setCurrentWave(gameState->getCurrentWave() + 1);
	}
}

void EnemyController::waveTwo() {
	if (::counter == 50 || ::counter == 450) {
		enemyWave(EnemyType::rhino);
	}
	if (::counter == 100 || ::counter == 150 || ::counter == 250
			|| ::counter == 375 || ::counter == 450) {
		enemyWave(EnemyType::skeleton);
	}
  if (::counter == 200 || ::counter == 300 || ::counter == 400) {
    enemyWave(EnemyType::lancer);
  }
	if (::counter >= 1000) {
		::counter = 0;
    ::wave++;
    gameState->updateHealthBy(1);
		gameState->setCurrentWave(gameState->getCurrentWave() + 1);
	}
}

void EnemyController::waveThree() {
  if (::counter == 500 || ::counter == 525) {
    enemyWave(EnemyType::rhino);
  }
  if (::counter == 200 || ::counter == 450) {
    enemyWave(EnemyType::skeleton);
  }
  if (::counter == 50 || ::counter == 75 || ::counter == 100
    || ::counter == 125 || ::counter == 150 || ::counter == 350) {
    enemyWave(EnemyType::lancer);
  }
  if (::counter >= 1000) {
    ::counter = 0;
    ::wave++;
    gameState->updateHealthBy(1);
    gameState->setCurrentWave(gameState->getCurrentWave() + 1);
  }
}

void EnemyController::waveFour() {
  if (::counter == 500 || ::counter ==550) {
    enemyWave(EnemyType::rhino);
  }
  if (::counter == 25 || ::counter == 50 || ::counter == 75
    || ::counter == 100) {
    enemyWave(EnemyType::skeleton);
  }
  if (::counter == 200 || ::counter == 400) {
    enemyWave(EnemyType::lancer);
  }
  if (::counter == 250 || ::counter == 300 || ::counter == 350) {
    enemyWave(EnemyType::demon);
  }
  if (::counter >= 1000) {
    ::counter = 0;
    this->modifier *= 1.2;
    gameState->updateHealthBy(2);
    if (gameState->getCurrentWave() >= 20) {
      ::wave = 5;
    } else {
      ::wave = 1;
    }
    gameState->setCurrentWave(gameState->getCurrentWave() + 1);
  }
}

void EnemyController::waveEND() {
  if (::counter == 50 || ::counter == 325 || ::counter == 20
    || ::counter == 25 || ::counter == 70 || ::counter == 980
    || ::counter == 125 || ::counter == 225 || ::counter == 750
    || ::counter == 850 || ::counter == 950 || ::counter == 525) {
    enemyWave(EnemyType::rhino);
  }
  if (::counter == 100 || ::counter == 200 || ::counter == 300
    || ::counter == 400 || ::counter == 500 || ::counter == 600
    || ::counter == 700 || ::counter == 800 || ::counter == 900) {
    enemyWave(EnemyType::skeleton);
  }
  if (::counter == 100 || ::counter == 250 || ::counter == 350
    || ::counter == 460 || ::counter == 560 || ::counter == 650) {
    enemyWave(EnemyType::lancer);
  }
  if (::counter == 111 || ::counter == 222 || ::counter == 333
    || ::counter == 444 || ::counter == 555 || ::counter == 666
    || ::counter == 777 || ::counter == 888 || ::counter == 999) {
    enemyWave(EnemyType::demon);
  }
  if (::counter >= 1000) {
    ::counter = 0;
    this->modifier *= 2;
    //::wave++;
    gameState->setCurrentWave(gameState->getCurrentWave() + 1);
  }
}


// This goes through the array and releases all enemy objects
// whose health are < 0, erasing them from the vector
void EnemyController::updateEnemy() {

}

// Deprecated. This causes unknown memory accesses
void EnemyController::removeEnemy(std::shared_ptr<Enemy> targetEnemy) {
// This is an acceptable computational cost due to rarity of action.
// O(N) for each deletion
	for (int i = 0, size = enemyVec->size(); i < size; i++) {
		if ((*enemyVec)[i] == targetEnemy) {
			targetEnemy = nullptr;
			enemyVec->erase(enemyVec->begin() + i);
			break;
		}
	}
}

void EnemyController::dealDamage(std::shared_ptr<Enemy> enemy, int damage) {
	if (enemy != nullptr && enemy->reduceHealth(damage) <= 0) {
		gameState->updateTamBy(enemy->getTamValue());
		removeEnemy(enemy);
		updateEnemy();
	}
}

void EnemyController::update() {
  // Go through each enemy object, and find the best point.
  // Follow that path! This is a simple implementation, which
  // relies on the fact that all paths follow linear changes,
  // aka no need for diagonal travel.

  switch (::wave) {
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
    // Enemy has reached the finish line
    if (enemy->getPathIndex() == maxPathIndex) {
      gameState->updateHealthBy(-(enemy->getDamage()));
      removeEnemy(enemy);
      break;
    }
    currentPos = enemy->getPosition();
    targetPos = pathInCubits[enemy->getPathIndex()];
    // Convert the path vector to one in Clickable::gridSizes
    targetPos = sf::Vector2f(
      (pathInCubits[enemy->getPathIndex()].x * Clickable::gridSize),
      (pathInCubits[enemy->getPathIndex()].y * Clickable::gridSize));
    distancePos = targetPos - currentPos;

    if (distancePos.x == 0 && distancePos.y == 0) {
      enemy->increasePathIndex();
    }
    else {
      pixelSpeed = enemy->getPixelSpeed();
      // Deal with excess movements
      if (distancePos.x != 0 && (abs(distancePos.x) < pixelSpeed)) {
        pixelSpeed = abs(distancePos.x);
      }
      else if (distancePos.y != 0 && abs(distancePos.y) < pixelSpeed) {
        pixelSpeed = abs(distancePos.y);
      }
      int y(0);
      //EnemyType type = enemy->getEnemyType();
      /*if (type == EnemyType::slow) {
        y = 0;
      } else if (type == EnemyType::regular) {
        y = 130;
      } else if (type == EnemyType::fast) {
        y = 260;
      } else {
        y = 75;
      }
      */
      //In each of these indexes, change the enemy sprite to reflect direction
      //string enemyType = ToString(enemy->getEnemyType());
    }
    if (distancePos.x > 0) {
      currentPos.x += pixelSpeed;
      enemy->dir = true;
      //enemy->setTextureRect(sf::IntRect(260, y, 130, 130));
    }
    else if (distancePos.x < 0) {
      currentPos.x -= pixelSpeed;
      enemy->dir = false;
      //enemy->setTextureRect(sf::IntRect(260, y, -130, 130));
    }
    else if (distancePos.y > 0) {
      currentPos.y += pixelSpeed;
      //enemy->setTextureRect(sf::IntRect(0, y, 130, 130));
    }
    else if (distancePos.y < 0) {
      currentPos.y -= pixelSpeed;
      //enemy->setTextureRect(sf::IntRect(0, y, 130, 130));
    }
    if (::counter % 5 == 0) {
      enemy->nextFrame();
    }
    enemy->setPosition(currentPos);
  }
  updateEnemy();
  ::counter++;
}
/*
void EnemyController::turnEnemy(shared_ptr<Enemy> enemy, sf::IntRect _textureRect, int direction){
	enemy->getTextureRect();

	int x = 0;
	int y = 0;
	char enemyType = ToString(enemy->getEnemytype());

	switch(enemyType) {
		case "slow":  y=0;
		case "regular": y=130;
		case "fast": y=260;
	}

	//1 means down, 2 means right
	switch(direction) {
	case 1: x = 0;
	case 2: x = 1;
	}
	enemy->setTextureRect(sf::IntRect());

	if(enemyType == "regular") {
		enemy->setTextureRect(sf::IntRect(222, 120, 120, 120));
		enemy->setTextureRect(_textureRect);

	}
	//enemy->setTextureRect(sf::IntRect(222, 120, 120, 120));
	//enemy->setTextureRect(textureRect);
	enemy->setPosition(sf::Vector2f(100, 400));
}
*/

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

std::vector<shared_ptr<Enemy>>* EnemyController::getEnemyVec() {
	return this->enemyVec;
}
