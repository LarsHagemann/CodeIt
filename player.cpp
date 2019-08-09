#include "player.hpp"
#include "game.hpp"
#include "item_pickaxe.hpp"

Player::Player(Game& game) : 
	Entity(game),
	m_inventoryIndex(0),
	m_rotation(0)
{
	m_sprite.setTexture(game.resources().loadTexture("player.png"));
	//m_inventory[0] = ItemPickaxe::create(m_game);
}

std::shared_ptr<Player> Player::create(Game& game)
{
	return std::make_shared<Player>(game);
}

void Player::turnRight()
{
	m_rotation = (m_rotation + 1) % 4;
}

void Player::inventorySelectNext()
{
	m_inventoryIndex = (m_inventoryIndex + 1) % m_inventory.size();
}

sf::Vector2u Player::getTarget() const
{
	auto move = getMoveDirection();
	sf::Vector2i target = static_cast<sf::Vector2i>(getPosition());

	target.x += move.x;
	target.y += move.y;
	m_game.getMap().verifyTile(target);

	return static_cast<sf::Vector2u>(target);
}

sf::Vector2<char> Player::getMoveDirection() const
{
	sf::Vector2<char> move;
	if (m_rotation == 0)
		move = { 1, 0 };
	else if (m_rotation == 1)
		move = { 0, 1 };
	else if (m_rotation == 2)
		move = { -1, 0 };
	else if (m_rotation == 3)
		move = { 0, -1 };
	return move;
}

bool Player::inventoryAdd(ItemPtr item)
{
	for (auto i = 0u; i < m_inventory.size(); ++i)
	{
		if (!m_inventory[i])
		{
			m_inventory[i] = item;
			return true;
		}
	}
	return false;
}

void Player::removeInventoryItem(ItemPtr item)
{
	for (auto i = 0u; i < m_inventory.size(); ++i)
	{
		if (m_inventory[i] == item)
			m_inventory[i] = nullptr;
	}
}

void Player::update()
{

}

void Player::draw(sf::RenderWindow& target, sf::RenderStates states)
{
	drawInventory(target, states);
	const auto texSize = m_sprite.getTexture()->getSize();
	const auto tilesize = m_game.getMap().getTileSize();
	const auto scale = std::min(
		tilesize / texSize.x,
		tilesize / texSize.y
	);
	m_sprite.setOrigin({ texSize.x / 2.f, texSize.y / 2.f });
	states.transform.translate(m_game.getMap().mapToPixelCoords(m_position));
	states.transform.translate(tilesize / 2.f, tilesize / 2.f);
	states.transform.scale(scale, scale);
	states.transform.rotate(m_rotation * 90.f);
	target.draw(m_sprite, states);
}

void Player::drawInventory(sf::RenderWindow& target, sf::RenderStates states) const
{
	const auto mapSize = m_game.getMap().getSize();
	const auto itemSize = std::min(
		(m_game.getGameSize().x - mapSize.x * m_game.getMap().getTileSize())
		- 10.f,
		m_game.getGameSize().y / 10.2f);
	const auto itemXPos = m_game.getGameSize().x - itemSize * 1.1f;
	const auto itemYOffset = itemSize * 0.1f;

	std::vector<unsigned> indeces;
	for (auto i = 0U; i < m_inventory.size(); ++i)
		if (i != m_inventoryIndex)
			indeces.push_back(i);
	indeces.push_back(m_inventoryIndex);

	for (auto i : indeces)
	{
		sf::RectangleShape item;
		if (i == m_inventoryIndex)
		{
			item.setOutlineColor(sf::Color::Red);
			item.setOutlineThickness(4.f);
		}
		else
		{
			item.setOutlineColor(sf::Color::Blue);
			item.setOutlineThickness(2.f);
		}
		item.setSize({ itemSize, itemSize });
		item.setFillColor(sf::Color::White);
		item.setPosition(
			{
				itemXPos,
				itemYOffset + i * itemSize
			}
		);
		target.draw(item, states);
		sf::RenderStates temp;
		temp.transform.translate(itemXPos, itemYOffset + i * itemSize);
		if (m_inventory[i])
			m_inventory[i]->draw(target, temp, itemSize);
	}
}
