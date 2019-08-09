#include "item_key.hpp"
#include "game.hpp"

ItemKey::ItemKey(Game& game) :
	Item(ITEM_KEY, game)
{
	m_inventoryIcon.setTexture(m_game.resources().loadTexture("key.png"));
}

bool ItemKey::onUseHandler(sf::Vector2u target)
{
	auto tileInfo = m_game.getMap().getTileInfo(target);
	if (tileInfo.destructableBy == ITEM_KEY)
	{
		m_game.getMap().updateTile(target, tileInfo.destructsTo);
		m_game.getPlayer()->removeInventoryItem(shared_from_this());
		return true;
	}
	else printf_s("Cannot use key on the target tile\n");
	return false;
}

std::shared_ptr<ItemKey> ItemKey::create(Game& game)
{
	return std::make_shared<ItemKey>(game);
}
