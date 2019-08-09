#include "entity_flamethrower.hpp"
#include "game.hpp"

std::vector<sf::Vector2u> FlamethrowerEntity::getTargets() const
{
	std::vector<sf::Vector2u> targets;
	for (auto i = 1u; i <= m_strength; ++i)
	{
		auto target = sf::Vector2u{
			m_position.x + m_direction.x * i,
			m_position.y + m_direction.y * i
		};
		targets.emplace_back(target);
	}
	return targets;
}

FlamethrowerEntity::FlamethrowerEntity(Game& game) :
	Entity(game),
	m_strength(0),
	m_frequency(0),
	m_currentCycle(0)
{
	m_sprite.setTexture(m_game.resources().loadTexture("fire.png"));
}

std::shared_ptr<FlamethrowerEntity> FlamethrowerEntity::create(Game& game)
{
	return std::make_shared<FlamethrowerEntity>(game);
}

void FlamethrowerEntity::onPlayerInteract()
{
}

void FlamethrowerEntity::draw(sf::RenderWindow& target, sf::RenderStates states)
{
	Entity::draw(target, states);
	if (!m_currentCycle)
	{
		auto targets = getTargets();
		for (auto tile : targets)
		{
			sf::RenderStates temp;
			auto pos = m_game.getMap().mapToPixelCoords(tile);
			temp.transform.translate(pos);
			target.draw(m_sprite, temp);
		}
	}
}

void FlamethrowerEntity::update()
{
	m_currentCycle = (m_currentCycle + 1) % m_frequency;
	if (!m_currentCycle)
	{
		auto targets = getTargets();
		for (auto tile : targets)
			if (m_game.getPlayer()->getPosition() == tile)
				throw std::exception("You burned yourself :(");
	}
}
