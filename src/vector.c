#include <stdio.h>
#include "../inc/vector.h"



/*
* @brief Initialize the vector
*/
void vector_init(Vector *vec, size_t size)
{
  vec->array = malloc(size * sizeof(Cell*));
  vec->used = 0;
  vec->size = size;
}


/*
* @brief Append value to vector
*/
void vector_append(Vector *vec, Cell *item)
{
  if (vec->used == vec->size)
  {
    vec->size *= 2;
    vec->array = realloc(vec->array, vec->size * sizeof(Cell*));
  }

  vec->array[vec->used] = item;
  vec->used++;
}


/*
* @brief Pop value from vector
*/
Cell *vector_pop(Vector *vec, uint32_t index) 
{
    if (index < 0 || index >= vec->used) 
    {
        printf("Index %ld out of range\n", index);
        exit(EXIT_FAILURE);
    }

    Cell *pop = vec->array[index];

    for (uint32_t i = index; i < vec->used - 1; i++) 
    {
        vec->array[i] = vec->array[i + 1];
    }

    vec->used--;

    return pop;
}


/*
* @brief Free the vector memory
*/
void vector_free(Vector *vec)
{
  free(vec->array);
  vec->array = NULL;
  vec->used = vec->size = 0;
}