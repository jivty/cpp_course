#include "GameState.h"
#include "Timer.h"
#include "Tower.h"

GameState::GameState(std::shared_ptr<Timer> timer)
  : timer(timer) {
  towerProps[TowerType::physic] = { {"gold", 30}, {"damage", 15}, {"range", 140}, {"cooldown", 1.25f * 30} };
  towerProps[TowerType::magic] = { {"gold", 30}, {"damage", 15}, {"range", 140}, {"cooldown", 1.25f * 30} };
  towerProps[TowerType::ultimate] = { {"gold", 50}, {"damage", 20}, {"range", 120}, {"cooldown", 1.5f * 30} };

  enemyProps[EnemyType::skeleton] = { {"gold", 2}, {"health", 60}, {"damage", 2}, {"speed", 2} };
  enemyProps[EnemyType::demon] = { {"gold", 4}, {"health", 100}, {"damage", 4}, {"speed", 1} };
  enemyProps[EnemyType::lancer] = { {"gold", 3}, {"health", 80}, {"damage", 3}, {"speed", 1} };
  enemyProps[EnemyType::rhino] = { {"gold", 1}, {"health", 40}, {"damage", 1}, {"speed", 3} };

  std::shared_ptr<sf::Music> music(std::make_shared<sf::Music>());
  this->music = music;
  if (!music->openFromFile("music/music.ogg"))
    std::cerr << "The music file was not found" << std::endl;
  music->setLoop(true);
}

std::shared_ptr<sf::Music> GameState::getMusic() {
  return music;
}

bool GameState::getMusicStatus() {
  return music->getStatus() == sf::SoundSource::Status::Playing;
}

int GameState::getHealth() {
	return this->health;
}

int GameState::getGold() {
	return this->gold;
}

int GameState::getCurrentWave() {
	return this->currentWave;
}

bool GameState::getHelperState() {
	return this->helperState;
}

void GameState::updateHealthBy(int update) {
	this->health += update;
  if (health < 0) {
    health = 0;
  }
	dirtyBit = true;
}

void GameState::updateGoldBy(int update) {
	this->gold += update;
	dirtyBit = true;
}

TowerType GameState::getPurchaseTower() {
	return this->purchaseTower;
}

void GameState::setPurchaseTower(TowerType towerType) {
	this->purchaseTower = towerType;
}

std::shared_ptr<Tower> GameState::getBoardTower() {
	return this->boardTower;
}

void GameState::setBoardTower(std::shared_ptr<Tower> tower) {
	this->boardTower = tower;
}

void GameState::setCurrentWave(int wave) {
	this->currentWave = wave;
	dirtyBit = true;
}

std::map<std::string, int> GameState::getTowerProps(TowerType type) {
	return this->towerProps[type];
}

std::map<std::string, int> GameState::getEnemyProps(EnemyType type) {
	return this->enemyProps[type];
}

void GameState::startGame(const int dif) {
  dirtyBit = true;
  difficulty = dif;
  switch (dif) {
  case 1:
    health = 20;
    gold = 300;
    break;
  case 2:
    health = 20;
    gold = 250;
    break;
  case 3:
    health = 15;
    gold = 250;
    break;
  case 4:
    health = 10;
    gold = 200;
    break;
  default:
    health = 99999999;
    gold = 99999999;
    difficulty = 0;
    break;
  }
  currentWave = 1;
  helperState = 1;
}

const int GameState::getDifficulty() const {
  return difficulty;
}

void GameState::toggleHelpScreen() {
	this->helperState = !helperState;
}

GameState::~GameState() {
  music->stop();
}

bool GameState::saveData(const std::string path) {
  bool success(false);
  std::ofstream fout;
  fout.open(path, std::ofstream::binary | std::ofstream::out | std::ofstream::trunc);
  if (fout.is_open()
    && fout.write((char*)& health, sizeof(health))
    && fout.write((char*)& gold, sizeof(gold))
    && fout.write((char*)& currentWave, sizeof(currentWave))
    && fout.write((char*)& difficulty, sizeof(difficulty))) {
    success = true;
  }
  fout.close();
  return success;
}

bool GameState::loadData(const std::string path) {
  bool success(false);
  std::ifstream fin;
  fin.open(path, std::ofstream::binary | std::ofstream::in);
  if (fin.is_open()
    && fin.read((char*)& health, sizeof(health))
    && fin.read((char*)& gold, sizeof(gold))
    && fin.read((char*)& currentWave, sizeof(currentWave))
    && fin.read((char*)& difficulty, sizeof(difficulty))) {
    success = true;
  }
  fin.close();
  if (!success) {
    std::cerr << "loading gamestate data failed" << std::endl;
  }
  return success;
}

void GameState::setDefault() {
  dirtyBit = true;
  health = 20;
  gold = 1000;
  currentWave = 1;
  difficulty = 1;
}
