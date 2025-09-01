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

Vector astar_create_path(float map[MAX_GRID][MAX_GRID], uint8_t *start, uint8_t *end, bool *success);

#endif /* ASTAR_H */