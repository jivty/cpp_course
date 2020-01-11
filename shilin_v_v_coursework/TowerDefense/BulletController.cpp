#include "BulletController.h"

BulletController::BulletController(std::shared_ptr<sf::RenderWindow> _window,
  std::shared_ptr<GameState> _gameState, std::shared_ptr<EnemyController> _enemyController,
  std::shared_ptr<std::vector<std::shared_ptr<Tower>>> _allTowers, 
  std::shared_ptr<std::vector<std::shared_ptr<Enemy>>> _allEnemy) 
  : window(_window)
  , gameState(_gameState)
  , enemyController(_enemyController)
  , allTowers(_allTowers)
  , allEnemy(_allEnemy) {
}

void BulletController::addThrowObjectToList(int index, int damage,
		sf::Vector2f towerPosition, std::weak_ptr<Enemy> enemyPtr, TowerType tType) {
	allBullets.push_back(
			std::make_shared<Bullet>(index, damage, towerPosition, enemyPtr, tType));
}

void BulletController::deleteBullet(Bullet* bullet) {
  for (auto bulit(allBullets.begin()); bulit != allBullets.end(); ++bulit) {
		if ((*bulit).get() == bullet) {
			allBullets.erase(bulit);
			break;
		}
	}
}

void BulletController::drawAllBulletsOnGrid(
		std::shared_ptr<sf::RenderWindow> _window) {
	for (auto& bullet : allBullets) {
		bullet->drawBullet(_window);
	}
}

void BulletController::updateBullets() {
  int i(0);
  while (i < allBullets.size()) {
		if (auto enemy = allBullets[i]->getEnemyTarget().lock()) {
			if (allBullets[i]->bulletEnemyCollision(
					enemy->getCenterPosition())) {
        int damage(allBullets[i]->getDamage());
        if (enemy->getEnemyType() == EnemyType::demon
          || (enemy->getEnemyType() == EnemyType::skeleton
            && allBullets[i]->getType() == TowerType::magic)
          || (enemy->getEnemyType() == EnemyType::lancer
            && allBullets[i]->getType() == TowerType::physic)) {
          damage *= 0.8f;
        }
				enemyController->dealDamage(enemy,
						damage);

				deleteBullet(allBullets[i].get());
				--i;
			} else {
				allBullets[i]->moveObjectTowardsEnemy(
						enemy->getCenterPosition());
			}
		} else {
			deleteBullet(allBullets[i].get());
			--i;
		}
		++i;
	}
}
bool BulletController::collisionDetected(std::shared_ptr<Tower> tower,
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

void BulletController::updateTowerEnemyRange() {
	if (allTowersInRangeOfEnemy.size() > 0)
		allTowersInRangeOfEnemy.erase(allTowersInRangeOfEnemy.begin(),
				allTowersInRangeOfEnemy.end());
	allEnemyInRangeOfTowers.erase(allEnemyInRangeOfTowers.begin(),
			allEnemyInRangeOfTowers.end());

	for (int i = 0, allTowerSize = allTowers->size(); i < allTowerSize; i++) {
		for (int j = 0, allEnemySize = allEnemy->size(); j < allEnemySize;
				j++) {
			if (collisionDetected((*allTowers)[i], (*allEnemy)[j])) {
				std::weak_ptr<Enemy> enemy = (*allEnemy)[j];
				allEnemyInRangeOfTowers.push_back(enemy);
				allTowersInRangeOfEnemy.push_back((*allTowers)[i]);
			}
		}
	}
}

void BulletController::update() { 
  for (int i = 0, towerSize = allTowers->size(); i < towerSize; i++) {
		if ((*allTowers)[i]->getCooldown() >= 1) {
			(*allTowers)[i]->decreaseCooldown();
		}
	}
  updateTowerEnemyRange();
	for (int i = 0, availableEnemy = allTowersInRangeOfEnemy.size();
			i < availableEnemy; i++) { 
		if (allTowersInRangeOfEnemy[i]->getCooldown() <= 0) {
			allTowersInRangeOfEnemy[i]->resetCooldown();
			auto enemy = allEnemyInRangeOfTowers[i].lock();
			addThrowObjectToList(allBullets.size() - 1,
					allTowersInRangeOfEnemy[i]->getDamage(),
					allTowersInRangeOfEnemy[i]->getPosition(),
					allEnemyInRangeOfTowers[i],
          allTowersInRangeOfEnemy[i]->getTowerType());	}
	}
	updateBullets();
}

void BulletController::render() {
	drawAllBulletsOnGrid(window);
}
