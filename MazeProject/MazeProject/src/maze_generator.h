#pragma once

#include "maze.h"
#include <string>
#include <stack>
#include <random>

namespace maze
{

	class Cell;
	class Maze;
	class Path;

	class MazeGenerator
	{
		public:
			MazeGenerator(unsigned seed, unsigned width, unsigned height): seed(seed), width(width), height(height){};
			void generate();
			bool depth_search(std::mt19937 &mt, std::vector< std::vector<bool> > &visited_cells);
			void build_solve_path(Maze *maze);

			void BinaryLoad(std::string file_path) {};
			void BinarySave(maze::Maze & maze, std::string file_path) {};
			void SvgSave() {};

		public:
			unsigned seed, width, height;
			std::stack<Cell *> unvisited_cells;
			std::vector<Path *> solve_paths;
			std::vector< std::vector<bool> > visited_cells;
			Maze *gen_maze;
	};
}
