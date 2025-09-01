#include <math.h>
#include "../inc/astar.h"
#include "../inc/vector.h"

#define PRINT_DEBUG 0

enum Location 
{
    LEFT,
    RIGHT,
    UP,
    DOWN
};


static void astar_get_child(uint8_t loc, Vector *vec, Cell *current)
{
    Cell *child = malloc(sizeof(Cell));
    switch(loc)
    {
        case LEFT:
            child->x = current->x - 1;
            child->y = current->y;
            child->parent = current;
            child->f = child->g = child->h = 0;

            vector_append(vec, child);
            break;

        case RIGHT:
            child->x = current->x + 1;
            child->y = current->y;
            child->parent = current;
            child->f = child->g = child->h = 0;

            vector_append(vec, child);
            break;

        case UP:
            child->x = current->x;
            child->y = current->y + 1;
            child->parent = current;
            child->f = child->g = child->h = 0;

            vector_append(vec, child);
            break;

        case DOWN:
            child->x = current->x;
            child->y = current->y - 1;
            child->parent = current;
            child->f = child->g = child->h = 0;

            vector_append(vec, child);
            break;
    }
}


static void astar_populate_children(Cell *current, Vector *vec, float map[MAX_GRID][MAX_GRID])
{
    if (current->y > 0 && map[current->y-1][current->x] != MOUNTAIN)
    {
        astar_get_child(DOWN, vec, current);
    }

    if (current->y < MAX_GRID-1 && map[current->y+1][current->x] != MOUNTAIN)
    {
        astar_get_child(UP, vec, current);
    }

    if (current->x > 0 && map[current->y][current->x-1] != MOUNTAIN)
    {
        astar_get_child(LEFT, vec, current);
    }

    if (current->x < MAX_GRID-1 && map[current->y][current->x+1] != MOUNTAIN)
    {
       astar_get_child(RIGHT, vec, current);
    }
}

/*
* @brief Create a path from start to end position using A* 
*/
Vector astar_create_path(float map[MAX_GRID][MAX_GRID], uint8_t *start, uint8_t *end, bool *success)
{
#if PRINT_DEBUG
    printf("Creating start node at [%d, %d]\n", start[0], start[1]);
#endif 
    // Create the start node cell
    Cell *start_node = malloc(sizeof(Cell));
    start_node->x = start[0];
    start_node->y = start[1];
    start_node->parent = NULL;
    start_node->f = start_node->g = start_node->h = 0;

#if PRINT_DEBUG
    printf("Creating end node at [%d, %d]\n", end[0], end[1]);
#endif
    // Create the end node cell
    Cell *end_node = malloc(sizeof(Cell));
    end_node->x = end[0];
    end_node->y = end[1];
    end_node->parent = NULL;
    end_node->f = end_node->g = end_node->h = 0;

    // Create the open and closed lists
    Vector open_list;
    Vector closed_list;
    vector_init(&open_list, START_SIZE);
    vector_init(&closed_list, START_SIZE);

    // Add the start node to the open list
    vector_append(&open_list, start_node);

#if PRINT_DEBUG
    printf("Starting search\n");
#endif
    while (open_list.used > 0)  // Keep searching through until end is found or nothing in list
    {
        Cell *current_node = open_list.array[0];
        uint32_t current_index = 0;

        // Search through open list to determine current node
        // Current node will have the lowest F cost
        for (uint32_t i = 0; i < open_list.used; i++)
        {
            // Ignore nodes that are mountains
            if ((open_list.array[i]->f < current_node->f) && (map[open_list.array[i]->y][open_list.array[i]->x] != MOUNTAIN))
            {
#if PRINT_DEBUG
                printf("Current node found at [%d, %d] with f score of %f\n", open_list.array[i]->x, open_list.array[i]->y, open_list.array[i]->f);
#endif
                current_node = open_list.array[i];
                current_index = i;
            }
        }

    // Put it in the closed list
    vector_pop(&open_list, current_index);
    vector_append(&closed_list, current_node);


    // Check if we're at the end position
    if ((current_node->x == end_node->x) && (current_node->y == end_node->y))
    {
#if PRINT_DEBUG
        printf("Found the end node at [%d, %d]\n", end_node->x, end_node->y);
#endif
        Vector path;
        vector_init(&path, 25);

        Cell *current_ptr = current_node;
        
        while (current_ptr != NULL)
        {
            static uint8_t count = 0;
#if PRINT_DEBUG
            printf("%d Adding path [%d, %d]\n", count, current_ptr->x, current_ptr->y);
#endif
            vector_append(&path, current_ptr);
            current_ptr = current_ptr->parent;

            count++;
        }
#if PRINT_DEBUG
        printf("Path made\n");
#endif
        free(start_node);
        free(end_node);
        vector_free(&open_list);
        vector_free(&closed_list);
        *success = 1;
        return path;
    }

    // Get the current cell's children
    Vector children;
    vector_init(&children, 4);
    astar_populate_children(current_node, &children, map);

    // Check all the children...
    for (uint8_t i = 0; i < children.used; i++)
    {
        uint8_t on_closed = 0;
        uint8_t on_open = 0;

        for (uint32_t j = 0; j < closed_list.used; j++)
        {
            // See if child is on the closed list. If so ignore
            if ((children.array[i]->x == closed_list.array[j]->x) && (children.array[i]->y == closed_list.array[j]->y))
            {
#if PRINT_DEBUG
                printf("Found child on [%d, %d] with parent [%d, %d] closed list\n", children.array[i]->x,children.array[i]->y, children.array[i]->parent->x, children.array[i]->parent->y);
#endif
                on_closed = 1;
                break;
            }
        }

        if (!on_closed)
        {
            // Calculate f,g,h
            int dx = children.array[i]->x - end_node->x;
            int dy = children.array[i]->y - end_node->y;

            children.array[i]->g = current_node->g + 1;
            children.array[i]->h = fabsf(dx) + fabsf(dy);
            children.array[i]->f = children.array[i]->g + children.array[i]->h;

            // Check if child is on the open list
            for (uint32_t j = 0; j < open_list.used; j++)
            {
                if ((children.array[i]->x == open_list.array[j]->x) && (children.array[i]->y == open_list.array[j]->y))
                {
#if PRINT_DEBUG
                    printf("Found child [%d, %d] on open list\n", children.array[i]->x, children.array[i]->y);
#endif
                    on_open = 1;
                    // If it's on the open list and has a better g score, swap it and recalculate
                    if (children.array[i]->g < open_list.array[j]->g)
                    {
#if PRINT_DEBUG
                        printf("G score better on child\n");
#endif
                        open_list.array[j]->parent = children.array[i]->parent;
                        open_list.array[j]->g = children.array[i]->g;
                        open_list.array[j]->f = open_list.array[j]->g + open_list.array[j]->h;
                    }
                }
            }

            // If it's not on the open list, add it 
            if (!on_open)
            {
#if PRINT_DEBUG
                printf("Not on open list, adding child [%d, %d]\n", children.array[i]->x, children.array[i]->y);
#endif
                vector_append(&open_list, children.array[i]);
            }
        }
    }
    
    vector_free(&children);
  }

    printf("Path cannot be made.");
    free(start_node);
    free(end_node);
    vector_free(&open_list);
    vector_free(&closed_list);
    
    Vector empty;
    vector_init(&empty, 0);
    *success = 0;
    return empty;
}