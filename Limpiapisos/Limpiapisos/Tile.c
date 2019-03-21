#include "Tile.h"

void	wash_Tile(tile_t* tile) {
	tile->state = 1;
}
void	mess_Tile(tile_t* tile) {
	tile->state = 0;
}
bool	is_clean_Tile(tile_t* tile) {
	return tile->state;
}
bool	is_dirty_Tile(tile_t* tile) {
	return !(tile->state);
}