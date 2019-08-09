#include "map.hpp"
#include "game.hpp"

sf::Vector2f Map::getTilesizeOffset(float tilesize) const
{
	const auto gameSize = m_game.getGameSize();
	const auto tileSizeY = gameSize.y / m_size.y;
	return { 
		0.f, 
		(tileSizeY - tilesize) * m_size.y / 2.f
	};
}

TileInfo Map::getTileInfo(sf::Vector2u target) const
{
	auto tileId = (Tiles)m_tiles.at(target.y * m_size.x + target.x);
	return sTileInfo.at(tileId);
}

void Map::updateTile(sf::Vector2u tileId, Tiles to)
{
	m_tiles.at(tileId.y * m_size.x + tileId.x) = to;
}

Map::Map(Game& game) :
	m_game(game)
{
}

float Map::getTileSize() const
{
	const auto gameSize = m_game.getGameSize() - sf::Vector2f{ 66.f, 0.f };
	const auto tileSizeX = gameSize.x / m_size.x;
	const auto tileSizeY = gameSize.y / m_size.y;
	return std::min(tileSizeX, tileSizeY);
}

sf::Vector2f Map::mapToPixelCoords(sf::Vector2u mapCoords) const
{
	auto tilesize = getTileSize();
	auto offset = getTilesizeOffset(tilesize);
	auto x = tilesize * mapCoords.x;
	auto y = tilesize * mapCoords.y;
	return sf::Vector2f(x, y) + offset;
}

void Map::update()
{
}

void Map::draw(sf::RenderWindow& window, sf::RenderStates states)
{
	// draw the map here:
	const auto tilesize = getTileSize();
	const auto offset = getTilesizeOffset(tilesize);
	const auto xWidth = tilesize * m_size.x;
	const auto yHeight = tilesize * m_size.y;

	states.transform.translate(offset);

	{
		for (auto i = 0u; i < m_tiles.size(); ++i)
		{
			auto tile = m_tiles.at(i);
			const auto x = i % m_size.x;
			const auto y = i / m_size.x;

			auto xPos = x * tilesize;
			auto yPos = y * tilesize;

			sf::RectangleShape block;
			block.setPosition({ xPos, yPos });
			block.setSize({ tilesize, tilesize });
			if (tile == TILE_DIRT)
				block.setFillColor(sf::Color(100, 50, 50));
			else if (tile == TILE_WALL)
				block.setFillColor(sf::Color::Black);
			else if (tile == TILE_GROUND)
				block.setFillColor(sf::Color(120, 120, 120));
			else if (tile == TILE_GATE)
				block.setFillColor(sf::Color(200, 130, 130));

			if (sf::Vector2u{ x,y } == m_goal)
			{
				block.setSize(block.getSize() - sf::Vector2f{10.f, 10.f});
				block.move({ 5.5f, 5.5f });
				block.setOutlineThickness(5.0f);
				block.setOutlineColor(sf::Color::Yellow);
			}

			window.draw(block, states);
		}
	}

	for (auto i = 0u; i <= m_size.x; ++i)
	{
		sf::RectangleShape line;
		line.setPosition({ i * tilesize, 0.f });
		line.setSize({ 1.f, yHeight });
		window.draw(line, states);
	}

	for (auto i = 0u; i <= m_size.y; ++i)
	{
		sf::RectangleShape line;
		line.setPosition({ 0.f, i * tilesize });
		line.setSize({ xWidth, 1.f });
		window.draw(line, states);
	}

	//for (auto& entity : m_entities)
	//	entity.draw(window, states);
}

void Map::verifyTile(sf::Vector2i tile)
{
	if ((tile.x >= 0 && tile.x < static_cast<int>(m_size.x))
		&& (tile.y >= 0 && tile.y < static_cast<int>(m_size.y)))
		return;
	throw std::exception("Invalid move operation");
}

bool Map::load(sf::Vector2u size, std::vector<unsigned>&& data)
{
	m_size = size;
	m_tiles = std::move(data);
	return m_size.x * m_size.y == m_tiles.size();
}
