#ifndef TD_TOWER_CONTROLLER_H
#define TD_TOWER_CONTROLLER_H

#include "Tower.h"
#include "GameState.h"
#include <SFML/Graphics.hpp>

using std::string;

class TowerController {
public:
	TowerController(std::shared_ptr<sf::RenderWindow> window,
    std::shared_ptr<GameState> gameState);
	~TowerController() = default;

	std::shared_ptr<Tower> spawnTower(sf::Vector2f position, TowerType type,
    float damage = -1.0f, float range = -1.0f, 
    float baseCooldown = -1.0f, int upgradeCost = 20);

	void process(const sf::Event& event, const sf::Vector2i& mousePos);
	void update();
	void render();
  bool saveData(const std::string path);
  bool loadData(const std::string path);
  void setDefault();

  std::shared_ptr<std::vector<std::shared_ptr<Tower>>> getTowerVec();

private:
  sf::Texture ultimateTexture;
  sf::Texture magicTexture;
  sf::Texture physicTexture;
  std::shared_ptr<sf::RenderWindow> window;
  std::shared_ptr<GameState> gameState;

  std::shared_ptr<std::vector<std::shared_ptr<Tower>>> towerVec;

};

#endif
