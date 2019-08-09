#pragma once
#include "entity.hpp"

class GoblinEntity : public Entity
{
private:
	std::vector<sf::Vector2u> m_path;
	unsigned m_currentPathNode;
public:
	GoblinEntity(Game& game);

	static std::shared_ptr<GoblinEntity> create(Game& game);

	void addToPath(sf::Vector2u path) { m_path.push_back(path); }

	sf::Vector2u getTarget() const;

	virtual void onPlayerInteract() override;
	virtual void update() override;

};

