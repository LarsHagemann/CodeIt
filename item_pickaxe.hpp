#pragma once
#include "item.hpp"

class ItemPickaxe : public Item
{
public:
	ItemPickaxe(Game& game);
	bool onUseHandler(sf::Vector2u target) override;
	static std::shared_ptr<ItemPickaxe> create(Game& game);
};