#pragma once
#include "entity.hpp"
#include "item.hpp"

class ChestEntity : public Entity
{
private:
	ItemPtr m_storedItem;
public:
	ChestEntity(Game& game);

	static std::shared_ptr<ChestEntity> create(Game& game);

	void setStoredItem(ItemPtr item) { m_storedItem = item; }

	virtual void onPlayerInteract() override;
	virtual void draw(sf::RenderWindow& target, sf::RenderStates states) override;
	virtual void update() override;
	
};
