#include "maze_generator.h"
#include "cell.h"
#include "path.h"

#include <unordered_set>
#include <iostream>
#include <fstream>

namespace maze
{
	void MazeGenerator::generate()
	{
		// init
		std::mt19937 mt(seed);

		gen_maze = new Maze(width, height);
		visited_cells = std::vector< std::vector<bool> >(width + 1, std::vector<bool>(height + 1, false));
		unvisited_cells.push(gen_maze->get_entry_cell());
		
		bool is_solve = depth_search(mt, gen_maze->get_entry_cell(), visited_cells);
		if (is_solve) {
			build_solve_path(gen_maze);
		}
		return;
		//get_paths(mt);
		build_solve_path(gen_maze);
		if (solve_paths[0]->start_cell == gen_maze->get_entry_cell()) {
			std::cout << "Has Solve Path" << std::endl;
		}
		else {
			std::cout << "Donot Has Solve Path" << std::endl;

		}
		return;
	}

	void MazeGenerator::get_paths(std::mt19937 &mt) {
		std::stack<maze::Cell *> path_stack;
		maze::Cell * cur_cell = nullptr, *next_cell = nullptr;
		unsigned long total_cell_cnt = height * width;
		unsigned long visited_cell_cnt = 0;

		/* Starting at top left */
		path_stack.push(gen_maze->get_cell(0, 0));
		visited_cell_cnt++;

		while (visited_cell_cnt < total_cell_cnt)
		{
			cur_cell = path_stack.top();
			unsigned current_y_pos = cur_cell->get_y_position();
			unsigned current_x_pos = cur_cell->get_x_position();

			/* Get unvisited neighbouring cells */
			std::vector<maze::Cell *> unvisited_cells;

			unsigned x_pos = cur_cell->get_x_position();
			unsigned y_pos = cur_cell->get_y_position();
			std::vector<Cell *> cell_vec;
			cell_vec.push_back(gen_maze->get_cell(x_pos, y_pos - 1));
			cell_vec.push_back(gen_maze->get_cell(x_pos, y_pos + 1));
			cell_vec.push_back(gen_maze->get_cell(x_pos - 1, y_pos));
			cell_vec.push_back(gen_maze->get_cell(x_pos + 1, y_pos));
			for (auto *cell : cell_vec) {
				if (cell != nullptr && !cell->has_path()) {
					unvisited_cells.push_back(cell);
				}
			}
			// no unvisited cells
			if (unvisited_cells.empty())
			{
				/* No more unvisited */
				path_stack.pop();
				continue;
			}

			// add unvisited cells by mt::19937
			unsigned random_index = mt() % unvisited_cells.size();
			next_cell = unvisited_cells[random_index];
			next_cell->prev_cell = cur_cell;
			gen_maze->add_path(cur_cell, next_cell);
			path_stack.push(next_cell);
			visited_cell_cnt++;
			cur_cell = nullptr;
		}
	}

	bool MazeGenerator::depth_search(std::mt19937 &mt, maze::Cell *start_cell, std::vector< std::vector<bool> > &visited_cells) {
		// exit cell
		if (visited_cells.size() == gen_maze->maze_size) {
			return true;
		}
		else if(start_cell == nullptr) {
			return false;
		}
		// save visited flag
		visited_cells[start_cell->get_x_position()][start_cell->get_y_position()] = true;
		int x1 = start_cell->get_x_position();
		int y1 = start_cell->get_y_position();
		/* up, down, left, right */
		unsigned x_pos = start_cell->get_x_position();
		unsigned y_pos = start_cell->get_y_position();
		Cell *cell_up = gen_maze->get_cell(x_pos, y_pos - 1);
		Cell *cell_down = gen_maze->get_cell(x_pos, y_pos + 1);
		Cell *cell_left = gen_maze->get_cell(x_pos - 1, y_pos);
		Cell *cell_right = gen_maze->get_cell(x_pos + 1, y_pos);
		std::vector<Cell *> cell_vec;
		cell_vec.push_back(cell_up);
		cell_vec.push_back(cell_down);
		cell_vec.push_back(cell_left);
		cell_vec.push_back(cell_right);

		while (cell_vec.size() > 0) {
			unsigned random_index = mt() % cell_vec.size();
			maze::Cell *cell = cell_vec[random_index];
			if (cell != nullptr && visited_cells[cell->get_x_position()][cell->get_y_position()] == false) {
				gen_maze->add_path(start_cell, cell);
				cell->prev_cell = start_cell;
				if (depth_search(mt, cell, visited_cells)) {
					return true;
				}
			}
			cell_vec.erase(cell_vec.begin() + random_index);
		}
		return false;
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
			std::vector<Path *> *paths = maze->get_paths();
			for (Path *path : *paths) {
				if (path->start_cell == prev_cell && path->end_cell == curr_cell) {
					solve_paths.push_back(path);
					path->is_exit_path = true;
				}
			}
			curr_cell = prev_cell;
		}
		std::reverse(solve_paths.begin(), solve_paths.end());
		
		std::ofstream outpath(outpath_file);
		if (outpath.is_open()) {
			for (Path *path : solve_paths) {
				Cell *start_cell = path->start_cell;
				Cell *end_cell = path->end_cell;
				int x1 = start_cell->get_x_position();
				int y1 = start_cell->get_y_position();
				int x2 = end_cell->get_x_position();
				int y2 = end_cell->get_y_position();
				outpath << "(" << x1 << ", " << y1 << ")" << " - > (" << x2 << ", " << y2 << ")" << std::endl;
			}
		}
		outpath.close();
		return;
	}
}

