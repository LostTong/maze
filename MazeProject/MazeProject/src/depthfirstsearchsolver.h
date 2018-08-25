#pragma once


#include "maze.h"
#include <stack>
#include <unordered_set>

namespace maze
{
	class DepthFirstSearchSolver
	{
        maze::Maze * maze;

		public:
			void solve_maze();
            DepthFirstSearchSolver(maze::Maze & maze);
            ~DepthFirstSearchSolver() {};
	};
}
