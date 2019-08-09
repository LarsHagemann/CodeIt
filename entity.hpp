#pragma once
#include "element.hpp"
#include <SFML/Graphics.hpp>

class Game;

class Entity : public Element, public std::enable_shared_from_this<Entity>
{
protected:
	sf::Sprite m_sprite;
	sf::Vector2u m_position;
	Game& m_game;
	bool m_scaleToTileSize;
public:
	Entity(Game& game) : m_game(game), m_scaleToTileSize(true) {}
	// this is where behaviour goes:
	virtual void update() = 0;
	virtual void onPlayerInteract() = 0;
	virtual void draw(sf::RenderWindow& window, sf::RenderStates states);

	void setPosition(sf::Vector2u pos) { m_position = pos; }
	sf::Vector2u getPosition() const  { return m_position; }
};

using EntityPtr = std::shared_ptr<Entity>;
