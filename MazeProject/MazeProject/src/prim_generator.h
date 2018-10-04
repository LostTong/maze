#pragma once

#include <stack>
#include <unordered_set>

#include "maze.h"
#include "growing_tree_generator.h"

namespace maze
{
	class PrimGenerator : public GrowingTreeGenerator
	{
		public:
			PrimGenerator(unsigned seed, unsigned width, unsigned height);
            ~PrimGenerator();
		
			Cell *get_next();
	};
}
