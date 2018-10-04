#pragma once

#include "growing_tree_generator.h"

namespace maze {
	class RecursiveGenerator : public GrowingTreeGenerator
	{
	public:
		RecursiveGenerator(unsigned seed, unsigned width, unsigned height);
		~RecursiveGenerator();

		Cell *get_next();
	};

}


