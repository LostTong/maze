#pragma once

#include "maze.h"
#include <fstream>
#include <string>
#include <memory>
#include <iostream>

namespace maze
{
	class SVGSave
	{
		public:
			SVGSave(maze::Maze & maze, std::string file_path) : maze(&maze), file_path(file_path) {};
			void save_svg_file();
			std::unique_ptr<maze::Maze> generate_maze(){ return nullptr; };
			void save_path(maze::Path &pathway, unsigned offset, std::fstream & output);
			
		public:
			maze::Maze *maze;
			std::string file_path;
			const int cell_size = 20;
			const int wall_width = (int)(0.1 * 20);
			const int path_width = 20 - 2 * wall_width;
			const std::string path_color = "rgb(255,255,255)";
			const std::string solved_path_color = "rgb(255,0,0)";
	};
}
