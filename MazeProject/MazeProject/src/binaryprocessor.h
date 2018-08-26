#pragma once
#include "maze.h"
#include "mazeprocessor.h"
#include <memory>
#include <fstream>

namespace maze
{
	class BinaryProcessor : public MazeProcessor
	{
		std::string file_path;
		maze::Maze * maze;
	public:
		BinaryProcessor(maze::Maze * maze, std::string file_path)
		{
			this->maze = maze,
			this->file_path = file_path;
		}
		virtual std::unique_ptr<maze::Maze> generate_maze() override;
		virtual void save_maze_file() override;
		std::string determin_edge_out_of_bound(unsigned x1, unsigned y1, unsigned x2, unsigned y2);
	};
}