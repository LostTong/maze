#include "growing_tree_generator.h"

using namespace maze;

GrowingTreeGenerator::GrowingTreeGenerator(unsigned seed, unsigned width, unsigned height) : seed(seed), width(width), height(height)
{
	mt = new std::mt19937(seed);
	gen_maze = new Maze(width, height);
	set = new Set<Cell>();
}


GrowingTreeGenerator::~GrowingTreeGenerator()
{
	if (gen_maze != nullptr) {
		delete gen_maze;
	}
	if (set != nullptr) {
		delete set;
	}

}

Cell *GrowingTreeGenerator::get_next() {
	return nullptr;
}

void GrowingTreeGenerator::generate() {
	
}