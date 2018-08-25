#pragma once

#include "maze.h"
#include <string>
#include <stack>
#include <random>

namespace maze
{

	class Cell;

	class MazeGenerator
	{
		public:
			MazeGenerator(unsigned seed, unsigned width, unsigned height): seed(seed), width(width), height(height){};
			std::unique_ptr<maze::Maze> generate();
			bool depth_search(Cell *cell);

			void BinaryLoad(std::string file_path) {};
			void BinarySave(maze::Maze & maze, std::string file_path) {};
			void SvgSave() {};

		public:
			unsigned seed, width, height;
			std::vector<Cell *> visited_cells;
			std::vector<Cell *> unvisited_cells;
			std::stack<Cell *> search_cell_stack;
	};
}
