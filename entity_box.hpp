#pragma once
#include "entity.hpp"

class BoxEntity : public Entity
{
public:
	BoxEntity(Game& game);

	static std::shared_ptr<BoxEntity> create(Game& game);

	virtual void onPlayerInteract() override;
	virtual void update() override;

};
