#ifndef TD_TOWER_ENEMY_CONTROLLER_H
#define TD_TOWER_ENEMY_CONTROLLER_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <iostream>
#include <vector>
#include <memory>
#include <cstdio>
#include <fstream>
#include <cassert>
#include <functional>

#include "GameState.h"
#include "Bullet.h"
#include "Tower.h"
#include "Enemy.h"
#include "EnemyController.h"

using std::weak_ptr;
using std::shared_ptr;

class TowerAndEnemyController {
public:
	TowerAndEnemyController(sf::RenderWindow* window, GameState* gameState,
			EnemyController* enemyController, vector<Tower*>* allTowers,
			vector<shared_ptr<Enemy>>* allEnemy);
	~TowerAndEnemyController();
	//throwTower Object
	//void addThrowTowerToList(sf::Vector2f position, int index); //using string
	//void deleteThrowTowerAtIndex(int index);
	//Throw Objects
	void addThrowObjectToList(int index, int damage, sf::Vector2f towerPosition,
			weak_ptr<Enemy> enemyPtr, TowerType tType);
	void drawAllThrowObjectsOnGrid(sf::RenderWindow* theWindow);
  void deleteBullet(Bullet* bullet);
	void deleteThrowObjectAtIndex(int index);
	void updateBullets();
	void updateTowerEnemyRange();

	//used for testing
	//void addEnemyObjectToList(sf::Vector2f _position, sf::Vector2f _size,
		//	sf::Texture* _texture, int type, double modifier);

	void update();
	void render();
private:
	sf::RenderWindow* window;
	GameState* gameState;
	EnemyController* enemyController;
	vector<Bullet*> allThrowObjects;

	vector<Tower*>* allThrowTowers;
	vector<Tower*> allThrowTowersInRangeOfEnemy;

	// This is a reference to the true enemy vector. Duplication
	// should always be as a weak pointer, to allow for bullets
	// to properly delete themselves once a target enemy is removed.
	vector<shared_ptr<Enemy>>* allEnemy;
	vector<weak_ptr<Enemy>> allEnemyInRangeOfTowers;

	bool collisionDetected(Tower*, weak_ptr<Enemy>);

	//vector<unique_ptr<Tower>> allTSlamTowers;
//vector<unique_ptr<Tower>> allSkipTowers;
	//vector<unique_ptr<Tower>> allSlamObjects;
//vector<unique_ptr<Tower>> allSkipObjects;
};

#endif
