#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <string>
#include <stdexcept>
#include <climits>
#include <memory>


#include "maze.h"
#include "mazegeneratorprocessor.h"
//#include "binaryload.h"
#include "depthfirstsearchsolver.h"
//#include "binarysave.h"
#include "binaryprocessor.h"
#include "svgprocessor.h"
#include "args_parser.h"
#include "maze_generator.h"

const std::string GENERATE_RECURSIVE_FLAG = "--gr";

const std::string LOAD_BIN_FLAG = "--lb";	

const std::string SOLVE_DEPTH_FIRST_FLAG = "--pd";
const std::string SOLVE_BREATH_FIRST_FLAG = "--pb";
const std::string SOLVE_A_STAR_FLAG = "--pa";

const std::string SAVE_BIN_FLAG = "--sb"; 
const std::string SAVE_SVG_FLAG = "--sv"; 

int main(int argc, char * argv[])
{
	
	maze::ArgsParser parser;
	bool parse_enable = parser.parse(argc, argv);
	if (parse_enable == false) {
		std::cerr << "Parse Args Failed!" << std::endl;
		return 0;
	}
	
	std::unique_ptr<maze::Maze> maze;
	std::unique_ptr<maze::MazeGenerator> generator;
	//std::unique_ptr<maze::MazeProcessor> persistence_strategy;

	try{
		//maze = factory->generate_maze();

		// generate maze
		if(parser.generate_maze_enable == true)
		{
			std::cout << "Start Generate Maze.\n";
			std::cout << "Seed: " << parser.generate_maze_seed << ". \n";
			std::cout << "Width: " << parser.generate_maze_width << ". \n";
			std::cout << "Height: " << parser.generate_maze_height << ". \n";

			generator = std::unique_ptr<maze::MazeGenerator>(new maze::MazeGenerator(parser.generate_maze_seed, parser.generate_maze_width, parser.generate_maze_height));
			generator->generate();
		}
		// load binary file
		if(parser.load_binary_file != "")
		{
			std::cout << "Loading maze binary from: " << parser.load_binary_file << ". \n";
			generator = std::unique_ptr<maze::MazeGenerator>(new maze::MazeGenerator(parser.generate_maze_seed, parser.generate_maze_width, parser.generate_maze_height));
			generator->generate();
		}
		// save binary file
		if(parser.save_binary_file != "")
		{
			std::cout << "Saving Binary File: " << parser.save_binary_file << ". \n";

			//persistence_strategy = std::unique_ptr<maze::PersistenceStrategy>(new maze::BinarySave(*maze.get(),save_path));
			//persistence_strategy = std::unique_ptr<maze::MazeProcessor>(new maze::BinaryProcessor(maze.get(), save_path));
			//persistence_strategy->BinarySave(*maze.get(), save_path);
		}
		// save svg file
		else if(parser.save_svg_file != "")
		{
			std::cout << "Saving SVG Fiel: " << parser.save_svg_file << ". \n";

			//persistence_strategy = std::unique_ptr<maze::PersistenceStrategy>(new maze::SVGSave(*maze.get(),save_path));
			//persistence_strategy = std::unique_ptr<maze::MazeProcessor>(new maze::SVGSave(*maze.get(), save_path));
		}


       
		//persistence_strategy->save_maze_file();
		std::cout << "Save Finish!" << std::endl;
        

		
	}
	catch (std::runtime_error e)
	{
		std::cerr << e.what() << "\n";
	}
	
}