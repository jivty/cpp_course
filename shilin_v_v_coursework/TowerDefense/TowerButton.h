#ifndef TD_TOWER_BUTTON_H
#define TD_TOWER_BUTTON_H

#include "Clickable.h"
#include "GameState.h"

//! \brief Кнопка башни в меню.
class TowerButton: public Clickable {
public:

  //! \brief Конструирование кнопки башни в меню.
  //!
  //! \param _position - позиция кнопки
  //! \param _radius - радиус кнопки
  //! \param _texture - текстура кнопки
  //! \param inText - стоимость башни
  //! \param inText2 - урон и время перезарядки башни
  //! \param _type - тип башни
  //! \param _menuTexture - текстура заднего фона для текста
	TowerButton(sf::Vector2f _position, int _radius, std::shared_ptr<sf::Texture> _texture,
			std::string inText, std::string inText2, TowerType _type,
    std::shared_ptr<GameState> _gameState, std::shared_ptr<sf::Texture> _menutexture);

  //! \brief Установка прямоугольного участка текстуры.
	void setTextureRect(const sf::IntRect& rect);

  //! \brief Деструктор.
  ~TowerButton() = default;

  //! \brief Тип башни.
	TowerType getTowerType();

  //! \brief Установка прозрачности.
	void setTransparency(const int transparency);

  //! \brief Обновление положения кнопки башни в меню.
	void update() override;

  //! \brief Отображение кнопки башни в меню.
	void render(sf::RenderWindow& _window) override;

  //! \brief Отображение текста характеристик башни.
	void renderText(sf::RenderWindow& _window) ;

private:
	TowerType towerType;
	std::shared_ptr<GameState> gameState;
  sf::Font font;
	void onClick() override;
	void onMouseEnter() override;
	void onMousePressed() override;
	void onMouseLeave() override;
	sf::CircleShape graphic;
  bool displayText{ false };
	sf::Text towerButtonText;
	sf::Text towerButtonText2;
	sf::RectangleShape towerTextBack;
};

#endif
