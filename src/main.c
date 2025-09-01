#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "../inc/map.h"
#include "../inc/astar.h"
#include "../inc/vector.h"


int main(void)
{
    static float grid_values[MAX_GRID][MAX_GRID];
    static uint8_t start[2];
    static uint8_t end[2];
    static bool path_made = false;

    map_extract(grid_values);
    map_get_positions(grid_values, start, end);
    map_print(grid_values);

    printf("\n\n\n");

    Vector print = astar_create_path(grid_values, start, end, &path_made);

    if (path_made)
    {
        for (uint32_t i = 1; i < print.used-1; i++)
        {
            grid_values[print.array[i]->y][print.array[i]->x] = PATH;
        }

        printf("Path coordinates: \n");
        uint32_t count = 0;
        for (uint32_t i = print.used-2; i > 0; i--)
        {
            printf("[%d, %d], ", print.array[i]->x, print.array[i]->y);
            count++;
            if (count % 10 == 0)
            {
                printf("\n");
            }
        }

        map_print(grid_values);
    }

    vector_free(&print);

    return 0;
}