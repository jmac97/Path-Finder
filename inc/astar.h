#ifndef ASTAR_H
#define ASTAR_H

#include <stdint.h>
#include <stdlib.h>
#include "vector.h"
#include "map.h"

#define START_SIZE 50

typedef struct Cell Cell;
typedef struct Vector Vector;
struct Cell
{
  uint8_t x;
  uint8_t y;
  float f;
  float g;
  float h;
  Cell *parent;
}__attribute__((packed));

/*
* @brief Create a path from start to end position using A* 
* 
* @param[in] map        Input map of 32x32 grid
* @param[in] start      Input start position, where [x,y] is [0,1]
* @param[in] end        Input end position, where [x,y] is [0,1]
* @param[in] success    Will equal 1 on finding path, 0 if no path found
*
* @return   Vector with the final path populated
*/
Vector astar_create_path(float map[MAX_GRID][MAX_GRID], uint8_t *start, uint8_t *end, bool *success);

#endif /* ASTAR_H */