#include "entity_goblin.hpp"
#include "game.hpp"

GoblinEntity::GoblinEntity(Game& game) :
	Entity(game),
	m_currentPathNode(0)
{
	m_sprite.setTexture(m_game.resources().loadTexture("goblin.png"));
}

std::shared_ptr<GoblinEntity> GoblinEntity::create(Game& game)
{
	return std::make_shared<GoblinEntity>(game);
}

sf::Vector2u GoblinEntity::getTarget() const
{
	auto dir = sf::Vector2i{
		static_cast<int>(m_path[m_currentPathNode].x) - static_cast<int>(m_position.x),
		static_cast<int>(m_path[m_currentPathNode].y) - static_cast<int>(m_position.y)
	};
	auto scale = std::abs(dir.x + dir.y);
	if (scale == 0) return m_position;
	dir = { dir.x / scale, dir.y / scale };
	return sf::Vector2u{
		m_position.x + dir.x,
		m_position.y + dir.y
	};
}

void GoblinEntity::onPlayerInteract()
{
	throw std::exception("A goblin killed you!");
}

void GoblinEntity::update()
{
	auto target = getTarget();
	if (target == m_game.getPlayer()->getPosition())
		throw std::exception("A goblin killed you!");
	if (target == m_path[m_currentPathNode])
		m_currentPathNode = (m_currentPathNode + 1) % m_path.size();
	setPosition(target);
}
