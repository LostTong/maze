#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <string>
#include <stdexcept>
#include <climits>
#include <memory>


#include "maze.h"
#include "depthfirstsearchsolver.h"
#include "binaryprocessor.h"
#include "svg_save.h"
#include "args_parser.h"
#include "maze_generator.h"

int main(int argc, char * argv[])
{
	maze::ArgsParser parser;
	bool parse_enable = parser.parse(argc, argv);
	if (parse_enable == false) {
		std::cerr << "Parse Args Failed!" << std::endl;
		return 0;
	}
	
	maze::Maze *maze = nullptr;
	std::unique_ptr<maze::MazeGenerator> generator;
	std::unique_ptr<maze::SVGSave> svg_save;

	try{
		// generate maze
		if(parser.generate_maze_enable == true)
		{
			std::cout << "Start Generate Maze.\n";
			std::cout << "Seed: " << parser.generate_maze_seed << ". \n";
			std::cout << "Width: " << parser.generate_maze_width << ". \n";
			std::cout << "Height: " << parser.generate_maze_height << ". \n";

			generator = std::unique_ptr<maze::MazeGenerator>(new maze::MazeGenerator(parser.generate_maze_seed, parser.generate_maze_width, parser.generate_maze_height));
			generator->generate();
			maze = generator->gen_maze;
		}
		// load binary file
		if(parser.load_binary_file != "")
		{
			std::cout << "Loading maze binary from: " << parser.load_binary_file << ". \n";
			generator = std::unique_ptr<maze::MazeGenerator>(new maze::MazeGenerator());
			generator->BinaryLoad(parser.load_binary_file);
		}
		// save binary file
		if(parser.save_binary_file != "")
		{
			std::cout << "Saving Binary File: " << parser.save_binary_file << ". \n";
			if (generator == nullptr)
			{
				std::cout << "Load maze error" << ". \n";
				return 0;
			}
			generator->BinarySave(parser.save_binary_file);
		}
		// save svg file
		if(parser.save_svg_file != "")
		{
			std::cout << "Saving SVG File: " << parser.save_svg_file << ". \n";
			if (generator == nullptr || generator->gen_maze == nullptr)
			{
				std::cout << "Load maze error" << ". \n";
				return 0;
			}
			maze = generator->gen_maze;		
			svg_save = std::unique_ptr<maze::SVGSave>(new maze::SVGSave(*maze, parser.save_svg_file));
			svg_save->save_svg_file();
		}

		std::cout << "Save Finish!" << std::endl;
	}
	catch (std::runtime_error e)
	{
		std::cerr << e.what() << "\n";
	}
	
}