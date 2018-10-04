#include "prim_generator.h"

using namespace maze;

PrimGenerator::PrimGenerator(unsigned seed, unsigned width, unsigned height) : GrowingTreeGenerator(seed, width, height)
{
   
}


PrimGenerator::~PrimGenerator() {

}

Cell *PrimGenerator::get_next() {
	int random_idx = (*mt)() % set->get_size();
	return set->get_value(random_idx);
}