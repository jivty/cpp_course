#ifndef TD_CLICKABLE_H
#define TD_CLICKABLE_H

#include <SFML/Graphics.hpp>

//! \brief Обеспечивание реагирования объектов на Mouse.
class Clickable {
public:

  //! \brief Умолчательный конструктор.
  Clickable() = default;

  //! \brief Конструктор по позиции и размеру.
  Clickable(sf::Vector2f _position, sf::Vector2f _size);

  //! \brief Виртуальный деструктор.
  virtual ~Clickable();

  //! \breif Получение позиции.
  const sf::Vector2f& getPosition() const;

  //! \brief Установка позиции.
  void setPosition(const sf::Vector2f& _position);

  //! \brief Получение размера.
  const sf::Vector2f& getSize() const;

  //! \brief Установка размера.
  void setSize(const sf::Vector2f& _size);

  //! \brief Обрабатывание события.
  void process(const sf::Event& event, const sf::Vector2i& mousePos);

  //! \brief Обновление.
  virtual void update() = 0;

  //! \brief Отображение.
  virtual void render(sf::RenderWindow& _window) = 0;

  static const int gridSize{ 40 }; //!< Размер ячейки игрового поля, стандартизирующий масштаб.

private:
  bool isHovering{ 0 };
  bool isPressed{ 0 };
  sf::Vector2f position{ sf::Vector2f(0, 0) };
  sf::Vector2f size{ sf::Vector2f(100, 100) };
	virtual bool insideShape(const sf::Vector2i& mousePos);

	virtual void onMouseEnter();
	virtual void onMousePressed();
	virtual void onMouseLeave();
	virtual void onClick() = 0;
};

#endif
