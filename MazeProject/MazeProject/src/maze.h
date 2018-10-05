#pragma once

#include "cell.h"
#include "path.h"
#include <vector>
#include <stdexcept>


namespace maze
{
	

	class Maze
	{

		public:
			Maze();
			Maze(int width, int height);
			~Maze();

			Cell *get_cell(unsigned x_pos, unsigned y_pos);
			void add_path(Cell *start_cell, Cell *end_cell);

			inline std::vector<Path *> *get_paths() { return &paths; };
			inline std::vector<std::vector<Cell *>> * get_cells() { return &cells; };
			Cell *get_entry_cell() { return get_cell(0, 0); }
			Cell *get_exit_cell() { return get_cell(width - 1, height - 1); }

		public:
			std::vector< std::vector< maze::Cell *> > cells;
			std::vector<Path *> paths;
			std::vector<Path *> *solved_paths;
			int width, height;
			int maze_size;
	};
}
