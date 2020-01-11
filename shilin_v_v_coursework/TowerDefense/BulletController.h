#ifndef TD_TOWER_ENEMY_CONTROLLER_H
#define TD_TOWER_ENEMY_CONTROLLER_H

#include "GameState.h"
#include "Bullet.h"
#include "Tower.h"
#include "Enemy.h"
#include "EnemyController.h"
#include <SFML/Graphics.hpp>

//! \brief Сопряжение контроллеров башен и NPC и управление снарядами.
class BulletController {
public:

  //! \brief Конструктор по параметрам.
	BulletController(std::shared_ptr<sf::RenderWindow> window, 
    std::shared_ptr<GameState> gameState, std::shared_ptr<EnemyController> enemyController, 
    std::shared_ptr<std::vector<std::shared_ptr<Tower>>> allTowers, 
    std::shared_ptr<std::vector<std::shared_ptr<Enemy>>> allEnemy);

  //! \brief Деструктор
  ~BulletController() = default;

  //! \brief Создание нового снаряда.
  //!
  //! \param index - индекс снаряда
  //! \param damage - наносимый урон NPC снарядом
  //! \param towerPosition - позиция башни
  //! \param enemyPtr - атакуемый NPC
  //! \param tType - тип башни
	void addThrowObjectToList(int index, int damage, sf::Vector2f towerPosition,
			std::weak_ptr<Enemy> enemyPtr, TowerType tType);

  //! \brief Отображение всех установленных башен.
	void drawAllBulletsOnGrid(std::shared_ptr<sf::RenderWindow> theWindow);

  //! \brief Удаление снаряда.
  void deleteBullet(Bullet* bullet);

  //! \brief Обновление летящих снарядов.
	void updateBullets();

  //! \brief Обновление списков NPC в зоне поражения.
	void updateTowerEnemyRange();

  //! \brief Обновление перезарядок и создание новых снарядов.
	void update();

  //! \brief Отображение снарядов.
	void render();

private:
	std::shared_ptr<sf::RenderWindow> window;
	std::shared_ptr<GameState> gameState;
	std::shared_ptr<EnemyController> enemyController;
	std::vector<std::shared_ptr<Bullet>> allBullets;

	std::shared_ptr<std::vector<std::shared_ptr<Tower>>> allTowers;
	std::vector<std::shared_ptr<Tower>> allTowersInRangeOfEnemy;

	std::shared_ptr<std::vector<std::shared_ptr<Enemy>>> allEnemy;
	std::vector<std::weak_ptr<Enemy>> allEnemyInRangeOfTowers;

	bool collisionDetected(std::shared_ptr<Tower>, std::weak_ptr<Enemy>);
};

#endif
