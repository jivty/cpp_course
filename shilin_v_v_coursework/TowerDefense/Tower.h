#ifndef TD_TOWER_H
#define TD_TOWER_H

#include "Clickable.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <string>
#include <vector>
#include <fstream>

//! \brief Типы башен.
enum class TowerType {
  empty, physic, magic, ultimate
};

//! \brief Оборонительная башня.
class Tower : public Clickable {
public:

  //! \brief Умолчательный коснтруктор.
  Tower() = default;

  //! \brief Конструирование башни по параметрам.
  //!
  //! \param position - позиция башни
  //! \param texture - текстура
  //! \param type - тип башни
  //! \param damage - наносимый урон
  //! \param range - радиус поражения
  //! \param cooldown - время перезарядки
  //! \param upgradeCost - стоимость улучшения
  Tower(const sf::Vector2f position, std::shared_ptr<sf::Texture> texture, TowerType type,
    int damage, float range, float cooldown, int upgradeCost);

  //! \brief Деструктор.
  ~Tower() = default;

  //! \brief Конструктор копирования.
  Tower(const Tower& tower) = default;

  //! \brief Присваивание.
  Tower& operator=(const Tower& tower) = default;

  bool wasClicked{ false }; //!< Возвращает true, если башня на игровом поле выбрана.

  //! \brief Установленный спрайт.
  sf::Sprite getTowerSprite() const;

  //! \brief Позиция башни на игровом поле.
  sf::Vector2f getPosition() const;

  //! \brief Позиция центра башни на игровом поле.
  sf::Vector2f getCenterPosition() const;

  //! \brief Наносимый урон.
  float getDamage() const;

  //! \brief Радиус поражения.
  float getRange() const;

  //! \brief Тип башни.
  TowerType getTowerType() const;

  //! \brief Время перезарядки.
  int getCooldown();

  //! \brief Стоимость улучшения.
  int getUpgradeCost();

  //! \brief Уменьшение оставшегося времени перезарядки.
  void decreaseCooldown();
  
  //! \brief Восстановить время перезарядки.
  void resetCooldown();

  //! \brief Обновление.
  void update() override;

  //! \brief Отображение башни.
  void render(sf::RenderWindow& _window) override;

  //! \brief Нажатие на башню на игровом поле.
  void onClick() override;

  //! \brief Улучшение башни.
  void upgrade();

  //! \brief Расстояние до NPC.
  float enemyDistance(sf::Vector2f enemy);

  //! \brief Возвращает true, если NPC - внутри зоны поражения башни.
  bool enemyCollides(sf::Vector2f enemy);

  //! \brief Сохранение параметров башни.
  bool saveData(const std::string path);

private:
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
