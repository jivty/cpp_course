#ifndef TD_TOWER_ENEMY_CONTROLLER_H
#define TD_TOWER_ENEMY_CONTROLLER_H

#include "GameState.h"
#include "Bullet.h"
#include "Tower.h"
#include "Enemy.h"
#include "EnemyController.h"
#include <SFML/Graphics.hpp>

class TowerAndEnemyController {
public:
	TowerAndEnemyController(std::shared_ptr<sf::RenderWindow> window, 
    std::shared_ptr<GameState> gameState, std::shared_ptr<EnemyController> enemyController, 
    std::shared_ptr<vector<std::shared_ptr<Tower>>> allTowers, 
    std::shared_ptr<vector<shared_ptr<Enemy>>> allEnemy);
  ~TowerAndEnemyController() = default;

	void addThrowObjectToList(int index, int damage, sf::Vector2f towerPosition,
			weak_ptr<Enemy> enemyPtr, TowerType tType);
	void drawAllThrowObjectsOnGrid(std::shared_ptr<sf::RenderWindow> theWindow);
  void deleteBullet(Bullet* bullet);
	void deleteThrowObjectAtIndex(int index);
	void updateBullets();
	void updateTowerEnemyRange();

	void update();
	void render();

private:
	std::shared_ptr<sf::RenderWindow> window;
	std::shared_ptr<GameState> gameState;
	std::shared_ptr<EnemyController> enemyController;
	vector<std::shared_ptr<Bullet>> allThrowObjects;

	std::shared_ptr<vector<std::shared_ptr<Tower>>> allThrowTowers;
	vector<std::shared_ptr<Tower>> allThrowTowersInRangeOfEnemy;

	std::shared_ptr<vector<shared_ptr<Enemy>>> allEnemy;
	vector<weak_ptr<Enemy>> allEnemyInRangeOfTowers;

	bool collisionDetected(std::shared_ptr<Tower>, weak_ptr<Enemy>);
};

#endif
