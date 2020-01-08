#include "TowerAndEnemyController.h"

TowerAndEnemyController::TowerAndEnemyController(std::shared_ptr<sf::RenderWindow> _window,
  std::shared_ptr<GameState> _gameState, std::shared_ptr<EnemyController> _enemyController,
  std::shared_ptr<vector<std::shared_ptr<Tower>>> _allTowers, 
  std::shared_ptr<vector<std::shared_ptr<Enemy>>> _allEnemy) 
  : window(_window)
  , gameState(_gameState)
  , enemyController(_enemyController)
  , allThrowTowers(_allTowers)
  , allEnemy(_allEnemy) {
}

void TowerAndEnemyController::addThrowObjectToList(int index, int damage,
		sf::Vector2f towerPosition, std::weak_ptr<Enemy> enemyPtr, TowerType tType) {
	allThrowObjects.push_back(
			std::make_shared<Bullet>(index, damage, towerPosition, enemyPtr, tType));
}

void TowerAndEnemyController::deleteBullet(Bullet* bullet) {
  for (auto bulit(allThrowObjects.begin()); bulit != allThrowObjects.end(); ++bulit) {
		if ((*bulit).get() == bullet) {
			allThrowObjects.erase(bulit);
			break;
		}
	}
}

void TowerAndEnemyController::deleteThrowObjectAtIndex(int index) {
	allThrowObjects[index].reset();
	allThrowObjects.erase(allThrowObjects.begin() + index);
}
void TowerAndEnemyController::drawAllThrowObjectsOnGrid(
		std::shared_ptr<sf::RenderWindow> _window) {
	for (auto& bullet : allThrowObjects) {
		bullet->drawBullet(_window);
	}
}

void TowerAndEnemyController::updateBullets() { 
	int i = 0;
	while(i<allThrowObjects.size()){
		if (auto enemy = allThrowObjects[i]->getEnemyTarget().lock()) {
			if (allThrowObjects[i]->bulletEnemyCollision(
					enemy->getCenterPosition())) {
        int damage(allThrowObjects[i]->getDamage());
        if (enemy->getEnemyType() == EnemyType::demon
          || (enemy->getEnemyType() == EnemyType::skeleton
            && allThrowObjects[i]->getType() == TowerType::magic)
          || (enemy->getEnemyType() == EnemyType::lancer
            && allThrowObjects[i]->getType() == TowerType::physic)) {
          damage *= 0.8f;
        }
				enemyController->dealDamage(enemy,
						damage);

				deleteBullet(allThrowObjects[i].get());
				--i;
			} else {
				allThrowObjects[i]->moveObjectTowardsEnemy(
						enemy->getCenterPosition());
			}
		} else {
			deleteBullet(allThrowObjects[i].get());
			--i;
		}
		++i;
	}
}
bool TowerAndEnemyController::collisionDetected(std::shared_ptr<Tower> tower,
		std::weak_ptr<Enemy> _enemy) {
	if (auto enemy = _enemy.lock()) {
		float distX = enemy->getCenterPosition().x
				- tower->getCenterPosition().x;
		float distY = enemy->getCenterPosition().y
				- tower->getCenterPosition().y;
		float distance = sqrt((distX * distX) + (distY * distY));
		if (distance <= tower->getRange())
			return true;
	}
	return false;
}

void TowerAndEnemyController::updateTowerEnemyRange() {
	if (allThrowTowersInRangeOfEnemy.size() > 0)
		allThrowTowersInRangeOfEnemy.erase(allThrowTowersInRangeOfEnemy.begin(),
				allThrowTowersInRangeOfEnemy.end());
	allEnemyInRangeOfTowers.erase(allEnemyInRangeOfTowers.begin(),
			allEnemyInRangeOfTowers.end());

	for (int i = 0, allTowerSize = allThrowTowers->size(); i < allTowerSize; i++) {
		for (int j = 0, allEnemySize = allEnemy->size(); j < allEnemySize;
				j++) {
			if (collisionDetected((*allThrowTowers)[i], (*allEnemy)[j])) {
				std::weak_ptr<Enemy> enemy = (*allEnemy)[j];
				allEnemyInRangeOfTowers.push_back(enemy);
				allThrowTowersInRangeOfEnemy.push_back((*allThrowTowers)[i]);
			}
		}
	}
}

void TowerAndEnemyController::update() { 
  for (int i = 0, towerSize = allThrowTowers->size(); i < towerSize; i++) {
		if ((*allThrowTowers)[i]->getCooldown() >= 1) {
			(*allThrowTowers)[i]->decreaseCooldown();
		}
	}
  updateTowerEnemyRange();
	for (int i = 0, availableEnemy = allThrowTowersInRangeOfEnemy.size();
			i < availableEnemy; i++) { 
		if (allThrowTowersInRangeOfEnemy[i]->getCooldown() <= 0) {
			allThrowTowersInRangeOfEnemy[i]->resetCooldown();
			auto enemy = allEnemyInRangeOfTowers[i].lock();
			addThrowObjectToList(allThrowObjects.size() - 1,
					allThrowTowersInRangeOfEnemy[i]->getDamage(),
					allThrowTowersInRangeOfEnemy[i]->getPosition(),
					allEnemyInRangeOfTowers[i],
          allThrowTowersInRangeOfEnemy[i]->getTowerType());	}
	}
	updateBullets();
}

void TowerAndEnemyController::render() {
	drawAllThrowObjectsOnGrid(window);
}
