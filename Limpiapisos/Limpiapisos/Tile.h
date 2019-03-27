#pragma once

#ifndef TILE_H
#define TILE_H


#include	<stdbool.h>


void	wash_Tile(bool* tile);

/*

Limpia la baldosa que se le pasa por parametros

*/


void	mess_Tile(bool* tile);

/*

Ensucia la baldosa que se le pasa por parametros

*/

bool	is_clean_Tile(bool* tile);

/*

Devuelve un bool que indica si la baldosa esta limpia (true) o no 

*/

bool	is_dirty_Tile(bool* tile);

/*

Devuelve un bool que indica si la baldosa esta sucia (true) o no

*/


#endif //TILE_H