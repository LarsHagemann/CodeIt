#include "item_pickaxe.hpp"
#include "game.hpp"

ItemPickaxe::ItemPickaxe(Game& game) :
	Item(ItemId::ITEM_PICKAXE, game)
{
	m_inventoryIcon.setTexture(game.resources().loadTexture("pickaxe.png"));
}

bool ItemPickaxe::onUseHandler(sf::Vector2u target)
{
	auto& map = m_game.getMap();
	auto tileinfo = map.getTileInfo(target);
	if (tileinfo.destructableBy == ITEM_PICKAXE)
		map.updateTile(target, tileinfo.destructsTo);
	else return false;
	return true;
}

std::shared_ptr<ItemPickaxe> ItemPickaxe::create(Game& game)
{
	return std::make_shared<ItemPickaxe>(game);
}
