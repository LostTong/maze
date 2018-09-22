#pragma once

#include <stack>
#include <unordered_set>

#include "maze.h"
#include "base_generator.h"

namespace maze
{
	class PrimGenerator : public BaseGenerator
	{
		public:
			PrimGenerator(unsigned seed, unsigned width, unsigned height);
            ~PrimGenerator();
		
			void generate();
	};
}
