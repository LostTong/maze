#pragma once

#include "maze.h"
#include <stdexcept>
#include <string>
#include <memory>
#include <iostream>

namespace maze
{
	class MazeProcessor
	{
		public:
			//virtual std::unique_ptr<maze::Maze> generate_maze() = 0;
			//virtual void save_maze_file() = 0;
			MazeProcessor() {};
			~MazeProcessor() {};

			void OuputLog(const char * tip_string)
			{
				std::cout << tip_string << std::endl;
			}
	};
}
