#pragma once

#ifndef TILE_H
#define TILE_H


#include	<stdbool.h>

typedef	struct
{
	bool tile;

}tile_t;

void	wash_Tile(tile_t tile);
void	mess_Tile(tile_t tile);
bool	is_clean_Tile(tile_t tile);
bool	is_dirty_Tile(tile_t tile);

#endif //TILE_H