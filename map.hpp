#pragma once
#include <SFML/Graphics.hpp>

#include "entity.hpp"
#include "tiles.hpp"

class Map
{
private:
	sf::Vector2u m_size;
	sf::Vector2u m_goal;
	std::vector<unsigned> m_tiles;
	Game& m_game;
public:
	Map(Game& game);
	float getTileSize() const;
	sf::Vector2u getSize() const { return m_size; }
	sf::Vector2f mapToPixelCoords(sf::Vector2u mapCoords) const;
	sf::Vector2f getTilesizeOffset(float tilesize) const;
	TileInfo getTileInfo(sf::Vector2u target) const;

	void updateTile(sf::Vector2u tileId, Tiles to);

	void update();
	void draw(sf::RenderWindow& window, sf::RenderStates states);

	void verifyTile(sf::Vector2i tile);

	bool load(sf::Vector2u size, std::vector<unsigned>&& data);
	void setGoal(sf::Vector2u goal) { m_goal = goal; }
	sf::Vector2u getGoal() const { return m_goal; }
};
