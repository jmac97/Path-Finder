#ifndef MAP_H
#define MAP_H

#include "mjson.h"
#include <stdint.h>

#define MAX_GRID 32

bool map_extract(float map[32][32]);
void map_get_positions(float map[32][32], uint8_t start[2], uint8_t end[2]);
bool map_print(float map[32][32]);

#endif