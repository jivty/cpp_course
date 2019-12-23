/*
 *  This class is responsible for holding all
 *  shared game state properties, allowing for
 *  communication and shared values between different
 *  controllers.
 */

#include "GameState.h"
#include "Timer.h"
#include "Tower.h"

const int FPS = 30;
GameState::GameState(Timer* timer) :
  timer(timer) {
  towerProps[TowerType::physic] = { {"tam", 30}, {"damage", 15}, {"range", 140}, {"cooldown", 1.25 * FPS} };
  towerProps[TowerType::magic] = { {"tam", 30}, {"damage", 15}, {"range", 140}, {"cooldown", 1.25 * FPS} };
  towerProps[TowerType::ultimate] = { {"tam", 50}, {"damage", 20}, {"range", 120}, {"cooldown", 1.5 * FPS} };

  enemyProps[EnemyType::skeleton] = { {"tam", 2}, {"health", 60}, {"damage", 2}, {"speed", 2} };
  enemyProps[EnemyType::demon] = { {"tam", 5}, {"health", 100}, {"damage", 4}, {"speed", 1} };
  enemyProps[EnemyType::lancer] = { {"tam", 3}, {"health", 80}, {"damage", 3}, {"speed", 1} };
  enemyProps[EnemyType::rhino] = { {"tam", 1}, {"health", 30}, {"damage", 1}, {"speed", 3} };
}

// Game State Accessors
int GameState::getHealth() {
	return this->health;
}
int GameState::getTams() {
	return this->tams;
}
int GameState::getCurrentWave() {
	return this->currentWave;
}
int GameState::getEnemyRemaining() {
	return this->enemyRemaining;
}
int GameState::getEnemyEliminated() {
	return this->enemyEliminated;
}
bool GameState::getHelperState() {
	return this->helperState;
}

// Start Next Wave
void GameState::startWave() {
	this->currentWave++;
	dirtyBit = true;
}

// Update Player Lives
void GameState::updateHealthBy(int update) {
	this->health += update;
  if (health < 0) {
    health = 0;
  }
	dirtyBit = true;
}

// Update Player Currency
void GameState::updateTamBy(int update) {
	this->tams += update;
	dirtyBit = true;
}

TowerType GameState::getPurchaseTower() {
	return this->purchaseTower;
}

void GameState::setPurchaseTower(TowerType towerType) {
	this->purchaseTower = towerType;
}

Tower* GameState::getBoardTower() {
	return this->boardTower;
}
void GameState::setBoardTower(Tower* tower) {
	this->boardTower = tower;
}

void GameState::setCurrentWave(int wave) {
	this->currentWave = wave;
	dirtyBit = true;
}

std::map<string, int> GameState::getTowerProps(TowerType type) {
	return this->towerProps[type];
}

std::map<string, int> GameState::getEnemyProps(EnemyType type) {
	return this->enemyProps[type];
}

void GameState::startGame() {
}

void GameState::endGame() {
}

void GameState::toggleHelpScreen() {
	this->helperState = !helperState;
}

GameState::~GameState() {
}

