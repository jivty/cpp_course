#ifndef TD_TOWER_H
#define TD_TOWER_H

#include "Clickable.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <string>
#include <vector>
#include <fstream>


using namespace std;
typedef sf::IntRect* srcArrayPtr;

enum class TowerType {
  empty, physic, magic, ultimate
};

class Tower : public Clickable {
public:
  Tower() = default;
  Tower(const sf::Vector2f position, std::shared_ptr<sf::Texture> texture, TowerType type,
    int damage, float range, float cooldown, int upgradeCost);
  ~Tower() = default;
  Tower(const Tower& tower) = default;
  Tower& operator=(const Tower& tower) = default;
  bool wasClicked{ false };

  sf::Sprite getTowerSprite() const;
  sf::Vector2f getOriginalTowerPosition();
  sf::Vector2f getPosition() const;
  sf::Vector2f getCenterPosition() const;
  float getDamage() const;
  float getRange() const;
  TowerType getTowerType() const;
  int getCooldown();
  int getUpgradeCost();

  void decreaseCooldown();
  void resetCooldown();

  void update() override;
  void render(sf::RenderWindow& _window) override;
  void onClick() override;
  virtual void upgrade();

  float enemyDistance(sf::Vector2f enemy);
  bool enemyCollides(sf::Vector2f enemy);
  void setPosition(sf::Vector2f);
  bool saveData(const std::string path);

private:
  sf::Vector2f coordinate{ 0,0 };
  sf::Sprite towerSprite;
  sf::Vector2f towerPos{ 0,0 };
  std::shared_ptr<sf::Texture> texture;
  sf::IntRect currentSprite;
  TowerType type{ TowerType::empty };
  float currentCooldown{ 0 };
  float towerDamage{ 0 };
  float towerRange{ 0 };
  float baseCooldown{ 0 };
  int upgradeCost{ 20 };
};

#endif
