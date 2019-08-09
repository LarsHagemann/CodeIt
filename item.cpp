#include "item.hpp"

Item::Item(ItemId myId, Game& game) :
	m_itemId(myId),
	m_useTime(10),
	m_game(game)
{
}

void Item::draw(
	sf::RenderTarget& target, 
	sf::RenderStates states,
	float itemSize) const
{
	if (m_inventoryIcon.getTexture())
	{
		auto texSize = m_inventoryIcon.getTexture()->getSize();
		auto scale = std::min(
			itemSize / texSize.x,
			itemSize / texSize.y
		);
		states.transform.scale(scale, scale);
		target.draw(m_inventoryIcon, states);
	}
}
