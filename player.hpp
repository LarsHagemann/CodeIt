#pragma once
#include "entity.hpp"
#include "item.hpp"
#include <array>

class Player : public Entity
{
private:
	std::array<ItemPtr, 10> m_inventory;
	unsigned m_inventoryIndex;
	unsigned m_rotation;
public:
	Player(Game& game);
	static std::shared_ptr<Player> create(Game& game);

	void setPosition(sf::Vector2u pos) { m_position = pos; }
	void move(sf::Vector2i dir) { m_position.x += dir.x; m_position.y += dir.y; }
	void turnRight();
	void inventorySelectNext();

	unsigned getInventoryIndex() const { return m_inventoryIndex; }
	ItemPtr getInventoryItem() { return m_inventory[m_inventoryIndex]; }

	sf::Vector2u getPosition()  const { return m_position; }
	sf::Vector2u getTarget() const;
	sf::Vector2<char> getMoveDirection() const;
	bool inventoryAdd(ItemPtr item);
	void removeInventoryItem(ItemPtr item);

	void onPlayerInteract() override {}
	void update() override;
	void draw(sf::RenderWindow& target, sf::RenderStates states) override;
	void drawInventory(sf::RenderWindow& target, sf::RenderStates states) const;
};
