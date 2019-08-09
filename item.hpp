#pragma once
#include "element.hpp"
#include <unordered_map>
#include <functional>
#include <SFML/Graphics.hpp>

class Game;

enum ItemId
{
	ITEM_NONE,
	ITEM_PICKAXE,
	ITEM_KEY,

	ITEM_COUNT
};

class Item : public Element, public std::enable_shared_from_this<Item>
{
protected:
	sf::Sprite m_inventoryIcon;
	ItemId m_itemId;
	unsigned m_useTime;
	Game& m_game;
public:
	Item(ItemId myId, Game& game);
	virtual bool onUseHandler(sf::Vector2u target) = 0;
	ItemId getItemId() const { return m_itemId; }
	unsigned getUseTime() const { return m_useTime; }
	void draw(
		sf::RenderTarget& target, 
		sf::RenderStates states,
		float itemSize) const;
};

using ItemPtr = std::shared_ptr<Item>;
