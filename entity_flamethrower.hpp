#pragma once
#include "entity.hpp"

class FlamethrowerEntity : public Entity
{
private:
	sf::Vector2i m_direction;
	unsigned m_strength;
	unsigned m_frequency;
	unsigned m_currentCycle;
private:
	std::vector<sf::Vector2u> getTargets() const;
public:
	FlamethrowerEntity(Game& game);

	static std::shared_ptr<FlamethrowerEntity> create(Game& game);

	void setStrength(unsigned s) { m_strength = s; }
	void setFrequency(unsigned f) { m_frequency = f; }
	void setDirection(sf::Vector2i dir) { m_direction = dir; }
	void setCurrentCycle(unsigned c) { m_currentCycle = c; }

	virtual void onPlayerInteract() override;
	virtual void draw(sf::RenderWindow& target, sf::RenderStates states) override;
	virtual void update() override;

};

