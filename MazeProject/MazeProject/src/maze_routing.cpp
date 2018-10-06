#include "maze_routing.h"

#include <queue>
#include <chrono>

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
	auto start = std::chrono::system_clock::now();
	solve_path2();
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> total_time = end - start;
	std::cout << "Maze Routing Total Time:" << total_time.count() << std::endl;

	build_path();

	return;

	has_solve_path = solve_path(maze->get_entry_cell(), maze->get_exit_cell());
	if (!has_solve_path) {
		std::cout << "Maze has no solve path!" << std::endl;
	}
}

void MazeRouting::solve_path2() {
	Cell *entry_cell = maze->get_entry_cell();
	Cell *exit_cell = maze->get_exit_cell();
	std::queue<Cell *> que;
	que.push(entry_cell);
	entry_cell->is_visited = true;
	std::vector<Cell *> cell_vec;
	while (!que.empty()) {
		Cell *cur_cell = que.front();
		que.pop();
		// up, left, down, right
		cell_vec.clear();
		int x_pos = cur_cell->get_x_position();
		int y_pos = cur_cell->get_y_position();
		cell_vec.push_back(maze->get_cell(x_pos, y_pos - 1));
		cell_vec.push_back(maze->get_cell(x_pos - 1, y_pos));
		cell_vec.push_back(maze->get_cell(x_pos, y_pos + 1));
		cell_vec.push_back(maze->get_cell(x_pos + 1, y_pos));
		for (auto *cell : cell_vec) {
			if (cell != nullptr && !cell->is_visited && cur_cell->is_connect_cell(cell)) {
				cell->prev_cell = cur_cell;
				if (cell == exit_cell) {
					has_solve_path = true;
					break;
				}
				que.push(cell);
				cell->is_visited = true;
			}
		}
	}
}

void MazeRouting::build_path() {
	if (!has_solve_path) {
		return;
	}
	Cell *entry_cell = maze->get_entry_cell();
	Cell *exit_cell = maze->get_exit_cell();
	Cell *prev_cell = nullptr;
	Cell *cur_cell = exit_cell;
	while (true) {
		prev_cell = cur_cell->prev_cell;
		for (auto *path : *(cur_cell->get_paths())) {
			if (path->start_cell == prev_cell) {
				path->is_exit_path = true;
				break;
			}
		}
		cur_cell = prev_cell;
		if (cur_cell == entry_cell) {
			return;
		}
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
				for (auto *path : *(maze->paths)) {
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