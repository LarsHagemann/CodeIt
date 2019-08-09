#pragma once
#include "resourcemanager.hpp"
#include "map.hpp"
#include "player.hpp"
#include "handler.hpp"

#include <Windows.h>
#include <thread>
#include <memory>

using EntityList = std::vector<EntityPtr>;
using LogicCallback = std::function<void(Handler&)>;

class Game
{
private:
	ResourceManager m_resourceManager;
	Map m_map;
	std::unique_ptr<sf::RenderWindow> m_window;
	EntityList m_entities;
	std::shared_ptr<Player> m_player;
	sf::Vector2f m_cachedSize;
	Handler m_handler;
	bool m_begun;
	bool m_ready;
	bool m_isRunning;
	std::thread m_gameThread;
private:
	void runIntern();
public:
	Game(sf::Vector2u size);
	~Game();

	ResourceManager& resources() { return m_resourceManager; }
	Map& getMap() { return m_map; }
	Handler& getHandler() { return m_handler; }
	std::shared_ptr<Player> getPlayer() { return m_player; }
	sf::Vector2f getGameSize() const;
	unsigned getStepCount() const { return m_handler.getCurrentStepCount(); }
	EntityList findEntity(sf::Vector2u pos, uuid ignore = 0);
	void removeEntity(EntityPtr entity);

	void run();
	void update();

	bool isWon() const;
	bool isRunning() const { return m_window && m_window->isOpen(); }
	bool isReady() const { return m_ready; }

	bool setupLevel(unsigned level);
};

static void run(LogicCallback&& logic, unsigned level, unsigned ms = 25)
{
	Game game({ 1080u, 720u });
	if (game.setupLevel(level))
	{
		game.run();
		try {
			while (!game.isReady()) Sleep(50);
			auto& handler = game.getHandler();
			handler.setBaseTimeoff(ms);
			logic(handler);
			if (game.isWon())
				printf_s(
					"You have won the game in %u steps!\n", 
					game.getStepCount()
				);
			else printf_s("Something didn't quite work yet!\n");
			Sleep(1000);
		}
		catch (std::exception & e)
		{
			printf_s("%s\n", e.what());
			getchar();
		}
	}
	else printf_s("Unable to setup level %u\n", level);
}
