#include "entity.hpp"
#include "game.hpp"

void Entity::draw(sf::RenderWindow& window, sf::RenderStates states)
{
	auto pos = m_game.getMap().mapToPixelCoords(m_position);
	auto size = m_game.getMap().getTileSize();
	auto texSize = m_sprite.getTexture()->getSize();
	if (m_scaleToTileSize)
		// scale the sprite
		m_sprite.setScale(
			size / texSize.x,
			size / texSize.y
		);
	else
		// center the sprite
		pos += (sf::Vector2f{size, size} - static_cast<sf::Vector2f>(
				m_sprite.getTexture()->getSize())
			) / 2.f;
	states.transform.translate(pos);
	window.draw(m_sprite, states);
}
