#include "entity_box.hpp"
#include "game.hpp"

BoxEntity::BoxEntity(Game& game) :
	Entity(game)
{
	m_sprite.setTexture(m_game.resources().loadTexture("box.png"));
}

std::shared_ptr<BoxEntity> BoxEntity::create(Game& game)
{
	return std::make_shared<BoxEntity>(game);
}

void BoxEntity::onPlayerInteract()
{
	auto pPos = m_game.getPlayer()->getPosition();
	auto dir = sf::Vector2i{
		static_cast<int>(pPos.x) - static_cast<int>(m_position.x),
		static_cast<int>(pPos.y) - static_cast<int>(m_position.y)
	};
	m_game.getPlayer()->setPosition(m_position);
	m_position = {
		m_position.x - dir.x,
		m_position.y - dir.y
	};
}

void BoxEntity::update()
{
}
