#ifndef MAP_H
#define MAP_H

#include "mjson.h"
#include <stdint.h>

#define MAX_GRID        32
#define MAX_CELL_AMOUNT 1024

#define MOUNTAIN        3.0f
#define FLAT_GROUND     -1.0f
#define PATH            5
#define START           8.3f
#define END             0.5f 

/*
* @brief Gets the grid values from a JSON file
* 
* @parm[in] map         A 32x32 array, extracted values placed here
*/
void map_extract(float map[MAX_GRID][MAX_GRID]);

/*
* @brief Gets the start and end positions from user
* 
* @param[in] map        A 32x32 array, positions placed here
* @param[in] start      Array of values for start x,y position
* @param[in] end        Array of values for end x,y position
*/
void map_get_positions(float map[MAX_GRID][MAX_GRID], uint8_t start[2], uint8_t end[2]);

/*
* @brief Prints out formatted map in console
* 
* @parm[in] map         A 32x32 array of map
*/
void map_print(float map[MAX_GRID][MAX_GRID]);

#endif /* MAP_H */