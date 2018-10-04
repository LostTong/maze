#include "recursive_generator.h"

using namespace maze;

RecursiveGenerator::RecursiveGenerator(unsigned seed, unsigned width, unsigned height) : GrowingTreeGenerator(seed, width, height)
{

}

RecursiveGenerator::~RecursiveGenerator()
{
}

Cell *RecursiveGenerator::get_next() {
	return set->pop();
}

