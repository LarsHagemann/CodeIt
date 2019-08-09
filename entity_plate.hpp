#pragma once
#include "entity.hpp"
#include "tiles.hpp"

class PlateEntity : public Entity
{
public:
	enum PlateType
	{
		P_CHANGE_TILE,

		P_NONE
	} m_type;
	struct ChangeTileInfo
	{
		Tiles m_defaultTile;
		Tiles m_tileOnTrigger;
		sf::Vector2u m_destination;
	};
private:
	union Info
	{
		ChangeTileInfo onTileChange;
	} m_data;
	void changeTileHandler();
public:
	PlateEntity(Game& game);

	static std::shared_ptr<PlateEntity> create(Game& game);

	void setInfo(ChangeTileInfo info);

	virtual void onPlayerInteract() override;
	virtual void update() override;
};
