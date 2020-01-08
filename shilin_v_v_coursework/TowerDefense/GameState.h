#ifndef TD_GAMESTATE_H
#define TD_GAMESTATE_H

#include "Timer.h"
#include "Tower.h"
#include <SFML/Audio.hpp>
#include <iostream>

enum class EnemyType {
	skeleton, demon, lancer, rhino, empty
};

class GameState {
public:
  GameState(std::shared_ptr<Timer> timer);
  virtual ~GameState();
  bool dirtyBit = true;
  std::shared_ptr<Timer> timer;
  sf::Vector2i mousePos;

  int getHealth();
  int getGold();
  int getCurrentWave();
  void setCurrentWave(int wave);
  int getEnemyRemaining();
  int getEnemyEliminated();
  bool getHelperState();
  TowerType getPurchaseTower();
  void setPurchaseTower(TowerType towerType);
  std::shared_ptr<Tower> getBoardTower();
  void setBoardTower(std::shared_ptr<Tower> tower);
  void setDefault();

  std::map<string, int> getTowerProps(TowerType type);
  std::map<string, int> getEnemyProps(EnemyType type);
  std::shared_ptr<sf::Music> getMusic();

  void startGame(const int dif);
  void endGame();
  void startWave();
  void updateHealthBy(int update);
  void updateGoldBy(int update);
  void toggleHelpScreen();
  bool getMusicStatus();
  const int getDifficulty() const;
  bool saveData(const std::string path);
  bool loadData(const std::string path);

private:
  std::map<TowerType, std::map<string, int>> towerProps;
  std::map<EnemyType, std::map<string, int>> enemyProps;
  std::shared_ptr<sf::Music> music;

  bool helperState{ false };

  int health{ 20 };
  int gold{ 1000 };
  int currentWave{ 1 };
  int enemyRemaining{ -1 };
  int enemyEliminated{ 0 };
  int difficulty{ 1 };

  TowerType purchaseTower = TowerType::empty;
  std::shared_ptr<Tower> boardTower{ nullptr };
};

#endif
