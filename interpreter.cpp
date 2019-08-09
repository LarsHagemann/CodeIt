#include "interpreter.hpp"
#include "entity_box.hpp"
#include "entity_chest.hpp"
#include "entity_plate.hpp"
#include "entity_warp.hpp"
#include "entity_goblin.hpp"
#include "entity_flamethrower.hpp"
#include "item_key.hpp"
#include "item_pickaxe.hpp"

Token Interpreter::expect(ETokenType type)
{
	if (m_current.type != type)
		throw std::exception("Expected different token type!");
	auto temp = m_current;
	advance();
	return temp;
}

Token Interpreter::advance()
{
	m_previous = m_current;
	m_current = m_scanner.scanToken();
	return m_current;
}

bool Interpreter::match(ETokenType type)
{
	if (m_current.type == type)
	{
		advance();
		return true;
	}
	return false;
}

EntityPtr Interpreter::make_chest()
{
	auto entity = ChestEntity::create(m_game);
	expect(T_PAREN_LEFT);
	auto pos = make_vector();
	entity->setPosition(pos);
	expect(T_COMMA);
	auto itemType = expect(T_IDENTIFIER).lexeme;
	if (itemType == "key")
		entity->setStoredItem(ItemKey::create(m_game));
	else if (itemType == "pickaxe")
		entity->setStoredItem(ItemPickaxe::create(m_game));
	expect(T_PAREN_RIGHT);
	return entity;
}

EntityPtr Interpreter::make_goblin()
{
	auto goblin = GoblinEntity::create(m_game);
	expect(T_PAREN_LEFT);
	auto pos = make_vector();
	goblin->addToPath(pos);
	goblin->setPosition(pos);
	while (match(T_COMMA))
	{
		auto node = make_vector();
		goblin->addToPath(node);
	}
	expect(T_PAREN_RIGHT);
	return goblin;
}

EntityPtr Interpreter::make_flamethrower()
{
	auto ft = FlamethrowerEntity::create(m_game);
	expect(T_PAREN_LEFT);
	auto pos = make_vector();
	expect(T_COMMA);
	auto dir = make_vectori();
	expect(T_COMMA);
	auto strength = std::stoul(expect(T_NUMBER).lexeme);
	expect(T_COMMA);
	auto frequency = std::stoul(expect(T_NUMBER).lexeme);
	expect(T_COMMA);
	auto cycle = std::stoul(expect(T_NUMBER).lexeme);
	ft->setPosition(pos);
	ft->setDirection(dir);
	ft->setStrength(strength);
	ft->setFrequency(frequency);
	ft->setCurrentCycle(cycle);
	expect(T_PAREN_RIGHT);
	return ft;
}

EntityPtr Interpreter::make_box()
{
	expect(T_PAREN_LEFT);
	auto pos = make_vector();
	expect(T_PAREN_RIGHT);
	auto entity = BoxEntity::create(m_game);
	entity->setPosition(pos);
	return entity;
}

EntityPtr Interpreter::make_plate()
{
	auto entity = PlateEntity::create(m_game);
	expect(T_PAREN_LEFT);
	auto pos = make_vector();
	expect(T_COMMA);
	auto type = expect(T_IDENTIFIER).lexeme;
	if (type == "change_tile")
	{
		expect(T_PAREN_LEFT);
		auto dest = make_vector();
		expect(T_COMMA);
		auto tileA = (Tiles)std::stoul(expect(T_NUMBER).lexeme);
		expect(T_COMMA);
		auto tileB = (Tiles)std::stoul(expect(T_NUMBER).lexeme);
		expect(T_PAREN_RIGHT);
		entity->setInfo(PlateEntity::ChangeTileInfo{
				tileA,
				tileB,
				dest
			}
		);
	}
	expect(T_PAREN_RIGHT);
	entity->setPosition(pos);
	return entity;
}

void Interpreter::make_warp(std::vector<EntityPtr>& ent)
{
	expect(T_PAREN_LEFT);
	auto a = make_vector();
	expect(T_COMMA);
	auto b = make_vector();
	auto wa = WarpEntity::create(m_game);
	auto wb = WarpEntity::create(m_game);
	wa->setDestination(b);
	wa->setPosition(a);
	wb->setDestination(a);
	wb->setPosition(b);
	wb->setUUID(wa->getUUID());
	ent.push_back(wa);
	ent.push_back(wb);
	expect(T_PAREN_RIGHT);
}

Interpreter::Interpreter(std::ifstream& input, Game& game) :
	m_scanner(input),
	m_game(game)
{
	m_current.type = T_INVALID;
	advance();
}

sf::Vector2u Interpreter::make_vector()
{
	expect(T_PAREN_LEFT);
	auto x = std::stoul(expect(T_NUMBER).lexeme);
	expect(T_COMMA);
	auto y = std::stoul(expect(T_NUMBER).lexeme);
	expect(T_PAREN_RIGHT);
	return { x,y };
}

sf::Vector2i Interpreter::make_vectori()
{
	expect(T_PAREN_LEFT);
	auto x = std::stol(expect(T_NUMBER).lexeme);
	expect(T_COMMA);
	auto y = std::stol(expect(T_NUMBER).lexeme);
	expect(T_PAREN_RIGHT);
	return { x,y };
}

std::vector<unsigned> Interpreter::make_map()
{
	std::vector<unsigned> res;
	expect(T_CBRACKET_LEFT);
	while (match(T_NUMBER))
		res.push_back(std::stoul(m_previous.lexeme));
	expect(T_CBRACKET_RIGHT);
	return res;
}

std::vector<EntityPtr> Interpreter::make_entities()
{
	std::vector<EntityPtr> res;
	expect(T_SBRACKET_LEFT);
	while (match(T_IDENTIFIER))
	{
		auto id = m_previous.lexeme;
		EntityPtr entity;
		if (id == "chest")
			entity = make_chest();
		else if (id == "warp")
			make_warp(res);
		else if (id == "goblin")
			entity = make_goblin();
		else if (id == "flamethrower")
			entity = make_flamethrower();
		else if (id == "box")
			entity = make_box();
		else if (id == "plate")
			entity = make_plate();
		else printf_s("Unknown entity %s\n", id.data());
		
		if (entity)
			res.push_back(entity);

		if (!match(T_COMMA))
			break;
	}
	expect(T_SBRACKET_RIGHT);
	return res;
}
