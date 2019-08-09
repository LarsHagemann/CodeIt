#include "entity_plate.hpp"
#include "game.hpp"

void PlateEntity::changeTileHandler()
{
	auto entities = m_game.findEntity(m_position, getUUID());
	if (!entities.empty())
		m_game.getMap().updateTile(
			m_data.onTileChange.m_destination, 
			m_data.onTileChange.m_tileOnTrigger
		);
	else
		m_game.getMap().updateTile(
			m_data.onTileChange.m_destination, 
			m_data.onTileChange.m_defaultTile
		);
}

PlateEntity::PlateEntity(Game& game) :
	Entity(game),
	m_data({}),
	m_type(P_CHANGE_TILE)
{
	m_data.onTileChange = { TILE_GROUND, TILE_GROUND, {0u, 0u} };
	m_sprite.setTexture(m_game.resources().loadTexture("plate.png"));
}

std::shared_ptr<PlateEntity> PlateEntity::create(Game& game)
{
	return std::make_shared<PlateEntity>(game);
}

void PlateEntity::setInfo(ChangeTileInfo info)
{
	m_data.onTileChange = info;
	m_type = P_CHANGE_TILE;
}

void PlateEntity::onPlayerInteract()
{
	m_game.getPlayer()->setPosition(m_position);
}

void PlateEntity::update()
{
	if (m_type == P_CHANGE_TILE)
		changeTileHandler();
}
