#include "base_generator.h"

using namespace maze;

BaseGenerator::BaseGenerator(unsigned seed, unsigned width, unsigned height) : seed(seed), width(width), height(height)
{
	mt = new std::mt19937(seed);
	gen_maze = new Maze(width, height);
}


BaseGenerator::~BaseGenerator()
{
	if (gen_maze != nullptr) {
		delete gen_maze;
	}

}

