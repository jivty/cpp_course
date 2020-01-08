#ifndef TD_CLICKABLE_H
#define TD_CLICKABLE_H

#include <SFML/Graphics.hpp>

class Clickable {
public:
	Clickable(sf::Vector2f _position = sf::Vector2f(0, 0), sf::Vector2f _size =
			sf::Vector2f(100, 100));
	virtual ~Clickable();

	const sf::Vector2f& getPosition() const;
	void setPosition(const sf::Vector2f& _position);

	const sf::Vector2f& getSize() const;
	void setSize(const sf::Vector2f& _size);

	void process(const sf::Event& event, const sf::Vector2i& mousePos);

	virtual void update() = 0;
	virtual void render(sf::RenderWindow& _window) = 0;

	void setDebug(bool mode);

  static const int gridSize{ 40 };

private:
	bool isHovering = 0, isPressed = 0, debug = 0;
	sf::Vector2f position, size;
	virtual bool insideShape(const sf::Vector2i& mousePos);

	virtual void onMouseEnter();
	virtual void onMousePressed();
	virtual void onMouseLeave();
	virtual void onClick() = 0;
};

#endif
