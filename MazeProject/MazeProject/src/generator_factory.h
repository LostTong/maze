#pragma once

#include <string.h>

#include "prim_generator.h"
#include "recursive_generator.h"
#include "maze.h"

class GeneratorFactory {
public:
	GeneratorFactory(const std::string generate_type, int seed, int width, int height) {
		this->generate_type = generate_type;
		this->width = width;
		this->height = height;
		do_generate();
	};
	~GeneratorFactory() {};
	
	void do_generate() {
		if (generate_type == "P") {
			PrimGenerator generator(seed, width, height);
			generator.generate();
			gen_maze = generator.gen_maze;
		}
		else if (generate_type == "R") {
			RecursiveGenerator generator(seed, width, height);
			generator.generate();
			gen_maze = generator.gen_maze;
		}
	}

public:
	std::string generate_type;
	int seed, width, height;
	maze::Maze *gen_maze;
};