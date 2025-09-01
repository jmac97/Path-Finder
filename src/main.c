#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "../inc/map.h"

static float grid_values[32][32];
static uint8_t start[2];
static uint8_t end[2];


// ~Path finding algo~ - what are the options out there
// Print map with path to traverse

int main(int argc, char *argv[])
{
    map_extract(grid_values);
    map_get_positions(grid_values, start, end);
    map_print(grid_values);

    return 0;
}