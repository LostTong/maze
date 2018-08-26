#pragma once

#include "maze.h"
#include "binaryprocessor.h"
#include <string>
#include <stack>
#include <random>
#include <memory>
#include <algorithm>

namespace maze
{

	class Cell;
	class Maze;
	class Path;

	class MazeGenerator
	{
		public:
			MazeGenerator(): gen_maze(nullptr) {};
			MazeGenerator(unsigned seed, unsigned width, unsigned height): seed(seed), width(width), height(height), gen_maze(nullptr){};
			void generate();
			void get_paths(std::mt19937 &mt);
			bool depth_search(std::mt19937 &mt, std::vector< std::vector<bool> > &visited_cells);
			void build_solve_path(Maze *maze);

			void BinaryLoad(std::string file_path) {
				binary_processor.file_path = file_path;
				gen_maze = binary_processor.generate_maze();
			};
			void BinarySave(std::string file_path) {
				binary_processor.file_path = file_path;
				binary_processor.maze = gen_maze;
				binary_processor.save_maze_file();
			};
			void SvgSave() {};

		public:
			unsigned seed, width, height;
			std::stack<Cell *> unvisited_cells;
			std::vector<Path *> solve_paths;
			std::vector< std::vector<bool> > visited_cells;
			Maze *gen_maze;
			const std::string outpath_file = "output_path.txt";
			BinaryProcessor binary_processor;
	};
}
