#pragma once
#include "item.hpp"
#include "tiles.hpp"
#include "player.hpp"
#include "map.hpp"

class Game;

class Handler
{
private:
	Game& m_game;
	std::shared_ptr<Player> m_player;
	Map& m_map;
	unsigned m_steps;
	unsigned m_baseTimeoff;
private:
	void updateSteps(unsigned steps, const char* msg);
public:
	Handler(Game& game);
	void setBaseTimeoff(unsigned ms) { m_baseTimeoff = ms; }

	/*player control*/
	void movePlayerForward();
	void turnPlayerRight();
	void useItem();
	unsigned inventoryIndex();
	void inventorySelectNext();
	ItemId inventoryItem();
	void interactFront();
	/*map control*/
	TileInfo infoFront();
	TileInfo getTileInfo(sf::Vector2u tileId);
	unsigned getCurrentStepCount() const { return m_steps; }
};