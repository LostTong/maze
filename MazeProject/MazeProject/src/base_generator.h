#pragma once

#include <random>
#include <algorithm>
#include <string>
#include <stack>

#include "maze.h"

namespace maze {
	class BaseGenerator
	{
	public:
		BaseGenerator() {};
		BaseGenerator(unsigned seed, unsigned width, unsigned height);
		virtual ~BaseGenerator();

		virtual void generate() = 0;

	public:
		unsigned seed, width, height;
		maze::Maze *gen_maze;
		std::mt19937 *mt;
	};
}



