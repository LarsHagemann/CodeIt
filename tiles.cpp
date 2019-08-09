#include "tiles.hpp"

const std::unordered_map<Tiles, TileInfo> sTileInfo = {
	{ TILE_GROUND, {true, ITEM_NONE, TILE_GROUND}},
	{ TILE_DIRT, {false, ITEM_PICKAXE, TILE_GROUND}},
	{ TILE_WALL,  {false, ITEM_NONE, TILE_WALL}},
	{ TILE_GATE, {false, ITEM_KEY, TILE_GROUND}},
};

