#pragma once

#include "base_generator.h"

namespace maze {
	class RecursiveGenerator : public BaseGenerator
	{
	public:
		RecursiveGenerator(unsigned seed, unsigned width, unsigned height);
		~RecursiveGenerator();

		void generate();
	};

}


