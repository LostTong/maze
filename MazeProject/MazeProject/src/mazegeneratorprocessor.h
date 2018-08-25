#pragma once

#include "maze.h"
#include "mazeprocessor.h"
#include <string>
#include <stack>
#include <random>

namespace maze
{
	class DepthFirstSearchGenerator : public MazeProcessor
	{
		unsigned height, width, seed;

		public:
			DepthFirstSearchGenerator(unsigned height_, unsigned width_, unsigned seed_):
				height(height_), width(width_), seed(seed_) {};
			virtual std::unique_ptr<maze::Maze> generate_maze() override;
			void save_maze_file() {};
	};
}
