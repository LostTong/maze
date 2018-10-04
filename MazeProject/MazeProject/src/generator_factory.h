#pragma once

#include <string.h>

#include "prim_generator.h"
#include "recursive_generator.h"

class GeneratorFactory {
public:
	GeneratorFactory() {};
	~GeneratorFactory() {};
	
	void do_generate(const std::string generate_type, int seed, int width, int height) {
		if (generate_type == "P") {
			PrimGenerator generator(seed, width, height);
			generator.generate();
		}
		else if (generate_type == "R") {
			RecursiveGenerator generator(seed, width, height);
			generator.generate();
		}
	}
};