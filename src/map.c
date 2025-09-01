#include <stdlib.h>
#include "../inc/map.h"
#include <stdint.h>
#include <string.h>

// variables for mjson parsing
static int json_count;
static int map_count;
static int tile_count;

static double values[MAX_CELL_AMOUNT]; // t_reals are doubles

// structs for mjson parsing
static const struct json_attr_t canvas_attr[] = 
{
    {"width", t_ignore, .dflt = {0}},
    {"height", t_ignore, .dflt = {0}},
    {NULL},
};

static const struct json_attr_t tileset_attr[] = 
{
    {"name", t_ignore, .dflt = {0}},
    {"image", t_ignore, .dflt = {0}},
    {"imagewidth", t_ignore, .dflt = {0}},
    {"imageheight", t_ignore, .dflt = {0}},
    {"tilewidth", t_ignore, .dflt = {0}},
    {"tileheight", t_ignore, .dflt = {0}},
    {NULL},
};

static const struct json_attr_t map_attr[] = 
{
    {"name", t_ignore, .dflt = {0}},
    {"tileset", t_ignore, .dflt = {0}},
    {"data", t_array, .addr.array.element_type = t_real,
                    .addr.array.maxlen = 1024,
                    .addr.array.count = &map_count,
                    .addr.array.arr.reals = {values}},
  {NULL},
};

static const struct json_attr_t json_attr[] = 
{
    {"layers", t_array, .addr.array.element_type = t_object,
                        .addr.array.arr.objects.subtype = map_attr,
                        .addr.array.maxlen = 10000,
                        .addr.array.count = &json_count},
    {"tilesets", t_array, .addr.array.element_type = t_object,
                        .addr.array.arr.objects.subtype = tileset_attr,
                        .addr.array.maxlen = 1000,
                        .addr.array.count = &tile_count},
    {"canvas", t_object, .addr.attrs = canvas_attr},
    {NULL},
};


/*
* @brief Gets the grid values from a JSON file
*/
void map_extract(float map[MAX_GRID][MAX_GRID])
{
    char path[50];
    printf("enter path to json file: ");
    scanf("%s", path);

    FILE *fp = fopen(path, "r");

    if (fp == NULL)
    {
        printf("File does not exist or can't be opened.");
        exit(EXIT_FAILURE);
    }

    fseek(fp, 0, SEEK_END);
    long file_size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    char *buffer = (char *)malloc(file_size + 1);
    if (buffer == NULL) {
        printf("memory error");
        fclose(fp);
        exit(EXIT_FAILURE);
    }

    fread(buffer, 1, file_size, fp);
    fclose(fp);

    uint8_t status = json_read_object(buffer, json_attr, NULL);
    if (status != 0)
    {
        // print mjson error message
        printf("%s\n", json_error_string(status));
    }

    uint16_t value_index = 0;
    for (uint8_t y = 0; y < 32; y++)
    {
      for (uint8_t x = 0; x < 32; x++)
      {
        map[y][x] = values[value_index];

        // remove anything that's not expected terrain 
        if (map[y][x] != FLAT_GROUND)
        {
            if (map[y][x] != MOUNTAIN)
            {
                map[y][x] = FLAT_GROUND;
            }
        }

        value_index++;
      }
    }
}

/*
* @brief Gets the start and end positions from user
*/
void map_get_positions(float map[MAX_GRID][MAX_GRID], uint8_t start[2], uint8_t end[2])
{
    int temp;
    printf("x coordinate for start: ");
    scanf("%d", &temp);
    if (temp >= MAX_GRID)
    {
        temp = MAX_GRID - 1;
    }
    else if (temp < 0)
    {
        temp = 0;
    }
    start[0] = temp;

    printf("y coordinate for start: ");
    scanf("%d", &temp);
    if (temp >= MAX_GRID)
    {
        temp = MAX_GRID - 1;
    }
    else if (temp < 0)
    {
        temp = 0;
    }
    start[1] = temp;

    printf("x coordinate for end: ");
    scanf("%d", &temp);
    if (temp >= MAX_GRID)
    {
        temp = MAX_GRID - 1;
    }
    else if (temp < 0)
    {
        temp = 0;
    }
    end[0] = temp;

    printf("y coordinate for end: ");
    scanf("%d", &temp);
    if (temp >= MAX_GRID)
    {
        temp = MAX_GRID - 1;
    }
    else if (temp < 0)
    {
        temp = 0;
    }
    end[1] = temp;

    if (!memcmp(start, end, 2))
    {
        printf("Positions can't match. Using default values [0,0] and [31,31] for start and end");
        start[0] = 0;
        start[1] = 0;
        end[0] = 31;
        end[0] = 31;
    }

    map[start[1]][start[0]] = START;
    map[end[1]][end[0]] = END;
}

/*
* @brief Prints out formatted map in console
*/
void map_print(float map[32][32])
{
    printf("\n");

    for (uint16_t y = 0; y < MAX_GRID; y++)
    {
        for (uint8_t x = 0; x < MAX_GRID; x++)
        {
            float square = map[y][x];
            if (square == MOUNTAIN)
            {
                printf("\033[48;5;94m%1s \033[m", "#");
            }
            else if (square == FLAT_GROUND)
            {
                printf("\033[48;5;34m%1s \33[m", "-");
            }
            else if (square == END)
            {
                printf("\033[38;5;200m%1s \033[m", "Z");
            }
            else if (square == START)
            {
                printf("\033[38;5;200m%1s \033[m", "A");
            }
            else if (square == PATH)
            {
                printf("\033[41m%1s \033[m", "*");
            }
            else
            {
                // other values already removed, shouldn't execute
                printf("\n\nUnknown value in map: %.1f [%d, %d]\n\n", map[y][x], x, y);
            }
        }

        printf("\n");
    }

    printf("\n\n\n");
}