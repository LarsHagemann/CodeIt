#pragma once
#include "entity.hpp"

class WarpEntity : public Entity
{
private:
	sf::Vector2u m_destination;
public:
	WarpEntity(Game& game);

	static std::shared_ptr<WarpEntity> create(Game& game);

	void setDestination(sf::Vector2u dest) { m_destination = dest; }

	virtual void onPlayerInteract() override;
	virtual void update() override;
};
