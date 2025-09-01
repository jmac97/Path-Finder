#include <stdlib.h>
#include "../inc/map.h"
#include <stdint.h>

// variables for mjson parsing
static int json_count;
static int map_count;
static int tile_count;

static double values[MAX_CELL_AMOUNT]; // t_reals are doubles

// structs for mjson parsing
static const struct json_attr_t canvas_attr[] = {
  {"width", t_ignore, NULL},
  {"height", t_ignore, NULL},
  {NULL},
};

static const struct json_attr_t tileset_attr[] = {
  {"name", t_ignore, NULL},
  {"image", t_ignore, NULL},
  {"imagewidth", t_ignore, NULL},
  {"imageheight", t_ignore, NULL},
  {"tilewidth", t_ignore, NULL},
  {"tileheight", t_ignore, NULL},
  {NULL},
};

static const struct json_attr_t map_attr[] = {
  {"name", t_ignore, NULL},
  {"tileset", t_ignore, NULL},
  {"data", t_array, .addr.array.element_type = t_real,
                    .addr.array.maxlen = 1024,
                    .addr.array.count = &map_count,
                    .addr.array.arr.reals = values},
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
bool map_extract(float map[32][32])
{
    char path[50];
    printf("enter path to json file: ");
    scanf("%s", path);

    FILE *fp = fopen(path, "r");

    if (fp == NULL)
    {
        printf("File does not exist or can't be opened.");
        return 0;
    }

    fseek(fp, 0, SEEK_END);
    long file_size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    char *buffer = (char *)malloc(file_size + 1);
    if (buffer == NULL) {
        printf("memory error");
        fclose(fp);
        return 0;
    }

    fread(buffer, 1, file_size, fp);
    fclose(fp);

    uint8_t status = json_read_object(buffer, json_attr, NULL);
    if (status != 0)
    {
        // print mjson error message
        printf("%s\n", json_error_string(status), json_count);
    }

    uint16_t value_index = 0;
    for (uint8_t y = 0; y < 32; y++)
    {
      for (uint8_t x = 0; x < 32; x++)
      {
        map[y][x] = values[value_index];

        // remove anything that's not expected terrain 
        if (map[y][x] != -1.0f)
        {
            if (map[y][x] != 3.0f)
            {
                map[y][x] = -1.0f;
            }
        }

        value_index++;
      }
    }

    return 1;
}

/*
* @brief Gets the start and end positions from user
*/
void map_get_positions(float map[32][32], uint8_t start[2], uint8_t end[2])
{
    printf("x coordinate for start: ");
    scanf("%d", &start[0]);
    if (start[0] >= MAX_GRID)
    {
        start[0] = MAX_GRID - 1;
    }

    printf("y coordinate for start: ");
    scanf("%d", &start[1]);
    if (start[1] >= MAX_GRID)
    {
        start[1] = MAX_GRID - 1;
    }

    printf("x coordinate for end: ");
    scanf("%d", &end[0]);
    if (end[0] >= MAX_GRID)
    {
        end[0] = MAX_GRID - 1;
    }

    printf("y coordinate for end: ");
    scanf("%d", &end[1]);
    if (end[1] >= MAX_GRID)
    {
        end[1] = MAX_GRID - 1;
    }

    map[start[1]][start[0]] = 8.1f;
    map[end[1]][end[0]] = 0.5f;
}

/*
* @brief Prints out formatted map in console
*/
bool map_print(float map[32][32])
{
    printf("\n");

    for (uint16_t y = 0; y < MAX_GRID; y++)
    {
      for (uint8_t x = 0; x < MAX_GRID; x++)
      {
        float square = map[y][x];
        if (square == 3)
        {
          printf("\033[48;5;94m%1s \033[m", "#");
        }
        else if (square == -1.0f)
        {
          printf("\033[48;5;34m%1s \33[m", "-");
        }
        else if (square == 0.5f)
        {
          printf("\033[38;5;200m%1s \033[m", "Z");
        }
        else if (square == 8.1f)
        {
          printf("\033[38;5;200m%1s \033[m", "A");
        }
        else if (square == 5.0f)
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