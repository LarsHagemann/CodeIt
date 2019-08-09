#include "entity_warp.hpp"
#include "game.hpp"

WarpEntity::WarpEntity(Game& game) :
	Entity(game)
{
	m_sprite.setTexture(m_game.resources().loadTexture("warp.png"));
}

std::shared_ptr<WarpEntity> WarpEntity::create(Game& game)
{
	return std::make_shared<WarpEntity>(game);
}

void WarpEntity::onPlayerInteract()
{
	m_game.getPlayer()->setPosition(m_destination);
	auto ent = m_game.findEntity(m_destination);
	for (auto entity : ent)
		if (entity->getUUID() != m_id)
			entity->onPlayerInteract();
}

void WarpEntity::update()
{
}
