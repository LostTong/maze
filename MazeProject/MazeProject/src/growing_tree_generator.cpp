#include "growing_tree_generator.h"

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
			if (cell != nullptr && !set->contain(cell)) {
				unvisited_cells.push_back(cell);
			}
		}
		if (unvisited_cells.empty()) {
			set->remove(cur_cell);
			continue;
		}
		// unvisited cells
		int random_idx = (*mt)() % unvisited_cells.size();
		Cell *next_cell = unvisited_cells[random_idx];
		gen_maze->add_path(cur_cell, next_cell);
		set->add(next_cell);
	}
}