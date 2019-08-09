#include "game.hpp"
#include "helper.hpp"
#include "interpreter.hpp"

#include <fstream>

bool Game::setupLevel(unsigned level)
{
	std::string levelFile = "Levels/level" + tostring(level) + ".dat";
	if (!fs::exists(levelFile))
		return false;

	std::ifstream fileIn(levelFile);
	if (!fileIn.good())
		return false;

	try {
		Interpreter ip(fileIn, *this);
		auto size = ip.make_vector();
		auto begin = ip.make_vector();
		auto goal = ip.make_vector();

		m_player->setPosition(begin);
		m_map.load(size, ip.make_map());
		m_map.setGoal(goal);

		auto entities = ip.make_entities();
		m_entities.insert(
			m_entities.end(), 
			entities.begin(), 
			entities.end()
		);

		printf_s("%d entities loaded\n", m_entities.size());
		printf_s("Starting level %u\n", level);
	}
	catch (std::exception & e)
	{
		printf_s("%s\n", e.what());
		return false;
	}
	return true;
}

void Game::runIntern()
{
	while (!m_begun) Sleep(50);
	m_window = std::make_unique<sf::RenderWindow>(
		sf::VideoMode(
			static_cast<unsigned>(m_cachedSize.x),
			static_cast<unsigned>(m_cachedSize.y)
		),
		"Game :)"
		);
	m_window->setFramerateLimit(30);
	m_window->setActive(true);
	ShowWindow(m_window->getSystemHandle(), SW_SHOWMAXIMIZED);
	m_isRunning = true;
	sf::Event event;
	while (m_isRunning)
	{
		while (m_window->pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				m_isRunning = false;
				m_window->close();
				break;
			case sf::Event::Resized:
				m_window->setView(sf::View(sf::FloatRect{
						0.f,
						0.f,
						static_cast<float>(event.size.width),
						static_cast<float>(event.size.height)
					}
				));
				m_cachedSize = static_cast<sf::Vector2f>(m_window->getSize());
				break;
			//case sf::Event::KeyPressed:
			//	if (event.key.code == sf::Keyboard::Key::Return)
			//		update();
			//	break;
			default:
				break;
			}
		}
		m_window->clear(sf::Color(200, 200, 200));
		m_map.draw(*m_window, sf::RenderStates::Default);
		for (auto entity : m_entities)
			if (entity)
				entity->draw(*m_window, sf::RenderStates::Default);
		m_window->display();
		if (!m_ready)
			m_ready = true;
	}
}

Game::Game(sf::Vector2u size) :
	m_map(*this),
	m_handler(*this),
	m_cachedSize(sf::Vector2f(size)),
	m_begun(false),
	m_gameThread(&Game::runIntern, this),
	m_ready(false),
	m_player(Player::create(*this))
{
	m_entities.push_back(m_player);
}

Game::~Game()
{
	if (m_window->isOpen())
		m_isRunning = false;
	if (m_gameThread.joinable())
		m_gameThread.join();
}

sf::Vector2f Game::getGameSize() const
{
	return m_cachedSize;
}

EntityList Game::findEntity(sf::Vector2u pos, uuid ignore)
{
	EntityList list;
	for (auto entity : m_entities)
		if (entity->getPosition() == pos && entity->getUUID() != ignore)
			list.push_back(entity);
	return list;
}

void Game::removeEntity(EntityPtr entity)
{
	auto target = std::find(
		m_entities.begin(),
		m_entities.end(),
		entity
	);
	if (target != m_entities.end())
		m_entities.erase(target);
}

void Game::run()
{
	m_begun = true;
}

void Game::update()
{
	for (auto entity : m_entities)
		entity->update();
	m_map.update();
}

bool Game::isWon() const
{
	return m_player->getPosition() == m_map.getGoal();
}
