#ifndef TD_ENEMY_CONTROLLER_H
#define TD_ENEMY_CONTROLLER_H

#include "Enemy.h"
#include "GameState.h"
#include "GameController.h"
#include <SFML/Graphics.hpp>

//! \brief Управление NPC.
class EnemyController {
public:

  //! \brief Конструирование котроллера.
  //!
  //! \param pathToFollow - путь передвижения NPC по карте
	EnemyController(std::shared_ptr<sf::RenderWindow> window, 
    std::shared_ptr<GameState> gameState,
			const std::vector<sf::Vector2f> pathToFollow);

  //! \brief Деструктор.
  ~EnemyController() = default;

  //! \brief Создание нового NPC.
  //!
  //! \param position - позиция создания
  //! \param type - тип NPC
  //! \param health - (не стандартное) здоровье создаваемого NPC
  //! \param targetPath - (не стандартный) индекс участка пути
	std::shared_ptr<Enemy> spawnEnemy(sf::Vector2f position, EnemyType type, 
    int health = -1, int targetPath = 0);

  //! \brief Удаление NPC.
	void removeEnemy(std::shared_ptr<Enemy> targetEnemy);

  //! \brief Причичнение урона NPC.
	void dealDamage(std::shared_ptr<Enemy> enemy, int damage);

  //! \brief Создание нового NPC в начале пути.
	void enemyWave(EnemyType type);

  //! \brief Вызов волны 1 типа.
	void waveOne();

  //! \brief Вызов волны 2 типа.
	void waveTwo();

  //! \brief Вызов волны 3 типа.
  void waveThree();

  //! \brief Вызов волны 4 типа.
  void waveFour();

  //! \brief Вызов волны особого типа для быстрого окончания игры.
  void waveEND();

  //! \brief Обновление контроллера.
	void update();

  //! \brief Отображение всех NPC.
	void render();

  //! \brief Сохранение параметров этапа игры.
  bool saveData(const std::string path);

  //! \brief Загрузка параметров этапа игры.
  bool loadData(const std::string path);

  //! \brief Установка начальных параметров игры.
  void setDefault();

  //! \brief Множитель усложнения игры.
	float getModifier();

  //! \brief Изменение множителя усложнения игры.
	void setModifier(float _modifier);

  //! \brief Vector живых NPC.
	std::shared_ptr<std::vector<std::shared_ptr<Enemy>>> getEnemyVec() const;

private:
  sf::Texture enemySpriteS;
  sf::Texture enemySpriteD;
  sf::Texture enemySpriteL;
  sf::Texture enemySpriteR;
  std::shared_ptr<sf::RenderWindow> window;
  std::shared_ptr<GameState> gameState;
  std::vector<sf::RectangleShape> framesS;
  std::vector<sf::RectangleShape> framesD;
  std::vector<sf::RectangleShape> framesL;
  std::vector<sf::RectangleShape> framesR;
  sf::Vector2f enemyBaseSize{ sf::Vector2f(Clickable::gridSize, Clickable::gridSize) };
  int counter{ 0 };
  int wave{ 1 };
  float modifier{ 1.0f };
  std::shared_ptr<std::vector<std::shared_ptr<Enemy>>> enemyVec;
  const std::vector<sf::Vector2f> pathInCubits;
};

#endif
