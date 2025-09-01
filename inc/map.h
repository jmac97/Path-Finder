#ifndef MAP_H
#define MAP_H

#include "mjson.h"
#include <stdint.h>

#define MAX_GRID 32
#define MAX_CELL_AMOUNT 1024

/*
* @brief Gets the grid values from a JSON file
* 
* @parm[in] map         A 32x32 array, extracted values placed here
*/
void map_extract(float map[32][32]);

/*
* @brief Gets the start and end positions from user
* 
* @param[in] map        A 32x32 array, positions placed here
* @param[in] start      Array of values for start x,y position
* @param[in] end        Array of values for end x,y position
*/
void map_get_positions(float map[32][32], uint8_t start[2], uint8_t end[2]);

/*
* @brief Prints out formatted map in console
* 
* @parm[in] map         A 32x32 array of map
*/
void map_print(float map[32][32]);

#endif /* MAP_H */