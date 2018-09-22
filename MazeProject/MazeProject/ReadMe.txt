Maze readme

---------------------------------------------------------


### Description
This program will be able to generate mazes given a seed and height and width.
You may save them into binary or SVG format. Binary files can be loaded into
the program so that it may be converted into an SVG.


### Installation
Go to the directory of these source files and call
    'make'

To remove the compiled files, simply call
    'make clean'



### Usage

#### Flags
###### --g seed width height
Input the random seed ,width and height to generate the maze.

###### --lb binary_file
Load a binary file that represents a maze.

###### --sb binary_file
Saves a maze to a binary file

###### --sv svg_file
Saves a maze to a SVG

##### Examples

./maze --g 1314 20 30 --sb output_binary.maze   (generate binary maze file with seed:1314, width:20, height:30 and output binary_file:output_binary.maze)

./maze --lb output_binary.maze --sv output.svg   (load binary file and output to SVG)

./maze --g 22 5 10 --sv output_svg.svg    (generate SVG maze file with seed:22, width:5, height:10 and ouput svg file:output_svg.svg)




