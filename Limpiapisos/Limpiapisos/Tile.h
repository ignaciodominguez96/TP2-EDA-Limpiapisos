#pragma once

#ifndef TILE_H
#define TILE_H


#include	<stdbool.h>


void	wash_Tile(bool* tile);
void	mess_Tile(bool* tile);
bool	is_clean_Tile(bool* tile);
bool	is_dirty_Tile(bool* tile);

#endif //TILE_H