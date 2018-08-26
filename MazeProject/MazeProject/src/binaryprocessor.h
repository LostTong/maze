#pragma once
#include "maze.h"
#include "mazeprocessor.h"
#include <memory>
#include <fstream>

namespace maze
{
	class BinaryProcessor : public MazeProcessor
	{
		
	public:
		std::string file_path;
		maze::Maze * maze;
		BinaryProcessor() {};
		BinaryProcessor(maze::Maze * maze, std::string file_path)
		{
			this->maze = maze,
			this->file_path = file_path;
		}
		maze::Maze* generate_maze();
		void save_maze_file();
		std::string determin_edge_out_of_bound(unsigned x1, unsigned y1, unsigned x2, unsigned y2);
	};
}