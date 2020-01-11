#ifndef TD_TOWER_CONTROLLER_H
#define TD_TOWER_CONTROLLER_H

#include "Tower.h"
#include "GameState.h"
#include <SFML/Graphics.hpp>

//! \brief Управление башнями.
class TowerController {
public:

  //! \brief Конструирование контроллера по параметрам.
	TowerController(std::shared_ptr<sf::RenderWindow> window,
    std::shared_ptr<GameState> gameState);

  //! \brief Деструктор
	~TowerController() = default;

  //! \brief Создание башни по параметрам.
  //!
  //! \param position - позиция башни
  //! \param type - тип башни
  //! \param damage - (не стандартный) урон
  //! \param range - (не стандартный) радиус
  //! \param baseCooldown - (не стандартное) время перезарядки
  //! \param upgradeCost - (не стандартная) стоимость улучшения
	std::shared_ptr<Tower> spawnTower(sf::Vector2f position, TowerType type,
    float damage = -1.0f, float range = -1.0f, 
    float baseCooldown = -1.0f, int upgradeCost = 20);

  //! \brief Обрабатывание событий.
	void process(const sf::Event& event, const sf::Vector2i& mousePos);

  //! \brief Отображение башен и радиуса выбранной башни.
	void render();

  //! \brief Сохранение всех башен.
  bool saveData(const std::string path);

  //! \brief Загрузка всех башен.
  bool loadData(const std::string path);

  //! \brief Очищение списка установленных башен.
  void setDefault();

  //! \brief Список установленных башен.
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
