#include "maze_routing.h"

using namespace maze;

MazeRouting::MazeRouting(maze::Maze *maze) {
	this->maze = maze;
	has_solve_path = false;
}

MazeRouting::~MazeRouting() {
	for (auto *path : solved_paths) {
		if (path != nullptr) {
			delete path;
			path = nullptr;
		}
	}
}

void MazeRouting::path_finding() {
	has_solve_path = solve_path(maze->get_entry_cell(), maze->get_exit_cell());
	if (!has_solve_path) {
		std::cout << "Maze has no solve path!" << std::endl;
	}
}

bool MazeRouting::solve_path(Cell *cur_cell, Cell *exit_cell) {
	if (cur_cell == nullptr) {
		return false;
	}
	// exit cell
	if (cur_cell == exit_cell) {
		solved_paths.push_back(new Path(cur_cell, exit_cell));
		return true;
	}
	// up, left, down, right
	int x_pos = cur_cell->get_x_position();
	int y_pos = cur_cell->get_y_position();
	std::vector<Cell *> cell_vec;
	cell_vec.push_back(maze->get_cell(x_pos, y_pos - 1));
	cell_vec.push_back(maze->get_cell(x_pos - 1, y_pos));
	cell_vec.push_back(maze->get_cell(x_pos, y_pos + 1));
	cell_vec.push_back(maze->get_cell(x_pos + 1, y_pos));
	// set visited
	cur_cell->is_visited = true;
	for (auto *cell : cell_vec) {
		if (cell != nullptr && !cell->is_visited) {
			if (solve_path(cell, exit_cell)) {
				for (auto *path : maze->paths) {
					if (path->start_cell == cur_cell && path->end_cell == cell) {
						path->is_exit_path = true;
						break;
					}
				}
				solved_paths.push_back(new Path(cur_cell, exit_cell));
				return true;
			}
		}
	}
	return false;
}