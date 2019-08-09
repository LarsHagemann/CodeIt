#pragma once
#include "scanner.hpp"
#include "helper.hpp"
#include "entity.hpp"
#include <SFML/System/Vector2.hpp>

class Interpreter
{
private:
	Scanner m_scanner;
	Token m_current;
	Token m_previous;
	Game& m_game;
private:
	Token expect(ETokenType type);
	Token advance();
	bool match(ETokenType type);
	EntityPtr make_chest();
	EntityPtr make_goblin();
	EntityPtr make_flamethrower();
	EntityPtr make_box();
	EntityPtr make_plate();
	void make_warp(std::vector<EntityPtr>& ent);
public:
	Interpreter(std::ifstream& input, Game& game);
public:
	sf::Vector2u make_vector();
	sf::Vector2i make_vectori();
	std::vector<unsigned> make_map();
	std::vector<EntityPtr> make_entities();
};