#pragma once
#include "item.hpp"

class ItemKey : public Item
{
private:

public:
	ItemKey(Game& game);
	virtual bool onUseHandler(sf::Vector2u target) override;

	static std::shared_ptr<ItemKey> create(Game& game);
};

