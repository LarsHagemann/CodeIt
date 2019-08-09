#include "entity_chest.hpp"
#include "game.hpp"

ChestEntity::ChestEntity(Game& game) :
	Entity(game)
{
	m_sprite.setTexture(game.resources().loadTexture("chest.png"));
}

std::shared_ptr<ChestEntity> ChestEntity::create(Game& game)
{
	return std::make_shared<ChestEntity>(game);
}

void ChestEntity::onPlayerInteract()
{
	auto player = m_game.getPlayer();
	if (player->inventoryAdd(m_storedItem))
		m_game.removeEntity(shared_from_this());
	else printf_s("Your inventory is full. Please empty a slot first!\n");
}

void ChestEntity::draw(sf::RenderWindow& target, sf::RenderStates states)
{
	Entity::draw(target, states);
	states.transform.translate(
		m_game.getMap().mapToPixelCoords(m_position)
	);
	if (m_storedItem)
	{
		auto size = m_game.getMap().getTileSize() * .75f;
		auto offset = (m_game.getMap().getTileSize() - size) / 2.f;
		states.transform.translate(offset, offset);
		m_storedItem->draw(
			target,
			states,
			size
		);
	}
}

void ChestEntity::update()
{
}
