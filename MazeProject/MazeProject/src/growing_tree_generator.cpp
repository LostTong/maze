#include "growing_tree_generator.h"

#include <chrono>

using namespace maze;

GrowingTreeGenerator::GrowingTreeGenerator(unsigned seed, unsigned width, unsigned height) : seed(seed), width(width), height(height)
{
	mt = new std::mt19937(seed);
	gen_maze = new Maze(width, height);
}


GrowingTreeGenerator::~GrowingTreeGenerator()
{
}

Cell *GrowingTreeGenerator::get_next() {
	return nullptr;
}

void GrowingTreeGenerator::generate() {
	auto start = std::chrono::system_clock::now();
	// set
	set = new Set<Cell>();
	// add entry cell
	set->add(gen_maze->get_entry_cell());
	// do generate
	while (set->get_size() > 0) {
		// get next cell
		Cell *cur_cell = get_next();
		// up, down, left, right: get unvisited neighboring cells
		int x_pos = cur_cell->get_x_position();
		int y_pos = cur_cell->get_y_position();
		std::vector<Cell *> cell_vec;
		cell_vec.push_back(gen_maze->get_cell(x_pos, y_pos - 1));
		cell_vec.push_back(gen_maze->get_cell(x_pos, y_pos + 1));
		cell_vec.push_back(gen_maze->get_cell(x_pos - 1, y_pos));
		cell_vec.push_back(gen_maze->get_cell(x_pos + 1, y_pos));
		std::vector<maze::Cell *> unvisited_cells;
		for (auto *cell : cell_vec) {
			if (cell != nullptr && !cell->has_path()) {
				unvisited_cells.push_back(cell);
			}
		}
		if (unvisited_cells.empty()) {
			//std::cout << "remove cell:" << cur_cell->get_x_position() << ", " << cur_cell->get_y_position()  << ", set_size: " << set->get_size() << std::endl;
			set->remove(cur_cell);
			continue;
		}
		// unvisited cells
		int random_idx = (*mt)() % unvisited_cells.size();
		Cell *next_cell = unvisited_cells[random_idx];
		gen_maze->add_path(cur_cell, next_cell);
		set->add(next_cell);
		//std::cout << "next_cell:" << next_cell->get_x_position() << ", " << next_cell->get_y_position() << std::endl;

	}
	
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> total_time = end - start;
	std::cout << "Maze Routing Total Time:" << total_time.count() << std::endl;
}