#include "TowerAndEnemyController.h"

TowerAndEnemyController::TowerAndEnemyController(sf::RenderWindow* _window,
		GameState* _gameState, EnemyController* _enemyController,
		vector<Tower*>* _allTowers, vector<std::shared_ptr<Enemy>>* _allEnemy) :
		window(_window), gameState(_gameState), enemyController(
				_enemyController), allThrowTowers(_allTowers), allEnemy(_allEnemy) {
}
TowerAndEnemyController::~TowerAndEnemyController() {
}

/*___________________________________________OBJECT BEING THROWN_________________________________________________*/

void TowerAndEnemyController::addThrowObjectToList(int index, int damage,
		sf::Vector2f towerPosition, std::weak_ptr<Enemy> enemyPtr, TowerType tType) {
	allThrowObjects.push_back(
			new Bullet(index, damage, towerPosition, enemyPtr, tType));
}

void TowerAndEnemyController::deleteBullet(Bullet* bullet) {
	// This is an acceptable computational cost due to rarity of action.
	// O(N) for each deletion
	for (int i = 0, size = allThrowObjects.size(); i < size; i++) {
		if ((allThrowObjects)[i] == bullet) {
			bullet = nullptr;
			allThrowObjects.erase(allThrowObjects.begin() + i);
			break;
		}
	}
}

void TowerAndEnemyController::deleteThrowObjectAtIndex(int index) {
	delete allThrowObjects[index];
	allThrowObjects[index] = nullptr;
	allThrowObjects.erase(allThrowObjects.begin() + index);
	//delete image? I dont think you'll need to explicitly do this
	//delete &allThrowObjects[index];
}
void TowerAndEnemyController::drawAllThrowObjectsOnGrid(
		sf::RenderWindow* _window) {	//draws the tower onto the grid
	for (auto& bullet : allThrowObjects) {
		bullet->drawBullet(_window);
	}
}
/*__________________________________________OBJECT BEING THROWN_________________________________________________*/

/*___________________________________________Attack Logic_________________________________________________*/

//if missile to enemy collision occurs, delete throwObject, else, move towards enemy
void TowerAndEnemyController::updateBullets() { //this parameter will be replaced by allEnemy[j]->getPosition() in each if statement
	int i = 0;
	while(i<allThrowObjects.size()){
	//for (int i = 0, bulletSize = allThrowObjects.size(); i < bulletSize;
	//		i++) { //for each throw object
		//if there's a collision, delete object and deal damage
		//cout<< "Bullet Positions:" << allThrowObjects[i]->getBulletPosition().x << " and y " << allThrowObjects[i]->getBulletPosition().y << endl;

		if (auto enemy = allThrowObjects[i]->getEnemyTarget().lock()) {
			if (allThrowObjects[i]->bulletEnemyCollision(
					enemy->getCenterPosition())) {
				//deal damage to enemy
        int damage(allThrowObjects[i]->getDamage());
        if (enemy->getEnemyType() == EnemyType::demon
          || (enemy->getEnemyType() == EnemyType::skeleton
            && allThrowObjects[i]->getType() == TowerType::magic)
          || (enemy->getEnemyType() == EnemyType::lancer
            && allThrowObjects[i]->getType() == TowerType::physic)) {
          damage *= 0.8;
        }
				enemyController->dealDamage(enemy,
						damage);

				//delete throw object
				deleteBullet(allThrowObjects[i]);
				--i;
			} else { //if the bullet assigned to a enemy hasnt hit yet, move towards enemy
				allThrowObjects[i]->moveObjectTowardsEnemy(
						enemy->getCenterPosition());
			}
		} else {
			deleteBullet(allThrowObjects[i]);
			--i;
		}
		++i;
	}
}

//Tower and enemy collision
// Uses Pythagorean to detect a point collision with a circle
bool TowerAndEnemyController::collisionDetected(Tower* tower,
		std::weak_ptr<Enemy> _enemy) {
	if (auto enemy = _enemy.lock()) {
		float distX = enemy->getCenterPosition().x
				- tower->getCenterPosition().x;
		float distY = enemy->getCenterPosition().y
				- tower->getCenterPosition().y;
		float distance = sqrt((distX * distX) + (distY * distY));
//	cout << "DistX: " << distX << " DistY: " << distY << endl;
//	cout << "Distance detected: " << distance << " for a range: "
//			<< tower->getRange() << endl;
		if (distance <= tower->getRange())
			return true;
	}
	return false;
}

//ascocitate each tower with a enemy within range, each with a vector of pointers (eg. tower index 0 will fire at enemy index 0)
void TowerAndEnemyController::updateTowerEnemyRange() {
	//clear contents of allThrowTowersInRangeOfEnemy
	if (allThrowTowersInRangeOfEnemy.size() > 0)
		allThrowTowersInRangeOfEnemy.erase(allThrowTowersInRangeOfEnemy.begin(),
				allThrowTowersInRangeOfEnemy.end());
	allEnemyInRangeOfTowers.erase(allEnemyInRangeOfTowers.begin(),
			allEnemyInRangeOfTowers.end());

	for (int i = 0, allTowerSize = allThrowTowers->size(); i < allTowerSize; i++) { //for each tower object
		for (int j = 0, allEnemySize = allEnemy->size(); j < allEnemySize;
				j++) { //for each enemy object
			if (collisionDetected((*allThrowTowers)[i], (*allEnemy)[j])) {
				// cout << "Tower Enemy Collision" << endl;		
				std::weak_ptr<Enemy> enemy = (*allEnemy)[j];
				allEnemyInRangeOfTowers.push_back(enemy);
				allThrowTowersInRangeOfEnemy.push_back((*allThrowTowers)[i]);
			}
		}
	}
}

//below creates two unique pointer vectors assigning each throw tower with a enemy target assigned to it
//cooldown, a generation of bullets
//if enemy is in range of a tower, generate a bullet as long as the tower is not on cooldown
//assign that bullet to a enemy object

void TowerAndEnemyController::update() { //essentially do every attack related function in a small time tick within process
	//for each tower, decrease its cooldown by one tick, when at 0 it can fire
	for (int i = 0, towerSize = allThrowTowers->size(); i < towerSize; i++) {
		if ((*allThrowTowers)[i]->getCooldown() >= 1) {
			(*allThrowTowers)[i]->decreaseCooldown();
		}
	}
	//ascocitate each tower with a enemy within range, each with a vector of pointers (eg. tower index 0 will fire at enemy index 0)
	updateTowerEnemyRange();
	//if the tower is not on cooldown, create a Bullet object that is assigned to a enemy object
	for (int i = 0, availableEnemy = allThrowTowersInRangeOfEnemy.size();
			i < availableEnemy; i++) { //towers and enemy will have same index i
		if (allThrowTowersInRangeOfEnemy[i]->getCooldown() <= 0) { //if the tower is not on cooldown fire a new bullet, else do nothing
			//cout << "Firing Bullet" << endl;
			allThrowTowersInRangeOfEnemy[i]->resetCooldown();
			auto enemy = allEnemyInRangeOfTowers[i].lock();
			(allThrowTowersInRangeOfEnemy)[i]->enemyDirection(enemy->getPosition());
			(allThrowTowersInRangeOfEnemy)[i]->Attack(); //sets directioon
			addThrowObjectToList(allThrowObjects.size() - 1,
					allThrowTowersInRangeOfEnemy[i]->getDamage(),
					allThrowTowersInRangeOfEnemy[i]->getPosition(),
					allEnemyInRangeOfTowers[i],
          allThrowTowersInRangeOfEnemy[i]->getTowerType()); //append a throw object to the end of the vector
			//allThrowObjects[allThrowObjects.size() - 1]->setEnemyTarget(allEnemyInRangeOfTowers[i]); //assign a enemy target
		}
	}
	//move each bullet towards its assigned enemy target, delete and deal damage if hit
	updateBullets();
}

void TowerAndEnemyController::render() {
	drawAllThrowObjectsOnGrid(window);
}

