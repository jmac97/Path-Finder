# Path-Finder
Getting a guy from one place to another

## Build Info
### Use Instructions
### Structure

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
    * Hits all the requiurements
    * Puts data into structs and arrays, making it easier to parse through and handle data

## Pathfinding Algorithms