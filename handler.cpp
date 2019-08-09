#include "handler.hpp"
#include "game.hpp"
#include <Windows.h>

void Handler::updateSteps(unsigned steps, const char* msg)
{
	if (!m_game.isRunning())
		throw(std::exception("Game stopped before handler finished"));
	m_game.update();
	if (steps == 0)
		return;
	printf_s("[+%u] %s\n", steps, msg);
	m_steps += steps;
	Sleep(steps * m_baseTimeoff);
}

Handler::Handler(Game& game) :
	m_game(game),
	m_map(game.getMap()),
	m_player(game.getPlayer()),
	m_baseTimeoff(25)
{
}

void Handler::movePlayerForward()
{
	updateSteps(10, "Moving forward");

	auto target = m_player->getTarget();
	auto move = m_player->getMoveDirection();
	auto tile = m_map.getTileInfo(target);

	if (tile.walkable)
	{
		auto list = m_game.findEntity(target);
		for (auto entity : list)
			entity->onPlayerInteract();
		if (list.empty())
			m_player->move(sf::Vector2i(move));
	}
	else
		updateSteps(40, "\tObstacle ahead!");
}

void Handler::turnPlayerRight()
{
	updateSteps(6, "Rotating...");
	m_player->turnRight();
}

void Handler::useItem()
{
	auto item = m_player->getInventoryItem();
	if (item)
	{
		updateSteps(item->getUseTime(), "using item");
		if (!item->onUseHandler(m_player->getTarget()))
			updateSteps(15, "\tUnable to use item");
	}
	else updateSteps(25, "\tNo item selected!");
}

unsigned Handler::inventoryIndex()
{
	updateSteps(0, "inventory using");
	return m_player->getInventoryIndex();
}

ItemId Handler::inventoryItem()
{
	auto item = m_player->getInventoryItem();
	if (item)
		return m_player->getInventoryItem()->getItemId();
	else return ITEM_NONE;
}

void Handler::interactFront()
{
	updateSteps(5, "Interacting");
	auto list = m_game.findEntity(m_player->getTarget());
	for (auto entity : list)
		entity->onPlayerInteract();
}

void Handler::inventorySelectNext()
{
	updateSteps(1, "Selecting next item");
	m_player->inventorySelectNext();
}

TileInfo Handler::infoFront()
{
	auto target = m_player->getTarget();
	return getTileInfo(target);
}

TileInfo Handler::getTileInfo(sf::Vector2u tileId)
{
	updateSteps(1, "Tile info");
	return m_map.getTileInfo(tileId);
}
