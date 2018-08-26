#include "maze_generator.h"
#include "cell.h"
#include "path.h"

#include <unordered_set>
#include <iostream>

namespace maze
{
	void MazeGenerator::generate()
	{
		// init
    	//Maze *maze = new Maze(width, height);
		std::mt19937 mt(seed);

		gen_maze = new Maze(width, height);
		/*
		for (int i = 0; i < width; i++) {
			for (int j = 0; j < height; j++) {
				if i > 09
			}
		}*/

		visited_cells = std::vector< std::vector<bool> > (width + 1, std::vector<bool>(height + 1, false));
		unvisited_cells.push(gen_maze->get_entry_cell());
		bool is_solve = depth_search(mt, visited_cells);
		if (is_solve) {
			build_solve_path(gen_maze);
		}
		return;
	}

	bool MazeGenerator::depth_search(std::mt19937 &mt, std::vector< std::vector<bool> > &visited_cells) {
		// search cell stack
		if (unvisited_cells.empty()) {
			return false;
		}
		// new start cell
		Cell *start_cell = unvisited_cells.top();
		//std::unordered_set< Cell*> visited_cells = *(std::unordered_set< Cell*> *)visited_cells_ptr;
		visited_cells[start_cell->get_x_position()][start_cell->get_y_position()] = true;
		unvisited_cells.pop();
		int x1 = start_cell->get_x_position();
		int y1 = start_cell->get_y_position();
		// is exit cell
		if (start_cell == gen_maze->get_exit_cell()) {
			return true;
		}
		/* up, down, left, right */
		unsigned x_pos = start_cell->get_x_position();
		unsigned y_pos = start_cell->get_y_position();
		Cell *cell_up = gen_maze->get_cell(x_pos, y_pos - 1);
		Cell *cell_down = gen_maze->get_cell(x_pos, y_pos + 1);
		Cell *cell_left = gen_maze->get_cell(x_pos - 1, y_pos);
		Cell *cell_right = gen_maze->get_cell(x_pos + 1, y_pos);
		std::vector<Cell *> cell_vec;
		cell_vec.push_back(gen_maze->get_cell(x_pos, y_pos - 1));
		cell_vec.push_back(gen_maze->get_cell(x_pos, y_pos + 1));
		cell_vec.push_back(gen_maze->get_cell(x_pos - 1, y_pos));
		cell_vec.push_back(gen_maze->get_cell(x_pos + 1, y_pos));
		// add unvisited cells by mt::19937
		while (true) {
			if (cell_vec.empty()) {
				break;
			}
			int idx = mt() % (cell_vec.size());
			Cell *cell = cell_vec[idx];
			if (cell != nullptr && visited_cells[cell->get_x_position()][cell->get_y_position()] == false) {
				unvisited_cells.push(cell);
				cell->prev_cell = start_cell;
				int x2 = cell->get_x_position();
				int y2 = cell->get_y_position();
				std::cout << "(" << x1 << ", " << y1 << ")" << " - > (" << x2 << ", " << y2 << ")" << std::endl;
			}
			cell_vec.erase(cell_vec.begin() + idx);
		}
		return depth_search( mt, visited_cells);
	}

	void MazeGenerator::build_solve_path(Maze *maze) {
		std::cout << "build_solve_path" << std::endl;
		solve_paths.clear();
		Cell *curr_cell = maze->get_exit_cell();
		while (true) {
			Cell *prev_cell = curr_cell->prev_cell;
			if (prev_cell == nullptr) {
				break;
			}
			Path *path = new Path(prev_cell, curr_cell);
			solve_paths.push_back(path);
			curr_cell = prev_cell;
		}
		std::reverse(solve_paths.begin(), solve_paths.end());
		for (Path *path : solve_paths) {
			Cell *start_cell = path->start_cell;
			Cell *end_cell = path->end_cell;
			int x1 = start_cell->get_x_position();
			int y1 = start_cell->get_y_position();
			int x2 = end_cell->get_x_position();
			int y2 = end_cell->get_y_position();
			std::cout << "(" << x1 << ", " << y1 << ")" << " - > (" << x2 << ", " << y2 << ")" << std::endl;
		}
		return;
	}
}

