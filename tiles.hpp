#pragma once
#include <unordered_map>
#include "item.hpp"

enum Tiles
{
	TILE_GROUND,
	TILE_DIRT,
	TILE_WALL,
	TILE_GATE,
	TILE_BOX,

	TILE_NONE
};

struct TileInfo
{
	bool walkable;
	ItemId destructableBy;
	Tiles destructsTo;
};

extern const std::unordered_map<Tiles, TileInfo> sTileInfo;

