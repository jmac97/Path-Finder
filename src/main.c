#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "../inc/map.h"
#include "../inc/astar.h"
#include "../inc/vector.h"

static float grid_values[MAX_GRID][MAX_GRID];
static uint8_t start[2];
static uint8_t end[2];


int main(int argc, char *argv[])
{
    map_extract(grid_values);
    map_get_positions(grid_values, start, end);
    map_print(grid_values);

    printf("\n\n\n");

    Vector print = astar_create_path(grid_values, start, end);
    for (uint32_t i = 1; i < print.used-1; i++)
    {
        if (grid_values[print.array[i]->y][print.array[i]->x] == MOUNTAIN)
        {
            printf("You messed up\n\n");
        }
        else
        {
            grid_values[print.array[i]->y][print.array[i]->x] = PATH;
        }
    }

    map_print(grid_values);

    vector_free(&print);

    return 0;
}