#ifndef TD_TOWER_H
#define TD_TOWER_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <math.h>
#include <string>
#include <vector>

#include "Clickable.h"

using namespace std;
typedef sf::IntRect* srcArrayPtr;

enum class TowerType {
  empty, physic, magic, ultimate
};

class Tower : public Clickable {
public:
  Tower(const sf::Vector2f position, sf::Texture* texture, TowerType type,
    int damage, int range, int cooldown);
  ~Tower();

  bool wasClicked;
  int upgradeCost;
  // accessors for attributes on heap
  srcArrayPtr* getIntRects() const;

  // accessors for attributes on stack
  char getDirection() const;
  char getMode() const;
  sf::Sprite getTowerSprite() const;
  sf::Vector2f getOriginalTowerPosition();
  sf::Vector2f getPosition() const;
  sf::Vector2f getCenterPosition() const;
  float getDamage() const;
  float getRange() const;
  TowerType getTowerType() const;
  int getCooldown();
  int getUpgradeCost();

  // Attribute modifiers
  void setMode(char);
  void setDirection(char);
  void decreaseCooldown();
  void resetCooldown();

  void update() override;
  void render(sf::RenderWindow& _window) override;
  void onClick() override;
  virtual void upgrade();

  // Handling attacks
  void enemyDirection(sf::Vector2f enemyPos); // find the direction of the enemy relative to the tower
  float enemyDistance(sf::Vector2f enemy); // returns distance between two points
  bool enemyCollides(sf::Vector2f enemy); // collision detection between two objects, using the distance function
  void Attack();
  void StopAttack();
  void flipSprite();
  void flipBack();

  // test function
  void setPosition(sf::Vector2f);

private:
  // Sprite properties
  sf::Vector2f coordinate; // the tower position on map
  sf::Sprite towerSprite;
  sf::Vector2f towerPos;
  sf::Texture* texture;
  sf::IntRect currentSprite;
  srcArrayPtr* srcSprite; // on heap
  int numPers = 3;
  int numFrame = 3;
  TowerType type;
  int spriteCooldownSwitch = 15;
  // the attributes about attack and tower properties
  char mode; // a - attack; s - stop attack
  char direction; // udlr -> up, down, left, right
  int currentCooldown;
  bool spriteFrame = true;
  // modifed by the upgrade function
  float towerDamage;
  float towerRange;
  int baseCooldown;
};
//
//class UltimateTower {
//public:
//  UltimateTower(const std::vector<float>);
//  //SlammingTower(const SlammingTower&);
//  //virtual ~ThrowingTower();
//  //SlammingTower& operator=(const SlammingTower&);
//
//  // accessors for attributes on heap
//  char getDirection() const;
//  char getMode() const;
//  sf::Sprite getTowerSprite() const;
//  sf::Vector2f gettowerPosition() const;
//  float getSpeed() const;
//  float getRange() const;
//  float getDamage() const;
//  void setMode(char);
//  void setDirection(char);
//  int getBaseCooldown();
//  int getCurrentCooldown();
//  void decreaseCooldown();
//
//  void enemyDirection(sf::Vector2f enemyPos); // find the direction of the enemy relative to the tower
//  float enemyDistance(sf::Vector2f enemy); // returns distance between two points
//  bool enemyCollides(sf::Vector2f enemy); // collision detection between two objects, using the distance function
//  void Attack();
//  void StopAttack();
//  void upgrade();
//
//private:
//  // sprites
//  sf::Sprite towerSprite;
//  sf::Texture towerTexture;
//  int numPers = 3;
//  int numFrame = 2;
//  sf::IntRect currentSprite;
//  srcArrayPtr* srcSprite;
//  std::vector<float> coordinate; // the tower position on map
//  sf::Vector2f towerPos;
//
//  // the attributes about attack and tower properties
//  char mode; // a - attack; s - stop attack
//  char direction; // udlr -> up, down, left, right
//
//  // modifed by the upgrade function
//  float* towerAttributes; // [0] = speed; [1] = range; [2] = damage
//
//  sf::CircleShape range; // the attack range shape
//
//  // probably not gonna need these attributes
//  sf::Clock animationClock;
//};
//// =====================
//
//class MagicTower {
//public:
//  MagicTower(const std::vector<float>);
//  //SwingingTower(const SwingingTower&);
//  //virtual ~ThrowingTower();
//  //SwingingTower& operator=(const SwingingTower&);
//
//  // accessors for attributes on heap
//  char getDirection() const;
//  char getMode() const;
//  sf::Sprite getTowerSprite() const;
//  sf::Vector2f gettowerPosition()const;
//  float getSpeed() const;
//  float getRange() const;
//  float getDamage() const;
//
//  void setMode(char);
//  void setDirection(char);
//  void enemyDirection(sf::Vector2f enemyPos); // find the direction of the enemy relative to the tower
//  float enemyDistance(sf::Vector2f enemy); // returns distance between two points
//  bool enemyCollides(sf::Vector2f enemy); // collision detection between two objects, using the distance function
//  void Attack();
//  void StopAttack();
//  void upgrade();
//  void flipSprite();
//  void flipBack();
//
//  /*
//   // controller oriented functions
//   void addTowerToList(std::string str, sf::Vector2f pos, sf::RenderWindow &windo);
//   void drawAllTowersOnBoard(sf::RenderWindow &theWindow);
//   void removeTowerFromContainer(std::vector<std::shared_ptr<Tower>>& container, Tower &aTower);
//   */
//
//private:
//  // sprites
//  sf::Sprite towerSprite;
//  sf::Texture towerTexture;
//  int numPers = 3;
//  int numFrame = 2;
//  sf::IntRect currentSprite;
//  srcArrayPtr* srcSprite;
//  std::vector<float> coordinate; // the tower position on map
//  sf::Vector2f towerPos;
//
//  // the attributes about attack and tower properties
//  char mode; // a - attack; s - stop attack
//  char direction; // udlr -> up, down, left, right
//  // modifed by the upgrade function
//  float* towerAttributes; // [0] = speed; [1] = range; [2] = damage
//
//  sf::CircleShape range; // the attack range shape
//
//  // the attribute that i have no idea what its doing but looks important
//  //std::list<std::shared_ptr<Tower>> towerList;
//  // but it's giving me errors so oh well whatever
//
//  // probably not gonna need these attributes
//  sf::Clock animationClock;
//};

#endif
