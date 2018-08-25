#pragma once

#include "maze.h"
#include <stdexcept>
#include <string>
#include <memory>
#include <iostream>

namespace maze
{
	class MazeFactory
	{
		public:
			virtual std::unique_ptr<maze::Maze> make_maze() = 0;
			virtual void persist_maze() = 0;
			MazeFactory() {};
			~MazeFactory() {};

			void OuputLog(const char * tip_string)
			{
				std::cout << tip_string << std::endl;
			}
	};
}
