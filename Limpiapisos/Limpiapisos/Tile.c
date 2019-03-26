#include "Tile.h"

void	wash_Tile(bool* tile) {
	*tile = true;
}
void	mess_Tile(bool* tile) {
	*tile = false;
}
bool	is_clean_Tile(bool* tile) {
	return *tile;
}
bool	is_dirty_Tile(bool* tile) {
	return !(*tile);
}