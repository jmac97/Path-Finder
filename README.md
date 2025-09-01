# Path Finder
Getting a guy from one place to another.

Takes in a JSON file based on [Risky Lab outputs](https://riskylab.com/tilemap/#), a start position, and an end postion to implement A* in the terminal.

## Example
### Normal Run
![Image](/outputs/example-half1.png)
![Image](/outputs/example-half2.png)

From Github Link:
![Image](/outputs/example-half12.png)
![Image](/outputs/example-half22.png)

### Enclosed Run
![Image](/outputs/example-enclosed.png)

## Build Info
### Use Instructions
Use Risky Labs to make compatible maps: https://riskylab.com/tilemap/#
    * Maps can only be 32x32
    * Only accept -1 (nothing) and 3 (mountain)

1. Build:
    * use make or:
    * gcc main.c mjson.c map.c vector.c astar.c -o pathfinder
2. run pathfinder.exe
3. follow command line instructions
### Structure
#### Map
Use the functions here to extract and display the map.

##### Extracting maps from a JSON
```C 
/*
* @brief Gets the grid values from a JSON file
* 
* @parm[in] map         A 32x32 array, extracted values placed here
*/
void map_extract(float map[MAX_GRID][MAX_GRID])
```
##### Getting user start and end positions
```C
/*
* @brief Gets the start and end positions from user
* 
* @param[in] map        A 32x32 array, positions placed here
* @param[in] start      Array of values for start x,y position
* @param[in] end        Array of values for end x,y position
*/
void map_get_positions(float map[MAX_GRID][MAX_GRID], uint8_t start[2], uint8_t end[2]);
```
##### Printing the map
```C
/*
* @brief Prints out formatted map in console
* 
* @parm[in] map         A 32x32 array of map
*/
void map_print(float map[MAX_GRID][MAX_GRID]);
```
#### Vector
Used in the A* implementation. Has typical init, append, pop, and free functions. Here vector is a dynamic array of Cells:
```C
struct Vector
{
    Cell **array;
    size_t used;
    size_t size;
}__attribute__((packed));
```
#### A*
Cells are defined as:
```C
struct Cell
{
  uint8_t x;
  uint8_t y;
  float f;
  float g;
  float h;
  Cell *parent;
}__attribute__((packed));
```
A* function that returns the found path:
```C
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
```

## Requirements
1. Create a path for the "battle unit" from starting position to end position.
    * Output a list of positions the unit must traverse. 
2. Start and end positions are user defined or randomly chosen.
3. Map input is a JSON file.
    *  Size is 32x32 cells.
    * "-1" is un-occupied ground terrain. 
    * "3" is elevated terrain (units cannot traverse because they are lazy, or aren't elves).

        ![legolas onsnow](https://i.pinimg.com/originals/06/82/a3/0682a3b258b58172465ef852b13142c0.gif)
    * "8.3" is the battle unit starting position. 
    * "0.5" is the end position.
4. Units move in discrete, single steps.
    * No partial positions. 
    * Can only move left/right and up/down on the map. No diagonal movements.
### Optional
5. Handle multiple units moving simultaneously.
    * Units can move toward the same or different target.
    * Ground terrain can only be occupied by one unit at a time.


## JSON Parsing
* I looked at the C librarys listed here: https://www.json.org/json-en.html
* I wanted to find something small, easy to port, and easy to use.
* I started using jsmn:
    * Small, simple, portable
    * Doesn't require me to do anything to install, just add .h file
    * Found it ok to use, it was slightly annoying to extract data
* I next on my "to try" list was mjson: 
    * Meets all my ~~desires~~ requirements
    * Puts data into structs and arrays, making it easier to parse through and handle data

## Pathfinding Algorithms
* Read up on three common algorithms: Breadth First Search, Dijkstra’s Algorithm, and A*
* A* seemed best of the three for this as it has a combination of their strengths (shortest path + heuristics)
    * Will use Manhattan distance since units can only go up/down and left/right
* Need at least dynamic arrays to store and sort Cells
    * Here is when I start regretting not quiuckly brushing up on C++ so I can use its built-in data structures (priority queues, vectors, etc)
 