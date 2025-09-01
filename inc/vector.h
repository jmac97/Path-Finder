#ifndef VECTOR_H
#define VECTOR_H

#include <stdint.h>
#include <stdlib.h>
#include "astar.h"


typedef struct Cell Cell;
typedef struct Vector Vector;
struct Vector
{
    Cell **array;
    size_t used;
    size_t size;
}__attribute__((packed));


/*
* @brief Initialize the vector
* 
* @parm[in] vec         Pointer to the vector to be initialized 
* @parm[in] size        Size 
*/
void vector_init(Vector *vec, size_t size);

/*
* @brief Append value to vector
* 
* @parm[in] vec         Pointer to the vector to be appended
* @parm[in] item        Valueu to be appended
*/
void vector_append(Vector *vec, Cell *item);

/*
* @brief Pop value from vector
* 
* @parm[in] vec         Pointer to the vector
* @parm[in] index       Location of value in vector to be popped
*/
Cell *vector_pop(Vector *vec, uint32_t index);

/*
* @brief Free the vector memory
* 
* @parm[in] vec         Pointer to the vector to be freed
*/
void vector_free(Vector *vec);

#endif /* VECTOR_H */