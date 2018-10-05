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
#include "generator_factory.h"
#include "maze_routing.h"

using namespace maze;

int main(int argc, char * argv[])
{
	maze::ArgsParser parser;
	bool parse_enable = parser.parse(argc, argv);
	if (parse_enable == false) {
		std::cerr << "Parse Args Failed!" << std::endl;
		return 0;
	}
	
	maze::Maze *maze = nullptr;
	std::unique_ptr<GeneratorFactory> maze_generator;
	std::unique_ptr<BinaryProcessor> binary_processor;
	std::unique_ptr<SVGSave> svg_save;
	std::unique_ptr<MazeRouting> maze_routing;

	try{
		// generate maze
		if(parser.generate_maze_enable == true)
		{
			std::cout << "Start Generate Maze.\n";
			std::cout << "Seed: " << parser.generate_maze_seed << ". \n";
			std::cout << "Width: " << parser.generate_maze_width << ". \n";
			std::cout << "Height: " << parser.generate_maze_height << ". \n";

			maze_generator = std::unique_ptr<GeneratorFactory>(new GeneratorFactory(parser.generate_maze_type, parser.generate_maze_seed, parser.generate_maze_width, parser.generate_maze_height));
			maze = maze_generator->gen_maze;
		}
		// load binary file
		if(parser.load_binary_file != "")
		{
			std::cout << "Loading maze binary from: " << parser.load_binary_file << ". \n";
			binary_processor = std::unique_ptr<maze::BinaryProcessor>(new maze::BinaryProcessor(parser.load_binary_file));
			maze = binary_processor->generate_maze();
		}
		// save binary file
		if(parser.save_binary_file != "")
		{
			std::cout << "Saving Binary File: " << parser.save_binary_file << ". \n";
			if (maze == nullptr)
			{
				std::cout << "Load maze error" << ". \n";
				return 0;
			}
			if (binary_processor == nullptr) {
				binary_processor = std::unique_ptr<maze::BinaryProcessor>();
			}
			binary_processor->save_maze_file(maze);
		}
		// solve maze
		if (parser.solve_maze_enable) {
			maze_routing = std::unique_ptr<MazeRouting>(new MazeRouting(maze));
			maze_routing->path_finding();
		}
		// save svg file
		if(parser.save_svg_file != "")
		{
			std::cout << "Saving SVG File: " << parser.save_svg_file << ". \n";
			if (maze == nullptr)
			{
				std::cout << "Load maze error" << ". \n";
				return 0;
			}
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