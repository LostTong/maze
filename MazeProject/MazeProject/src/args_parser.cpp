#include "args_parser.h"

#include <iostream>

namespace maze {
	ArgsParser::ArgsParser()
	{
	}


	ArgsParser::~ArgsParser()
	{
	}

	void ArgsParser::init() {
		load_binary_file = "";
		save_binary_file = "";
		save_svg_file = "";

		generate_maze_enable = false;
		solve_maze_enable = false;
		generate_maze_seed = 0;
		generate_maze_width = 0;
		generate_maze_height = 0;
	}

	bool ArgsParser::parse(int argc, char * argv[]) {
		// init
		this->init();
		std::string program_name = argv[0];

		/* parse */
		for (int i = 1; i < argc; i++) {
			std::string cur_arg = argv[i];
			std::string next_arg = "";
			if (i + 1 < argc) {
				next_arg = argv[i + 1];
			}
			// load binary file
			if (cur_arg == load_binary_flag) {
				if (next_arg == "") {
					std::cerr << "Load Binary File: parameters invalid." << std::endl;
					return false;
				}
				else {
					load_binary_file = next_arg;
					i++;
				}
			}
			// save binary file
			else if (cur_arg == save_binary_flag) {
				if (next_arg == "") {
					std::cerr << "Save Binary File: parameters invalid." << std::endl;
					return false;
				}
				else {
					save_binary_file = next_arg;
					i++;
				}
			}
			// save svg file
			else if (cur_arg == save_svg_flag) {
				if (next_arg == "") {
					std::cerr << "Save Binary File: parameters invalid." << std::endl;
					return false;
				}
				else {
					save_svg_file = next_arg;
					i++;
				}
			}
			// generate maze
			else if (cur_arg == generate_maze_prim || cur_arg == generate_maze_recursive) {
				if (next_arg == "") {
					std::cerr << "Save Binary File: parameters invalid." << std::endl;
					return false;
				}
				else {
					// seed, width, height
					if (i + 3 < argc) {
						try {
							generate_maze_enable = true;
							generate_maze_seed = (unsigned)std::stol(next_arg);
							generate_maze_width = (unsigned)std::stol(argv[i + 2]);
							generate_maze_height = (unsigned)std::stol(argv[i + 3]);
							i += 3;
							if (cur_arg == generate_maze_prim) {
								generate_maze_type = "P";
							}
							else {
								generate_maze_type = "R";
							}
						}
						catch (const char* msg) {
							std::cerr << "Save Binary File: parameters invalid with msg:" << msg << std::endl;
							return false;
						}
					}
					else {
						std::cerr << "Save Binary File: parameters invalid." << std::endl;
						return false;
					}

				}
			}
			// solve maze
			else if(cur_arg == solve_maze) {
				solve_maze_enable = true;
			}
			// invalid args
			else {
				std::cerr << "Invalid args." << std::endl;
				return false;
			}
		}

		/* verify */ 
		// save svg without load binary/generate maze
		if (save_svg_file != "" && (load_binary_file == "" && generate_maze_enable == false)) {
			std::cerr << "Save SVG File Without Load Binary or Generate Maze." << std::endl;
			return false;
		}
		// save binary without generate maze
		if (save_binary_file != "" && (load_binary_file == "" && generate_maze_enable == false)) {
			std::cerr << "Save Binary File Without Load Binary or Generate Maze." << std::endl;
			return false;
		}
		return true;

	}
}
