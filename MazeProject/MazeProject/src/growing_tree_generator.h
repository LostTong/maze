#pragma once

#include <random>
#include <algorithm>
#include <string>
#include <stack>

#include "maze.h"
#include "set.h"
#include "cell.h"

using namespace maze;

class GrowingTreeGenerator
{
public:
	GrowingTreeGenerator() {};
	GrowingTreeGenerator(unsigned seed, unsigned width, unsigned height);
	virtual ~GrowingTreeGenerator();

	virtual Cell *get_next();
	void generate();

public:
	unsigned seed, width, height;
	maze::Maze *gen_maze;
	std::mt19937 *mt;
	Set<Cell> *set;
};



